aux_source_directory(
    ${PROJECT_SOURCE_DIR}/src
    SRC_LIST
)

add_executable(TimePie
    ${SRC_LIST}
)

target_include_directories(TimePie PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/interface
)

target_link_libraries(TimePie PRIVATE
    EPDriver
    lg
    sigc++
    libtimer
    sqlite
    serialib
)
