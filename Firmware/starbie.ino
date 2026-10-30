

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <DHT.h>
#include <Preferences.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>


const int I2C_SDA_PIN = 6;
const int I2C_SCL_PIN = 7;
const int DHT_PIN = 3;
const int BUTTON_ONE_PIN = 4;
const int BUTTON_TWO_PIN = 5;
const int BUZZER_PIN = 8;
const int LED_PIN = 9;
const int NUMPIXELS = 6;

const bool USE_DHT11 = true;
const uint8_t OLED_ADDRESS = 0x3C;
const uint8_t MPU6050_ADDRESS = 0x68;


const int STARTING_JOY = 70;
const int STARTING_ENERGY = 75;
const int STARTING_FULLNESS = 65;
const bool RESET_SAVED_PET_ON_BOOT = false;

enum PetReaction {
  NAP_REACTION,
  JUMP_REACTION,
  HEART_REACTION,
  RUN_REACTION,
  DODGE_GAME_REACTION,
  REACTION_GAME_REACTION,
  LIGHT_SHOW_REACTION,
  SOUND_TEST_REACTION,
};

enum View {
  PET_VIEW,
  MENU_VIEW,
  STATS_VIEW,
  DODGE_GAME_VIEW,
  REFLEX_GAME_VIEW,
  LIGHT_SHOW_VIEW,
  SOUND_TEST_VIEW,
  SNAKE_GAME_VIEW,  
};

struct MenuItem {
  const char *label;
  int joyChange;
  int energyChange;
  int fullnessChange;
  PetReaction reaction;
};

const MenuItem MENU_ITEMS[] = {
  {"NAP",   1,  18, -4, NAP_REACTION},
  {"PLAY", 12, -9, -5, RUN_REACTION},
  {"DODGE", 5,  -5, -2, DODGE_GAME_REACTION},
  {"REFLEX", 8, -3, -2, REACTION_GAME_REACTION},
  {"LIGHTS", 4,  0,  0, LIGHT_SHOW_REACTION},
  {"SOUND",  4,  0,  0, SOUND_TEST_REACTION},
  {"PET",    7,  0,  0, HEART_REACTION},
};

const MenuItem MENU_ITEMS[] = {
  {"NAP",    1,   18, -4, NAP_REACTION},
  {"PLAY",  12,   -9, -5, RUN_REACTION},
  {"DODGE",  5,   -5, -2, DODGE_GAME_REACTION},
  {"REFLEX", 8,   -3, -2, REACTION_GAME_REACTION},
  {"LIGHTS", 4,    0,  0, LIGHT_SHOW_REACTION},
  {"SOUND",  4,    0,  0, SOUND_TEST_REACTION},
  {"PET",    7,    0,  0, HEART_REACTION},
  {"SNAKE",  6,   -4, -3, (PetReaction)8},
};

const int MENU_ITEM_COUNT = sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]);

const float MENU_TILT_LIMIT = 6.0f;
const float MENU_CENTER_DEADZONE = 0.8f;
const float SHAKE_THRESHOLD = 7.0f;
const float STANDARD_GRAVITY = 9.80665f;


const int PET_SPRITE_WIDTH = 32;
const int PET_SPRITE_HEIGHT = 32;
const uint8_t PROGMEM PET_SPRITE[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x70, 0x0a, 0x00, 0x00, 0xf8, 0x1f, 0x00,
  0x00, 0x8c, 0x3f, 0x80, 0x00, 0x43, 0xff, 0x00,
  0x00, 0x43, 0xff, 0x00, 0x00, 0x30, 0x7e, 0x00,
  0x00, 0x98, 0x01, 0x00, 0x01, 0x98, 0x01, 0x80,
  0x03, 0x00, 0x10, 0xc0, 0x03, 0x04, 0x00, 0xc0,
  0x01, 0x8b, 0x01, 0x80, 0x01, 0xcb, 0x03, 0x80,
  0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0,
  0x01, 0xc0, 0x03, 0x80, 0x01, 0x80, 0x01, 0x80,
  0x00, 0x60, 0x06, 0x00, 0x00, 0x3f, 0xfc, 0x00,
  0x00, 0x7f, 0xfe, 0x00, 0x00, 0x70, 0x0e, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int MENU_CENTER_X = 64;
const int MENU_CENTER_Y = 32;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_MPU6050 mpu;
DHT dht(DHT_PIN, DHT11);
Preferences preferences;
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

struct PetState {
  int joy;
  int energy;
  int fullness;
};

struct ButtonState {
  int pin;
  bool stableState;
  bool lastRawState;
  uint32_t lastChangedAt;
};

enum View {
  PET_VIEW,
  MENU_VIEW,
  STATS_VIEW,
  DODGE_GAME_VIEW,
  REFLEX_GAME_VIEW,
  LIGHT_SHOW_VIEW,
  SOUND_TEST_VIEW,
};

PetState pet = {STARTING_JOY, STARTING_ENERGY, STARTING_FULLNESS};
ButtonState buttonOne = {BUTTON_ONE_PIN, HIGH, HIGH, 0};
ButtonState buttonTwo = {BUTTON_TWO_PIN, HIGH, HIGH, 0};
View currentView = PET_VIEW;

bool mpuFound = false;
bool dhtFound = false;
float accelerationX = 0.0f;
float accelerationY = 0.0f;
float accelerationZ = STANDARD_GRAVITY;
float temperatureC = NAN;
float humidity = NAN;
float menuScrollAngle = 0.0f;
int selectedMenuItem = 0;
uint32_t lastMpuReadAt = 0;
uint32_t lastDhtReadAt = 0;
uint32_t lastShakeAt = 0;
uint32_t shakeAnimationEndsAt = 0;
uint32_t petJumpStartedAt = 0;
uint32_t nappingUntil = 0;
uint32_t heartAnimationEndsAt = 0;
uint32_t playRunStartedAt = 0;
int nappingPetX = 0;


int dodgePlayerY = 32;
int dodgeObstacleX = 128;
int dodgeObstacleY = 32;
int dodgeScore = 0;
bool dodgeGameOver = false;

uint32_t reflexStartTime = 0;
int reflexScore = 0;
bool reflexWaiting = false;
bool reflexGameOver = false;

int keepInRange(int value, int smallest, int largest) {
  return constrain(value, smallest, largest);
}

void changePet(int joyChange, int energyChange, int fullnessChange) {
  pet.joy = keepInRange(pet.joy + joyChange, 0, 100);
  pet.energy = keepInRange(pet.energy + energyChange, 0, 100);
  pet.fullness = keepInRange(pet.fullness + fullnessChange, 0, 100);
}

void loadPet() {
  preferences.begin("starcade", false);
  if (RESET_SAVED_PET_ON_BOOT) {
    preferences.clear();
  }
  pet.joy = preferences.getInt("joy", STARTING_JOY);
  pet.energy = preferences.getInt("energy", STARTING_ENERGY);
  pet.fullness = preferences.getInt("full", STARTING_FULLNESS);
}

void savePet() {
  preferences.putInt("joy", pet.joy);
  preferences.putInt("energy", pet.energy);
  preferences.putInt("full", pet.fullness);
}

void setUpButton(ButtonState &button) {
  pinMode(button.pin, INPUT_PULLUP);
  button.stableState = digitalRead(button.pin);
  button.lastRawState = button.stableState;
  button.lastChangedAt = millis();
}

bool wasPressed(ButtonState &button) {
  const bool rawState = digitalRead(button.pin);
  const uint32_t now = millis();
  if (rawState != button.lastRawState) {
    button.lastRawState = rawState;
    button.lastChangedAt = now;
  }
  if (rawState != button.stableState && now - button.lastChangedAt >= 30) {
    button.stableState = rawState;
    return button.stableState == LOW;
  }
  return false;
}

void updateMpu() {
  if (!mpuFound || millis() - lastMpuReadAt < 30) return;
  lastMpuReadAt = millis();
  sensors_event_t acceleration, gyro, sensorTemperature;
  mpu.getEvent(&acceleration, &gyro, &sensorTemperature);
  accelerationX = acceleration.acceleration.x;
  accelerationY = acceleration.acceleration.y;
  accelerationZ = acceleration.acceleration.z;
}

void updateDht() {
  if (!dhtFound || millis() - lastDhtReadAt < 2200) return;
  lastDhtReadAt = millis();
  float newH = dht.readHumidity();
  float newT = dht.readTemperature();
  if (!isnan(newH)) humidity = newH;
  if (!isnan(newT)) temperatureC = newT;
}

int petWalkingX(uint32_t now) {
  int farthestX = SCREEN_WIDTH - PET_SPRITE_WIDTH;
  uint32_t roundTrip = static_cast<uint32_t>(farthestX) * 2;
  uint32_t step = (now / 70) % roundTrip;
  return step <= farthestX ? step : roundTrip - step;
}

bool isNapping() {
  return nappingUntil != 0 && millis() < nappingUntil;
}

bool isPlaying() {
  return playRunStartedAt != 0 && millis() - playRunStartedAt < 1600;
}

int playRunX(uint32_t now) {
  int farthestX = SCREEN_WIDTH - PET_SPRITE_WIDTH;
  uint32_t lapAge = (now - playRunStartedAt) % 800;
  float progress = static_cast<float>(lapAge) / 800.0f;
  return progress < 0.5f ? static_cast<int>(progress * 2.0f * farthestX)
                         : static_cast<int>((1.0f - progress) * 2.0f * farthestX);
}

void updateMenuSelection() {
  float xTilt = accelerationX;
  if (xTilt > 3.0f) {
    selectedMenuItem = (selectedMenuItem + 1) % MENU_ITEM_COUNT;
    delay(200);
  } else if (xTilt < -3.0f) {
    selectedMenuItem = (selectedMenuItem - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
    delay(200);
  }
}

void chooseMenuItem() {
  const MenuItem &item = MENU_ITEMS[selectedMenuItem];
  changePet(item.joyChange, item.energyChange, item.fullnessChange);
  savePet();
  uint32_t now = millis();
  nappingUntil = 0;
  playRunStartedAt = 0;

  if (item.reaction == NAP_REACTION) {
    nappingPetX = petWalkingX(now);
    nappingUntil = now + 48000;
    tone(BUZZER_PIN, 500, 200);
    currentView = PET_VIEW;
  } else if (item.reaction == RUN_REACTION) {
    playRunStartedAt = now;
    tone(BUZZER_PIN, 1200, 150);
    currentView = PET_VIEW;
  } else if (item.reaction == DODGE_GAME_REACTION) {
    dodgeScore = 0;
    dodgeGameOver = false;
    dodgeObstacleX = 128;
    dodgeObstacleY = random(10, 50);
    currentView = DODGE_GAME_VIEW;
    tone(BUZZER_PIN, 900, 100);
  } else if (item.reaction == REACTION_GAME_REACTION) {
    reflexScore = 0;
    reflexGameOver = false;
    reflexWaiting = true;
    reflexStartTime = now + random(1000, 3000);
    currentView = REFLEX_GAME_VIEW;
    tone(BUZZER_PIN, 800, 100);
  } else if (item.reaction == LIGHT_SHOW_REACTION) {
    currentView = LIGHT_SHOW_VIEW;
    tone(BUZZER_PIN, 1500, 100);
  } else if (item.reaction == SOUND_TEST_REACTION) {
    currentView = SOUND_TEST_VIEW;
    tone(BUZZER_PIN, 2000, 100);
  } else {
    petJumpStartedAt = now;
    tone(BUZZER_PIN, 1000, 100);
    currentView = PET_VIEW;
  }
}

} else if (item.reaction == SOUND_TEST_REACTION) {
    currentView = SOUND_TEST_VIEW;
    tone(BUZZER_PIN, 2000, 100);
  } else if (item.reaction == (PetReaction)8) { 
    initSnakeGame();
    currentView = SNAKE_GAME_VIEW;
    tone(BUZZER_PIN, 1000, 100);
  } else {
    petJumpStartedAt = now;
    tone(BUZZER_PIN, 1000, 100);
    currentView = PET_VIEW;
  }



void handleButtons() {
  if (wasPressed(buttonOne)) {
    if (currentView == MENU_VIEW) {
      chooseMenuItem();
    } else if (currentView == DODGE_GAME_VIEW || currentView == REFLEX_GAME_VIEW || 
               currentView == LIGHT_SHOW_VIEW || currentView == SOUND_TEST_VIEW) {
      currentView = PET_VIEW;
    } else {
      currentView = MENU_VIEW;
      selectedMenuItem = 0;
    }
  }
  if (wasPressed(buttonTwo)) {
    if (currentView != PET_VIEW && currentView != MENU_VIEW) {
      currentView = PET_VIEW;
    } else {
      currentView = currentView == STATS_VIEW ? PET_VIEW : STATS_VIEW;
    }
  }
}

void drawPet() {
  display.clearDisplay();
  uint32_t now = millis();
  int petX = isNapping() ? nappingPetX : petWalkingX(now);
  if (isPlaying()) petX = playRunX(now);
  int petY = SCREEN_HEIGHT - PET_SPRITE_HEIGHT;
  petX = constrain(petX, 0, SCREEN_WIDTH - PET_SPRITE_WIDTH);
  display.drawBitmap(petX, petY, PET_SPRITE, PET_SPRITE_WIDTH, PET_SPRITE_HEIGHT, SSD1306_WHITE);
  display.display();
}

void drawMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 5);
  display.print(F("-- STARCADE MENU --"));

  for (int i = 0; i < MENU_ITEM_COUNT; i++) {
    int yPos = 20 + (i * 10);
    if (i == selectedMenuItem) {
      display.setCursor(5, yPos);
      display.print(F(">"));
    }
    display.setCursor(15, yPos);
    display.print(MENU_ITEMS[i].label);
  }
  display.display();
}

void drawStats() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(4, 5);
  display.print("JOY: "); display.print(pet.joy);
  display.setCursor(4, 20);
  display.print("ENERGY: "); display.print(pet.energy);
  display.setCursor(4, 35);
  display.print("TEMP: "); display.print(temperatureC); display.print(" C");
  display.display();
}

void runDodgeGame() {
  display.clearDisplay();
  if (!dodgeGameOver) {
    if (accelerationY > 2.0f) dodgePlayerY -= 3;
    if (accelerationY < -2.0f) dodgePlayerY += 3;
    dodgePlayerY = constrain(dodgePlayerY, 10, 54);

    dodgeObstacleX -= 4;
    if (dodgeObstacleX < 0) {
      dodgeObstacleX = 128;
      dodgeObstacleY = random(10, 50);
      dodgeScore += 10;
      tone(BUZZER_PIN, 1200, 50);
    }

    if (dodgeObstacleX < 16 && abs(dodgePlayerY - dodgeObstacleY) < 10) {
      dodgeGameOver = true;
      tone(BUZZER_PIN, 300, 300);
    }

    display.fillRect(10, dodgePlayerY - 4, 8, 8, SSD1306_WHITE);
    display.fillRect(dodgeObstacleX, dodgeObstacleY - 6, 6, 12, SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Score: "); display.print(dodgeScore);
  } else {
    display.setCursor(20, 20);
    display.print("GAME OVER!");
    display.setCursor(20, 35);
    display.print("Final: "); display.print(dodgeScore);
    display.setCursor(10, 50);
    display.print("Press button to exit");
  }
  display.display();
}

void runReflexGame() {
  display.clearDisplay();
  uint32_t now = millis();
  display.setCursor(10, 20);
  if (reflexWaiting) {
    if (now < reflexStartTime) {
      display.print("WAIT FOR SIGNAL...");
      pixels.clear();
      pixels.show();
    } else {
      display.print("HIT BUTTON NOW!");
      for(int i=0; i<NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(200, 0, 0));
      }
      pixels.show();
      if (wasPressed(buttonOne)) {
        reflexScore = max(1, 100 - (int)(now - reflexStartTime));
        reflexWaiting = false;
        tone(BUZZER_PIN, 2500, 200);
      }
    }
  } else {
    display.print("SCORE: "); display.print(reflexScore);
    display.setCursor(10, 40);
    display.print("Press button to exit");
    pixels.clear();
    pixels.show();
    if (wasPressed(buttonOne)) {
      currentView = PET_VIEW;
    }
  }
  display.display();
}

void runLightShow() {
  display.clearDisplay();
  display.setCursor(20, 25);
  display.print("LIGHT SHOW ACTIVE");
  display.display();

  uint32_t now = millis() / 100;
  for(int i=0; i<NUMPIXELS; i++) {
    int red = sin(now + i) * 127 + 128;
    int green = cos(now + i) * 127 + 128;
    pixels.setPixelColor(i, pixels.Color(red, green, 50));
  }
  pixels.show();
}

void runSoundTest() {
  display.clearDisplay();
  display.setCursor(25, 25);
  display.print("SOUND TEST MODE");
  display.display();
  tone(BUZZER_PIN, random(400, 2000), 100);
  delay(200);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  setUpButton(buttonOne);
  setUpButton(buttonTwo);
  loadPet();

  pinMode(BUZZER_PIN, OUTPUT);
  pixels.begin();
  pixels.show();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    while (true) delay(10);
  }

  mpuFound = mpu.begin(MPU6050_ADDRESS, &Wire);
  if (mpuFound) {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  }

  if (USE_DHT11) {
    dht.begin();
    dhtFound = true;
  }
}

void loop() {
  updateMpu();
  updateDht();
  handleButtons();

  if (currentView == MENU_VIEW) {
    updateMenuSelection();
    drawMenu();
  } else if (currentView == STATS_VIEW) {
    drawStats();
  } else if (currentView == DODGE_GAME_VIEW) {
    runDodgeGame();
  } else if (currentView == REFLEX_GAME_VIEW) {
    runReflexGame();
  } else if (currentView == LIGHT_SHOW_VIEW) {
    runLightShow();
  } else if (currentView == SOUND_TEST_VIEW) {
    runSoundTest();
  } else {
    drawPet();
  }
  delay(16);


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


const int SNAKE_GRID_SIZE = 4; 
const int SNAKE_MAX_LENGTH = 50;

struct Point {
  int x;
  int y;
};

Point snake[SNAKE_MAX_LENGTH];
int snakeLength = 3;
Point snakeDir = {1, 0}; // Moving right initially
Point food = {10, 10};
bool snakeGameOver = false;
uint32_t lastSnakeMoveTime = 0;
const uint32_t SNAKE_FRAME_DELAY = 150; // Speed of the snake

void initSnakeGame() {
  snakeLength = 3;
  snake[0] = {8, 8};
  snake[1] = {7, 8};
  snake[2] = {6, 8};
  snakeDir = {1, 0};
  food = {random(2, 28), random(2, 14)};
  snakeGameOver = false;
  lastSnakeMoveTime = millis();
}

void updateSnakeGame(bool buttonUpPressed, bool buttonDownPressed, bool buttonActionPressed) {
  if (snakeGameOver) {
    if (buttonActionPressed) {
      initSnakeGame(); // Restart on button press
    }
    return;
  }

  
  if (buttonUpPressed && snakeDir.y == 0) {
    snakeDir = {0, -1};
  } else if (buttonDownPressed && snakeDir.y == 0) {
    snakeDir = {0, 1};
  }

 
  uint32_t now = millis();
  if (now - lastSnakeMoveTime >= SNAKE_FRAME_DELAY) {
    lastSnakeMoveTime = now;

  
    for (int i = snakeLength - 1; i > 0; i--) {
      snake[i] = snake[i - 1];
    }

   
    snake[0].x += snakeDir.x;
    snake[0].y += snakeDir.y;

   (Screen is 128x64 -> 32x16 grid blocks)
    if (snake[0].x < 0 || snake[0].x >= 32 || snake[0].y < 0 || snake[0].y >= 16) {
      snakeGameOver = true;
      return;
    }

    
    for (int i = 1; i < snakeLength; i++) {
      if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
        snakeGameOver = true;
        return;
      }
    }


    if (snake[0].x == food.x && snake[0].y == food.y) {
      if (snakeLength < SNAKE_MAX_LENGTH) {
        snakeLength++;
      }
      food = {random(0, 32), random(0, 16)};
    }
  }
}

void drawSnakeGame() {
  display.clearDisplay();

  if (!snakeGameOver) {
    
    display.fillRect(food.x * SNAKE_GRID_SIZE, food.y * SNAKE_GRID_SIZE, SNAKE_GRID_SIZE - 1, SNAKE_GRID_SIZE - 1, SSD1306_WHITE);

    for (int i = 0; i < snakeLength; i++) {
      display.fillRect(snake[i].x * SNAKE_GRID_SIZE, snake[i].y * SNAKE_GRID_SIZE, SNAKE_GRID_SIZE - 1, SNAKE_GRID_SIZE - 1, SSD1306_WHITE);
    }
  } else {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30, 20);
    display.print(F("SNAKE OVER"));
    display.setCursor(20, 35);
    display.print(F("Press to Restart"));
  }

  display.display();
} 
void loop() {
  updateMpu();
  updateDht();
  handleButtons();

  if (currentView == MENU_VIEW) {
    updateMenuSelection();
    drawMenu();
  } else if (currentView == STATS_VIEW) {
    drawStats();
  } else if (currentView == DODGE_GAME_VIEW) {
    runDodgeGame();
  } else if (currentView == REFLEX_GAME_VIEW) {
    runReflexGame();
  } else if (currentView == LIGHT_SHOW_VIEW) {
    runLightShow();
  } else if (currentView == SOUND_TEST_VIEW) {
    runSoundTest();
  } else if (currentView == SNAKE_GAME_VIEW) 
    updateSnakeGame(wasPressed(buttonOne), wasPressed(buttonTwo), wasPressed(buttonOne));
    drawSnakeGame();
  } else {
    drawPet();
  }
  delay(16);
}
