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