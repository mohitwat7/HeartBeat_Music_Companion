#include <Wire.h>
#include <LiquidCrystal.h>

#define SCREEN_WIDTH 16
#define SCREEN_HEIGHT 2
#define PULSE_SENSOR_PIN A0 // Pulse sensor pin
#define MAX_PULSE_RATE 1500 // Maximum allowed pulse rate, multiplied by 10

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // Initialize LCD display with the appropriate pins

// Arrays of song titles for different pulse rate ranges
const char* relaxingSongs[] = {
  "Habits",
  "Atlantis",
  "Hurts so good",
  "Reckless",
  "Breathe",
  "Icon",
  "Paris in rain",
  "Levels",
  "Train wreck",
  "Stereo hearts"
};

const char* normalSongs[] = {
  "Blank Space",
  "Dont blame me",
  "FLORIDA",
  "DOWN BAD",
  "EXILE",
  "ROSES",
  "ALL TOO WELL",
  "CLOSER",
  "ALL WE KNOW",
  "RED"
};

const char* energeticSongs[] = {
  "HEART ATTACK BY ENRIQUE IGLEASIAS",
  "MEXICO BY DEMITRI VEGAS",
  "I KNOW BY TRAVIS SCOTT",
  "LOVE ME AGAIN BY JOHN NEWMAN",
  "ICON BY JADEN SMITH",
  "TOO MANY NIGHTS BY METERO BOOMIN",
  "HEYNA BY TRAVIS SCOTT",
  "GOOSEBUMPS BY TRAVIS SCOTT",
  "NIGGAS IN PARIS BY KANYE WEST",
  "FEIN BY TRAVIS SCOTT"
};

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging
  
  // Initialize the LCD display
  lcd.begin(SCREEN_WIDTH, SCREEN_HEIGHT);

  // Clear the LCD display
  lcd.clear();
}

void loop() {
  // Read pulse sensor data
  int pulseRate = analogRead(PULSE_SENSOR_PIN);
  
  // Constrain pulse rate to be between 0 and 1500
  pulseRate = constrain(pulseRate, 0, MAX_PULSE_RATE);
  
  // Divide the pulse rate by 10
  pulseRate /= 10;
  
  // Print the pulse rate
  lcd.setCursor(0, 0);
  lcd.print("Pulse: ");
  lcd.print(pulseRate);
  lcd.print("   "); // Clear any remaining characters

  // Suggest a song based on pulse rate
  suggestSong(pulseRate);
  
  delay(1000);  // Delay for 1 second
}

void suggestSong(int pulseRate) {
  // Clear previous song name
  lcd.setCursor(0, 1);
  lcd.print("                ");
  
  lcd.setCursor(0, 1);
  lcd.print("Song: ");
  
  const char* songName;
  if (pulseRate < 60) {
    // Select a relaxing song randomly
    int index = random(0, sizeof(relaxingSongs) / sizeof(relaxingSongs[0]));
    songName = relaxingSongs[index];
  } else if (pulseRate >= 60 && pulseRate <= 90) {
    // Select a normal song randomly
    int index = random(0, sizeof(normalSongs) / sizeof(normalSongs[0]));
    songName = normalSongs[index];
  } else {
    // Select an energetic song randomly
    int index = random(0, sizeof(energeticSongs) / sizeof(energeticSongs[0]));
    songName = energeticSongs[index];
  }

  // Print the entire song name
  lcd.print(songName);
}