//www.elegoo.com
//warningdist16.09.23
extern int servoPin;
extern const byte Trig, Echo;
#include <Servo.h> //servo library
Servo myservo; // create servo object to control servo
#define warningdist 25

int ABS = 255;

#include <NewPing.h>
#define warningdist 25
NewPing sonar(15, 14, 200);
long middleDistance, rightDistance, leftDistance;
int forangle = 94;
int leftangle = 170;
int rightangle = 15;

extern int ENA;
extern int ENB;
extern int in1;
extern int in2;
extern int in3;
extern int in4;

void _mForward()
{
    analogWrite(ENA,ABS);
    analogWrite(ENB,ABS);
    digitalWrite(in1,HIGH);//digital output
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    Serial.println("go forward!");
}

void _mBack()
{
    analogWrite(ENA,ABS);
    analogWrite(ENB,ABS);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    Serial.println("go back!");
}

void _mleft()
{
    analogWrite(ENA,ABS);
    analogWrite(ENB,ABS);
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    Serial.println("go left!");
}

void _mright()
{
    analogWrite(ENA,ABS);
    analogWrite(ENB,ABS);
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    Serial.println("go right!");
}
void _mStop()
{
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
    Serial.println("Stop!");
}


void setup() {
  Serial.begin (9600);
  // Set the pin directions
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  myservo.attach(servoPin);

}



void loop() 
{ 
    myservo.write(forangle);//setservo position according to scaled value
    //delay(5); 
    middleDistance = sonar.ping_cm();
    #ifdef send
    Serial.print("middleDistance=");
    Serial.println(middleDistance);
    #endif

    if(middleDistance<=warningdist)
    {     
      _mStop();
      delay(500);                         
      myservo.write(rightangle);          
      delay(1000);      
      rightDistance = sonar.ping_cm();

      #ifdef send
      Serial.print("rightDistance=");
      Serial.println(rightDistance);
      #endif

      delay(500);
       myservo.write(forangle);              
      delay(1000);                                                  
      myservo.write(leftangle);              
      delay(1000); 
      leftDistance = sonar.ping_cm();

     #ifdef send
      Serial.print("leftDistance=");
      Serial.println(leftDistance);
      #endif

      delay(500);
      myservo.write(forangle);              
      delay(1000);
      if(rightDistance>leftDistance)  
      {
        _mright();
        delay(360);
       }
       else if(rightDistance<leftDistance)
       {
        _mleft();
        delay(360);
       }
       else if((rightDistance<=warningdist)||(leftDistance<=warningdist))
       {
        _mBack();
        delay(180);
       }
       else
       {
        _mForward();
       }
    }  
    else
        _mForward();                     
}


