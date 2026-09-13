#include <Arduino.h>

#include <config/led_config.h>
#include <config/light_duration_config.h>
#include <config/timer_config.h>
#include <traffic_light_controller.h>
#include <traffic_light_state_config.h>

namespace {

uint8_t currentPhaseIndex = 0;
uint32_t phaseElapsedUs = 0;
uint32_t blinkElapsedUs = 0;
bool blinkLightIsOn = true;
volatile TrafficLightOperatingMode requestedOperatingMode =
    TrafficLightOperatingMode::Normal;
TrafficLightOperatingMode activeOperatingMode =
    TrafficLightOperatingMode::Normal;

void setLed(uint8_t ledIndex, bool isOn) {
  digitalWrite(ledPins[ledIndex], isOn ? HIGH : LOW);
}

void turnOffAllLeds() {
  for (uint8_t i = 0; i < ledCount; ++i) {
    setLed(i, false);
  }
}

void applyCurrentPhase() {
  turnOffAllLeds();
  blinkLightIsOn = true;

  switch (trafficLightCycle[currentPhaseIndex].state) {
    case TrafficLightState::Green:
      setLed(greenLedIndex, true);
      break;
    case TrafficLightState::Yellow:
      setLed(yellowLedIndex, true);
      break;
    case TrafficLightState::Red:
      setLed(redLedIndex, true);
      break;
    case TrafficLightState::RedAndYellow:
      setLed(redLedIndex, true);
      setLed(yellowLedIndex, true);
      break;
  }
}

void applyNightYellowBlinkingMode() {
  turnOffAllLeds();
  blinkLightIsOn = true;
  setLed(yellowLedIndex, true);
}

void moveToNextPhase() {
  currentPhaseIndex = (currentPhaseIndex + 1) % trafficLightCycleLength;
  phaseElapsedUs = 0;
  blinkElapsedUs = 0;
  applyCurrentPhase();
}

void applyRequestedOperatingMode() {
  activeOperatingMode = requestedOperatingMode;
  phaseElapsedUs = 0;
  blinkElapsedUs = 0;

  if (activeOperatingMode == TrafficLightOperatingMode::NightYellowBlinking) {
    applyNightYellowBlinkingMode();
    return;
  }

  currentPhaseIndex = 0;
  applyCurrentPhase();
}

}  // namespace

void initializeTrafficLightController() {
  for (uint8_t i = 0; i < ledCount; ++i) {
    pinMode(ledPins[i], OUTPUT);
  }

  currentPhaseIndex = 0;
  phaseElapsedUs = 0;
  blinkElapsedUs = 0;
  requestedOperatingMode = TrafficLightOperatingMode::Normal;
  activeOperatingMode = TrafficLightOperatingMode::Normal;
  applyCurrentPhase();
}

void toggleTrafficLightOperatingMode() {
  if (requestedOperatingMode == TrafficLightOperatingMode::Normal) {
    requestedOperatingMode = TrafficLightOperatingMode::NightYellowBlinking;
    return;
  }

  requestedOperatingMode = TrafficLightOperatingMode::Normal;
}

void ARDUINO_ISR_ATTR handleTrafficLightTimerTick() {
  if (requestedOperatingMode != activeOperatingMode) {
    applyRequestedOperatingMode();
  }

  if (activeOperatingMode == TrafficLightOperatingMode::NightYellowBlinking) {
    blinkElapsedUs += TIMER_ALARM_PERIOD_US;

    if (blinkElapsedUs >= YELLOW_BLINK_INTERVAL_MS * 1000UL) {
      blinkElapsedUs = 0;
      blinkLightIsOn = !blinkLightIsOn;
      setLed(yellowLedIndex, blinkLightIsOn);
    }

    return;
  }

  const TrafficLightPhase& currentPhase =
      trafficLightCycle[currentPhaseIndex];

  phaseElapsedUs += TIMER_ALARM_PERIOD_US;

  if (currentPhase.mode == TrafficLightMode::Blinking) {
    blinkElapsedUs += TIMER_ALARM_PERIOD_US;

    if (blinkElapsedUs >= GREEN_BLINK_INTERVAL_MS * 1000UL) {
      blinkElapsedUs = 0;
      blinkLightIsOn = !blinkLightIsOn;
      setLed(greenLedIndex, blinkLightIsOn);
    }
  }

  if (phaseElapsedUs >= currentPhase.durationMs * 1000UL) {
    moveToNextPhase();
  }
}
