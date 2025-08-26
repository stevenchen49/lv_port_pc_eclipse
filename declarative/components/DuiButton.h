#pragma once

#include "core/DuiView.h"
#include <string>
#include <functional>

class DuiButton : public DuiView<DuiButton> {
public:
    explicit DuiButton(const std::string& label);
    DuiButton(DuiButton&&) = default; // Use default move constructor

    DuiButton& setLabel(const std::string& label);

    // Modifier for click action
    DuiButton& onClick(std::function<void()> action) &;
    DuiButton&& onClick(std::function<void()> action) &&;

    // Modifier for background color
    DuiButton& bgColor(lv_color_t color) &;
    DuiButton&& bgColor(lv_color_t color) &&;

private:
    std::function<void()> m_onClickAction;
    static void lvgl_event_cb(lv_event_t* e);
};
