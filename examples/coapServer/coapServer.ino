/*
ESP-COAP Server
*/

#include <ESP8266WiFi.h>
#include <coap_server.h>
#include "config.h"

void callback_light(coapPacket &packet, IPAddress ip, int port, int obs);

coapServer coap;

//WiFi connection info
const char* ssid = "xxxx";
const char* password = "xxxx";

int i=0,j=sizeof(feedpin)/sizeof(feedpin[0]);

// CoAP server endpoint URL

void callback_light(coapPacket *packet, IPAddress ip, int port,int obs) {

  // send response
  char p[packet->payloadlen + 1];
  memcpy(p, packet->payload, packet->payloadlen);
  p[packet->payloadlen] = NULL;
  
  int a;

  
  String message(p),x;
    
  if(packet->code == 3){
    for (i=0;i<j;i++){
      
     if(packet->paasmerurl.endsWith(feedname[i])){
          
        if(feedtype[i]== "actuator"){
               if (message == "OFF" || message == "off"){
                      
                      digitalWrite(feedpin[i],LOW);
                      coap.sendResponse(ip,port,"Put Function");
                      message = "\0";
                      packet->paasmerurl="\0";
                      packet->code=0;
                      break;
                }
               else if(message == "ON" || message == "on"){
                      digitalWrite(feedpin[i],HIGH);
                      coap.sendResponse(ip,port,"Put function");
                      message = "\0";
                      packet->paasmerurl="\0";
                      packet->code=0;
                      break;
               } 
               
                
         }
            break;
      }
     
    }
    
  }
  if (packet->code == 1){
     for(i=0;i<j;i++){
      
      if(packet->paasmerurl.endsWith(feedname[i])){        
          char *led= (digitalRead(feedpin[i]))? ((char *) "1") :((char *) "0");
          coap.sendResponse(ip,port,led);
          packet->paasmerurl="\0";
          packet->code=0;
          message = "\0";
 memset(p, 0, sizeof(p));
            break; 
      }
      
    }
    
  }
  
  
}

void setup() {
  yield();
  coap.serialcoap();
  WiFi.begin(ssid, password);
  Serial.println(" ");

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
   
    yield();
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
 
   // LED State
   for (i=0;i<j;i++){
      if(feedtype[i]=="sensor"){
        pinMode(feedpin[i], INPUT);
      }
      else{
        pinMode(feedpin[i],OUTPUT);
      }
   }
 
   char feedpath[50];
   
  // add server url endpoints.
   for (i=0;i<j;i++){
    sprintf(feedpath,"%s/%s",devicename,feedname[i]);
    coap.server(callback_light,feedpath);
    strcpy(feedpath,"\0");
    coap.start();
   }
}

void loop() {
  coap.loop();
  //delay(1000);
}

