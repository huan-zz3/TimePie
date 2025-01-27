project(lg)

add_library(${PROJECT_NAME} SHARED IMPORTED GLOBAL)

# target_include_directories(lg INTERFACE 
#         ${CMAKE_CURRENT_SOURCE_DIR}
# )
set_target_properties(${PROJECT_NAME} PROPERTIES 
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/liblgpio.so
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}"
)
