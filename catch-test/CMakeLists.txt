# 启用C++11或更高标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DCATCHDEBUG_MODE)

# Add a test-case for dtuart
set(main tests-main.cpp)
# set(SRC_LIST
    # ${CMAKE_SOURCE_DIR}/src/ML307R-DL.cpp
# )
add_executable(uart-tests
    ${main}
    # ${SRC_LIST}
    # uart-tests.cpp
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

# Add a test-case for timebook
set(main tests-main.cpp)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/timebook SRC_LIST)
add_executable(timebook-tests
    ${main}
    ${SRC_LIST}
    ${CMAKE_CURRENT_SOURCE_DIR}/timebook-tests.cpp
    ${CMAKE_SOURCE_DIR}/src/timebook/timebook.cpp
)
target_include_directories(timebook-tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(timebook-tests
    # EPDriver
    # lg
    sigc++
    libtimer
    sqlite3cpp
    serialib
    4gdtu
)
add_test(NAME timebook-tests
        COMMAND timebook-tests
)
# set_target_properties(timebook-tests PROPERTIES
#     CXX_STANDARD 14
#     CXX_STANDARD_REQUIRED ON
# )
# target_compile_definitions(timebook-tests PUBLIC -DCATCHDEBUG_MODE)

# Add a test-case for dtutime
set(main tests-main.cpp)
# set(SRC_LIST
#     ${CMAKE_SOURCE_DIR}/src/dtutime.cpp
#     ${CMAKE_SOURCE_DIR}/src/ML307R-DL.cpp
# )
add_executable(dtutime-tests
    ${main}
    # ${SRC_LIST}
    # dtutime-tests.cpp
)
target_include_directories(dtutime-tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(dtutime-tests
    # EPDriver
    # lg
    sigc++
    libtimer
    # sqlite
    serialib
)
add_test(NAME dtutime-tests
        COMMAND dtutime-tests
)

# Add a test-case for sqlite
set(main tests-main.cpp)
# set(SRC_LIST
#     ${CMAKE_SOURCE_DIR}/src/sqlite3db.cpp
#     # ${CMAKE_SOURCE_DIR}/src/ML307R-DL.cpp
# )
add_executable(sqlite-tests
    ${main}
    # ${SRC_LIST}
    # sqlite-tests.cpp
)
target_include_directories(sqlite-tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(sqlite-tests
    # EPDriver
    # lg
    sigc++
    # libtimer
    sqlite
    # serialib
)
add_test(NAME sqlite-tests
        COMMAND sqlite-tests
)