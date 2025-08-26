
#include "lvgl.h"
#include "layouts/DuiVStack.h"
#include "layouts/DuiHStack.h"
#include "components/DuiText.h"
#include "components/DuiButton.h"
#include <memory>
#include <iostream>

// 为了使用新语法，我们需要为 DuiText 和 DuiButton 添加移动构造函数
// (通常编译器会自动生成，但显式声明一下更清晰)

// A simple example of how to use the declarative UI
void dui_main() {
    // 之前使用尾随 Lambda 的代码
    /*
    auto* ui_root = new DuiVStack(nullptr, [](auto&amp; add) {
        add(std::make_shared<DuiText>("Hello from the new syntax!"));
        
        auto button = std::make_shared<DuiButton>("Click Me");
        button->bgColor(lv_palette_main(LV_PALETTE_GREEN))
              .onClick([] { 
                  std::cout << "Button clicked!" << std::endl; 
              });
        add(button);

        add(std::make_shared<DuiHStack>(nullptr, std::initializer_list<std::shared_ptr<DuiView>>{
            std::make_shared<DuiText>("Left"),
            std::make_shared<DuiText>("Right")
        }));
    });
    */

    // ⭐ 使用最终的、基于可变参数模板和移动语义的语法 ⭐
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

// NOTE: This is a placeholder main function.
// In a real project, you would integrate this with your application's main loop
// and lvgl's tick/handler functions.
int main(int argc, char** argv) {
    // Basic LVGL initialization
    lv_init();

    // Initialize display and input devices (platform-specific)
    // For PC simulator, this is usually handled by lv_port_pc_eclipse's main.c
    // We are just calling our dui_main here to construct the UI.
    // In a real application, you would need to replace the default main loop.

    dui_main();

    // LVGL's task handler loop
    // while(1) {
    //     lv_timer_handler();
    //     usleep(5 * 1000);
    // }

    return 0;
}
