aux_source_directory(
    ${PROJECT_SOURCE_DIR}/src
    SRC_LIST
)
aux_source_directory(
    ${PROJECT_SOURCE_DIR}/component
    COMPOMENT_LIST
)
aux_source_directory(
    ${PROJECT_SOURCE_DIR}/page
    PAGE_LIST
)

add_executable(TimePie
    ${SRC_LIST}
    ${COMPOMENT_LIST}
    ${PAGE_LIST}
)

target_include_directories(TimePie PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/interface
    ${PROJECT_SOURCE_DIR}/component
    ${PROJECT_SOURCE_DIR}/page
)

target_link_libraries(TimePie PRIVATE
    EPDriver
    lg
    sigc++
    libtimer
    sqlite
    serialib
    pthread
    eventpp
)
