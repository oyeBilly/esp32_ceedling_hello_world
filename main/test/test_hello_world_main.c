#include "unity.h"
#include "cmock.h"

#include "mock_hey_ceedling.h"

#include "hello_world_main.h"

void test_app_main_should_callHeyCeedling(void)
{
    hey_ceedling_ExpectAndReturn(0);

    app_main();
}