int ls=8; //left sensor:
int rs=7; //right sensor:
int lm1=13; //left motor postive:
int lm2=12; // left motor negative:
int rm1=11; //right motor postitive:
int rm2=10; //right mototr negative:
//int gm1=; // gripper motor postitive:
//int gm2=8; //gripper motor negative:
int count=1;
void line_follow();

void setup() {
 pinMode(ls, INPUT);
 pinMode(rs, INPUT);
pinMode(lm1, OUTPUT);
pinMode(lm2, OUTPUT);
pinMode(rm1, OUTPUT);
pinMode(rm2, OUTPUT);
//pinMode(gm1, OUTPUT);
//pinMode(gm2, OUTPUT);
Serial.begin(9600);
}
void forward()
{
 digitalWrite(lm1,HIGH);
  digitalWrite(lm2, LOW);
   digitalWrite(rm1,HIGH);
    digitalWrite(rm2,LOW);
        Serial.println(" forward");
    
}
void left()
{
 digitalWrite(lm1,LOW);
  digitalWrite(lm2, LOW);
   digitalWrite(rm1,HIGH);
    digitalWrite(rm2,LOW);
        Serial.println(" left");
    
}
void right()
{
 digitalWrite(lm1,HIGH);
  digitalWrite(lm2, LOW);
   digitalWrite(rm1,LOW);
    digitalWrite(rm2,LOW);
        Serial.println(" right");
    
}
void stop1()
{
 digitalWrite(lm1,LOW);
  digitalWrite(lm2, LOW);
   digitalWrite(rm1,LOW);
    digitalWrite(rm2,LOW);
        Serial.println(" stop");
    
}
void grip()
{ //digitalWrite(gm1,HIGH);
  //digitalWrite(gm2,LOW);
  //delay(2000);//adjust according to motor rpm:
Serial.println("grip");
}
void release1()
{ //digitalWrite(gm1,LOW);
//digitalWrite(gm2,HIGH);
//delay(2000); //adjust yourself:
Serial.println("released");
}
void rotate()
{ digitalWrite(lm1,HIGH);
digitalWrite(lm2,LOW);
digitalWrite(rm1,LOW);
digitalWrite(rm2,HIGH);
delay(2100);
}
void loop()
{
  
  
  line_follow();
  
  
  }

  void line_follow()
  {
    int l=digitalRead(ls);
      Serial.println(l);
  int r=digitalRead(rs);
      Serial.println(r);
          Serial.println(count);
    
    
  if(l==1&&r==1)
  { forward();
  }
  if(l==1&&r==0){
    right();
  }
  if(l==0&&r==1)
  { left();
  }
  if(l==0&&r==0)
  { stop1();
  delay(2000);
  if(count==1)
  { grip();
  delay(2000);
  rotate();
  count=1;
  line_follow();
  }  
  else if(count==2)
  { release1();
  delay(1000);
  count = 1;
  rotate();
  line_follow();
  } 
  }
  }
  
