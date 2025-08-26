#include "DuiViewBase.h"

DuiViewBase::DuiViewBase(DuiViewBase* parent) : m_parent(parent) {}

DuiViewBase::~DuiViewBase() {
    if (m_lvObject) {
        lv_obj_del(m_lvObject);
        m_lvObject = nullptr;
    }
}

DuiViewBase::DuiViewBase(DuiViewBase&& other) noexcept
    : DuiObject(std::move(other)), m_lvObject(other.m_lvObject), m_parent(other.m_parent) {
    other.m_lvObject = nullptr;
}

lv_obj_t* DuiViewBase::lvObject() const {
    return m_lvObject;
}
