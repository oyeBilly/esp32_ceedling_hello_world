#include "unity.h"
#include "cmock.h"

// try mocking the other headers even though we don't care to use them
// #include <stdio.h>
// #include "mock_sdkconfig.h"
// #include "mock_freertos/FreeRTOS.h"
// #include "mock_freertos/task.h"
// #include "mock_esp_chip_info.h"
// #include "mock_esp_flash.h"

#include "mock_hey_ceedling.h"

#include "hello_world_main.h"

void test_app_main_should_callHeyCeedling(void)
{
    hey_ceedling_expect();

    app_main();
}