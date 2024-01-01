//Library yang digunakan
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

//Wifi yang digunakan
#define WIFI_SSID "4GMIFI_9014"
#define WIFI_PASSWORD "Buatkuliah"

//broker
String mqttBroker = "test.mosquitto.org";

//inisialisasi
WiFiClient client;
PubSubClient mqtt(client);

void setup()
{
  Serial.begin(9600);
  connectWifi();
  mqtt.setServer(mqttBroker.c_str(), 1883);
}

void loop()
{
  //menghubungkan ulang mqtt jika terputus
  if (!mqtt.connected())
  {
    connect_mqtt();
    Serial.println("MQTT Connected");
    
  }
  //pengriman pesan ke broker mqtt
  mqtt.loop();
  mqtt.publish("esp32/p0katenakz", "Terhubung");
  Serial.println("Pesan Terkirim");
  delay(700);
}

void connect_mqtt()
{
  while (!mqtt.connected())
  {
    Serial.println("Connecting MQTT...");
    if (mqtt.connect("esp32"))
    {
      mqtt.subscribe("esp32/p0katenakz");
    }
  }
}

void connectWifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
