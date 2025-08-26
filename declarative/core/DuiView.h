#pragma once

#include "DuiViewBase.h"

template <typename Derived>
class DuiView : public DuiViewBase {
public:
    // Modifiers
    Derived& width(int w) & {
        lv_obj_set_width(m_lvObject, w);
        return static_cast<Derived&>(*this);
    }
    Derived&& width(int w) && {
        return std::move(width(w));
    }

    Derived& height(int h) & {
        lv_obj_set_height(m_lvObject, h);
        return static_cast<Derived&>(*this);
    }
    Derived&& height(int h) && {
        return std::move(height(h));
    }
};
