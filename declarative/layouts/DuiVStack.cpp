#include "DuiVStack.h"
#include "lvgl.h"

DuiVStack::DuiVStack() {
    m_lvObject = lv_obj_create(lv_scr_act());
    lv_obj_set_size(m_lvObject, LV_PCT(100), LV_PCT(100));
    lv_obj_set_layout(m_lvObject, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(m_lvObject, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(m_lvObject, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
}

DuiVStack::DuiVStack(std::initializer_list<std::shared_ptr<DuiViewBase>> children) : DuiVStack() {
    for (const auto& child : children) {
        addChild(child);
    }
}

DuiVStack::DuiVStack(ContentBuilder builder) : DuiVStack() {
    auto adder = [this](std::shared_ptr<DuiViewBase> child) {
        this->addChild(child);
    };
    builder(adder);
}


void DuiVStack::addChild(std::shared_ptr<DuiViewBase> child) {
    m_children.push_back(child);
    lv_obj_set_parent(child->lvObject(), m_lvObject);
}
