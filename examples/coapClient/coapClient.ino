/*
ESP-COAP Client
*/
#include <ESP8266WiFi.h>
#include "coap_client.h"
#include "config.h"

//instance for coapclient
coapClient coap;

//WiFi connection info
const char* ssid = "SSID";

const char* password = "PASS";

//ip address and default port of coap server in which your interested in
IPAddress ip(xxx,xxx,xxx,xxx);
int port =5683;
char * feed(){
  
char IP[20],data[500],data2[150];
int i=0,udpPort= 5683,j;
IPAddress Board = WiFi.localIP();
sprintf(IP, "%d.%d.%d.%d:%d", Board[0], Board[1], Board[2], Board[3], udpPort);
Serial.println(IP);
j = sizeof(feedname)/sizeof(feedname[0]);
for(i=0;i<j;i++){
  if(i==0)
    sprintf(data,"[{\"name\":\"%s\",\"feeds\":[{\"name\":\"%s\",\n\"type\":\"%s\"},\n",devicename,feedname[i],feedtype[i]);

  if((i<(j-1)) && (i != 0)){
    sprintf(data2,"{\"name\":\"%s\",\n\"type\":\"%s\"},\n",feedname[i],feedtype[i]);
    strcat(data,data2);
    strcpy(data2,"\0");
  }
  if((i==(j-1)) && (i != 0)){
    sprintf(data2,"{\"name\":\"%s\",\n\"type\":\"%s\"}],\"ip_add\":\"%s\"}]",feedname[i],feedtype[i],IP);
    strcat(data,data2);
  }
  
  }
  Serial.println(strlen(data));
  //Serial.println(data);
  return data;
}
// coap client response callback
void callback_response(coapPacket &packet, IPAddress ip, int port);

// coap client response callback
void callback_response(coapPacket &packet, IPAddress ip, int port) {
    char p[packet.payloadlen + 1];
    memcpy(p, packet.payload, packet.payloadlen);
    p[packet.payloadlen] = NULL;

    //response from coap server
 if(packet.type==3 && packet.code==0){
      Serial.println("ping ok");
    }

    Serial.println(p);
}

void setup() {
   
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.println(" ");

    // Connection info to WiFi network
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
    // Print the IP address of client
    Serial.println(WiFi.localIP());

    // client response callback.
    // this endpoint is single callback.
    coap.response(callback_response);

    // start coap client
    coap.start();
  
    char *data = feed();
       
    COAP_CONTENT_FORMAT;
    #define COAP_TEXT_PLAIN "text/plain";
    int get_data = coap.put(ip,port,"devices",data,strlen(data));
    
    
}


void loop() {
    bool state;
  
  
    state= coap.loop();
   
}
