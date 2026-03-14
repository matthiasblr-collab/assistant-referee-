 #include <Adafruit_GFX.h> //ecran 
 #include <Adafruit_ST7789.h> // ecran 
 #include <SPI.h> // ecran 

#include <Keypad.h> //clavier 

char touches[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte brochesLignes[4] = {9, 8, 7, 6};    // 4 lignes
byte brochesColonnes[4] = {5, 4, 3, 2};  // 4 colonnes

Keypad clavier = Keypad(makeKeymap(touches), brochesLignes, brochesColonnes, 4, 4);
 #define TFT_CS 10
 #define TFT_DC 9
 #define TFT_RST 8

 Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
 
 int tempsActuel = 0; 
 bool chronoEnCours = false;
 unsigned long dernierMillis = 0;
 

void setup() {
  Serial.begin(9600);
  tft.init(240,320);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {

char touche = clavier.getKey();

if(touche == 'A'){
  chronoEnCours = !chronoEnCours;
}

if(touche == 'B'){
  tempsActuel = 0;
  tft.fillScreen(ST77XX_BLACK);   
  tft.setCursor(10, 100);         
  tft.setTextColor(ST77XX_WHITE); 
  tft.setTextSize(4);
  tft.print("00:00");
}
if(chronoEnCours == true && millis()- dernierMillis >= 1000) { 
tempsActuel = tempsActuel + 1; 
 dernierMillis = millis();

int minutes = tempsActuel / 60;
int secondes = tempsActuel % 60;

 tft.fillScreen(ST77XX_BLACK);   
  tft.setCursor(10, 100);         
  tft.setTextColor(ST77XX_WHITE); 
  tft.setTextSize(4);

  if(minutes < 10){
  tft.print("0");
}
tft.print(minutes);

tft.print(":");

if(secondes < 10){
  tft.print("0");
}
 tft.println(secondes);
 }

 
  
}

