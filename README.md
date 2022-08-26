# Hey Ceedling Example

Modified the esp-idf "hello world" example to demonstrate unit testing esp32 projects on a host machine using ceedling to build and run unit tests. Target builds for the esp32 are done separately with the ESP-IDF toolchain.

## Pre Reqs
1. ESP-IDF (https://github.com/espressif/esp-idf)
2. Throw The Switch's docker image: `docker pull throwtheswitch/madsciencelab`

## How to use example

1. Open your test environment: `docker run -it --rm -v $PWD:/project throwtheswitch/madsciencelab`
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
Compiling hello_world_main.c...
In file included from /esp/freertos/FreeRTOS-Kernel/include/freertos/FreeRTOS.h:79,
                 from main/hello_world_main.c:9:
/esp/newlib/platform_include/sys/reent.h:9:14: fatal error: sys/reent.h: No such file or directory
    9 | #include_next<sys/reent.h>
      |              ^~~~~~~~~~~~~
compilation terminated.
ERROR: Shell command failed.
~~~

*NOTICE in project.yml include section* that the file is explicitly included! On windows running wsl I get an error the arg is too big, I wonder if it is truncated on mac and that's why it appears missing?


## Example folder contents

The project **hello_world** contains one source file in C language [hello_world_main.c](main/hello_world_main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── pytest_hello_world.py      Python script used for automated testing
├── main
│   ├── CMakeLists.txt
│   └── hello_world_main.c
└── README.md                  This is the file you are currently reading
```

For more information on structure and contents of ESP-IDF projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the ESP-IDF Programming Guide.

## Troubleshooting

* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.

## Technical support and feedback

n/a
