cmake_minimum_required(VERSION 3.16)

project(monopoly VERSION 0.1 LANGUAGES CXX)

# 顯示 JSON 檔案到專案樹
file(GLOB JSON_FILES "${CMAKE_CURRENT_SOURCE_DIR}/json/*.json")
source_group("JSON Files" FILES ${JSON_FILES})

file(GLOB JSON_FILES "${CMAKE_CURRENT_SOURCE_DIR}/json/*")

foreach(json_file ${JSON_FILES})
    get_filename_component(filename ${json_file} NAME)
    configure_file(${json_file} ${CMAKE_CURRENT_BINARY_DIR}/json/${filename} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 下面要註解掉
set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt6.9.0\\6.9.0\\mingw_64\\lib\\cmake")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

#set(CMAKE_PREFIX_PATH "/Users/kai/Qt6.9.0/6.9.0/macos/lib/cmake")
#
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
# 上面要註解掉

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appmonopoly
    main.cpp
    resourse.qrc
    ${JSON_FILES}
)

qt_add_qml_module(appmonopoly
    URI monopoly
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES Dice.h
        SOURCES Dice.cpp
        RESOURCES resourse.qrc
        SOURCES eventHandler.h
        SOURCES eventHandler.cpp
        SOURCES Land.h
        SOURCES Land.cpp
        SOURCES map.h
        SOURCES map.cpp
        SOURCES mapHandler.h
        SOURCES Player.h
        SOURCES Player.cpp
        SOURCES MovePoint.h
        SOURCES MovePoint.cpp
        SOURCES mapHandler.cpp
        SOURCES UseCardSetting.h
        SOURCES UseCardSetting.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appmonopoly PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appmonopoly
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appmonopoly
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appmonopoly
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
