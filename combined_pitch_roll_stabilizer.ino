#include <Wire.h>
#include <MPU6050.h>
#include <ESP32Servo.h>

MPU6050 mpu;
Servo servoPitch;
Servo servoRoll;

// ---------------- Pins ----------------
#define SERVO_PITCH 18
#define SERVO_ROLL  19

// ---------------- MPU Variables (shared) ----------------
int16_t ax, ay, az;
int16_t gx, gy, gz;

float pitch = 0;
float roll  = 0;

unsigned long previousTime;

// Flat position references
const float pitchRef = 4.0;
const float rollRef  = 1.0;

void setup()
{
  Serial.begin(115200);

  Wire.begin(21, 22);
  delay(100);

  mpu.initialize();
  Serial.println("MPU6050 Initialized");

  servoPitch.attach(SERVO_PITCH);
  servoPitch.write(90);

  servoRoll.attach(SERVO_ROLL);
  servoRoll.write(90);

  delay(500);

  // Initial reading (shared for both pitch and roll init)
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  pitch = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / PI;
  roll  = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  previousTime = micros();
}

void loop()
{
  unsigned long currentTime = micros();
  float dt = (currentTime - previousTime) / 1000000.0;
  previousTime = currentTime;

  // Single shared sensor read per loop iteration
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // =========================================================
  // ======================  PITCH  =========================
  // =========================================================

  // Accelerometer angle
  float accelPitch = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / PI;

  // Gyroscope rate
  float gyroPitchRate = gx / 131.0;

  // Complementary Filter
  pitch = 0.98 * (pitch + gyroPitchRate * dt) + 0.02 * accelPitch;

  // Reference angle
  float pitchError = pitch - pitchRef;

  // ---------------- DEAD BAND ----------------
  if (abs(pitchError) < 1.0)
      pitchError = 0;

  // ---------------- ADAPTIVE GAIN ----------------
  float pitchGain;

  if (abs(pitchError) < 5)
      pitchGain = 0.6;      // Slow movement

  else if (abs(pitchError) < 15)
      pitchGain = 1.0;      // Medium speed

  else
      pitchGain = 1.5;      // Fast response

  // Desired Servo Position
  int targetServoPitch = constrain(90 + pitchGain * pitchError, 45, 135);

  // ---------------- SMOOTH SERVO ----------------
  static float servoPosPitch = 90;

  float speedPitch;

  if (abs(targetServoPitch - servoPosPitch) < 5)
      speedPitch = 0.15;

  else if (abs(targetServoPitch - servoPosPitch) < 20)
      speedPitch = 0.30;

  else
      speedPitch = 0.55;

  servoPosPitch += (targetServoPitch - servoPosPitch) * speedPitch;

  servoPitch.write((int)servoPosPitch);

  // =========================================================
  // =======================  ROLL  ==========================
  // =========================================================

  // Accelerometer Roll
  float accelRoll = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  // Gyroscope Roll Rate
  float gyroRollRate = gy / 131.0;

  // Complementary Filter
  roll = 0.98 * (roll + gyroRollRate * dt) + 0.02 * accelRoll;

  // Error from level
  float rollError = roll - rollRef;

  // ---------------- Deadband ----------------
  if (abs(rollError) < 7.0)
    rollError = 0;

  // ---------------- Adaptive Gain ----------------
  float rollGain;

  // Positive Roll (very gentle)
  if (rollError >= 0)
  {
      if (rollError < 5)
          rollGain = 0.15;
      else if (rollError < 15)
          rollGain = 0.30;
      else
          rollGain = 0.55;      // Even at +25°, servo moves gently
  }

  // Negative Roll (stronger)
  else
  {
      if (rollError > -5)
          rollGain = 0.50;
      else if (rollError > -15)
          rollGain = 1.20;
      else
          rollGain = 2.00;
  }

  int targetServoRoll = constrain(90 - rollGain * rollError, 30, 140);

  // ---------------- Smooth Servo ----------------
  static float servoPosRoll = 90;

  float speedRoll;

  if (abs(targetServoRoll - servoPosRoll) < 5)
      speedRoll = 0.25;
  else if (abs(targetServoRoll - servoPosRoll) < 20)
      speedRoll = 0.60;
  else
      speedRoll = 1.00;

  servoPosRoll += (targetServoRoll - servoPosRoll) * speedRoll;

  servoRoll.write((int)servoPosRoll);

  // =========================================================
  // ======================  SERIAL  =========================
  // =========================================================
  Serial.print("Pitch: ");
  Serial.print(pitch, 2);
  Serial.print("  PErr: ");
  Serial.print(pitchError, 2);
  Serial.print("  PTarget: ");
  Serial.print(targetServoPitch);
  Serial.print("  PServo: ");
  Serial.print((int)servoPosPitch);

  Serial.print("   ||   Roll: ");
  Serial.print(roll, 2);
  Serial.print("  RErr: ");
  Serial.print(rollError, 2);
  Serial.print("  RTarget: ");
  Serial.print(targetServoRoll);
  Serial.print("  RServo: ");
  Serial.println((int)servoPosRoll);

  delay(10);
}
