#include <lvgl.h>
#include "lv_conf.h"
#include <WT32settings.h>
// место для инклуда нового Демо.h

void setup() {
  Serial.begin(115200); /* prepare for possible serial debug */
  DisplayInit();
  // вызов функции нового демо из Демо.h
}

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}