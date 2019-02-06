#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>                                                    //add the soft serial libray

int x=1;
int count = 0;                                          // count = 0
char input[24];                                         // character array of size 12 
boolean flag = 0;  

// Set these to run example.

#define FIREBASE_HOST "attendance-sys-1520055292438.firebaseio.com"

#define FIREBASE_AUTH "8dnEiS5hwfbPfVcRSdJnAfUqBn1QdL7rZ0tv44dP"

#define WIFI_SSID "unique"

#define WIFI_PASSWORD "zzzzzzzz"

int i=0;
int b =0;
String a;
void setup() {
  Serial.begin(9600);
  //myserial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
       }

    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

    
    }

void loop() {


  
   if(Serial.available())
   {
      count = 0;
      while(Serial.available() && count < 24)          // Read 12 characters and store them in input array
      {
         input[count] = Serial.read();
         count++;
         i=2;
         delay(5);
      }
      Serial.print(input);                             // Print RFID tag number 
      
   }
if(i==2){
   if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='8'&& 
        input[7]=='2'&&input[8]=='1'&&input[9]=='7'&&input[10]=='2')
          { 
            a=Firebase.getString("ECE/SEM6/EC333/15010206/attendance");
            b = a.toInt()+1;;
            Firebase.setString("ECE/SEM6/EC333/15010206/attendance",String(b));
      }

      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='7'&& 
        input[7]=='5'&&input[8]=='5'&&input[9]=='2'&&input[10]=='0')
          {
            a=Firebase.getString("ECE/SEM6/EC333/15010209/attendance");
            b=a.toInt()+1;;
            Firebase.setString("ECE/SEM6/EC333/15010209/attendance",String(b));
          }
    else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&& 
        input[6]=='8'&&input[7]=='4'&&input[8]=='5'&&input[9]=='4'&&input[10]=='6')
{
            a=Firebase.getString("ECE/SEM6/EC333/15010210/attendance");
            b=a.toInt()+1;;
            Firebase.setString("ECE/SEM6/EC333/15010210/attendance",String(b));
      }
      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='8'&& 
        input[7]=='2'&&input[8]=='3'&&input[9]=='2'&&input[10]=='3')
          { 
            a=Firebase.getString("ECE/SEM6/EC333/15010212/attendance");
            b=a.toInt()+1;;
            Firebase.setString("ECE/SEM6/EC333/15010212/attendance",String(b));  
      }
       else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='7'&& 
        input[7]=='5'&&input[8]=='3'&&input[9]=='2'&&input[10]=='1')
          {
            a=Firebase.getString("ECE/SEM6/EC333/15010207/attendance");
            b=a.toInt()+1;
            Firebase.setString("ECE/SEM6/EC333/15010207/attendance",String(b));
      }
      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='9'&&input[6]=='2'&& 
        input[7]=='5'&&input[8]=='7'&&input[9]=='9'&&input[10]=='0')
          {
            a=Firebase.getString("ECE/SEM6/EC333/15010203/attendance");
            b=a.toInt()+1;
            Firebase.setString("ECE/SEM6/EC333/15010203/attendance",String(b));
      }
      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='8'&& 
        input[7]=='2'&&input[8]=='8'&&input[9]=='1'&&input[10]=='0')
          {
            a=Firebase.getString("ECE/SEM6/EC333/15010205/attendance");
            b=a.toInt()+1;
            Firebase.setString("ECE/SEM6/EC333/15010205/attendance",String(b));
      }
      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='7'&& 
        input[7]=='5'&&input[8]=='5'&&input[9]=='2'&&input[10]=='8')
          {
            a=Firebase.getString("ECE/SEM6/EC333/15010208/attendance");
            b=a.toInt()+1;
            Firebase.setString("ECE/SEM6/EC333/15010208/attendance",String(b));
      }
      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='8'&& 
        input[7]=='4'&&input[8]=='4'&&input[9]=='5'&&input[10]=='9')
          {
            a=Firebase.getString("ECE/SEM6/EC333/15010213/attendance");
            b=a.toInt()+1;
            Firebase.setString("ECE/SEM6/EC333/15010213/attendance",String(b));
      }
      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='7'&&input[6]=='6'&& 
        input[7]=='7'&&input[8]=='7'&&input[9]=='2'&&input[10]=='0')
          {
            a=Firebase.getString("ECE/SEM6/EC333/15010202/attendance");
            b=a.toInt()+1;
            Firebase.setString("ECE/SEM6/EC333/15010202/attendance",String(b));
      }
      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='4'&& 
        input[7]=='4'&&input[8]=='5'&&input[9]=='6'&&input[10]=='6')
          {
            a=Firebase.getString("ECE/SEM6/EC333/15010204/attendance");
            b=a.toInt()+1;
            Firebase.setString("ECE/SEM6/EC333/15010204/attendance",String(b));
      }
      i=0;
}

      if (Firebase.failed()){ // Check for errors 
        Serial.print("setting /number failed:");
        Serial.println(Firebase.error());
        return;
      }
      delay(300);
       }


