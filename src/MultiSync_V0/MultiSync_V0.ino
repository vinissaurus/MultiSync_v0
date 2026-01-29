#include "MultiSync_V0.h"

#define LED_R 3
#define LED_G 4
#define LED_B 5
#define LED_WW 18
#define LED_CW 19

void setup() {
  // Wait for serial connection for a while

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_WW, OUTPUT);
  pinMode(LED_CW, OUTPUT);

}

void loop() {
  // Small animation combining random colors on RGB and WW/CW LEDs

  analogWrite(LED_R, random(0, 256));
  analogWrite(LED_G, random(0, 256));
  analogWrite(LED_B, random(0, 256));
  analogWrite(LED_WW, random(0, 256));
  analogWrite(LED_CW, random(0, 256));
  delay(500);


}