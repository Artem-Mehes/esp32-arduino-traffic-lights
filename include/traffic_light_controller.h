#ifndef TRAFFIC_LIGHT_CONTROLLER_H
#define TRAFFIC_LIGHT_CONTROLLER_H

#include <Arduino.h>

// Налаштовує світлодіоди та вмикає перший стан циклу.
void initializeTrafficLightController();

// Перемикає між звичайним та нічним режимами.
void toggleTrafficLightOperatingMode();

// Викликається апаратним таймером для оновлення стану світлофора.
void ARDUINO_ISR_ATTR handleTrafficLightTimerTick();

#endif  // TRAFFIC_LIGHT_CONTROLLER_H
