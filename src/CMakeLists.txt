set(DIRECTORIES
    eventbus
    gui/components
    gui/pages
    interaction/physicalkey
    interaction/screentouch
    interaction/loglight
    macro
    timebook
    bgservice
)

foreach(DIR ${DIRECTORIES})
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/${DIR} ${DIR}_LIST)
    list(APPEND SRC_LIST ${${DIR}_LIST})
endforeach()

add_executable(TimePie
    ${SRC_LIST}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(TimePie PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(TimePie PRIVATE
    macro
    epdcpp
    sigc++
    libtimer
    sqlite3cpp
    eventpp
    4gdtu
    glog
)
