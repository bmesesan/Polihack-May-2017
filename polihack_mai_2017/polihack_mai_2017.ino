
#include <Servo.h>
Servo servo;

float tempC;
int pos = 90;
char inSerial[25];
int ledAlbastru = 8;
int ledVerde = 9;
int ledRosu = 10;
int ledPin = 13;
int fanl = 5;
int pintx = 1;
int pinrx = 0;
int pinServo = 6;
int tempPin = 0;
void Check_LEDS(char inStr[]);
void allpinslow();
void setup()
{ 
  Serial.begin(9600); 
  pinMode(ledPin,OUTPUT);
  pinMode(fanl, OUTPUT);
  servo.attach(pinServo);
  pinMode(pintx,OUTPUT);
  pinMode(pinrx,INPUT);
  pinMode(ledAlbastru, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRosu, OUTPUT);
  allpinslow();
}
void Check_Protocol(char inSerial[]);
void loop(){
      int i=0;
      delay(100);
      tempC = analogRead(tempPin);
      tempC = (5.0*tempC*100.0)/1024.0;
      if (tempC>25)
      {
        digitalWrite(ledPin, HIGH);
      }
      else
      {
        digitalWrite(fanl,HIGH);
        digitalWrite(ledPin,LOW);
        for(i=pos;i<90;i++)
        {
            servo.write(i);
            delay(10);//rotim servo-ul//
        }
        pos=90;
      }
      delay(1000);
      if(Serial.available()>0)
       {     while(Serial.available()>0)
            {
                 inSerial[i]=Serial.read();
                 i++;
            }
       }
       inSerial[i]='\0';
       Check_Protocol(inSerial);
}



void allpinslow()
{
  digitalWrite(ledAlbastru, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledRosu, LOW);
}

void Check_Protocol(char inSerial[])
{
  int m = 0;
  int i = 0;
   Check_LEDS(inSerial);
  if(strcmp(inSerial,"inchide geam")==0)
  {
    for(i=pos;i<90;i++)
    {
      servo.write(i);
      delay(10);//rotim servo-ul//
    }
    pos = 90;
    digitalWrite(ledPin,LOW);
    Serial.println("\nSe deschide geamul.");
    for(m=0;m<11;m++)
    {
      inSerial[m]=0;
    }
    i=0;
  }
  if(strcmp(inSerial,"porneste ventilator")==0)
  {
    digitalWrite(fanl,LOW);
    digitalWrite(ledPin,LOW);
    Serial.println("\nSe deschide ventilatorul.");
    for(m=0;m<11;m++)
    {
      inSerial[m]=0;
    }
    i=0;
  }
 if(strcmp(inSerial,"deschide geam")==0)
  {
    for(i=pos;i>0;i--)
    {
      servo.write(i);
      delay(10);//rotim servo-ul//
    }
    pos = 0;
    digitalWrite(ledPin,LOW);
    Serial.println("\nSe inchide geamul.");
    for(m=0;m<11;m++)
    {
      inSerial[m]=0;
    }
    i=0;
  }
  if(strcmp(inSerial,"opreste ventilator")==0)
  {
    digitalWrite(fanl,HIGH);
    digitalWrite(ledPin,LOW);
    Serial.println("\nSe inchide ventilatorul.");
    for(m=0;m<11;m++)
    {
      inSerial[m]=0;
    }
    i=0;
  }
   else{
    for(m=0;m<11;m++){
      inSerial[m]=0;
    }
    i=0;
  }
}


void Check_LEDS(char inStr[])
{
  int i = 0;
  int m = 0;
  Serial.println(inStr);
  if(strcmp(inStr,"Cafea Mare")==0)
  {
    allpinslow();
    digitalWrite(ledRosu, HIGH);
    Serial.println("Led rosu on");
    for(m=0;m<11;m++)
    {
      inStr[m]=0;
    }
    i=0;             
  }
  if(strcmp(inStr,"Suc de mere")==0)
  {
    allpinslow();
    digitalWrite(ledVerde, HIGH);
    Serial.println("Led verde on");
    for(m=0;m<11;m++)
    {
      inStr[m]=0;
    }
    i=0;
  }
  if(strcmp(inStr,"Cafea scurta")==0)
  {
    allpinslow();
    digitalWrite(ledAlbastru,HIGH);
    Serial.println("Led albastru on");
    for(m=0;m<11;m++)
    {
      inStr[m]=0;
    }
    i=0;
  }
  if(strcmp(inStr,"Cappuccino")==0)
  {
    allpinslow();
    digitalWrite(ledAlbastru,HIGH);
    digitalWrite(ledRosu,HIGH);
    Serial.println("Led magenta on");
    for(m=0;m<11;m++)
    {
      inStr[m]=0;
    }
    i=0;
  }
  if(strcmp(inStr,"Apa minerala")==0)
  {
    allpinslow();
    digitalWrite(ledAlbastru,HIGH);
    digitalWrite(ledVerde,HIGH);
    Serial.println("Led cien on");
    for(m=0;m<11;m++)
    {
      inStr[m]=0;
    }
    i=0;
  }
  if(strcmp(inStr,"Lemon Tea")==0)
  {
    allpinslow();
    digitalWrite(ledRosu,HIGH);
    digitalWrite(ledVerde,HIGH);
    Serial.println("Led galben on");
    for(m=0;m<11;m++)
    {
      inStr[m]=0;
    }
    i=0;
  }
}
