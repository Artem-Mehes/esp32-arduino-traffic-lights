#ifndef TRAFFIC_LIGHT_STATE_CONFIG_H
#define TRAFFIC_LIGHT_STATE_CONFIG_H

#include <config/light_duration_config.h>
#include <stdint.h>

// Активні сигнали світлофора.
enum class TrafficLightState : uint8_t {
  Green,
  Yellow,
  Red,
  RedAndYellow,
};

// Режим показу сигналу.
enum class TrafficLightMode : uint8_t {
  Steady,
  Blinking,
};

// Загальний режим роботи світлофора.
enum class TrafficLightOperatingMode : uint8_t {
  Normal,
  NightYellowBlinking,
};

// Один етап циклу світлофора.
struct TrafficLightPhase {
  TrafficLightState state;
  TrafficLightMode mode;
  uint32_t durationMs;
};

// Послідовність етапів відповідно до ПДР.
constexpr TrafficLightPhase trafficLightCycle[] = {
    {TrafficLightState::Green, TrafficLightMode::Steady,
     GREEN_LIGHT_DURATION_MS},
    {TrafficLightState::Green, TrafficLightMode::Blinking,
     GREEN_BLINK_DURATION_MS},
    {TrafficLightState::Yellow, TrafficLightMode::Steady,
     YELLOW_LIGHT_DURATION_MS},
    {TrafficLightState::Red, TrafficLightMode::Steady, RED_LIGHT_DURATION_MS},
    {TrafficLightState::RedAndYellow, TrafficLightMode::Steady,
     RED_AND_YELLOW_DURATION_MS},
};

constexpr uint8_t trafficLightCycleLength =
    sizeof(trafficLightCycle) / sizeof(trafficLightCycle[0]);

#endif  // TRAFFIC_LIGHT_STATE_CONFIG_H
