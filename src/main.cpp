#include <Arduino.h>
#include <config/led_config.h>
#include <traffic_light_state_config.h>
#include <traffic_light_timer.h>

void setup() {
  for (uint8_t i = 0; i < ledCount; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }

  if (!initializeTrafficLightTimer()) {
    return;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
