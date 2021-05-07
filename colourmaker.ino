/*The button part of this code was created following the example code below.
 * 
 *
 * The example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button
 */
#include <Adafruit_NeoPixel.h>

#define LED_PIN    8

// How many NeoPixels are attached to the Arduino? 
#define LED_COUNT 223

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)

// constants won't change. They're used here to set pin numbers:
const int BUTTON_PIN_YELLOW1 = 2;       // the number of the pushbutton pin
const int BUTTON_PIN_BLUE1 = 3;
const int BUTTON_PIN_GREEN1 = 4;
const int BUTTON_PIN_YELLOW2 = 5;
const int BUTTON_PIN_BLUE2 = 6;
const int BUTTON_PIN_GREEN2 = 7;

// Variables will change:
int lastStateY1 = LOW;  // the previous state from the input pin
int lastStateB1 = LOW;  // the previous state from the input pin
int lastStateG1 = LOW;  // the previous state from the input pin
int lastStateY2 = LOW;  // the previous state from the input pin
int lastStateB2 = LOW;  // the previous state from the input pin
int lastStateG2 = LOW;  // the previous state from the input pin

int currentStateY1;                // the current reading from the input pin
int currentStateB1;                // the current reading from the input pin
int currentStateG1;                // the current reading from the input pin
int currentStateY2;                // the current reading from the input pin
int currentStateB2;                // the current reading from the input pin
int currentStateG2;                // the current reading from the input pin

int currentProgram=0; 

//variables for 'chase'
int i=0;
int wait=50;
uint32_t color;



void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the pushbutton pin as an pull-up input
  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(BUTTON_PIN_YELLOW1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_BLUE1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_GREEN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_YELLOW2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_BLUE2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_GREEN2, INPUT_PULLUP);
}

void loop() {

  int buttonPressed = checkButtons();
  
  if(currentProgram == 2)// chase yellow
  {
    Serial.println("Switching to rainbow 10");
    
    rainbow(10,2);    
  }
  else if(currentProgram == 3) // chase blue
  {
    Serial.println("Switching to rainbow 100");
    rainbow(100,3);
   }
  else if(currentProgram == 4) //chase green
  {
    Serial.println("Switching to rainbow 5");
   rainbow(5,4);
  }
  else if(currentProgram == 5) //turn off pixels
  {
    Serial.println("Turning off pixels.");
    strip.clear();
    strip.show();
  }
  else if(currentProgram == 6) //Does nothing right now.
  {
 
  }
  else if(currentProgram == 7) // Does nothing right now.
  {
    
  }

}

// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.

int checkButtons()
{
  int newButtonPressed = 0;
  
  currentStateY1 = digitalRead(BUTTON_PIN_YELLOW1);
  currentStateB1 = digitalRead(BUTTON_PIN_BLUE1);
  currentStateG1 = digitalRead(BUTTON_PIN_GREEN1);
  currentStateY2 = digitalRead(BUTTON_PIN_YELLOW2);
  currentStateB2 = digitalRead(BUTTON_PIN_BLUE2);
  currentStateG2 = digitalRead(BUTTON_PIN_GREEN2);
  
    if(lastStateY1 == HIGH && currentStateY1 == LOW)
  {
    Serial.println("The Y1 button is pressed");
    currentProgram=2;
    newButtonPressed=1;
  }
  else if(lastStateY1 == LOW && currentStateY1 == HIGH)
    Serial.println("The Y1 button is released");

 if(lastStateB1 == HIGH && currentStateB1 == LOW)
 {
    Serial.println("The B1 button is pressed");
    currentProgram=3;
    newButtonPressed=1;
 }
  else if(lastStateB1 == LOW && currentStateB1 == HIGH)
    Serial.println("The B1 button is released");

 if(lastStateG1 == HIGH && currentStateG1 == LOW)
 {
    Serial.println("The G1 button is pressed");
    currentProgram=4;
    newButtonPressed=1;
 }
  else if(lastStateG1 == LOW && currentStateG1 == HIGH)
    Serial.println("The G1 button is released");

 if(lastStateY2 == HIGH && currentStateY2 == LOW)
 {
    Serial.println("The Y2 button is pressed");
    currentProgram=5;
    newButtonPressed=1;
 }
  else if(lastStateY2 == LOW && currentStateY2 == HIGH)
  {
    Serial.println("The Y2 button is released");
  }
 if(lastStateB2 == HIGH && currentStateB2 == LOW)
 {
    Serial.println("The B2 button is pressed");
    currentProgram=6;
    newButtonPressed=1;
 }
  else if(lastStateB2 == LOW && currentStateB2 == HIGH)
    Serial.println("The B2 button is released");

 if(lastStateG2 == HIGH && currentStateG2 == LOW)
 {
    Serial.println("The G2 button is pressed");
    currentProgram=7;
    newButtonPressed=1;
 }
  else if(lastStateG2 == LOW && currentStateG2 == HIGH)
    Serial.println("The G2 button is released");


      // save the the last state
  lastStateY1 = currentStateY1;
  lastStateB1 = currentStateB1;
  lastStateG1 = currentStateG1;
  lastStateY2 = currentStateY2;
  lastStateB2 = currentStateB2;
  lastStateG2 = currentStateG2;

return newButtonPressed;
}
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait, int programNumber) {
  int buttonPressed = 0;
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
    
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) 
  {
   if(currentProgram == programNumber)
   { 
    buttonPressed = checkButtons();
  
    for(int i=0; i<strip.numPixels(); i++) 
    {
      int buttonPressed = checkButtons();

        // For each pixel in strip...
        // Offset pixel hue by an amount to make one full revolution of the
        // color wheel (range of 65536) along the length of the strip
        // (strip.numPixels() steps):
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
        // optionally add saturation and value (brightness) (each 0 to 255).
        // Here we're using just the single-argument hue variant. The result
        // is passed through strip.gamma32() to provide 'truer' colors
        // before assigning to each pixel:
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      
    }
   }
   else
   {firstPixelHue=1000000;}
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
