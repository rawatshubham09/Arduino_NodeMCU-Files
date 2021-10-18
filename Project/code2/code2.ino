#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
#define BAUDRATE 57600
#define LED 12
#define ATT_TH 90
int R_motor1 = A0;
int R_motor2 = A1;
int L_motor1 = A2;
int L_motor2 = A3;
byte payloadData[32] = {0};
byte checksum=0,generatedchecksum=0,Poorquality,Attention;
int  Att_Avg=0,Plength;
int  k=0,j=0;
int flag=0;
int sig;
int val1=0,val2=0,val3=0,val4=0;
/**************************************************/
void lcd_init()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("NeuroskyMindwave");
  lcd.setCursor(0, 1);
  lcd.print("Robot    Control");
  delay(5000);
  lcd.clear();
}
/**************************************************/
void move_f()
{
  digitalWrite(R_motor1,LOW);digitalWrite(R_motor2,HIGH);
  digitalWrite(L_motor1,LOW);digitalWrite(L_motor2,HIGH);
}
/**************************************************/
void move_s()
{
  digitalWrite(R_motor1,LOW);digitalWrite(R_motor2,LOW);
  digitalWrite(L_motor1,LOW);digitalWrite(L_motor2,LOW);
}
/**************************************************/
void setup() 
{
   Serial.begin(BAUDRATE);           // USB
   pinMode(LED, OUTPUT);
   lcd_init();
   lcd.setCursor(0, 0);
   lcd.print("Signal : ");
   lcd.setCursor(0, 1);
   lcd.print("Value  : ");
   digitalWrite(LED, HIGH);
   lcd.setCursor(15,0);lcd.print("-");
   pinMode(R_motor1,OUTPUT);pinMode(R_motor2,OUTPUT);
   pinMode(L_motor1,OUTPUT);pinMode(L_motor2,OUTPUT);
   move_s();
}
/**************************************************/
byte ReadOneByte()           // One Byte Read Function
{
  int ByteRead;
  while(!Serial.available());
  ByteRead = Serial.read();
  return ByteRead;
}
/**************************************************/
void loop()                     // Main Function
{
  while (1)
  {
    if(ReadOneByte() == 170)        // AA 1 st Sync data
    {
      if(ReadOneByte() == 170)      // AA 2 st Sync data
      {
        Plength = ReadOneByte();
        if(Plength == 32)   // Big Packet
        { 
          generatedchecksum = 0;
          for(int i = 0; i < Plength; i++) 
          {  
            payloadData[i]     = ReadOneByte();      //Read payload into memory
            generatedchecksum  += payloadData[i] ;
          }
          generatedchecksum = 255 - generatedchecksum;
          checksum  = ReadOneByte();
        
          if(checksum == generatedchecksum)        // Varify Checksum
          {
            Poorquality  = payloadData[1];
            Attention    = payloadData[29];
            sig = (200-Poorquality)/2;
            lcd.setCursor(9,0);lcd.print(sig);lcd.print("  ");
            lcd.setCursor(9,1);lcd.print(Attention);lcd.print("  ");
            Attention_Fun(Attention);
           }
          } 
        }
      }
    }         
 } 
/**************************************************/
void Attention_Fun(byte data1)
{
  if (Poorquality == 0)
  {            
    //val4=val3;
    //val3=val2;
    //val2=val1;
    //val1=data1;
    //Att_Avg = (val1+val2+val3+val4)/4;
    Att_Avg = data1;
    if (Att_Avg >= ATT_TH)
    {
        digitalWrite(LED, LOW);
        lcd.setCursor(15,0);lcd.print("1");
        val1=0;val2=0;val3=0;val4=0;
        move_f();
    }
    else if (Att_Avg < ATT_TH)
    {
        digitalWrite(LED, HIGH);
        lcd.setCursor(15,0);lcd.print("0");
        val1=0;val2=0;val3=0;val4=0;
        move_s();
    }
  }
  else
  {
    lcd.setCursor(15,0);lcd.print("-");
    move_s();
  } 
}
/**************************************************/
