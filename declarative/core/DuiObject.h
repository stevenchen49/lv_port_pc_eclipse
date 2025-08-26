#pragma once

#include <string>

class DuiObject {
public:
    DuiObject() = default;
    virtual ~DuiObject() = default;

    void setObjectName(const std::string& name);
    std::string objectName() const;

private:
    std::string m_objectName;
};
