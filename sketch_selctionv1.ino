// ================================
// LIBRAIRIES
// ================================
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Keypad.h>

// ================================
// PROTOTYPES DES FONCTIONS
// ================================
void drawMenu();
void showMessage(int option);

// ================================
// PINS ECRAN
// ================================
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// ================================
// VARIABLES GLOBALES
// ================================
int menuIndex = 0;              // Curseur du menu
const int menuSize = 3;         // Nombre d'options
bool inMessage = false;         // Mode message actif ?
int currentMessageOption = 0;   // Option actuellement affichée dans le message

String menu[menuSize] = {
  "Judo",
  "Foot",
  "Basketball"
};

// ================================
// CLAVIER 4x4
// ================================
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, A0, A1};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ================================
// SETUP
// ================================
void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  drawMenu(); // Affichage initial du menu
}

// ================================
// LOOP
// ================================
void loop() {
  char key = keypad.getKey(); // Lire touche

  if (!inMessage) {
    // ================================
    // MODE MENU
    // ================================
    if (key) {
      if (key == '9') { // Monter curseur
        menuIndex--;
        if (menuIndex < 0) menuIndex = menuSize - 1;
        drawMenu();
      }
      if (key == '#') { // Descendre curseur
        menuIndex++;
        if (menuIndex >= menuSize) menuIndex = 0;
        drawMenu();
      }
      if (key == 'C') { // Valider option
        currentMessageOption = menuIndex; // Sauvegarde option sélectionnée
        inMessage = true;                 // Passe en mode message
        showMessage(currentMessageOption);
      }
    }
  } else {
    // ================================
    // MODE MESSAGE
    // ================================
    if (key) {
      if (key == 'D') { // Valider "Back"
        inMessage = false;   // Retour au menu
        drawMenu();
      }
    }
  }
}

// ================================
// FONCTION D'AFFICHAGE MENU
// ================================
void drawMenu() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(2);

  for (int i = 0; i < menuSize; i++) {
    if (i == menuIndex) {
      tft.setTextColor(ILI9341_YELLOW);
      tft.setCursor(20, 40 + i * 30);
      tft.print("> ");
    } else {
      tft.setTextColor(ILI9341_WHITE);
      tft.setCursor(20, 40 + i * 30);
      tft.print("  ");
    }
    tft.print(menu[i]);
  }
}

// ================================
// FONCTION D'AFFICHAGE MESSAGE
// ================================
void showMessage(int option) {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(20, 80);

  // Message selon option
  if (option == 0) tft.print("Mode selectionné: Judo");
  else if (option == 1) tft.print("Mode selectionné: Foot");
  else if (option == 2) tft.print("Mode selectionné: Basketball");

  // Affiche "Back" en haut à gauche
  tft.setTextColor(ILI9341_YELLOW);
  tft.setCursor(0, 0);
  tft.print("> Back");
}
