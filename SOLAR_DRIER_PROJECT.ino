#include <Stepper.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Key.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT11 
LiquidCrystal_I2C lcd(0x27,20,4);
DHT dht(DHTPIN, DHTTYPE);
double ldr1=A0, ldr2=A1;
double Setpoint=500,Input,Output,ITerm,lastError;
double Kp=2.32, Ki=2240, Kd=0;
int sampleTime=1000;
float temperature=0, humidity=0;
double value1,value2, tolerance=50;
#define relay A3
#define lswtch1 3
#define lswtch2 4
int c=0;
    //EEPROM VARIABLES...
int tempAddress = 0;
int humAddress = 60;


//control variables
int limTemp, limHum;
char key;
const byte ROWS=4,COLS=3;
char keys[ROWS][COLS]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}  
};
  byte rowPins[ROWS]={6,5,1,0};  //
  byte colPins[COLS]={13,12,7,};
  //keypad object
  Keypad keypad=Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);
 unsigned long previous_key_time=0, key_hold_time=2000;
    unsigned long lastTime=0;
        ///////motor pins
int pin1=8;
int pin2=9;
int pin3=10;
int pin4=11;
           // int stepsPerRevolution=200;
              int stepsPerRevolution=25;
  //motor object
  Stepper motor(stepsPerRevolution,8,9,10,11);  
unsigned long tym;
unsigned long intv_temp_rcd = 1; //record temp after every 1 second
unsigned long prev_temp_rcd = 0;
unsigned long tt;
double previous_ldr_time=0, ldr_tym=1000;
  byte degree[8] = {
  B00100,
  B01010,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000
};
  
void setup() {
    Serial.begin(9600);
    keypad.addEventListener(keypadEvent);  
  dht.begin();
 lcd.init();
 lcd.backlight();
  pinMode(2, INPUT);
  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
  
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT); 
  
 pinMode(relay, OUTPUT);
 digitalWrite(relay, HIGH);
 //limit switch
  pinMode(lswtch1, INPUT);
  digitalWrite(lswtch1, HIGH);
  pinMode(lswtch2, INPUT);
 digitalWrite(lswtch2, HIGH);

   lcd.clear();
     lcd.createChar(0, degree);
        motor.setSpeed(30);
          //    homing();
      retrievePrevious();
    homing();
}


void loop() {
 tym=millis()/1000;
  key = keypad.getKey();
   int i,ldre,ldrw,sum1=0,sum2=0;

   //FINDING AVERAGE OF LDRE
for(i=0; i<5; i++){
  ldre=analogRead(A0);
  sum1 +=ldre;
  value1=sum1/5;
  }
 
 //FINDING AVERAGE OF LDRW
  for(i=0; i<5; i++){
  ldrw=analogRead(A1);
  sum2 +=ldrw;
  value2=sum2/5;
  }
   
  int Input=value1-value2;

  //calling pid function
 Output=PID_Control(Input);

int speed1=map(Output,2147483648,4294967296,30,60);     //mapping PID output as speed parameter
 motor.setSpeed(speed1);
 
 if(Input==0){
    motor.step(0);
 }
 
 else if(abs(Input)>tolerance){
  int dir=Input>0?1:-1;
  int le =digitalRead(lswtch1);  //reading east limit swtch
  int lw =digitalRead(lswtch2);   //reading west limit swtch
 
  if(le==HIGH&&lw==HIGH){       //Limit swtches are  not pressed go either west or east
   motor.step(dir);
  }
  else if(le==LOW&&dir>0){        //Limit swtch east is pressed only go west
   motor.step(dir);
  }
  else if(lw==LOW&&dir<0){        //Limit swtch west is pressed only go east
   motor.step(dir);
  }
 
 }
  
else{ //do nothing if input<tolerance
  }
 
//recording temperature every  second
  if (tym - prev_temp_rcd > intv_temp_rcd) {
    prev_temp_rcd = tym;

    temp_Humidity_Display();
       
  }
  
  // checking events every 2 seconds
  if (millis()-previous_key_time>key_hold_time){
    previous_key_time=millis();
keypadEvent(key);
  }
  
}
//homing codes
void homing(){
  int x=digitalRead(lswtch1);

 while(x==HIGH&&c==0){    //checking if limit switch1 is pressed
  int x=digitalRead(lswtch1);
  motor.step(-1);     // moving to the east

  if(x==LOW) c=1;   //if limit switch1 is pressed set c to 1 to stop the while loop
  }
x=digitalRead(lswtch1);
if(x==LOW){   //if limit switch1 is pressed step to homming position
  c=1;
  delay(1000);    //for debounce
   motor.step(67);
}
}
