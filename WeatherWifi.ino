/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

/*****Necessary Adafruit libraries***/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306_mod.h"

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
/**********************************/

#include <WiFi.h>

const char* ssid     = "Tufts_Wireless";
const char* password = "";

const char* title = "Blinkblob Weather Stream";    //Stream title (not used in the sketch)
const char* alias = "blinkblob_weather";          // stream alias: you can see the data by accessing silklab.fctn.io:8080/big_t
const char* host = "silklab.fctn.io"; //10.42.0.1 //http://silklab.fctn.io
const char* streamId   = "OXB11OE3zLHxJGgbBVjMhDkppdy"; // the public key
const char* privateKey = "MRE669bwa8U2PLjYQOyztwqzzAn"; // private key

bool CURRENT_STATE = digitalRead(14);

/**Weather******************/
float Temperature =0;
float TemperatureMoyenne =0;
int TensionAnalog =0;
/**Weather******************/

//Initialize webserver
WiFiServer server(80);

void setup()
{
  // As usual start serial for debugging purposes
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /*******Adafrui tDisplay Setup*******/
    bool CURRENT_STATE = digitalRead(14);
    pinMode(14, INPUT_PULLUP);

    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    // init done
    
    // Show image buffer on the display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    display.display();
    delay(2000);
  
    // Clear the buffer.
    display.clearDisplay();
  
    // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("0");
    display.display();
    /*******End of Adafruit Display Setup*******/

    /******* Web Server Setup ******************/
    pinMode(5, OUTPUT);      // set the LED pin mode
    server.begin();
    /******* End of Web Server Setup ******************/

}

// A fake temperature value to log
float value = 0;
String conversion = "celcius";


float get_temp(String weather_type)
{

    
    //  Get CELCIUS
      TemperatureMoyenne = 0;
      for (int i=1;i<=5;i++)
      {
        TensionAnalog = analogRead(A0);   
        TemperatureMoyenne =  TemperatureMoyenne + ( ( (TensionAnalog /204.8)  -0.5) / 0.01);
      }
    
      Serial.print(TemperatureMoyenne);
      Temperature = TemperatureMoyenne/5;
    
      if (weather_type == "farenheit")
      {
        Temperature = (Temperature*9/5) + 32;
        return Temperature;
      }
      else
      {
        // If farenheight isn't passed in, return celcius (default)
        return Temperature;
      }
   
}

void display_temp(float temp)
{

  
    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    // init done
    
    // Show image buffer on the display hardware.
    // Since the buffer is intialized with an Adafruit splashscreen
    // internally, this will display the splashscreen.
    display.display();
    delay(2000);
  
    // Clear the buffer.
    display.clearDisplay();
  
    // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(temp);
    display.display();
  return;

}


/*String web_server()
{
  WiFiClient client = server.available();
  // if you get a client,
  if (client) 
  {
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to change to celcius");
            client.print("Click <a href=\"/F\">here</a> to change to celcius");
            client.print(conversion);


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          return "celcius";                   // print it out the serial monito

        }
        else if (currentLine.endsWith("GET /F")) {
          return "farenheit";     
      }
    }

}
}
*/
}

void loop()
{
    delay(5000);

    // Intialize webserver
    //conversion = web_server();
    
    // Get weather and display it
    value = get_temp(conversion);
    display_temp(value);

      WiFiClient client_server = server.available();

if (client_server) 
  {
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client_server.connected()) {            // loop while the client's connected
      if (client_server.available()) {             // if there's bytes to read from the client,
        char c = client_server.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client_server.println("HTTP/1.1 200 OK");
            client_server.println("Content-type:text/html");
            client_server.println();

            // the content of the HTTP response follows the header:
            client_server.print("Click <a href=\"/H\">here</a> to change to celcius\n");
            client_server.println("Click <a href=\"/F\">here</a> to change to farenheit\n");
            client_server.println("current mode:\n");
            client_server.println(conversion);


            // The HTTP response ends with another blank line:
            client_server.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          return "celcius";                   // print it out the serial monito

        }
        else if (currentLine.endsWith("GET /F")) {
          return "farenheit";     
      }
    }

}
}

    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
//    WiFiClient client;
    const int httpPort = 8080;
    if (!client_server.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = "/input/";
    url += streamId;
    url += "?private_key=";
    url += privateKey;
    url += "&temp=";    // here goes the name of the variable you specified in "Fields"
    url += value;

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    // we built the URI (here called url) before, now we include it in the HTTP request
    client_server.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    // Let's wait and see if we get a HTTP response from the server (database)
    unsigned long timeout = millis();

    // check if response is present
    while (client_server.available() == 0) {
      // but wait no more than 5 seconds
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client_server.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client_server.available()) {
        String line = client_server.readStringUntil('\r');
        Serial.print(line);
    }

    


    
    Serial.println();
    Serial.println("closing connection");
}
