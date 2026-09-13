#include <Arduino.h>

#include <config/button_config.h>
#include <traffic_light_button.h>

namespace {

unsigned long lastPollTime = 0;
unsigned long lastRawChangeTime = 0;
bool lastRawState = HIGH;
bool stableState = HIGH;

}  // namespace

void initializeModeButton() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // На старті вважаємо поточний рівень стабільним.
  lastRawState = digitalRead(BUTTON_PIN);
  stableState = lastRawState;
}

bool pollModeButton() {
  const unsigned long currentTime = millis();

  // Опитуємо кнопку лише з заданим інтервалом.
  if (currentTime - lastPollTime < BUTTON_POLLING_INTERVAL_MS) {
    return false;
  }

  lastPollTime = currentTime;

  const bool rawState = digitalRead(BUTTON_PIN);

  // Помітили зміну фізичного рівня.
  if (rawState != lastRawState) {
    lastRawState = rawState;
    lastRawChangeTime = currentTime;
  }

  // Рівень не змінювався достатньо довго і став стабільним.
  if (rawState != stableState &&
      currentTime - lastRawChangeTime >= BUTTON_DEBOUNCE_TIME_MS) {
    stableState = rawState;

    // INPUT_PULLUP: натиснута кнопка з'єднує пін із GND, тобто дає LOW.
    return stableState == LOW;
  }

  return false;
}
