# LVGL C++20 声明式 UI 框架 (实验性)

本项目旨在为 LVGL (Light and Versatile Graphics Library) 提供一个实验性的 C++20 封装层，使其能够以类似 SwiftUI 的声明式语法进行 UI 开发。

## 核心目标

- **声明式语法**: 使用直观、简洁的语法描述 UI 结构，替代 LVGL 原有的命令式 C API。
- **类型安全**: 利用 C++ 的类型系统，在编译期发现 UI 结构中的错误。
- **高性能**: 通过 C++20 的移动语义 (Move Semantics) 和零成本抽象，确保声明式封装不会带来显著的性能开销。
- **可扩展性**: 设计易于扩展的组件和修饰符系统。
- **代码风格**: 遵循驼峰式命名和类似 Qt 的代码风格。

## 技术实现亮点

本项目利用了一系列现代 C++ 的高级特性来构建优雅且高效的 API：

1.  **可变参数模板 (Variadic Templates)**:
    用于实现布局容器（如 `VStack`, `HStack`）的构造函数，使其能接受任意数量、任意类型的子视图，实现了 `VStack(Text(...), Button(...))` 这样的语法。

2.  **移动语义 (Move Semantics)**:
    所有视图组件都被设计为“只可移动” (Move-only) 类型。在 UI 结构构建时，视图对象的所有权被高效地转移，避免了昂贵的拷贝操作。

3.  **CRTP (Curiously Recurring Template Pattern)**:
    用于实现修饰符的链式调用。通过 `class DuiButton : public DuiView<DuiButton>` 这样的设计，基类 `DuiView` 中的通用修饰符 (`.width()`, `.height()`) 能够返回正确的派生类类型 (`DuiButton&`)，从而可以无缝链接派生类特有的修饰符 (`.onClick()`)。

4.  **引用限定符 (Reference Qualifiers)**:
    所有修饰符都提供了左值 (`&`) 和右值 (`&&`) 两个版本的重载。这保证了框架在处理临时对象（如 `DuiButton(...)`）和命名变量（如 `auto myButton = ...;`）时，都能表现得既安全又高效。

5.  **类型擦除 (Type Erasure)**:
    通过引入一个共同的非模板基类 `DuiViewBase`，解决了 CRTP 与多态容器的冲突。这使得布局容器内部可以使用 `std::vector<std::shared_ptr<DuiViewBase>>` 来存储不同类型的子视图。

## 设计思路总结

我们的核心设计哲学是**“将开发者的意图直接转化为代码”**。我们摒弃了 LVGL 原生的命令式风格（即一步步创建、设置、添加对象），转而追求一种更高级的、声明式的抽象。

- **声明式为核心**: 开发者应该只需描述 UI 的“最终形态”，而无需关心其构建过程。我们追求的最终语法 `VStack(Text(...), Button(...))` 正是这一思想的体现。
- **零成本抽象**: 声明式的便利性不应以牺牲性能为代价。我们利用 C++20 的移动语义和编译期特性，确保所创建的抽象层在运行时几乎没有额外开销。
- **类型安全与流畅API**: 通过链式调用修饰符 (`.width(100).bgColor(...)`)，让配置UI组件的过程如行云流水般自然，同时利用类型系统在编译期捕获错误。

### C++23 的可能性：终极简化

我们当前采用 CRTP 和引用限定符重载的模式，是 C++20 中能达到的最佳实践。但值得一提的是，C++23 引入了名为 **“Deducing `this`”** 的新特性，它允许将所有修饰符的两个重载版本完美地合并成一个，让框架的内部实现达到前所未有的简洁。

```cpp
// C++23 版本的修饰符 (仅为演示)
template <typename Self>
auto&& width(this Self&& self, int w) {
    lv_obj_set_width(self.m_lvObject, w);
    return std::forward<Self>(self); // 完美转发 this
}
```

## 如何使用

以下是一个简单的示例，展示了如何使用本框架构建一个 UI 界面：

```cpp
// main.cpp

#include "layouts/DuiVStack.h"
#include "layouts/DuiHStack.h"
#include "components/DuiText.h"
#include "components/DuiButton.h"
#include <iostream>

void dui_main() {
    new DuiVStack(
        DuiText("This is the ultimate syntax!").width(200),
        DuiButton("Movable Button")
            .bgColor(lv_palette_main(LV_PALETTE_BLUE))
            .onClick([]{ std::cout << "Moved button clicked!" << std::endl; }),
        DuiHStack(
            DuiText("Left"),
            DuiButton("Right")
        )
    );
}
```

## 如何编译

1.  将 `declarative` 目录添加到主 `CMakeLists.txt` 中：`add_subdirectory(declarative)`
2.  确保 `declarative/CMakeLists.txt` 正确配置了 LVGL 的头文件路径和链接库。
3.  使用 CMake 生成构建文件并编译。

## 未来展望

- 添加更多的基础组件 (Slider, Image, Checkbox等)。
- 丰富修饰符系统 (Font, Color, Alignment, Padding等)。
- 探索数据绑定机制。
