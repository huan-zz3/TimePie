# 启用C++11或更高标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DCATCHDEBUG_MODE)

set(main tests-main.cpp)
set(SRC_LIST
    ${CMAKE_SOURCE_DIR}/src/ML307R-DL.cpp
)
add_executable(uart-tests
    ${main}
    ${SRC_LIST}
    uart-tests.cpp
)
target_include_directories(uart-tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(uart-tests
    # EPDriver
    # lg
    sigc++
    libtimer
    # sqlite3
    serialib
)
add_test(NAME uart-tests
        COMMAND uart-tests
)
