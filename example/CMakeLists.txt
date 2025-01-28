project(example)

set(my_sigc_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/my_sigc_${PROJECT_NAME}.cpp)
add_executable(my_sigc_${PROJECT_NAME}
    ${my_sigc_SRC_LIST}
)
target_include_directories(my_sigc_${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
target_link_libraries(my_sigc_${PROJECT_NAME} PRIVATE
    sigc++
)
