#include <lvgl.h>
#include <Arduino.h>

/* Toggle button event handler */
  static void toggle_event_handler(lv_event_t * e)
  {
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
      LV_LOG_USER("Toggled");
      Serial.println("Toggled");
    }
  }

  /* Counter button event handler */
  static void counter_event_handler(lv_event_t * e)
  {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
      static uint8_t cnt = 0;
      cnt++;

      /*Get the first child of the button which is the label and change its text*/
      lv_obj_t *label = lv_obj_get_child(btn, 0);
      lv_label_set_text_fmt(label, "Button: %d", cnt);
      LV_LOG_USER("Clicked");
      Serial.println("Clicked");
    }
  }

void lv_button_demo(void);

void DemoTitle()
{
    /*** Create simple label and show LVGL version ***/
    String LVGL_Arduino = "WT32-SC01 with LVGL ";
    LVGL_Arduino += String('v') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
    lv_obj_t *label = lv_label_create(lv_scr_act()); // full screen as the parent
    lv_label_set_text(label, LVGL_Arduino.c_str());  // set label text
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 5);      // Center but 20 from the top
}

void lv_button_demo(void)
  {
    DemoTitle();
    lv_obj_t *label;

    // Button with counter
    lv_obj_t *btn1 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn1, counter_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_set_pos(btn1, 100, 100);   /*Set its position*/
    lv_obj_set_size(btn1, 120, 50);   /*Set its size*/


    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);

    // Toggle button
    lv_obj_t *btn2 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn2, toggle_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_pos(btn2, 250, 100);   /*Set its position*/
    lv_obj_set_size(btn2, 120, 50);   /*Set its size*/

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Toggle Button");
    lv_obj_center(label);
  }