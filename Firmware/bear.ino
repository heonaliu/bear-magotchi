// // buttons (traced from schematic)

// these aren't used in my program ----
// #define BTN1 0 // SW1 -> MCU Pin 1 -> GPIO2
// #define BTN2 1 // SW2 -> MCU Pin 2 -> GPIO3
// #define BTN3 2 // SW3 -> MCU PIN 3 -> GPIO4
// #define SCL 6 // PIN 5 GPIO06
// #define SDA 7  // PIN 6 GPIO07
// #define BUZZER 10 // PIN 11 GPIO10

// =================================
// brings in display driver and graphics functions
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 0.96" OLED resolution (128x64px)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 //reset pin for OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// the way I wired was SW3 on top, SW1 on bottom
#define BTN_TOP 4
#define BTN_MIDDLE 3
#define BTN_BOTTOM 2
#define BUZZER_PIN 10

// define pet model
struct Pet {
  int hunger;
  int happiness;
  int energy;
  unsigned long age;

};

Pet pet;

enum Screen {
  SCREEN_MAIN,
  SCREEN_FEED,
  SCREEN_PLAY,
  SCREEN_SLEEP
};

// tracks the current screen
Screen currentScreen = SCREEN_MAIN;

// stores the last time pet was updated
unsigned long lastUpdate = 0; 

void updatePet() {
  if (millis() - lastUpdate > 5000) { // 5000 millisec ==> 5 sec
    pet.hunger--;
    pet.happiness--;
    pet.energy--;

    //specify conditions and not go <0
    if (pet.hunger < 0) pet.hunger = 0;
    if (pet.happiness < 0) pet.happiness = 0;
    if (pet.energy < 0) pet.energy = 0;

    pet.age += 5;
    lastUpdate = millis(); // reupdate millis
  } 
}

unsigned long lastButtonPress = 0;
void checkButtons() {
  if (millis() - lastButtonPress < 200) return; //debounce effect

  if (digitalRead(BTN_TOP) == LOW) {
    //only setting state not acting yet
    currentScreen = SCREEN_FEED;
    tone(BUZZER_PIN, 1000, 50); //(buzzer, hz, time)
    lastButtonPress = millis(); //refresh when last pressed
  }
  else if (digitalRead(BTN_MIDDLE)==LOW) {
    currentScreen = SCREEN_PLAY;
    tone(BUZZER_PIN, 1200, 50);
    lastButtonPress = millis();
  }
  else if (digitalRead(BTN_BOTTOM)==LOW){
    currentScreen = SCREEN_SLEEP;
    tone(BUZZER_PIN, 800, 50);
    lastButtonPress = millis();
  }

}

void handleScreenLogic() {
  switch(currentScreen) {
    case SCREEN_FEED:
      pet.hunger += 10;
      if (pet.hunger >100) pet.hunger = 100;
      currentScreen = SCREEN_MAIN;
      break;

    case SCREEN_PLAY:
      pet.happiness += 10;
      pet.energy -=5;
      if (pet.energy<0) pet.energy = 0;
      currentScreen = SCREEN_MAIN;
      break;

    case SCREEN_SLEEP:
      pet.energy += 15;
      if (pet.energy >100) pet.energy = 100;
      
      break;

    //main shows stats, other states do actions
    case SCREEN_MAIN:
      break;
  }
}

const unsigned char PROGMEM petHappy[] = {
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00011000, 0b00011000,
  0b00100110, 0b01100100,
  0b00100011, 0b11000100,
  0b00110000, 0b00001100,
  0b01100000, 0b00000110,
  0b01000100, 0b00100010,
  0b10001000, 0b00010001,
  0b10000010, 0b01000001,
  0b10000001, 0b10000001,
  0b10000000, 0b00000001,
  0b01000000, 0b00000010,
  0b00111111, 0b11111100,
  0b00000000, 0b00000000
};

const unsigned char PROGMEM petSad[] = {
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00011000, 0b00011000,
  0b00100110, 0b01100100,
  0b00100011, 0b11000100,
  0b00110000, 0b00001100,
  0b01100000, 0b00000110,
  0b01011100, 0b00111010,
  0b10001001, 0b00010001,
  0b10001010, 0b10010001,
  0b10001000, 0b00010001,
  0b10001000, 0b00010001,
  0b01001000, 0b00010010,
  0b00111111, 0b11111100,
  0b00000000, 0b00000000
};
 const unsigned char PROGMEM petNeutral[] = {
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00011000, 0b00011000,
  0b00100110, 0b01100100,
  0b00100011, 0b11000100,
  0b00110000, 0b00001100,
  0b01100000, 0b00000110,
  0b01001000, 0b00010010,
  0b10001001, 0b10010001,
  0b10000000, 0b00000001,
  0b10000000, 0b00000001,
  0b10000000, 0b00000001,
  0b01000000, 0b00000010,
  0b00111111, 0b11111100,
  0b00000000, 0b00000000
};

const unsigned char PROGMEM petSleep[] = {
  0b00000000, 0b00011000,
  0b00000000, 0b00011010,
  0b00000000, 0b01000000,
  0b00011000, 0b00011000,
  0b00100110, 0b01100100,
  0b00100011, 0b11000100,
  0b00110000, 0b00001100,
  0b01100000, 0b00000110,
  0b01000000, 0b00000010,
  0b10011100, 0b00111001,
  0b10000001, 0b10000001,
  0b10000000, 0b00000001,
  0b10000000, 0b00000001,
  0b01000000, 0b00000010,
  0b00111111, 0b11111100,
  0b00000000, 0b00000000
};

void render() {
  display.clearDisplay();
  const unsigned char* sprite;

  if (currentScreen == SCREEN_SLEEP) {
    sprite= petSleep;
  } else if (pet.hunger < 30 || pet.happiness < 30 || pet.energy < 30) {
    sprite = petSad;
  } else if (pet.hunger > 50 && pet.happiness >50 && pet.energy > 50) {
    sprite = petHappy;
  } else {
    sprite = petNeutral;
  }

  //draw pet sprite
  display.drawBitmap(56, 2, sprite, 16,16, SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0,24);
  display.print("HUN ");
  drawBar(24, 24,pet.hunger);

  display.setCursor(0,34);
  display.print("HAP ");
  drawBar(24, 34, pet.happiness);

  display.setCursor(0,44);
  display.print("ENG ");
  drawBar(24, 44, pet.energy);

  display.setCursor(0,56);
  display.println("[Feed] [Play] [Sleep]");

  display.display();
}

void drawBar(int x, int y, int value) {
  int barWidth = 100;
  int barHeight = 6;
  int fillWidth = map(value, 0,100,0, barWidth);

  display.drawRect(x,y,barWidth,barHeight,SSD1306_WHITE); //outline
  display.fillRect(x,y, fillWidth, barHeight,SSD1306_WHITE); //filled portion
}


void setup() {

  Wire.begin(6,7);

  pinMode(BTN_TOP, INPUT_PULLUP);
  pinMode(BTN_MIDDLE, INPUT_PULLUP);
  pinMode(BTN_BOTTOM, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  
  //init oled
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);  //drawing color
  display.setCursor(0,0);
  display.println("Tamagotchi Init...");
  display.display(); // must call if want anything to appear
  delay(1000);

  pet.hunger = 80;
  pet.happiness = 80;
  pet.energy = 80;
  pet.age = 0;
}

void loop() {
  checkButtons(); // read input
  updatePet();
  handleScreenLogic();
  render();
  delay(100);
}