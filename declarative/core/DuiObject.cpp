#include "DuiObject.h"

void DuiObject::setObjectName(const std::string& name) {
    m_objectName = name;
}

std::string DuiObject::objectName() const {
    return m_objectName;
}
