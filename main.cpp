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

        // 创建按钮组件
        static std::shared_ptr<Gui::Button> button = std::make_shared<Gui::Button>();
        
        button->genObjectSync(lv_screen_active())
            .setConfig(Gui::ButtonConfig::defaultConfig())
            .setPos(10, 10)
            .setSize(100, 50)
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
