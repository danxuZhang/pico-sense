#include <WebServer.h>
#include <WiFi.h>
#include <Wire.h>

#include "DEV_Config.h"
#include "Debug.h"
#include "SHTC3.h"

// WiFi Credentials
#include "secrets.h"

// Prometheus Monitoring
const int PROMETHEUS_PORT = 9100;
WebServer server(PROMETHEUS_PORT);

// I2C pins definition
const int SDA_PIN = 8;
const int SCL_PIN = 9;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(2000); // Give serial connection time to establish
  Serial.println("\nStarting up...");

  DEV_ModuleInit();
  SHTC3_Init();

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Prometheus is available on port: ");
  Serial.println(PROMETHEUS_PORT);

  // Set up metrics endpoint
  server.on("/metrics", handleMetrics);
  server.begin();
}

void handleMetrics() {
  int16_t id;
  bool crc_res;
  float temp, hum;
  crc_res = SHTC3_Measurement(&temp, &hum);
  id = SHTC3_Read_Id();
  if (id == -1 || crc_res == false) {
    Serial.printf("Error： Measurement CRC8 check failure \r\n");
  }

  String metrics = "";
  // Prometheus metric format
  metrics += "# HELP temperature_celsius Current temperature in celsius\n";
  metrics += "# TYPE temperature_celsius gauge\n";
  metrics += "temperature_celsius ";
  metrics += String(temp);
  metrics += "\n";

  metrics +=
      "# HELP relative_humidity_percent Current relative humidity percentage\n";
  metrics += "# TYPE relative_humidity_percent gauge\n";
  metrics += "relative_humidity_percent ";
  metrics += String(hum);
  metrics += "\n";

  Serial.print("Handled request: ");
  Serial.printf("SHTC3 0x%x TEMP %.2f RH %.2f\n", id, temp, hum);

  server.send(200, "text/plain", metrics);
}

void loop() {
  server.handleClient();
  delay(100);
}