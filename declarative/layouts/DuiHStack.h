#pragma once

#include "core/DuiView.h"
#include <vector>
#include <memory>
#include <utility> // For std::forward

class DuiHStack : public DuiView<DuiHStack> {
public:
    explicit DuiHStack();
    DuiHStack(std::initializer_list<std::shared_ptr<DuiViewBase>> children);
    DuiHStack(DuiHStack&&) = default;

    // 新增：可变参数模板构造函数
    template<typename... Children>
    DuiHStack(Children&&... children) {
        (addChild(std::make_shared<typename std::remove_reference<Children>::type>(std::move(children))), ...);
    }

    void addChild(std::shared_ptr<DuiViewBase> child);

private:
    std::vector<std::shared_ptr<DuiViewBase>> m_children;
};
