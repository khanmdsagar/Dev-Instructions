#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char* ssid = "ALP"; //Enter Wi-Fi SSID
const char* password =  "netflix70"; //Enter Wi-Fi Password
const char indexPage[] PROGMEM = {"<!DOCTYPE html>\n"
"<html>\n"
"<title>Khan Microsystem</title>\n"
"<meta charset=\"UTF-8\">\n"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
"<link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\">\n"
"<link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Raleway\">\n"
"<style>\n"
"body,h1 {font-family: \"Raleway\", sans-serif}\n"
"body, html {height: 100%}\n"
".bgimg {\n"
"    background-image: url('\thttps://www.w3schools.com/w3images/forestbridge.jpg');\n"
"    min-height: 100%;\n"
"    background-position: center;\n"
"    background-size: cover;\n"
"}\n"
".text-center{\n"
"\ttext-align: center;\n"
"}\n"
"</style>\n"
"<body>\n"
"\n"
"<div class=\"bgimg w3-display-container w3-animate-opacity w3-text-white\">\n"
"\n"
"  <div class=\"w3-display-topleft w3-padding-large w3-xlarge\">\n"
"    Khan Microsystem\n"
"  </div>\n"
"  \n"
"  <div class=\"w3-display-middle\">\n"
"    <h1 class=\"w3-jumbo w3-animate-top text-center\">Welcome</h1>\n"
"    <hr class=\"w3-border-grey\" style=\"margin:auto; width:40%\">\n"
"  </div>\n"
"  \n"
"</div>\n"
"\n"
"</body>\n"
"</html>\n"
""};
 
void setup() {
  Serial.begin(115200); //Begin Serial at 115200 Baud
  WiFi.begin(ssid, password);  //Connect to the WiFi network
  
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
      delay(500);
      Serial.println("Waiting to connect...");
  }
  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP
  
  server.on("/", handle_index); //Handle Index page
  
  server.begin(); //Start the server
  Serial.println("Server listening");
}

void loop() {
  server.handleClient(); //Handling of incoming client requests
}

void handle_index() {
  //Print Hello at opening homepage
  server.send(200, "text/html", indexPage);
}
