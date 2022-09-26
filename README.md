# Hey Ceedling Example

Modified the esp-idf "hello world" example to demonstrate unit testing esp32 projects on a host machine using ceedling to build and run unit tests. Target builds for the esp32 are done separately with the ESP-IDF toolchain.

Parts of hello world are still commented out. I could try getting freeRTOS includes to work OR I could just add the needed fuctions to a stub in test/support again. I'm too lazy to do either one right now but I think this repo effectively demonstrates adding new code to esp-idf projects and testing alongside existing esp-idf code. These esp-idf examples aren't really written to be good modular unit-testable code though, definitely read up on some TDD tutorials for how to do that.

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
# Troubleshooting
If your ceedling build doesn't work as above try running `ceedling clobber` first. This is needed if you add new plugins to your yaml file (e.g. adding expect_any_args to cmock)

useful tutorials: http://www.electronvector.com/blog/add-unit-tests-to-your-current-project-with-ceedling
Tips for mocking freeRTOS functions: https://github.com/ThrowTheSwitch/Ceedling/issues/579#issuecomment-1146343363

# Tracking things I tried to get this working
1. Removed all the calls to freeRTOS and esp_ functions from main, all tests  worked
2. Add back section to read chip info (esp_chip_info.h), need to include files from the xtensa tools (added as volume to docker) but actually we don't want the xtensa tools because that would mean building for the esp32 target! 

3. So we need to add `sys/cdefs.h` and similar files for linux 
... or can we mock it away? No, it generates warnings bc include file is in both test and source but doesn't resolve the error causing test build to fail

4. Also study the nvs_flash demo to figure out how they draw the line between hw dependency and mocks. Seems like they have hard coded mocks and stubs for a limited number of components

5. So do we need a mock for esp_chip_info.h and esp_flash.h ? No

6. Took out the esp_flash.h and everything for esp_chip_info.h works. Need to include mock_esp_chip_info.h in test though

7. Trying to add back esp_flash.h support. esp_flash.h has too many dependencies. Rather than refactor part of the esp_idf though we can just make a stub in /test/support with only the functions we care about.

8. Parts of hello world are still commented out. I could try getting freeRTOS includes to work OR I could just add the needed fuctions to a stub in test/support again. I'm too lazy to do either one right now but I think this repo effectively demonstrates adding new code to esp-idf projects and testing alongside existing esp-idf code. These esp-idf examples aren't really written to be good modular unit-testable code though, definitely read up on some TDD tutorials for how to do that.


