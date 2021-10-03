#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(39,16,2);

float pulse, frequency, capacitance, inductance;
int counter;
void setup(){
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(11, INPUT);
  pinMode(12, OUTPUT);
  lcd.setCursor(2,0);
  lcd.print("Henlo Fren!");
  Serial.println("Henlo Fren!");
  counter = 1;
  delay(800);
}
void loop(){
 digitalWrite(12,HIGH);
 delay(5);
 digitalWrite(12,LOW);
 delayMicroseconds(100);
 pulse = pulseIn(11,HIGH,5000);
 if(pulse > 0.1){

  capacitance = 2.1E-6; //Capacitor value goes here



  frequency = 1.E6/(2*pulse);                                //becos of waifform
  inductance = 1./(sq(3.1416)*4.*sq(frequency)*capacitance);//Actual calculation
  inductance = inductance*1.E6;                            //Changing units

  //serial printing...
  Serial.print("Frequency (Hz): ");
  Serial.println(frequency);
  Serial.print("Inductance (μH): ");
  Serial.println(inductance);

  //LCD printing...
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Freq: ");
  lcd.print(frequency);
  lcd.print("Hz");
  lcd.setCursor(0,1);
  lcd.print("Induct: ");
  lcd.print(inductance);
  lcd.print("uH");

  counter = 1;

  delay(500);
 }
  else{
    
    if(counter == 1){
    Serial.println("No Connection");
    counter = 0;
    }
    
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("No Connection!");
    delay(250);
  }
}
