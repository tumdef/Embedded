#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;
int pos = 0;

const byte NONE = 0;
const byte LEFT = 1;
const byte UP = 2;
const byte RIGHT = 3;
const byte DOWN = 4;
const byte SELECT = 5;

const byte keypadPin = A0;
byte key = 0;

void setup() {
Serial.begin(9600);
while (!Serial) { ; }
Serial.println(F("Start\n"));
initialDisplay();
pinMode(keypadPin, INPUT_PULLUP);// sets analog pin for input
pinMode(2, OUTPUT); //vcc => pin 2
myservo.attach(7); // servo => pin 7
}

void loop()
{
digitalWrite(2, HIGH);
key = getKey();
if (key==LEFT) {Serial.println("LEFT");}
if (key==RIGHT) {Serial.println("RIGHT");}
if (key==UP) 
{
  Serial.println("UP");
  // เมื่อกดปุ่มขึ้น เซอร์โวจะยกไม้ขึ้น แสดงข้อความต้อนรับ แล้วรอ 5 วินาที จากนั้นจะเอาไม้กั้นลง
  lcd.clear();
  myservo.write(90);
  lcd.print("Welcome");
  delay(5000);
  myservo.write(-90);
  initialDisplay();
 }
if (key==DOWN) {Serial.println("DOWN");}
if (key==SELECT) {Serial.println("SELECT");}
delay(100);
}

byte getKey()
{
int val = 0;
byte button = 0;
val = analogRead(keypadPin);
button = NONE;
if (val <=20) { button = LEFT; }
else if ((val >=100) && (val <=200)){button = UP; }
else if ((val >=300) && (val <=400)){button = DOWN; }
else if ((val >=500) && (val <=600)){button = RIGHT; }
else if ((val >=700) && (val <=800)){button = SELECT; }
return button;
}

void initialDisplay()
{
lcd.init();
lcd.backlight(); //คำสั่งเปิดไฟแบล็คไลท์ 
lcd.print("Parking Lot");
 delay(1000); // คำสั่งหน่วงเวลา 1000 ms หรือ 1 วินาที
}
