#include "unity.h"
#include "cmock.h"

#include "mock_esp_chip_info.h"
#include "mock_esp_flash.h"
#include "mock_hey_ceedling.h"

#include "hello_world_main.h"

void test_app_main_should_callHeyCeedling(void)
{
    hey_ceedling_ExpectAndReturn(0);
    // esp_chip_info_Ignore();
    esp_chip_info_ExpectAnyArgs();
    esp_flash_get_size_ExpectAnyArgsAndReturn(0);
    app_main();
}