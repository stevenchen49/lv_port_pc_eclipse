#pragma once

#include "core/DuiView.h"
#include <string>

class DuiText : public DuiView<DuiText> {
public:
    explicit DuiText(const std::string& text);
    DuiText(DuiText&&) = default;

    DuiText& setText(const std::string& text);
    std::string text() const;
};
