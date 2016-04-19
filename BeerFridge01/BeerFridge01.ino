#include <math.h>
#include <LiquidCrystal.h>
#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;  //Kelvin to Celsius        
 Temp = (Temp * 9.0)/ 5.0 + 32.0; //Celsius to F
 return Temp;
}

double setTemp = 65.00;
const int upButtonPin = 7;
const int downButtonPin = 6;
int upButtonState = 0;
int downButtonState = 0;     
int val=analogRead(0);      
double temp=Thermistor(val);

void getTempLoop () {
  lcd.print("Temp = ");
  lcd.print(temp);   
  lcd.print(" F");
  lcd.setCursor(0,1);
  lcd.print("SetTemp = ");
  lcd.print(setTemp);           
  lcd.clear();
}


void setup() {
 Serial.begin(9600);
 pinMode(8, OUTPUT);
 lcd.begin(16, 2);
 pinMode(upButtonPin, INPUT);
 pinMode(downButtonPin, INPUT);
 timer.setTime(1000, getTempLoop);
}



void changeTempLoop () {
  upButtonState = digitalRead(upButtonPin);
  downButtonState = digitalRead(downButtonPin);
  if (upButtonState == HIGH) {
    setTemp++;
  }
  if (downButtonState == HIGH) {
    setTemp--;
  }
  delay(100);
}

void fridgeController(double temp,double setTemp) {
   if (temp > setTemp) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }
  delay(5000);
}



void loop() {
  fridgeController(temp, setTemp);
  timer.run()
  changeTempLoop();
}
