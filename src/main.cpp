#include <Arduino.h>
#include <traffic_light_controller.h>
#include <traffic_light_timer.h>

void setup() {
  initializeTrafficLightController();

  if (!initializeTrafficLightTimer()) {
    return;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
