/**
 * @file main.cpp
 * @brief LVGL PC Port with C++ wrapper
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"

#include "components/iface/Button.h"
#include "components/iface/ButtonConfig.h"
#include "components/iface/Checkbox.h"
#include "components/iface/CheckboxConfig.h"
#include "components/iface/Radio.h"
#include "components/iface/RadioConfig.h"
#include "components/iface/Switch.h"
#include "components/iface/SwitchConfig.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_display_t * hal_init(int32_t w, int32_t h);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * @brief LVGL Application class
 * 
 * This class provides a C++ wrapper around the LVGL functionality
 */
class LVGLApplication {
private:
    lv_display_t* display_;
    bool initialized_;
    
public:
    /**
     * @brief Constructor
     */
    LVGLApplication() : display_(NULL), initialized_(false) {
        std::cout << "LVGL Application initializing..." << std::endl;
    }
    
    /**
     * @brief Destructor
     */
    ~LVGLApplication() {
        cleanup();
    }
    
    /**
     * @brief Initialize the LVGL application
     * @param width Display width
     * @param height Display height
     * @return true if initialization successful, false otherwise
     */
    bool initialize(int32_t width, int32_t height) {
        if (initialized_) {
            std::cerr << "LVGL already initialized!" << std::endl;
            return false;
        }
        
        try {
            // Initialize LVGL
            lv_init();
            
            // Initialize the display and input devices
            display_ = hal_init(width, height);
            if (!display_) {
                std::cerr << "Failed to initialize display!" << std::endl;
                return false;
            }
            
            initialized_ = true;
            std::cout << "LVGL Application initialized successfully" << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Exception during initialization: " << e.what() << std::endl;
            return false;
        }
    }
    
    /**
     * @brief Run the demo with specified arguments
     * @param argc Number of arguments
     * @param argv Argument array
     * @return true if demo started successfully, false otherwise
     */
    bool runDemo(int argc, char** argv) {
        if (!initialized_) {
            std::cerr << "LVGL not initialized!" << std::endl;
            return false;
        }
        
        try {
            // Open a demo or an example
            if (argc == 0) {
                lv_demo_widgets();
                // lv_example_chart_1();
            } else {
                if (!lv_demos_create(&argv[1], argc - 1)) {
                    lv_demos_show_help();
                    return false;
                }
            }
            
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Exception during demo execution: " << e.what() << std::endl;
            return false;
        }
    }
    
    /**
     * @brief Main application loop
     */
    void run() {
        if (!initialized_) {
            std::cerr << "LVGL not initialized!" << std::endl;
            return;
        }
        
        std::cout << "Starting main loop..." << std::endl;
        
        try {
            while (true) {
                // Periodically call the lv_task handler.
                // It could be done in a timer interrupt or an OS task too.
                lv_timer_handler();
                usleep(10 * 1000);
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception in main loop: " << e.what() << std::endl;
        }
    }
    
    /**
     * @brief Cleanup resources
     */
    void cleanup() {
        if (initialized_) {
            std::cout << "Cleaning up LVGL..." << std::endl;
            lv_deinit();
            initialized_ = false;
            display_ = NULL;
        }
    }
    
    /**
     * @brief Get display pointer
     * @return Display pointer or NULL if not initialized
     */
    lv_display_t* getDisplay() const {
        return display_;
    }
    
    /**
     * @brief Check if application is initialized
     * @return true if initialized, false otherwise
     */
    bool isInitialized() const {
        return initialized_;
    }
};

int main(int argc, char **argv)
{
    (void)argc; /*Unused*/
    (void)argv; /*Unused*/

    try {
        // Create LVGL application instance
        LVGLApplication app;
        
        // Initialize the application
        if (!app.initialize(480, 320)) {
            std::cerr << "Failed to initialize LVGL application" << std::endl;
            return -1;
        }

        // 设置黑色主题背景
        lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(Gui::ColorConfig::Black), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(lv_screen_active(), LV_OPA_COVER, LV_PART_MAIN);
        
                // 创建按钮组件
        static std::shared_ptr<Gui::Button> textButton = std::make_shared<Gui::Button>();
        static std::shared_ptr<Gui::Button> greenButton = std::make_shared<Gui::Button>();
        
        textButton->genObjectSync(lv_screen_active())
            .setConfig(Gui::ButtonConfig::prsText())
            .setPos(Gui::ComponentConfig::Pos(50, 50, 100, 40))
            .show();

        greenButton->genObjectSync(lv_screen_active())
            .setConfig(Gui::ButtonConfig::prsPrimary())
            .setPos(Gui::ComponentConfig::Pos(50, 200, 100, 40))
            .show();
            
        // 创建复选框组件 - 展示四种状态
        static std::shared_ptr<Gui::Checkbox> checkbox1 = std::make_shared<Gui::Checkbox>();
        static std::shared_ptr<Gui::Checkbox> checkbox2 = std::make_shared<Gui::Checkbox>();
        static std::shared_ptr<Gui::Checkbox> checkbox3 = std::make_shared<Gui::Checkbox>();
        static std::shared_ptr<Gui::Checkbox> checkbox4 = std::make_shared<Gui::Checkbox>();
        
        // 从上到下：checked/unchecked/checked-disabled/unchecked-disabled
        checkbox1->genObjectSync(lv_screen_active())
            .setConfig(Gui::CheckboxConfig::defaultConfig().setChecked(true))
            .setPos(Gui::ComponentConfig::Pos(200, 50, 30, 30))
            .show();
            
        checkbox2->genObjectSync(lv_screen_active())
            .setConfig(Gui::CheckboxConfig::defaultConfig().setChecked(false))
            .setPos(Gui::ComponentConfig::Pos(200, 100, 30, 30))
            .show();
            
        checkbox3->genObjectSync(lv_screen_active())
            .setConfig(Gui::CheckboxConfig::defaultConfig().setChecked(true).setEnabled(false))
            .setPos(Gui::ComponentConfig::Pos(200, 150, 30, 30))
            .show();
            
        checkbox4->genObjectSync(lv_screen_active())
            .setConfig(Gui::CheckboxConfig::defaultConfig().setChecked(false).setEnabled(false))
            .setPos(Gui::ComponentConfig::Pos(200, 200, 30, 30))
            .show();
            
        // 创建单选按钮组件 - 展示两种状态
        static std::shared_ptr<Gui::Radio> radio1 = std::make_shared<Gui::Radio>();
        static std::shared_ptr<Gui::Radio> radio2 = std::make_shared<Gui::Radio>();
        
        // 从上到下：checked/unchecked
        radio1->genObjectSync(lv_screen_active())
            .setConfig(Gui::RadioConfig::defaultConfig().setChecked(true))
            .setPos(Gui::ComponentConfig::Pos(300, 50, 30, 30))
            .show();
            
        radio2->genObjectSync(lv_screen_active())
            .setConfig(Gui::RadioConfig::defaultConfig().setChecked(false))
            .setPos(Gui::ComponentConfig::Pos(300, 100, 30, 30))
            .show();
            
        // 创建开关组件 - 展示四种状态
        static std::shared_ptr<Gui::Switch> switch1 = std::make_shared<Gui::Switch>();
        static std::shared_ptr<Gui::Switch> switch2 = std::make_shared<Gui::Switch>();
        static std::shared_ptr<Gui::Switch> switch3 = std::make_shared<Gui::Switch>();
        static std::shared_ptr<Gui::Switch> switch4 = std::make_shared<Gui::Switch>();
        
        // 从上到下：开启(亮绿)/关闭(浅灰)/开启(橄榄绿)/关闭(深灰)
        switch1->genObjectSync(lv_screen_active())
            .setConfig(Gui::SwitchConfig::defaultConfig().setOn(true))
            .setPos(Gui::ComponentConfig::Pos(400, 50, 50, 25))
            .show();
            
        switch2->genObjectSync(lv_screen_active())
            .setConfig(Gui::SwitchConfig::defaultConfig().setOn(false))
            .setPos(Gui::ComponentConfig::Pos(400, 100, 50, 25))
            .show();
            
        switch3->genObjectSync(lv_screen_active())
            .setConfig(Gui::SwitchConfig::oliveConfig().setOn(true))
            .setPos(Gui::ComponentConfig::Pos(400, 150, 50, 25))
            .show();
            
        switch4->genObjectSync(lv_screen_active())
            .setConfig(Gui::SwitchConfig::oliveConfig().setOn(false))
            .setPos(Gui::ComponentConfig::Pos(400, 200, 50, 25))
            .show();
            

        // Run the demo
        // if (!app.runDemo(argc, argv)) {
        //     std::cerr << "Failed to run demo" << std::endl;
        //     return -1;
        // }
        
        // Start the main loop
        app.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "Unknown exception occurred" << std::endl;
        return -1;
    }
    
    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_display_t * hal_init(int32_t w, int32_t h)
{
  lv_group_set_default(lv_group_create());

  lv_display_t * disp = lv_sdl_window_create(w, h);

  lv_indev_t * mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);

  LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t * cursor_obj;
  cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
  lv_image_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

  lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
  lv_indev_set_display(mousewheel, disp);

  lv_indev_t * keyboard = lv_sdl_keyboard_create();
  lv_indev_set_display(keyboard, disp);
  lv_indev_set_group(keyboard, lv_group_get_default());

  return disp;
}
