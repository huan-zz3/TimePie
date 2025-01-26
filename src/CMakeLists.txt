add_executable(TimePie
        main.cpp
        ${PROJECT_SOURCE_DIR}/include/interface.h
        ${PROJECT_SOURCE_DIR}/include/predefine.h
)

 target_link_libraries(TimePie
         EPDriver
 )