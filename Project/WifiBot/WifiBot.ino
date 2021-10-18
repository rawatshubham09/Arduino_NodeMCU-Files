#include <ESP8266WiFi.h>

String  i;
WiFiServer server(80);

void setup()
{
  i = "";

  Serial.begin(115200);

  pinMode(16, OUTPUT); // GPIO pin16=D0 of NodeMCU 12E or in place of '16' you can write'D0' directly || -->Connected to motordriver 
  pinMode(5, OUTPUT);  // GPIO pin5=D1 of NodeMCU 12E or in place of '16' you can write 'D0' directly || -->Connected to motordriver
  pinMode(4, OUTPUT);  // GPIO pin4=D2 of NodeMCU 12E or in place of '16' you can write 'D0' directly || -->Connected to motordriver
  pinMode(0, OUTPUT);  // GPIO pin0=D3 of NodeMCU 12E or in place of '16' you can write 'D0' directly || -->Connected to motordriver
    WiFi.disconnect();
  delay(2000);
  Serial.println("Connecting to WIFI");
   WiFi.begin("realme 3 Pro","2e0cbeccd3a4");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }Serial.println("I am Connected");
  Serial.println("My Local IP is : ");
  Serial.print((WiFi.localIP()));
  server.begin();

}


void loop()
{

    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    i = (client.readStringUntil('\r'));
   
    Serial.println(i);
    if (i == "GET /forward HTTP/1.1") {
      digitalWrite(16,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(0,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("forward");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "GET /reverse HTTP/1.1") {
      digitalWrite(16,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(0,HIGH);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("reverse");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "GET /right HTTP/1.1") {
      digitalWrite(16,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(0,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("right");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "GET /left HTTP/1.1") {
      digitalWrite(16,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(0,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("left");
      client.println("</html>");
      client.stop();
      delay(1);

    }
    if (i == "GET /stop HTTP/1.1") {
      digitalWrite(16,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(0,LOW);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("stop");
      client.println("</html>");
      client.stop();
      delay(1);

    }

}
