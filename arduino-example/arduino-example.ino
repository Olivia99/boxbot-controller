//#include <IRremote.h>

//int remoteInputPin = 3;
IRrecv receiver(remoteInputPin);
decode_results results;

int motorRightForward   = 9;
int motorRightReverse   = 10;
int motorLeftForward    = 11;
int motorLeftReverse    = 12;

void setup() {
  Serial.begin(9600);
  //receiver.enableIRIn();

  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightReverse, OUTPUT);
  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftReverse, OUTPUT);
}

void forward() {
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightReverse, LOW);
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftReverse, LOW);
}

void reverse() {
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightReverse, HIGH);
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftReverse, HIGH);
}
void halt() {
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightReverse, LOW);
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftReverse, LOW);
}

// add more control functions here!

// end of control functions
void serialEvent() {
  String input = Serial.readStringUntil('\n');
  input.trim();
 if (receiver.decode(&results)) {
    Serial.println(results.value, HEX);
  if (input == "forward") {
    Serial.println("FORWARD!");
    // go forward
        forward();
  } else if (input == "left") {
    // go left
   halt();
  } else if (input == "right") {
    // go right
    halt();
    
  } else if (input == "reverse") {
    // go back
   reverse();
  }
 }
}

