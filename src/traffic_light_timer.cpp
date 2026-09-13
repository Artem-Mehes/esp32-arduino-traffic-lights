#include <Arduino.h>
#include <config/timer_config.h>
#include <traffic_light_controller.h>
#include <traffic_light_timer.h>

namespace {

hw_timer_t* trafficLightTimer = nullptr;

void ARDUINO_ISR_ATTR onTrafficLightTimer() {
  handleTrafficLightTimerTick();
}

}  // namespace

bool initializeTrafficLightTimer() {
  // 80 МГц / 80 = 1 МГц, тобто один відлік таймера дорівнює 1 мкс.
  trafficLightTimer = timerBegin(TIMER_NUMBER, TIMER_PRESCALER, true);
  if (trafficLightTimer == nullptr) {
    return false;
  }

  timerAttachInterrupt(trafficLightTimer, &onTrafficLightTimer, true);
  timerAlarmWrite(trafficLightTimer, TIMER_ALARM_PERIOD_US, true);
  timerAlarmEnable(trafficLightTimer);

  return true;
}
