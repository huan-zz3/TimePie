project(example)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create a sigc_example executable
set(sigc_example_name sigc)
set(sigc_target ${sigc_example_name}_${PROJECT_NAME})
set(sigc_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${sigc_target}.cpp)
add_executable(${sigc_target}
    ${sigc_SRC_LIST}
)
target_include_directories(${sigc_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${sigc_target} PRIVATE
    sigc++
)

# Create a EPD_example executable
set(epd_example_name EPD)
set(epd_target ${epd_example_name}_${PROJECT_NAME})
set(epd_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${epd_target}.cpp)
add_executable(${epd_target}
    ${epd_SRC_LIST}
)
target_include_directories(${epd_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${epd_target} PRIVATE
    lg
    EPDriver
    sigc++
    pthread
)

# Create a result_example executable
set(result_example_name result)
set(result_target ${result_example_name}_${PROJECT_NAME})
set(result_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${result_target}.cpp)
add_executable(${result_target}
    ${result_SRC_LIST}
)
target_include_directories(${result_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${result_target} PRIVATE
    # lg
    # EPDriver
    sigc++
    # pthread
)

# Create a KeySysfsDetect_example executable
set(keysysfsdetect_example_name keysysfsdetect)
set(keysysfsdetect_target ${keysysfsdetect_example_name}_${PROJECT_NAME})
set(keysysfsdetect_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${keysysfsdetect_target}.cpp)
add_executable(${keysysfsdetect_target}
    ${keysysfsdetect_SRC_LIST}
)
target_include_directories(${keysysfsdetect_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${keysysfsdetect_target} PRIVATE
    # lg
    # EPDriver
    # sigc++
    # pthread
)

# Create a timer_example executable
set(timer_example_name timer)
set(timer_target ${timer_example_name}_${PROJECT_NAME})
set(timer_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${timer_target}.cpp)
add_executable(${timer_target}
    ${timer_SRC_LIST}
)
target_include_directories(${timer_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${timer_target} PRIVATE
    libtimer
)

# Create a draw1_example executable
set(draw1_example_name draw1)
set(draw1_target ${draw1_example_name}_${PROJECT_NAME})
set(draw1_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${draw1_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/devicelayer.cpp
#     SRC_LIST
# )
add_executable(${draw1_target}
    ${draw1_SRC_LIST}
    # ${SRC_LIST}
    ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${draw1_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${draw1_target} PRIVATE
    lg
    EPDriver
    sigc++
    pthread
    libtimer
)

# Create a serialib_example executable
set(serialib_example_name serialib)
set(serialib_target ${serialib_example_name}_${PROJECT_NAME})
set(serialib_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${serialib_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/devicelayer.cpp
#     SRC_LIST
# )
add_executable(${serialib_target}
    ${serialib_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${serialib_target} PRIVATE 
    # ${CMAKE_SOURCE_DIR}/include
    # ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${serialib_target} PRIVATE
    # lg
    # EPDriver
    # sigc++
    # pthread
    # libtimer
    serialib
)

# Create a json_example executable
set(json_example_name json)
set(json_target ${json_example_name}_${PROJECT_NAME})
set(json_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${json_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/devicelayer.cpp
#     SRC_LIST
# )
add_executable(${json_target}
    ${json_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
set_target_properties(${json_target} PROPERTIES CMAKE_CXX_STANDARD 11)
target_include_directories(${json_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    # ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${json_target} PRIVATE
    # lg
    # EPDriver
    # sigc++
    # pthread
    # libtimer
    # json
)