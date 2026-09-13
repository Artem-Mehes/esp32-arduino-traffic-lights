#ifndef TRAFFIC_LIGHT_BUTTON_H
#define TRAFFIC_LIGHT_BUTTON_H

// Налаштовує кнопку перемикання режиму.
void initializeModeButton();

// Повертає true один раз для кожного стабільного натискання кнопки.
bool pollModeButton();

#endif  // TRAFFIC_LIGHT_BUTTON_H
