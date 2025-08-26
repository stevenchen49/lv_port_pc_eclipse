#include "DuiButton.h"
#include "lvgl.h"

DuiButton::DuiButton(const std::string& label) {
    m_lvObject = lv_btn_create(lv_scr_act()); // Temporarily create on screen

    lv_obj_t* lbl = lv_label_create(m_lvObject);
    lv_label_set_text(lbl, label.c_str());
    lv_obj_center(lbl);

    lv_obj_add_event_cb(m_lvObject, lvgl_event_cb, LV_EVENT_CLICKED, this);
}

DuiButton& DuiButton::setLabel(const std::string& label) {
    lv_obj_t* lbl = lv_obj_get_child(m_lvObject, 0);
    if (lbl) {
        lv_label_set_text(lbl, label.c_str());
    }
    return *this;
}

DuiButton& DuiButton::onClick(std::function<void()> action) & {
    m_onClickAction = std::move(action);
    return *this;
}

DuiButton&& DuiButton::onClick(std::function<void()> action) && {
    return std::move(this->onClick(std::move(action)));
}

DuiButton& DuiButton::bgColor(lv_color_t color) & {
    lv_obj_set_style_bg_color(m_lvObject, color, LV_PART_MAIN);
    return *this;
}

DuiButton&& DuiButton::bgColor(lv_color_t color) && {
    return std::move(this->bgColor(color));
}

void DuiButton::lvgl_event_cb(lv_event_t* e) {
    DuiButton* self = static_cast<DuiButton*>(lv_event_get_user_data(e));
    if (self && self->m_onClickAction) {
        self->m_onClickAction();
    }
}
