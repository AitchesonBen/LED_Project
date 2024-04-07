#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define LED_PIN        6
#define BUTTON_PIN     7

#define NUMPIXELS 6 // NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pixels.begin();
  //Goes blue when starting
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 50));
    pixels.show();
    delay(DELAYVAL);
  }
}

void loop() {
  bool button = buttonChecked();
  int time = 0;
  if (button == true)
  {
    int number = random(1000, 6000);
    delay(1000);
    pixels.clear();
    pixels.show();
    delay(number);
    blue();
  }
}

bool buttonChecked() {
  if(digitalRead(BUTTON_PIN) == LOW)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void flashRed() {
    for (int j=0; j<3; j++){
      //Red flash
      for(int i=0; i<NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(50, 0, 0));
      }
      pixels.show();
      delay(100);
      //Turns off
      for(int i=0; i<NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      }
      pixels.show(); 
      delay(100);
    }
}

void blue() {
  bool newButton = buttonChecked();
  if(newButton == false){
    //Goes red if before blue flash
    flashRed();
    return;
  }
  //Blue flash for when to let go
  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 50));
    pixels.show();
  }
  delay(750);
  bool newButton2 = buttonChecked();
  if(newButton2 == false){
    //Goes green if let go before time runs out and you win :)
    for(int i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(50, 50, 0));
      pixels.show();
    }
  }
  else {
    //Goes red if time goes out
    flashRed();
  }
}