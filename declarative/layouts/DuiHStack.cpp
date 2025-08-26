#include "DuiHStack.h"
#include "lvgl.h"

DuiHStack::DuiHStack() {
    m_lvObject = lv_obj_create(lv_scr_act());
    lv_obj_set_size(m_lvObject, LV_PCT(100), LV_PCT(100));
    lv_obj_set_layout(m_lvObject, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(m_lvObject, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(m_lvObject, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
}

DuiHStack::DuiHStack(std::initializer_list<std::shared_ptr<DuiViewBase>> children) : DuiHStack() {
    for (const auto& child : children) {
        addChild(child);
    }
}

void DuiHStack::addChild(std::shared_ptr<DuiViewBase> child) {
    m_children.push_back(child);
    lv_obj_set_parent(child->lvObject(), m_lvObject);
}
