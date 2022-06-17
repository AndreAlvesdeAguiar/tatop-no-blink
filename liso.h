#define BLYNK_TEMPLATE_ID "TMPLZkLdPvaF"
#define BLYNK_DEVICE_NAME "teste"
#define BLYNK_AUTH_TOKEN "QGJroTkiW9YnW9Xij1w0Vy3EZhCfZ7sB"

#define BLYNK_PRINT Serial

//
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//
//memorial de calculo
//moiture -> 35
//dht22 -> 34
// led 1 -> 12
// led 2 -> 13
// led 3 -> 4

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

//
#include <Wire.h>
#include <Adafruit_GFX.h>

//

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Okura&Aguiar";
char pass[] = "*welcome03";

const int air = 2800;
const int water = 1584;

int soilread;     //analogRead soilpin
int soilpercent;
int soilpin = 35;

#define DHTPIN 5    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor1()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void sendSensor2()
{
  soilread = analogRead(soilpin);
  soilpercent = map(soilread, air, water, 0, 100);
  Serial.println(soilread);
  Serial.println(soilpercent);
  delay(10);

  Blynk.virtualWrite(V9, soilpercent);
  Blynk.virtualWrite(V8, soilread);

}


void setup()
{


  delay(2000);

  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();


  pinMode(13, OUTPUT);                          //Definição dos pinos a serem utilizados (botão estará na porta 21)
  pinMode(12, OUTPUT);
  pinMode(4, INPUT);
  // Setup a function to be called every second
  timer.setInterval(2000L, sendSensor1);
  timer.setInterval(5000L, sendSensor2);
}

void loop()
{


  //
  Blynk.run();
  timer.run();
}
