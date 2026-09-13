#include <Arduino.h>
#include <traffic_light_button.h>
#include <traffic_light_controller.h>
#include <traffic_light_timer.h>

void setup() {
  initializeTrafficLightController();
  initializeModeButton();

  if (!initializeTrafficLightTimer()) {
    return;
  }
}

void loop() {
  if (pollModeButton()) {
    toggleTrafficLightOperatingMode();
  }
}
