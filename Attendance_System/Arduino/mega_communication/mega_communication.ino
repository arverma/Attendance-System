#include <SoftwareSerial.h>
SoftwareSerial espSerial =  SoftwareSerial(2,3);
long int temp[100];
int b=0;
int count = 0;                                          // count = 0
char input[24];                                         // character array of size 12 
boolean flag = 0;
int l=0;
int y=1;

String apiKey = "79339NFZKEGLUPUO";
String ssid="unique";
String password ="zzzzzzzz";
boolean DEBUG=true;

void showResponse(int waitTime){
    long t=millis();
    char c;
    while (t+waitTime>millis()){
      if (espSerial.available()){
        c=espSerial.read();
        if (DEBUG) Serial.print(c);
      }
    }
                   
}


boolean thingSpeakWrite(long int value1,long int value2){

  
  
  espSerial.println("AT+CIPMUX=0");
  showResponse(500);
  if (DEBUG)  Serial.println("AT+CIPMUX=0");

  
  String cmd = "AT+CIPSTART=\"TCP\",\"";                  
  cmd += "184.106.153.149";                              
  cmd += "\",80";
  espSerial.println(cmd);
  showResponse(500);
  if (DEBUG) Serial.println(cmd);
  
   
  String getStr = "GET /update?key=";
  getStr += apiKey;
  if(value1>=15010201&&value1<=15010299)
  {
  getStr +="&field3=";
  }
  else
  {
  getStr +="&field1=";
  }
  getStr += String(value1);
  getStr += "\r\n\r\n";
  
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  espSerial.println(cmd);
  showResponse(500);
  if (DEBUG)  Serial.println(cmd);
  
  espSerial.print(getStr);
  delay(200);
  espSerial.print(getStr);
  Serial.print(espSerial);
  showResponse(1000);
  if (DEBUG)  Serial.print(getStr);
  
  espSerial.println("AT+CIPCLOSE");
  if (DEBUG)   Serial.println("AT+CIPCLOSE");
  y++;
}

void setup() {
  Serial.begin(9600);
  DEBUG=true;
  Serial.begin(9600); 
  espSerial.begin(115200);
  espSerial.println("AT+CWMODE=1");
  showResponse(500);
  if (DEBUG)  Serial.println("AT+CWMODE=1");


  espSerial.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");  // set your home router SSID and password
  showResponse(5000);

  Serial.println("Setup completed");
}

void loop() {
  int c=0;

  if(Serial.available())
   {
      count = 0;
      while(Serial.available() && count < 24)          // Read 12 characters and store them in input array
      {
         input[count] = Serial.read();
         count++;
         b=2;
         delay(5);
      }  
      l=l+1;
      Serial.println(l);
   }
      if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='8'&& 
        input[7]=='2'&&input[8]=='1'&&input[9]=='7'&&input[10]=='2')
          { 
        temp[l]=15010206;
      }

      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='7'&& 
        input[7]=='5'&&input[8]=='5'&&input[9]=='2'&&input[10]=='0')
          {
            temp[l]=15010209;
          }
    else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&& 
        input[6]=='8'&&input[7]=='4'&&input[8]=='5'&&input[9]=='4'&&input[10]=='6')
{
        temp[l]=15010210;
      }
      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='8'&& 
        input[7]=='2'&&input[8]=='3'&&input[9]=='2'&&input[10]=='3')
          {   
        temp[l]=15010212;
      }
       else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='7'&& 
        input[7]=='5'&&input[8]=='3'&&input[9]=='2'&&input[10]=='1')
          {
        temp[l]=15010207;
      }
      else
      {
        temp[l]=00000001;
      }
      if(temp[y]>0)
      {
thingSpeakWrite(temp[y],temp[y]); 
while(c<=160)
{

  if(Serial.available())
   {
      count = 0;
      while(Serial.available() && count < 24)          // Read 12 characters and store them in input array
      {
         input[count] = Serial.read();
         count++;
         delay(5);
      }  
      l=l+1;
      Serial.println(l);
   }
      if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='8'&& 
        input[7]=='2'&&input[8]=='1'&&input[9]=='7'&&input[10]=='2')
          { 
        temp[l]=15010206;
      }
      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='7'&& 
        input[7]=='5'&&input[8]=='5'&&input[9]=='2'&&input[10]=='0')
          {
            temp[l]=15010209;
          }
    else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&& 
        input[6]=='8'&&input[7]=='4'&&input[8]=='5'&&input[9]=='4'&&input[10]=='6')
{
        temp[l]=15010210;
      }
      else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='8'&& 
        input[7]=='2'&&input[8]=='3'&&input[9]=='2'&&input[10]=='3')
          {   
        temp[l]=15010212;
      }
       else if(input[0]=='$'&&input[1]=='0'&&input[2]=='0'&&input[3]=='0'&&input[4]=='6'&&input[5]=='8'&&input[6]=='7'&& 
        input[7]=='5'&&input[8]=='3'&&input[9]=='2'&&input[10]=='1')
          {
        temp[l]=15010207;
      }
      else
      {
        temp[l]=00000001;
      }
  c++;
  delay(100);
}
      }
      if(l>=100)
      {
        l=0;
      }
      if(y>=101)
      {
        y=1;
      }
}





