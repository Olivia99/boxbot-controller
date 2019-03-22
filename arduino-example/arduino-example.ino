#include <IRremote.h>

int remoteInputPin = 3;
IRrecv receiver(remoteInputPin);
decode_results results;

int motorRightForward   = 9;
int motorRightReverse   = 10;
int motorLeftForward    = 11;
int motorLeftReverse    = 12;

void setup() {
  Serial.begin(9600);
  receiver.enableIRIn();

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
  if (input == "0x8CB44") {
    Serial.println("FORWARD!");
    // go forward
        forward();
  } else if (input == "0xCB44") {
    // go left
   halt();
  } else if (input == "right") {
    // go right
    
  } else if (input == "backwards") {
    // go back
   reverse();
  }
 }
}


void loop() {
  if (receiver.decode(&results)) {
    Serial.println(results.value, HEX);

    if (results.value == "forward") {
      forward();
      Serial.println("FORWARD");
    } else if (results.value == "left") {
      Serial.println("HALT");
      halt();
    } // add more "else if" conditions here for other buttons!
    else if (results.value == "reverse") {
      Serial.println("REVERS");
      reverse();
    }

    receiver.resume();
  }

}
