/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialEvent
*/

// Serial Port Input Setup
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
// Tone Pin and Tone Setup
const int tone_pin = 9;  // Connect the Oscope to this pin
int freq = 3400; // Default hardcoded value

void setup() {
  // initialize freq:
  tone(tone_pin,freq);
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  Serial.println("Enter a Frequency > ");
  
}

void loop() {
  //Serial.println(stringComplete);
  //Serial.println("Enter a Frequency > ");
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    freq = inputString.toInt();
    //Serial.println(freq);
    tone(tone_pin,freq); 
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
