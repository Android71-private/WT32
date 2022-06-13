#include <Arduino.h>
#define LGFX_AUTODETECT // Autodetect board
#define LGFX_USE_V1     // set to use new version of library

#include <LovyanGFX.hpp> // main library
static LGFX lcd; // declare display variable

#include <lvgl.h>

/*** Function declaration ***/
static void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
static void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
static void DisplayInit();


/*** Setup screen for LVGL ***/
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;

static void DisplayInit()
{
    lcd.init(); // Initialize LovyanGFX
    lv_init();  // Initialize lvgl

    // Setting display to landscape
    if (lcd.width() < lcd.height())
    lcd.setRotation(lcd.getRotation() ^ 1);

    lcd.setBrightness(128); // моя вставка для проверки. Работает. испытано до 4

    /* LVGL : Setting up buffer to use for display */
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

    /*** LVGL : Setup & Initialize the display device driver ***/
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = display_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*** LVGL : Setup & Initialize the input device driver ***/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    lv_indev_drv_register(&indev_drv); 
}

/*** Display callback to flush the buffer to screen ***/
  static void display_flush(lv_disp_drv_t * disp, const lv_area_t *area, lv_color_t *color_p)
  {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    //lcd.pushColors((uint16_t *)&color_p->full, w * h, true);
    lcd.pushPixels((uint16_t *)&color_p->full, w * h, true);
    // имя функции pushColors изменено на pushPixels по совету Platformio
    lcd.endWrite();

    lv_disp_flush_ready(disp);
  }

  /*** Touchpad callback to read the touchpad ***/
  static void touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
  {
    uint16_t touchX, touchY;
    bool touched = lcd.getTouch(&touchX, &touchY);

    if (!touched)
    {
      data->state = LV_INDEV_STATE_REL;  // released
    }
    else
    {
      data->state = LV_INDEV_STATE_PR; // pressed

      /*Set the coordinates*/
      data->point.x = touchX;
      data->point.y = touchY;

      Serial.printf("Touch (x,y): (%03d,%03d)\n",touchX,touchY );
    }
  }