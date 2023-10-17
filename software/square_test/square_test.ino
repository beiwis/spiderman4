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
int UltrasonicEcho = 3;// Replace with the actual pin number for your ultrasonic sensor
int obstacle_distance = 10; // You can adjust this distance as needed

// Define states for the robot
enum RobotState {
  MOVE_FORWARD,
  MOVE_RIGHT,
  MOVE_BACKWARD,
  MOVE_LEFT,
  STOP
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
  pinMode(UltrasonicTrig, OUTPUT);  
  // Set the ultrasonic sensor pin as INPUT
  pinMode(UltrasonicEcho, INPUT);
}

int checkUtrasonic(){
  long duration;
  int distance;
  int timeout = 38; //ms
  
  // Clears the trigPin
  digitalWrite(UltrasonicTrig, LOW);
  delay(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(UltrasonicTrig, HIGH);
  delay(10);
  digitalWrite(UltrasonicTrig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(UltrasonicEcho, HIGH);
  // Calculating the distance in cm's
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  duration = pulseIn(UltrasonicEcho, HIGH, timeout)
}
void moveForward() {
  //Code to move forward
  
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
  analogWrite(ena, 100);
  analogWrite(enB, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void loop() {
  // Get ultrasonic measurement
  int distance = digitalRead(Ultrasonic); 
  
  switch (currentState) {
    case MOVE_FORWARD:
      if (distance < obstacle_distance) {
        StopMotors();
        delay(5000);
      } 
      else if (i>5){
        StopMotors();
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
        StopMotors();
        delay(5000);
      } 
      else if (i>5){
        StopMotors();
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
        StopMotors();
        delay(5000);
      } 
      else if (i>5){
        StopMotors();
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
        StopMotors();
        delay(5000);
      } 
      else if (i>5){
        StopMotors();
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
