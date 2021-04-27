#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 14     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
// pin de la dreta a G14
// Connect pin 2 of the sensor to 3.3V
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)

int h,t,h_2,t_2;




DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,20,4);  //sometimes the LCD adress is not 0x3f. Change to 0x27 if it dosn't work.


// SSID & Password
const char* ssid = "MOVISTAR_AB50"; // Enter your SSID here
const char* password = "9YomYMooH7RoK3qFqxqq"; //Enter your Password here
WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

float read_t(){
  // LLEGEIX LA TEMPERATURA EN CENTIGRADS
  t = dht.readTemperature();
  delay(100);
  return t;
}

float read_h(){
    h = dht.readHumidity();
    delay(100);
    return h;
}
// Handle root url (/)
void handle_root(void);



void setup() {
  Serial.begin(9600);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP()); //Show ESP32 IP on serial
  server.on("/", handle_root);
  server.begin();
  Serial.println("HTTP server started");
  delay(100);
  lcd.init();
  lcd.backlight();            //Activate backlight

  Serial.println("DHTxx test!");

  dht.begin();

  h=read_h();
  t=read_t();
}

void loop() {
  server.handleClient();
  delay(2000);


  h=read_h();
  t=read_t();


  // MIRA SI POT LLEGIR LES DADES DEL SESNOR
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Humitat "); 
  lcd.setCursor(10,0);
  lcd.print(h);
  lcd.setCursor(16,0);
  lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print("Temperatura "); 
  lcd.setCursor(13,1);
  lcd.print(t);
  lcd.setCursor(18,1);
  lcd.print("C");

  delay(1000);

Serial.println(String(read_t()));
}

  // HTML & CSS contents which display on web server
  String HTML_inicio = "<!DOCTYPE html>\
  <html>\
  <META HTTP-EQUIV='Refresh' CONTENT='1'>\
  <body>\
  <h1>PAGINA ESP32 DE ALBERT CAMBRAS </h1>\ ";

  // HTML & CSS contents which display on web server
  String HTML_temp = "<h2>TEMPERATURA:</h2><h1>\ ";

  String HTML_hum = "</h1></h1><h2>HUMITAT:</h2><h1>\ ";

  String HTML_final= "</h1>\
  </body>\
  </html> ";

  void handle_root(){
  server.send(200, "text/html", HTML_inicio+HTML_temp+String(read_t())+HTML_hum+String(read_h())+HTML_final);
  }