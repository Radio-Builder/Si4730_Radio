#include <SI4735.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include "AiEsp32RotaryEncoder.h"

//------------------------------- TFT Display Init ------------------------------//
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
void setupDisplay(void)
{
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_WHITE);
}

//------------------------------- Encoder Init ------------------------------//
#define ROTARY_ENCODER_A_PIN 34
#define ROTARY_ENCODER_B_PIN 35
#define ROTARY_ENCODER_BUTTON_PIN 32
#define ROTARY_ENCODER_STEPS 4
#define ROTARY_ENCODER_VCC_PIN -1
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
long lastEncoderReading = 0;

void IRAM_ATTR readEncoderISR()
{
	rotaryEncoder.readEncoder_ISR();
}

void setupEncoder(void)
{
  	//we must initialize rotary encoder
	rotaryEncoder.begin();
	rotaryEncoder.setup(readEncoderISR);
	rotaryEncoder.setAcceleration(250); //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
}

//------------------------------- Switches Init ------------------------------//
#define SW_4_PIN 19
#define SW_3_PIN 16
#define SW_2_PIN 4

void setupSwitches(void)
{
  pinMode(SW_2_PIN,INPUT);  
  pinMode(SW_3_PIN,INPUT);  
  pinMode(SW_4_PIN,INPUT);  
}

//------------------------------- Si4735 Init ------------------------------//
#define RESET_PIN 13
#define FM_FUNCTION 0

uint16_t currentFrequency = 8910;
uint16_t previousFrequency;
SI4735 rx;

void setupSi4735(void)
{
  digitalWrite(RESET_PIN, HIGH);

  // Look for the Si47XX I2C bus address
  int16_t si4735Addr = rx.getDeviceI2CAddress(RESET_PIN);
  if ( si4735Addr == 0 ) {
    Serial.println("Si473X not found!");
    Serial.flush();
    while (1);
  } else {
    Serial.print("The SI473X / SI474X I2C address is 0x");
    Serial.println(si4735Addr, HEX);
  }

  delay(500);
  rx.setup(RESET_PIN, FM_FUNCTION);
  rx.setFM(8400, 10800, 8910, 10);

  delay(500);
  currentFrequency = previousFrequency = rx.getFrequency();
  rx.setVolume(60);
}


void setup()
{
   Serial.begin(9600);
   while(!Serial);

  setupDisplay();
  setupEncoder();
  setupSi4735();
  
  tft.setTextColor(TFT_WHITE,TFT_BLACK );  
  tft.drawString("Freq ",5,30,4);  
  tft.setTextColor(TFT_BLACK,TFT_WHITE );  
  String freq = String(float(currentFrequency)/100.0)+ "  ";
  tft.drawString(freq,70,30,4);  

}

// Main
void loop()
{ 
  long currentReading = rotaryEncoder.readEncoder();
  long change =  currentReading -lastEncoderReading;
  bool update = false;  

  if(change !=0){
    currentFrequency = currentFrequency + change*10;
    lastEncoderReading = currentReading;
    update = true;  
    }

  int bState2=digitalRead(SW_2_PIN);
  int bState3=digitalRead(SW_3_PIN);
  int bState4=digitalRead(SW_4_PIN);
  
  if(bState2==1){

    currentFrequency = 10580;     // Newstalk
    update = true;  
  }

  if(bState3==1){
    //setupSi4735();
    currentFrequency = 9620;      // Midlands 
    update = true; 
  }

  if(bState4==1){
    currentFrequency = 8910;      // RTE 1
    update = true; 
    }
  
  if(update==true){
    String freq = String(float(currentFrequency)/100.0) + "   ";
    tft.drawString(freq,70,30,4)+ "   ";
    rx.setFrequency(currentFrequency);
  }
    
}
