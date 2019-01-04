#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ArduinoOTA.h>
#include <WS2812FX.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

int ledPin = D8;

#define LED_COUNT 60
#define LED_PIN 1
#define CONFIG_BUTTON D3

#define AIO_SERVER      "io.adafruit.com" // ON LAISSE L'ADRESSE
#define AIO_SERVERPORT  1883 // ON LAISSE LE PORT
#define AIO_USERNAME    "USER_NAME" // NOM DU USER ADAFRUIT.IO
#define AIO_KEY         "ADAFRUIT.IO KEY" // CLÉ ADAFRUIT.IO

#define SPEED_MIN 10
#define SPEED_MAX 65535

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe ruban = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/ruban");

Adafruit_MQTT_Subscribe puissance = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/puissance");

Adafruit_MQTT_Subscribe animation = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/animation");

Adafruit_MQTT_Subscribe vitesse = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/vitesse");

void MQTT_connect();

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ws2812fx.init();
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(CONFIG_BUTTON, INPUT);
  //ledstart();
  WiFiManager wifiManager;
  wifiManager.autoConnect("GOOG-LED");
  //WiFi.begin(WLAN_SSID, WLAN_PASS);
  mqtt.subscribe(&ruban);
  mqtt.subscribe(&puissance);
  mqtt.subscribe(&animation);
  mqtt.subscribe(&vitesse);
  ws2812fx.init();
  ws2812fx.setBrightness(125);
  ws2812fx.setColor(GREEN);
  ws2812fx.start();
  ArduinoOTA.setHostname("OTA-GOOG-LED");
  ArduinoOTA.begin();
}

uint32_t x = 0;

void loop() {
  if ( digitalRead(CONFIG_BUTTON) == LOW ) {
    WiFiManager wifiManager;
     ws2812fx.init();
     ws2812fx.setBrightness(255);    
     ws2812fx.setColor(RED);
     ws2812fx.service();
      digitalWrite(ledPin, LOW);
    //wifiManager.resetSettings();
    
    if (!wifiManager.startConfigPortal("GOOG-LED")) {
      delay(3000);
      ESP.reset();
      delay(5000);
    }
  }
  ws2812fx.service();
    ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }
  });
  ArduinoOTA.onEnd([]() {
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
  });
  ArduinoOTA.onError([](ota_error_t error) {
    if (error == OTA_AUTH_ERROR) {
    } else if (error == OTA_BEGIN_ERROR) {
    } else if (error == OTA_CONNECT_ERROR) {
    } else if (error == OTA_RECEIVE_ERROR) {
    } else if (error == OTA_END_ERROR) {
    }
  });
  ArduinoOTA.handle();
  MQTT_connect();
  digitalWrite(ledPin, HIGH);
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(10))) {

    if (subscription == &ruban) {

      if (strcmp((char *)ruban.lastread, "rouge") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(RED);
      }
      if (strcmp((char *)ruban.lastread, "vert") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(GREEN);
      }
      if (strcmp((char *)ruban.lastread, "bleu") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(BLUE);
      }
      if (strcmp((char *)ruban.lastread, "jaune") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(YELLOW);
      }
      if (strcmp((char *)ruban.lastread, "majenta") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(MAGENTA);
      }
      if (strcmp((char *)ruban.lastread, "cyan") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(CYAN);
      }
      if (strcmp((char *)ruban.lastread, "blanc") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(WHITE);
      }
      if (strcmp((char *)ruban.lastread, "noir") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(BLACK);
      }
      if (strcmp((char *)ruban.lastread, "mauve") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(PURPLE);
      }
      if (strcmp((char *)ruban.lastread, "orange") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(ORANGE);
      }
      if (strcmp((char *)ruban.lastread, "rose") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(PINK);
      }
      if (strcmp((char *)ruban.lastread, "ultra") == 0) {
        ws2812fx.setMode(FX_MODE_STATIC);
        ws2812fx.setColor(ULTRAWHITE);
      }
    }
    if (subscription == &animation) {
      if (strcmp((char *)animation.lastread, "0") == 0) {
        ws2812fx.setMode(0);
      }
      if (strcmp((char *)animation.lastread, "1") == 0) {
        ws2812fx.setMode(1);
      }
      if (strcmp((char *)animation.lastread, "2") == 0) {
        ws2812fx.setMode(2);
      }
      if (strcmp((char *)animation.lastread, "3") == 0) {
        ws2812fx.setMode(3);
      }
      if (strcmp((char *)animation.lastread, "4") == 0) {
        ws2812fx.setMode(4);
      }
      if (strcmp((char *)animation.lastread, "5") == 0) {
        ws2812fx.setMode(5);
      }
      if (strcmp((char *)animation.lastread, "6") == 0) {
        ws2812fx.setMode(6);
      }
      if (strcmp((char *)animation.lastread, "7") == 0) {
        ws2812fx.setMode(7);
      }
      if (strcmp((char *)animation.lastread, "8") == 0) {
        ws2812fx.setMode(8);
      }
      if (strcmp((char *)animation.lastread, "9") == 0) {
        ws2812fx.setMode(9);
      }
      if (strcmp((char *)animation.lastread, "10") == 0) {
        ws2812fx.setMode(10);
      }
      if (strcmp((char *)animation.lastread, "11") == 0) {
        ws2812fx.setMode(11);
      }
      if (strcmp((char *)animation.lastread, "12") == 0) {
        ws2812fx.setMode(12);
      }
      if (strcmp((char *)animation.lastread, "13") == 0) {
        ws2812fx.setMode(13);
      }
      if (strcmp((char *)animation.lastread, "14") == 0) {
        ws2812fx.setMode(14);
      }
      if (strcmp((char *)animation.lastread, "15") == 0) {
        ws2812fx.setMode(15);
      }
      if (strcmp((char *)animation.lastread, "16") == 0) {
        ws2812fx.setMode(16);
      }
      if (strcmp((char *)animation.lastread, "17") == 0) {
        ws2812fx.setMode(17);
      }
      if (strcmp((char *)animation.lastread, "18") == 0) {
        ws2812fx.setMode(18);
      }
      if (strcmp((char *)animation.lastread, "19") == 0) {
        ws2812fx.setMode(19);
      }
      if (strcmp((char *)animation.lastread, "20") == 0) {
        ws2812fx.setMode(20);
      }
      if (strcmp((char *)animation.lastread, "21") == 0) {
        ws2812fx.setMode(21);
      }
      if (strcmp((char *)animation.lastread, "22") == 0) {
        ws2812fx.setMode(22);
      }
      if (strcmp((char *)animation.lastread, "23") == 0) {
        ws2812fx.setMode(23);
      }
      if (strcmp((char *)animation.lastread, "24") == 0) {
        ws2812fx.setMode(24);
      }
      if (strcmp((char *)animation.lastread, "25") == 0) {
        ws2812fx.setMode(25);
      }
      if (strcmp((char *)animation.lastread, "26") == 0) {
        ws2812fx.setMode(26);
      }
      if (strcmp((char *)animation.lastread, "27") == 0) {
        ws2812fx.setMode(27);
      }
      if (strcmp((char *)animation.lastread, "28") == 0) {
        ws2812fx.setMode(28);
      }
      if (strcmp((char *)animation.lastread, "29") == 0) {
        ws2812fx.setMode(29);
      }
      if (strcmp((char *)animation.lastread, "30") == 0) {
        ws2812fx.setMode(30);
      }
      if (strcmp((char *)animation.lastread, "31") == 0) {
        ws2812fx.setMode(31);
      }
      if (strcmp((char *)animation.lastread, "32") == 0) {
        ws2812fx.setMode(32);
      }
      if (strcmp((char *)animation.lastread, "33") == 0) {
        ws2812fx.setMode(33);
      }
      if (strcmp((char *)animation.lastread, "34") == 0) {
        ws2812fx.setMode(34);
      }
      if (strcmp((char *)animation.lastread, "35") == 0) {
        ws2812fx.setMode(35);
      }
      if (strcmp((char *)animation.lastread, "36") == 0) {
        ws2812fx.setMode(36);
      }
      if (strcmp((char *)animation.lastread, "37") == 0) {
        ws2812fx.setMode(37);
      }
      if (strcmp((char *)animation.lastread, "38") == 0) {
        ws2812fx.setMode(38);
      }
      if (strcmp((char *)animation.lastread, "39") == 0) {
        ws2812fx.setMode(39);
      }
      if (strcmp((char *)animation.lastread, "40") == 0) {
        ws2812fx.setMode(40);
      }
      if (strcmp((char *)animation.lastread, "41") == 0) {
        ws2812fx.setMode(41);
      }
      if (strcmp((char *)animation.lastread, "42") == 0) {
        ws2812fx.setMode(42);
      }
      if (strcmp((char *)animation.lastread, "43") == 0) {
        ws2812fx.setMode(43);
      }
      if (strcmp((char *)animation.lastread, "44") == 0) {
        ws2812fx.setMode(44);
      }
      if (strcmp((char *)animation.lastread, "45") == 0) {
        ws2812fx.setMode(45);
      }
      if (strcmp((char *)animation.lastread, "46") == 0) {
        ws2812fx.setMode(46);
      }
      if (strcmp((char *)animation.lastread, "47") == 0) {
        ws2812fx.setMode(47);
      }
      if (strcmp((char *)animation.lastread, "48") == 0) {
        ws2812fx.setMode(48);
      }
      if (strcmp((char *)animation.lastread, "49") == 0) {
        ws2812fx.setMode(49);
      }
      if (strcmp((char *)animation.lastread, "50") == 0) {
        ws2812fx.setMode(50);
      }
      if (strcmp((char *)animation.lastread, "51") == 0) {
        ws2812fx.setMode(51);
      }
      if (strcmp((char *)animation.lastread, "52") == 0) {
        ws2812fx.setMode(52);
      }
      }
    if (subscription == &puissance) {

      if (strcmp((char *)puissance.lastread, "100") == 0) {
        ws2812fx.setBrightness(255);
      }
      if (strcmp((char *)puissance.lastread, "90") == 0) {
        ws2812fx.setBrightness(225);
      }
      if (strcmp((char *)puissance.lastread, "80") == 0) {
        ws2812fx.setBrightness(200);
      }
      if (strcmp((char *)puissance.lastread, "70") == 0) {
        ws2812fx.setBrightness(175);
      }
      if (strcmp((char *)puissance.lastread, "60") == 0) {
        ws2812fx.setBrightness(150);
      }
      if (strcmp((char *)puissance.lastread, "50") == 0) {
        ws2812fx.setBrightness(125);
      }
      if (strcmp((char *)puissance.lastread, "40") == 0) {
        ws2812fx.setBrightness(100);
      }
      if (strcmp((char *)puissance.lastread, "30") == 0) {
        ws2812fx.setBrightness(75);
      }
      if (strcmp((char *)puissance.lastread, "20") == 0) {
        ws2812fx.setBrightness(50);
      }
      if (strcmp((char *)puissance.lastread, "10") == 0) {
        ws2812fx.setBrightness(25);
      }    
    }
    if (subscription == &vitesse) {
      if (strcmp((char *)vitesse.lastread, "minimum") == 0) {
        ws2812fx.setSpeed(65535);
      }
      if (strcmp((char *)vitesse.lastread, "1 / 4") == 0) {
        ws2812fx.setSpeed(49151);
      } 
      if (strcmp((char *)vitesse.lastread, "moyenne") == 0) {
        ws2812fx.setSpeed(32767);
      }
      if (strcmp((char *)vitesse.lastread, "3 / 4") == 0) {
        ws2812fx.setSpeed(16383);
      }                         
      if (strcmp((char *)vitesse.lastread, "maximum") == 0) {
        ws2812fx.setSpeed(10);
      }            
      }
  }
}
void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    mqtt.disconnect();
    delay(3000);
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
}
