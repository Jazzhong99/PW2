#include <motordriver_4wd.h>
#include <motordriver_4wd_dfs.h>
unsigned long interval = 3;
unsigned long int currentTime = 0;
unsigned long int timeCount = 0;
int irRight = 3;   //Initialize their pins number, connected using digital wire
int irLeft  = 11;
int ir3 = 12;
int irValueR = 0;  //Everything starts from LOW / 0
int irValueL = 0;
int irValue3 = 0;
int encoder = 2;  //At pin number 2
int current = LOW;  //currently is OFF = LOW / 0
int previous = LOW;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  MOTOR.init(); //initializing motor
  Serial.begin(9600); //setting Baud rate
  pinMode(irRight, INPUT);  //Their function
  pinMode(irLeft, INPUT);
  pinMode(ir3, INPUT);
  pinMode(encoder, INPUT);  //Encoder act as an input, it reads something can send it out to the car
}

void loop() {
  // put your main code here, to run repeatedly:
  current = digitalRead(encoder);  //Read everything and from the IR sensors
  irValueR = digitalRead(irRight);
  irValueL = digitalRead(irLeft);
  irValue3 = digitalRead(ir3);
  if (irValueL == LOW && irValue3 == LOW && irValueR == LOW) {  //Start to use if/else statement, let robot car to function
    //stop at finishing line, a black horizontal tape, BLACK = Absorb = 0, when 0, everything OFF
    MOTOR.setSpeedDir1(0, DIRF);
    MOTOR.setSpeedDir2(0, DIRF);

  }

  else if (irValueL == HIGH && irValue3 == LOW && irValueR == HIGH) {  //Middle line is black, hence = 0
    //go straight
    MOTOR.setSpeedDir1(25, DIRF);  //speed, DIRection Forward
    MOTOR.setSpeedDir2(25, DIRF);
  }


  else if (irValueL == HIGH && irValue3 == LOW && irValueR == LOW) {
    //turn right 90 degrees
    MOTOR.setSpeedDir1(50, DIRR); //right
    MOTOR.setSpeedDir2(50, DIRF); //left
  }

  else if (irValueL == LOW && irValue3 == LOW && irValueR == HIGH) {   // <<<<<BLACK BLACK | WHITE>>>
    //turning left 90 degrees
    MOTOR.setSpeedDir1(50, DIRF);  //Let o = tyre , Motor one moves Forward [Motor two<-(L)o  o(R)->Motor one]
    MOTOR.setSpeedDir2(50, DIRR);  //Moving backward (Reverse) so can slow down the car and let the car to read the black line more effectively
  }

  else if (irValueL == HIGH && irValue3 == HIGH && irValueR == LOW) {
    //turning right
    MOTOR.setSpeedDir1(12, DIRR);
    MOTOR.setSpeedDir2(30, DIRF);  //Motor two need to be higher speed, and also same concept, motor one forward, motor two backward, the speed is different
    //due to the motor, so we need to adjust it
  }

  else if (irValueL == LOW && irValue3 == HIGH && irValueR == HIGH) {
    //turning left
    MOTOR.setSpeedDir1(30, DIRF);
    MOTOR.setSpeedDir2(12, DIRR);
  }  //Above are overall all about the IR Sensors read the line
  if (current == HIGH && previous == LOW)  //This function is to let the count to read something, currently now turn ON, when turned ON, count started to count
  { //Hence, count adding, keep on increasing in the loop
    count ++;
    Serial.print("Count(Left)");  //Print out the count read by the left encoder only, just only a print function , below is to print out the count read by the encoder
    Serial.println(count);  //We here use serial print at the same time send into the LCD shield code, so that there is an input coming in
  }
  previous = current;  //Prevent the loop to stop, so when its outside the if statement, it will comes to this function, hence, the things inside if loop is keep
  //on running
}
