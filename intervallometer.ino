// Intervallometer v0.1
// Andrea Paraggio (based on intervaluino by lord yo)
// Licensed under a Creative Commons (Attribution Non-Commercial Share-Alike) license

int shutter_on = 200;           // time to press shutter, set between 100 and 300
int shutter_wait = 5000;        // initial time to wait to begin sequence
int wakeup = 300;               // time to activate wakeup (focus)
int wakewait = 1000;            // time between wake and shutter

int switchPin = 2;              // input from switch from digital pin 2
int pot = 0;                    // input from potentiometer from analog pin 0
int shutterBtn = 11;            // output for shutter relay from pin 11
int focusBtn = 8;               // output for focus relay from digital pin 8
int focusLed = 3;               // output for focus relay from digital pin 3
int shutterLed = 4;             // output for focus relay from digital pin 4

int val;                        // value of button press
int buttonState;                // check variable for change of button press
int on_off = 0;                 // state of sequence (turned on, turned off)

float potentiometer;
long interval;


void setup() {
  Serial.begin(9600);
  Serial.println("Checking status...");
  delay(1000);
  pinMode(switchPin, INPUT);    // switchpin receives input
  Serial.println("Switch OK");
  delay(300);
  pinMode(pot, INPUT);
  Serial.println("Potentiometer OK");
  delay(300);
  pinMode(focusBtn, OUTPUT);
  digitalWrite(focusLed, HIGH);
  delay(1000);
  digitalWrite(focusLed, LOW);
  Serial.println("Focus button OK");
  pinMode(shutterBtn, OUTPUT);
  digitalWrite(shutterLed, HIGH);
  delay(1000);
  digitalWrite(shutterLed, LOW);
  Serial.println("Shutter OK");
  delay(300);
  
  buttonState = digitalRead(switchPin); //read value of the button
  Serial.println("Press the switch to start Timelapse");
}


void loop() {
  val = digitalRead(switchPin);      // read button value and store it in val
  //Serial.println(on_off);
  potentiometer = analogRead(pot);
  //Serial.println(potentiometer);
  interval = map(potentiometer,0.0,1023.0,0.0,30000.0);
  Serial.println(interval);
  
  if (val != buttonState) {          // if the button state has changed…
    if (val == LOW) {                // check if the button is pressed…
      if (on_off == 0) {             // if the sequence is currently off…
        on_off = 1;                    // turn the sequence on
        delay(shutter_wait);           // wait the initial period
      } else {
        on_off = 0;                  // turn the sequence off
      }
    }
  }

  buttonState = val;               //switch the button state

  if (on_off == 1) {                //while the sequence is turned on…
    digitalWrite(focusBtn, HIGH);   //turn wakeup/focus on
    Serial.println("Focus on");
    digitalWrite(focusLed, HIGH);
    delay(wakeup);                 //keep focus
    //digitalWrite(wakepin, LOW);    //turn wakeup off
    delay(wakewait);               //wait
    digitalWrite(shutterBtn, HIGH);    //press the shutter
    digitalWrite(shutterLed, HIGH);
    Serial.println("Shot");
    delay(shutter_on);    //wait the shutter release time
    digitalWrite(shutterBtn, LOW);     //release shutter
    digitalWrite(shutterLed, LOW);
    digitalWrite(focusBtn, LOW);     //release shutter
    digitalWrite(focusLed, LOW);
    Serial.println("...");
    delay(interval);            //wait for next round
  }
}

