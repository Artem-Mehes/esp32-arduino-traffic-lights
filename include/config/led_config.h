#ifndef TRAFFIC_LIGHT_LED_CONFIG_H
#define TRAFFIC_LIGHT_LED_CONFIG_H

#include <stdint.h>

// Піни світлодіодів у порядку: зелений, жовтий, червоний.
constexpr uint8_t ledPins[] = {4, 5, 6};
constexpr uint8_t ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

constexpr uint8_t greenLedIndex = 0;
constexpr uint8_t yellowLedIndex = 1;
constexpr uint8_t redLedIndex = 2;

#endif  // TRAFFIC_LIGHT_LED_CONFIG_H
