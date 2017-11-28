# PAASMER-CoAP-V-1
**Paasmer CoAP V-1** is an SDK with ESP8266 Arduino libraries and Gateway Server for SBC's.

## Overview
**Paasmer CoAP V-1** is a collection of source files that enables you to connect to the Paasmer IoT Platform. It uses **CoAP** protocol (Constrained Application Protocol) as a transport client.

## Features
**Paasmer CoAP V-1** simplifies the controlling of your devices with **Paasmer IoT** via **CoAP** protocol. The SDK is tested with **RaspberryPi** as a CoAP Gateway and **ESP8266** as the End device. 

## CoAP Connection
**Paasmer CoAP V-1** provides a specialized web transfer protocol for use with constrained nodes and constrained networks in the Internet of Things. The protocol is designed for machine-to-machine (M2M) applications such as building automation. 

### Paasmer CoAP Gateway
**Paasmer CoAP V-1** Gateway establishes communication between the End-devices and Paasmer IoT platform. It will connect and controls the End-devices and update the status to the Paasmer IoT platform.

### Paasmer CoAP End-Device
**Paasmer CoAP V-1** End-Device communicates to the Paasmer Gateway and Control GPIO Pins based on Gateway instructions.

## Pre-Requisites 
Registration on the [PAASMER portal](http://developers.paasmer.co) is necessary to connect the devices to the **Paasmer IoT Platform** .

### Gateway Requisites
* SBC Board/System with any flavour of Linux with Java installed. 
* Port forwarding of the Gateway's IP address, [click here](https://www.pcworld.com/article/244314/how_to_forward_ports_on_your_router.html) to know how Port forwarding is done.

### End-Devices Requisites
* ESP8266 Device
* Lastest version of Arduino IDE with ESP devices compatibility installed on your computer. [Arduino software](https://www.arduino.cc/en/main/software) 


## Working with Paasmer-CoAP
* The Paasmer-CoAP implementation consists of Two parts,
	- Gateway
	- End-Point 

* Download the SDK or clone it using the command below.

```
git clone github.com/PaasmerIoT/Paasmer-CoAP-V-1.git
```
* This Will download the Arduino Libraries and Gateway.

### Gateway
* Copy the `Gateway` directory to the SBC/System supporting Java for Gateway implementation.

* To connect the Gateway to Paasmer IoT Platform, go to the `<Gateway_dir>` run the below command.

```
java -cp paasmer-coapgateway-0.0.1-SNAPSHOT-jar-with-dependencies.jar com.paasmer.coap.GatewayServer
```
* This will ask for the UserName and Password of your Paasmer Account.

### End-Point
* Copy the `<End-Point_dir>` to the Arduino Libraries directory. Restart the Arduino IDE, you can find Paasmer-ESP-CoAP examples. 

* The End-Point have **Client** and **Server** part. The **Client** is for registering your device to Paasmer IoT Platform and **Server** is for controlling and collecting feed details.

#### Working with Paasmer-CoAP client
* Go to the `CoapClient` directory open the `CoAPClient.ino` file in the Arduino IDE, Edit the Config file as given below

```
#define devicename "xxxx" 
char feedname[][15]={"feed1","feed2"};
char feedtype[][15]={"sensor","actuator"};

```
* Edit the SSID and Password and enter your Gateway IP address

```
const char* ssid = "SSID";
const char* password = "Passwd";

IPAddress ip(xxx,xxx,xxx,xxx)
```
* Upload the Code to the ESP8266 and open the Serial monitor to get the IP and message `success` to ensure the device is added to the Paasmer Platform.

#### Working with Paasmer-CoAP server

* Go to the `CoapServer` directory open `CoAPServer.ino` file in the Arduino IDE, Edit the Config file with same feeds and desired Pin Numbers as in the Client code.

```
#define devicename "xxxx" 
char feedname[][15]={"feed1","feed2"};
int feedpin[]={16,5,4};
String feedtype[]={"sensor","actuator","actuator"};
```

* Now Upload the Server code to the ESP8266, now you can control the feeds from Paasmer Web UI once the device is connected to the Gateway.


## Known Issues

* With concern for the low memory available for the ESP8266 device, There may be chances for the device to restart. We are working to provide the best user experience.In the upcoming releases, we may fix this. 

## Support

The support forum is hosted on the GitHub, issues can be identified by users and the Team from Paasmer would be taking up requests and resolving them. You could also send a mail to support@paasmer.co with the issue details for a quick resolution. 

## Note
* The Paasmer-CoAP-V-1 utilizes the features provided by libcoap.

