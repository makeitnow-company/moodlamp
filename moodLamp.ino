#define BLYNK_PRINT Serial

//자신의 BLYNK DEVICE INFO값 넣기
#define BLYNK_TEMPLATE_ID "*******"
#define BLYNK_DEVICE_NAME "********"
#define BLYNK_AUTH_TOKEN "*******"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Adafruit_NeoPixel.h>


#define PIN       18 //네오픽셀이 연결된 GPIO핀
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int count = 0;

char auth[] = BLYNK_AUTH_TOKEN;

// SSID와 PW입력하기
char ssid[] = "************";
char pass[] = "********";

BlynkTimer timer;

int RGB_RED = 0;
int RGB_GREEN = 0;
int RGB_BLUE = 0;

BLYNK_WRITE(V20){
  RGB_RED = param.asInt();
  showNeoPixcel();
}

BLYNK_WRITE(V21){
  RGB_GREEN = param.asInt();
  showNeoPixcel();
}

BLYNK_WRITE(V22){
  RGB_BLUE = param.asInt();
  showNeoPixcel();
}

void showNeoPixcel(){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i,pixels.Color(RGB_RED, RGB_GREEN, RGB_BLUE));
  }
  pixels.show();
}

void neoPixcel(){
  int sensor = analogRead(34);
  if (sensor > 3500){
    count++;
    if(count==1){
      for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(255, 0, 0));
      }
    
    }else if(count==2){
      for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(0, 255, 0));
      }
    }else if(count==3){
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(0, 0, 255));
      }
    }else if(count==4){
      for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(255, 255, 0));
      }
    }else if(count==5){
      for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(255, 0, 255));
      }
    }else if(count==6){
      for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(0, 255, 255));
      }
    }else if(count==7){
      for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(255, 255, 255));
      }
    }else if(count==8){
      for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i,pixels.Color(0, 0, 0));
      }
      count=0;
    }
  }
    pixels.show();
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(300L, neoPixcel);
  pixels.begin();
}

void loop()
{
  Blynk.run();
  timer.run();
}

  
