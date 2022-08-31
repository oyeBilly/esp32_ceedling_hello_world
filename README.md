# Hey Ceedling Example

Modified the esp-idf "hello world" example to demonstrate unit testing esp32 projects on a host machine using ceedling to build and run unit tests. Target builds for the esp32 are done separately with the ESP-IDF toolchain.

## Pre Reqs
1. ESP-IDF (https://github.com/espressif/esp-idf)
2. Throw The Switch's docker image: `docker pull throwtheswitch/madsciencelab`

## How to use example

1. Open your test environment with a volume for your project and a volume for the esp-idf: `docker run -it --rm -v $PWD:/project -v $PWD/../esp-idf:/esp-idf throwtheswitch/madsciencelab`
2. test the edge component (no dependency on esp-idf): `ceedling test:hey_ceedling`
You should get similar results:
~~~
Test 'test_hey_ceedling.c'
--------------------------
Compiling hey_ceedling.c...
Linking test_hey_ceedling.out...
Running test_hey_ceedling.out...

-----------
TEST OUTPUT
-----------
[test_hey_ceedling.c]
  - "hey ceedling"

--------------------
OVERALL TEST SUMMARY
--------------------
TESTED:  1
PASSED:  1
FAILED:  0
IGNORED: 0
~~~

3. Test the main function: `ceedling test`
~~~
Test 'test_hey_ceedling.c'
--------------------------
Running test_hey_ceedling.out...


Test 'test_hello_world_main.c'
------------------------------
/esp-idf/components/esp_hw_support/include/esp_chip_info.h:7:9: warning: #pragma once in main file
    7 | #pragma once
      |         ^~~~
Generating runner for test_hello_world_main.c...
Compiling test_hello_world_main_runner.c...
Linking test_hello_world_main.out...
Running test_hello_world_main.out...

-----------
TEST OUTPUT
-----------
[test_hey_ceedling.c]
  - "hey ceedling"

[test_hello_world_main.c]
  - "Hello world!"
  - "This is esp32 chip with 0 CPU core(s), WiFi/BT/BLE, "

--------------------
OVERALL TEST SUMMARY
--------------------
TESTED:  2
PASSED:  2
FAILED:  0
IGNORED: 0
~~~

# Step By Step Changes 
1. Removed all the calls to freeRTOS and esp_ functions from main, all tests  worked
2. Add back section to read chip info (esp_chip_info.h), need to include files from the xtensa tools (added as volume to docker) but actually we don't want the xtensa tools because that would mean building for the esp32 target! 

So we need to add `sys/cdefs.h` and similar files for linux 
... or can we mock it away? No, it generates warnings bc include file is in both test and source but doesn't resolve the error causing test build to fail

Also study the nvs_flash demo to figure out how they draw the line between hw dependency and mocks. Seems like they have hard coded mocks and stubs for a limited number of components

So do we need a mock for esp_chip_info.h and esp_flash.h ? No

Took out the esp_flash.h and everything for esp_chip_info.h works. Need to include mock_esp_chip_info.h in test though




