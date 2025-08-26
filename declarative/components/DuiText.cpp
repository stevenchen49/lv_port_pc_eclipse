#include "DuiText.h"
#include "lvgl.h"

DuiText::DuiText(const std::string& text) {
    m_lvObject = lv_label_create(lv_scr_act()); // Temporarily create on screen
    lv_label_set_text(m_lvObject, text.c_str());
}

DuiText& DuiText::setText(const std::string& text) {
    lv_label_set_text(m_lvObject, text.c_str());
    return *this;
}

std::string DuiText::text() const {
    return lv_label_get_text(m_lvObject);
}
