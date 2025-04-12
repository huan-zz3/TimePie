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

# Create a sigc_mutilthread_example executable
set(sigc_mutilthread_example_name sigc_mutilthread)
set(sigc_mutilthread_target ${sigc_mutilthread_example_name}_${PROJECT_NAME})
set(sigc_mutilthread_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${sigc_mutilthread_target}.cpp)
add_executable(${sigc_mutilthread_target}
    ${sigc_mutilthread_SRC_LIST}
)
target_include_directories(${sigc_mutilthread_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${sigc_mutilthread_target} PRIVATE
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
    
    epdcpp
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
    
    # epdcpp
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
    
    # epdcpp
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
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${draw1_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${draw1_target} PRIVATE
    
    epdcpp
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
    
    # epdcpp
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
    
    # epdcpp
    # sigc++
    # pthread
    # libtimer
    # json
)

# Create a draw_plrc_example executable (Point Line Rectangle Circle)
set(draw_plrc_example_name draw_plrc)
set(draw_plrc_target ${draw_plrc_example_name}_${PROJECT_NAME})
set(draw_plrc_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${draw_plrc_target}.cpp)
# aux_source_directory(
    # ${CMAKE_SOURCE_DIR}/devicelayer.cpp
    # SRC_LIST
# )
add_executable(${draw_plrc_target}
    ${draw_plrc_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${draw_plrc_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${draw_plrc_target} PRIVATE
    
    epdcpp
    sigc++
    pthread
    libtimer
)

# Create a draw_charstrnum_example executable (Point Line Rectangle Circle)
set(draw_charstrnum_example_name draw_charstrnum)
set(draw_charstrnum_target ${draw_charstrnum_example_name}_${PROJECT_NAME})
set(draw_charstrnum_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${draw_charstrnum_target}.cpp)
# aux_source_directory(
    # ${CMAKE_SOURCE_DIR}/devicelayer.cpp
    # SRC_LIST
# )
add_executable(${draw_charstrnum_target}
    ${draw_charstrnum_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${draw_charstrnum_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${draw_charstrnum_target} PRIVATE
    
    epdcpp
    sigc++
    pthread
    libtimer
)

# Create a draw_timedate_example executable (Point Line Rectangle Circle)
set(draw_timedate_example_name draw_timedate)
set(draw_timedate_target ${draw_timedate_example_name}_${PROJECT_NAME})
set(draw_timedate_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${draw_timedate_target}.cpp)
# aux_source_directory(
    # ${CMAKE_SOURCE_DIR}/devicelayer.cpp
    # SRC_LIST
# )
add_executable(${draw_timedate_target}
    ${draw_timedate_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${draw_timedate_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${draw_timedate_target} PRIVATE
    
    epdcpp
    sigc++
    pthread
    libtimer
)

# Create a draw_bmpvarymode_example executable (Point Line Rectangle Circle)
set(draw_bmpvarymode_example_name draw_bmpvarymode)
set(draw_bmpvarymode_target ${draw_bmpvarymode_example_name}_${PROJECT_NAME})
set(draw_bmpvarymode_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${draw_bmpvarymode_target}.cpp)
# aux_source_directory(
    # ${CMAKE_SOURCE_DIR}/devicelayer.cpp
    # SRC_LIST
# )
add_executable(${draw_bmpvarymode_target}
    ${draw_bmpvarymode_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${draw_bmpvarymode_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${draw_bmpvarymode_target} PRIVATE
    
    epdcpp
    sigc++
    pthread
    libtimer
)

# Create a draw_partcleanshow_example executable (Point Line Rectangle Circle)
set(draw_partcleanshow_example_name draw_partcleanshow)
set(draw_partcleanshow_target ${draw_partcleanshow_example_name}_${PROJECT_NAME})
set(draw_partcleanshow_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${draw_partcleanshow_target}.cpp)
# aux_source_directory(
    # ${CMAKE_SOURCE_DIR}/devicelayer.cpp
    # SRC_LIST
# )
add_executable(${draw_partcleanshow_target}
    ${draw_partcleanshow_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${draw_partcleanshow_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${draw_partcleanshow_target} PRIVATE
    
    epdcpp
    sigc++
    pthread
    libtimer
)

# Create a draw_gesture_example executable (Point Line Rectangle Circle)
set(draw_gesture_example_name draw_gesture)
set(draw_gesture_target ${draw_gesture_example_name}_${PROJECT_NAME})
set(draw_gesture_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${draw_gesture_target}.cpp)
# aux_source_directory(
    # ${CMAKE_SOURCE_DIR}/devicelayer.cpp
    # SRC_LIST
# )
add_executable(${draw_gesture_target}
    ${draw_gesture_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${draw_gesture_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${draw_gesture_target} PRIVATE
    
    epdcpp
    sigc++
    pthread
    libtimer
)

# Create a EPD_touch_example executable
set(EPD_touch_example_name EPD_touch)
set(EPD_touch_target ${EPD_touch_example_name}_${PROJECT_NAME})
set(EPD_touch_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${EPD_touch_target}.cpp)
# aux_source_directory(
    # ${CMAKE_SOURCE_DIR}/devicelayer.cpp
    # SRC_LIST
# )
add_executable(${EPD_touch_target}
    ${EPD_touch_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${EPD_touch_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${EPD_touch_target} PRIVATE
    epdcpp
    # sigc++
    pthread
    libtimer
    macro
)

# Create a draw_multidirectionalbmp_example executable
set(draw_multidirectionalbmp_example_name draw_multidirectionalbmp)
set(draw_multidirectionalbmp_target ${draw_multidirectionalbmp_example_name}_${PROJECT_NAME})
set(draw_multidirectionalbmp_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${draw_multidirectionalbmp_target}.cpp)
# aux_source_directory(
    # ${CMAKE_SOURCE_DIR}/devicelayer.cpp
    # SRC_LIST
# )
add_executable(${draw_multidirectionalbmp_target}
    ${draw_multidirectionalbmp_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${draw_multidirectionalbmp_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${draw_multidirectionalbmp_target} PRIVATE
    
    epdcpp
    sigc++
    pthread
    libtimer
)

# Create a draw_pagecomp_example executable
set(draw_pagecomp_example_name draw_pagecomp)
set(draw_pagecomp_target ${draw_pagecomp_example_name}_${PROJECT_NAME})
set(draw_pagecomp_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${draw_pagecomp_target}.cpp)
aux_source_directory(
    ${CMAKE_SOURCE_DIR}/page
    SRC_LIST1
)
aux_source_directory(
    ${CMAKE_SOURCE_DIR}/component
    SRC_LIST2
)
add_executable(${draw_pagecomp_target}
    ${draw_pagecomp_SRC_LIST}
    ${SRC_LIST1}
    ${SRC_LIST2}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${draw_pagecomp_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
    ${CMAKE_SOURCE_DIR}/page
    ${CMAKE_SOURCE_DIR}/component
)
target_link_libraries(${draw_pagecomp_target} PRIVATE
    
    epdcpp
    sigc++
    pthread
    libtimer
)

# Create a stdthread_example executable
set(stdthread_example_name stdthread)
set(stdthread_target ${stdthread_example_name}_${PROJECT_NAME})
set(stdthread_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${stdthread_target}.cpp)
add_executable(${stdthread_target}
    ${stdthread_SRC_LIST}
)
target_include_directories(${stdthread_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${stdthread_target} PRIVATE
    
    # epdcpp
    # sigc++
    # pthread
    # libtimer
)
# Create a keyepd_example executable
set(keyepd_example_name keyepd)
set(keyepd_target ${keyepd_example_name}_${PROJECT_NAME})
set(keyepd_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${keyepd_target}.cpp)
add_executable(${keyepd_target}
    ${keyepd_SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
    # ${CMAKE_SOURCE_DIR}/src/keyepd.cpp
)
target_include_directories(${keyepd_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${keyepd_target} PRIVATE
    
    epdcpp
    sigc++
    # pthread
    # libtimer
)
# Create a TimerModeSelection_example executable
set(TimerModeSelection_example_name TimerModeSelection)
set(TimerModeSelection_target ${TimerModeSelection_example_name}_${PROJECT_NAME})
set(TimerModeSelection_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${TimerModeSelection_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/page
#     SRC_LIST1
# )
aux_source_directory(
    ${CMAKE_SOURCE_DIR}/src/gui/components
    SRC_LIST2
)
add_executable(${TimerModeSelection_target}
    ${TimerModeSelection_SRC_LIST}
    # ${SRC_LIST1}
    ${SRC_LIST2}
    ${CMAKE_SOURCE_DIR}/src/gui/pages/epd_pages.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/pages/TimerModeSelection.cpp
    ${CMAKE_SOURCE_DIR}/src/interaction/screentouch/keyepd.cpp
)
target_include_directories(${TimerModeSelection_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(${TimerModeSelection_target} PRIVATE
    epdcpp
    sigc++
    pthread
    libtimer
)
# Create a TimerDashboard_example executable
set(TimerDashboard_example_name TimerDashboard)
set(TimerDashboard_target ${TimerDashboard_example_name}_${PROJECT_NAME})
set(TimerDashboard_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${TimerDashboard_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/page
#     SRC_LIST1
# )
aux_source_directory(
    ${CMAKE_SOURCE_DIR}/src/gui/components
    SRC_LIST2
)
add_executable(${TimerDashboard_target}
    ${TimerDashboard_SRC_LIST}
    # ${SRC_LIST1}
    ${SRC_LIST2}
    ${CMAKE_SOURCE_DIR}/src/gui/pages/epd_pages.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/pages/TimerDashboard.cpp
    ${CMAKE_SOURCE_DIR}/src/interaction/screentouch/keyepd.cpp
    ${CMAKE_SOURCE_DIR}/src/bgservice/servicelayer.cpp
    ${CMAKE_SOURCE_DIR}/src/eventbus/eventinstance.cpp
)
target_include_directories(${TimerDashboard_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(${TimerDashboard_target} PRIVATE
    epdcpp
    sigc++
    pthread
    libtimer
    4gdtu
    eventpp
)
# Create a TimerCategoryGrid_example executable
set(TimerCategoryGrid_example_name TimerCategoryGrid)
set(TimerCategoryGrid_target ${TimerCategoryGrid_example_name}_${PROJECT_NAME})
set(TimerCategoryGrid_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${TimerCategoryGrid_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/page
#     SRC_LIST1
# )
aux_source_directory(
    ${CMAKE_SOURCE_DIR}/src/gui/components
    SRC_LIST2
)
add_executable(${TimerCategoryGrid_target}
    ${TimerCategoryGrid_SRC_LIST}
    # ${SRC_LIST1}
    ${SRC_LIST2}
    ${CMAKE_SOURCE_DIR}/src/gui/pages/epd_pages.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/pages/TimerCategoryGrid.cpp
    ${CMAKE_SOURCE_DIR}/src/interaction/screentouch/keyepd.cpp
    ${CMAKE_SOURCE_DIR}/src/bgservice/servicelayer.cpp
    ${CMAKE_SOURCE_DIR}/src/eventbus/eventinstance.cpp
)
target_include_directories(${TimerCategoryGrid_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(${TimerCategoryGrid_target} PRIVATE
    epdcpp
    sigc++
    pthread
    libtimer
    4gdtu
    eventpp
)

# Create a dtutime_example executable
set(dtutime_example_name dtutime)
set(dtutime_target ${dtutime_example_name}_${PROJECT_NAME})
set(dtutime_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${dtutime_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/page
#     SRC_LIST1
# )
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/component
#     SRC_LIST2
# )
add_executable(${dtutime_target}
    ${dtutime_SRC_LIST}
    # ${SRC_LIST1}
    # ${SRC_LIST2}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
    # ${CMAKE_SOURCE_DIR}/src/servicelayer.cpp
    # ${CMAKE_SOURCE_DIR}/src/dtutime.cpp
    # ${CMAKE_SOURCE_DIR}/src/ML307R-DL.cpp
)
target_include_directories(${dtutime_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/interface
    # ${CMAKE_SOURCE_DIR}/page
    # ${CMAKE_SOURCE_DIR}/component
)
target_link_libraries(${dtutime_target} PRIVATE
    
    epdcpp
    sigc++
    pthread
    libtimer
    serialib
)
# Create a eventpp_example executable
set(eventpp_example_name eventpp)
set(eventpp_target ${eventpp_example_name}_${PROJECT_NAME})
set(eventpp_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${eventpp_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/devicelayer.cpp
#     SRC_LIST
# )
add_executable(${eventpp_target}
    ${eventpp_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${eventpp_target} PRIVATE 
    # ${CMAKE_SOURCE_DIR}/include
    # ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${eventpp_target} PRIVATE
    eventpp
)
# Create a eventpploop_example executable
set(eventpploop_example_name eventpploop)
set(eventpploop_target ${eventpploop_example_name}_${PROJECT_NAME})
set(eventpploop_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${eventpploop_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/devicelayer.cpp
#     SRC_LIST
# )
add_executable(${eventpploop_target}
    ${eventpploop_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${eventpploop_target} PRIVATE 
    # ${CMAKE_SOURCE_DIR}/include
    # ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${eventpploop_target} PRIVATE
    eventpp
)
# Create a eventppapply_example executable
set(eventppapply_example_name eventppapply)
set(eventppapply_target ${eventppapply_example_name}_${PROJECT_NAME})
set(eventppapply_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${eventppapply_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/devicelayer.cpp
#     SRC_LIST
# )
add_executable(${eventppapply_target}
    ${eventppapply_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${eventppapply_target} PRIVATE 
    # ${CMAKE_SOURCE_DIR}/include
    # ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${eventppapply_target} PRIVATE
    eventpp
)
# Create a eventbus_example executable
set(eventbus_example_name eventbus)
set(eventbus_target ${eventbus_example_name}_${PROJECT_NAME})
set(eventbus_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${eventbus_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/devicelayer.cpp
#     SRC_LIST
# )
add_executable(${eventbus_target}
    ${eventbus_SRC_LIST}
    # ${SRC_LIST}
    # ${CMAKE_SOURCE_DIR}/src/devicelayer.cpp
)
target_include_directories(${eventbus_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    # ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${eventbus_target} PRIVATE
    eventpp
)

# Create a ledsysfs_example executable
set(ledsysfs_example_name ledsysfs)
set(ledsysfs_target ${ledsysfs_example_name}_${PROJECT_NAME})
set(ledsysfs_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${ledsysfs_target}.cpp)
# aux_source_directory(
#     ${CMAKE_SOURCE_DIR}/devicelayer.cpp
#     SRC_LIST
# )
add_executable(${ledsysfs_target}
    ${ledsysfs_SRC_LIST}
    # ${SRC_LIST}
    ${CMAKE_SOURCE_DIR}/src/interaction/loglight/ledinstance.cpp
    ${CMAKE_SOURCE_DIR}/src/interaction/loglight/ledsysfs.cpp
)
target_include_directories(${ledsysfs_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    # ${CMAKE_SOURCE_DIR}/interface
)
target_link_libraries(${ledsysfs_target} PRIVATE
    # eventpp
    macro
)

# Create a glog_example executable
set(glog_example_name glog)
set(glog_target ${glog_example_name}_${PROJECT_NAME})
set(glog_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${glog_target}.cpp)
add_executable(${glog_target}
    ${glog_SRC_LIST}
)
target_include_directories(${glog_target} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(${glog_target} PRIVATE
    glog
)