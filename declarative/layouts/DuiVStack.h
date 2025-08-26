#pragma once

#include "core/DuiView.h"
#include <vector>
#include <memory>
#include <functional>
#include <utility>

class DuiVStack : public DuiView<DuiVStack> {
public:
    using ContentBuilder = std::function<void(std::function<void(std::shared_ptr<DuiViewBase>)>)>;

    explicit DuiVStack();
    DuiVStack(std::initializer_list<std::shared_ptr<DuiViewBase>> children);
    DuiVStack(ContentBuilder builder);
    DuiVStack(DuiVStack&&) = default;

    // 可变参数模板构造函数
    template<typename... Children>
    DuiVStack(Children&&... children) {
        (addChild(std::make_shared<typename std::remove_reference<Children>::type>(std::move(children))), ...);
    }

    void addChild(std::shared_ptr<DuiViewBase> child);

private:
    std::vector<std::shared_ptr<DuiViewBase>> m_children;
};
