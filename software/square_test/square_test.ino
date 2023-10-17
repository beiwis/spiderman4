// Pin definitions
int FrontIn1 = 22; // Replace with the actual pin numbers for your setup
int FrontIn2 = 24;
int FrontIn3 = 26;
int FrontIn4 = 28;
int FrontENA = 9;
int FrontENB = 10;

int BackIn1 = 5;
int BackIn2 = 6;
int BackIn3 = 7;
int BackIn4 = 8;
int BackENA = 11;
int BackENB = 12;

int i = 0;
int UltrasonicTrig = 4;
int UltrasonicEcho = 3;
int obstacle_distance = 10; // You can adjust this distance as needed

// Define states for the robot
enum RobotState {
  MOVE_FORWARD,
  MOVE_RIGHT,
  MOVE_BACKWARD,
  MOVE_LEFT
};

RobotState currentState = MOVE_FORWARD;

void setup() {
  // Set the motor pins as OUTPUT
  pinMode(FrontIn1, OUTPUT);
  pinMode(FrontIn2, OUTPUT);
  pinMode(FrontIn3, OUTPUT);
  pinMode(FrontIn4, OUTPUT);
  pinMode(FrontENA, OUTPUT);
  pinMode(FrontENB, OUTPUT);
  pinMode(BackIn1, OUTPUT);
  pinMode(BackIn2, OUTPUT);
  pinMode(BackIn3, OUTPUT);
  pinMode(BackIn4, OUTPUT);
  pinMode(BackENA, OUTPUT);
  pinMode(BackENB, OUTPUT);
  // Set the Ultrasonic pins
  pinMode(UltrasonicTrig, OUTPUT);  
  pinMode(UltrasonicEcho, INPUT);
}

int checkUltrasonic(){
  unsigned long duration = 0;
  int distance = 0;
  int timeout = 38000; //us
  // Clears the trigger pin
  digitalWrite(UltrasonicTrig, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin on HIGH state for 10 micro seconds
  digitalWrite(UltrasonicTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltrasonicTrig, LOW);
  // Reads the echo pin, returns the sound wave travel time in microseconds
  duration = pulseIn(UltrasonicEcho, HIGH, timeout);
  // Calculating the distance in cm's
  distance = duration * 0.034 / 2;
  return distance;
}
void moveForward() {
  analogWrite(FrontENA, 100); //we should calibrate this value
  analogWrite(FrontENB, 100);
  digitalWrite(FrontIn1, HIGH); //and actuallY do this the right way cause im not sure at all about this
  digitalWrite(FrontIn2, LOW);
  digitalWrite(FrontIn3, HIGH);
  digitalWrite(FrontIn4, LOW);
  
}

void moveBackward() {
  // Code to move backward
}

void moveRight() {
  // Code to turn right
}

void moveLeft() {
  // Code to turn left
}

void stopMotors() {
  analogWrite(FrontENA, 0);
  analogWrite(FrontENB, 0);
  analogWrite(BackENA, 0);
  analogWrite(BackENB, 0); 
}

void loop() {
  // Get ultrasonic measurement
  int distance = checkUltrasonic(); 
  
  switch (currentState) {
    case MOVE_FORWARD:
      if (distance < obstacle_distance) {
        stopMotors();
        delay(5000);
      } 
      else if (i>5){
        stopMotors();
        currentState = MOVE_RIGHT;
        i = 0;
      }
      else {
         moveForward();
         delay(200);
         i+=1;      
      }
      break;

    case MOVE_RIGHT:
      if (distance < obstacle_distance) {
        stopMotors();
        delay(5000);
      } 
      else if (i>5){
        stopMotors();
        currentState = MOVE_BACKWARD;
        i = 0;
      }
      else {
         moveRight();
         delay(200);
         i+=1;      
      }
      break;

    case MOVE_BACKWARD:
      if (distance < obstacle_distance) {
        stopMotors();
        delay(5000);
      } 
      else if (i>5){
        stopMotors();
        currentState = MOVE_LEFT;
        i = 0;
      }
      else {
         moveBackward();
         delay(200);
         i+=1;      
      }
      break;

    case MOVE_LEFT:      
      if (distance < obstacle_distance) {
        stopMotors();
        delay(5000);
      } 
      else if (i>5){
        stopMotors();
        currentState = MOVE_FORWARD;
        i = 0;
        delay(3000);
      }
      else {
         moveLeft();
         delay(200);
         i+=1;      
      }
      break;
  }
}
