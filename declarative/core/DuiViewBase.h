#pragma once

#include "DuiObject.h"
#include "lvgl.h"

// The common, non-template base class for all views
class DuiViewBase : public DuiObject {
public:
    explicit DuiViewBase(DuiViewBase* parent = nullptr);
    virtual ~DuiViewBase();

    DuiViewBase(DuiViewBase&& other) noexcept;

    lv_obj_t* lvObject() const;

protected:
    lv_obj_t* m_lvObject = nullptr;
    DuiViewBase* m_parent = nullptr;
};
