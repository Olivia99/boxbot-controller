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

void loop() {
  if (receiver.decode(&results)) {
    Serial.println(results.value, HEX);

    if (results.value == 0x8CB44) {
      forward();
      Serial.println("FORWARD");
    } else if (results.value == 0xCB44) {
      Serial.println("HALT");
      halt();
    } // add more "else if" conditions here for other buttons!
    else if (results.value == 0x5EB44) {
      Serial.println("REVERS");
      reverse();
    }

    receiver.resume();
  }

}
