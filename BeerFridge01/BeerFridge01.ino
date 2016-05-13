#include <math.h>
#include <LiquidCrystal.h>
#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

double setTemp = 65.00;
const int upButtonPin = 7;
const int downButtonPin = 6;
int upButtonState = 0;
int downButtonState = 0; 

// Set and send the thermistor method the thermistor resistance.
int val=analogRead(0);
double temp = 100.00;       


// Take in the analog input of the thermistor and return the actual temperature.
double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;  //Kelvin to Celsius        
 Temp = (Temp * 9.0)/ 5.0 + 32.0; //Celsius to F
 return Temp;
}


// This will display the temperature on the LCD Screen.
void displayTempLoop() {
  lcd.clear();
  lcd.print("Temp = ");
  lcd.print(temp);   
  lcd.print(" F");
  lcd.setCursor(0,1);
  lcd.print("SetTemp = ");
  lcd.print(setTemp);           
}


// This controls turning the fridge on and off. 
// It turns off the fridge once it is one degree F below the set temperature and it turns the fridge back on once it is one degree above the set temp.
void fridgeController() {
   if (temp > setTemp) {
    double aboveTemp = setTemp + 1;
    if (temp >= aboveTemp) {
     digitalWrite(8, HIGH); 
    }
  } else {
    double belowTemp = setTemp - 1;
    if (temp <= belowTemp) {
     digitalWrite(8, LOW); 
    }
  }
}

// This will listen for a button change and then change the set temp.
void changeTempLoop() {
  upButtonState = digitalRead(upButtonPin);
  downButtonState = digitalRead(downButtonPin);
  if (upButtonState == HIGH) {
    setTemp++;
  }
  if (downButtonState == HIGH) {
    setTemp--;
  }
}


void setup() {
 Serial.begin(9600);
 pinMode(8, OUTPUT);
 lcd.begin(16, 2);
 pinMode(upButtonPin, INPUT);
 pinMode(downButtonPin, INPUT);
 timer.setInterval(100, displayTempLoop);
 timer.setInterval(1000, fridgeController);
 timer.setInterval(100, changeTempLoop);
}



void loop() {
  val=analogRead(0);
  temp = Thermistor(val);
  timer.run();
}
