#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  static lv_style_t tabview_indic_style;
  tabview_indic_style.body.border.color = LV_COLOR_WHITE;
  tabview_indic_style.body.border.width = 4;
  tabview_indic_style.body.border.part = LV_BORDER_FULL;
  tabview_indic_style.body.border.opa = LV_OPA_100;
  tabview_indic_style.body.padding.inner = 5;
  tabview_indic_style.body.opa = LV_OPA_100;

  static lv_style_t tabview_btn_style;
  lv_style_copy(&tabview_btn_style, &lv_style_plain);
  tabview_btn_style.body.main_color = LV_COLOR_HEX(0xa600ff);
  tabview_btn_style.body.grad_color = LV_COLOR_HEX(0xa600ff);
  tabview_btn_style.text.color = LV_COLOR_WHITE;

  static lv_style_t tabview_btn_tgl_style;
  lv_style_copy(&tabview_btn_tgl_style, &tabview_btn_style);
  tabview_btn_tgl_style.body.border.width = 2;
  tabview_btn_tgl_style.body.border.color = LV_COLOR_WHITE;

  static lv_style_t tabview_btn_pr_style;
  lv_style_copy(&tabview_btn_pr_style, &lv_style_plain);
  tabview_btn_pr_style.body.main_color = LV_COLOR_WHITE;
  tabview_btn_pr_style.body.grad_color = LV_COLOR_WHITE;
  tabview_btn_pr_style.text.color = LV_COLOR_WHITE;

  lv_obj_t *tabview_windows = lv_tabview_create(lv_scr_act(), NULL);
  lv_obj_t *tab_drive = lv_tabview_add_tab(tabview_windows, "Drive");
  lv_obj_t *tab_tilt = lv_tabview_add_tab(tabview_windows, "Tilt");
  lv_obj_t *tab_rollers = lv_tabview_add_tab(tabview_windows, "Rollers");

  static lv_style_t btn_rel_style;
  lv_style_copy(&btn_rel_style, &tabview_btn_tgl_style);
  btn_rel_style.body.radius = LV_RADIUS_CIRCLE;

  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_INDIC,
                       &tabview_indic_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_REL,
                       &tabview_btn_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_PR,
                       &tabview_btn_pr_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_TGL_REL,
                       &tabview_btn_tgl_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_TGL_PR,
                       &tabview_btn_pr_style);

  lv_obj_t *btn_drive_up = lv_btn_create(tab_drive, NULL);
  lv_btn_set_style(btn_drive_up, LV_BTN_STYLE_REL, &btn_rel_style);
  lv_obj_set_size(btn_drive_up, 50, 50);
  lv_obj_set_pos(btn_drive_up, 207, 10);
  lv_obj_t *btn_drive_down = lv_btn_create(tab_drive, btn_drive_up);
  lv_obj_set_y(btn_drive_down, 120);
  lv_obj_t *btn_drive_left = lv_btn_create(tab_drive, btn_drive_up);
  lv_obj_set_pos(btn_drive_left, 152, 65);
  lv_obj_t *btn_drive_right = lv_btn_create(tab_drive, btn_drive_left);
  lv_obj_set_x(btn_drive_right, 262);

  lv_obj_t *label_drive_up = lv_label_create(btn_drive_up, NULL);
  lv_label_set_text(label_drive_up, SYMBOL_UP);
  lv_obj_t *label_drive_down = lv_label_create(btn_drive_down, NULL);
  lv_label_set_text(label_drive_down, SYMBOL_DOWN);
  lv_obj_t *label_drive_left = lv_label_create(btn_drive_left, NULL);
  lv_label_set_text(label_drive_left, SYMBOL_LEFT);
  lv_obj_t *label_drive_right = lv_label_create(btn_drive_right, NULL);
  lv_label_set_text(label_drive_right, SYMBOL_RIGHT);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
