# Hey Ceedling Example

Modified the esp-idf "hello world" example to demonstrate unit testing esp32 projects on a host machine using ceedling to build and run unit tests. Target builds for the esp32 are done separately with the ESP-IDF toolchain.

## Pre Reqs
1. ESP-IDF (https://github.com/espressif/esp-idf)
2. Throw The Switch's docker image: `docker pull throwtheswitch/madsciencelab`

## How to use example

1. Open your test environment: `docker run -it --rm -v $PWD:/project throwtheswitch/madsciencelab` or use the one below to include the esp-idf volume too `docker run -it --rm -v $PWD:/project -v $PWD/../esp-idf:/esp-idf throwtheswitch/madsciencelab` or this one which has xtensa tools too `docker run -it --rm -v $PWD:/project -v $PWD/../esp-idf:/esp-idf -v $PWD/../../.espressif/tools/xtensa-esp32-elf/esp-2021r2-patch3-8.4.0/xtensa-esp32-elf/xtensa-esp32-elf:/xtensa_tools throwtheswitch/madsciencelab`
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


# Step By Step Changes 
1. Removed all the calls to freeRTOS and esp_ functions from main, all tests  worked
2. Add back section to read chip info (esp_chip_info.h), need to include files from the xtensa tools (added as volume to docker) but actually we don't want the xtensa tools because that would mean building for the esp32 target! 

So we need to add `sys/cdefs.h` and similar files for linux 
... or can we mock it away? No, it generates warnings bc include file is in both test and source but doesn't resolve the error causing test build to fail

Also study the nvs_flash demo to figure out how they draw the line between hw dependency and mocks. Seems like they have hard coded mocks and stubs for a limited number of components

So do we need a mock for esp_chip_info.h and esp_flash.h ?




