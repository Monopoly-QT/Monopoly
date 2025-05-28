cmake_minimum_required(VERSION 3.16)

project(monopoly VERSION 0.1 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

 if (CMAKE_HOST_SYSTEM MATCHES "Darwin")
     set(CMAKE_PREFIX_PATH "~/Qt6.9.0/6.9.0/macos/lib/cmake")
 # elseif (CMAKE_HOST_SYSTEM MATCHES "Windows")
 #    set(CMAKE_PREFIX_PATH "C:/Qt/Qt6.9.0/6.9.0/mingw_64/lib/cmake")
 endif ()

#set(CMAKE_PREFIX_PATH "D:/Qt/6.9.0/mingw_64/lib/cmake")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appmonopoly
    main.cpp
        Resources/resourse.qrc
    ${JSON_FILES}
)

file(GLOB JSON_FILES "Resources/json/*.json")
foreach(json_file ${JSON_FILES})
    get_filename_component(filename ${json_file} NAME)
    configure_file(${json_file} ${CMAKE_CURRENT_BINARY_DIR}/json/${filename} COPYONLY)

    # 加入 build dependency
    list(APPEND JSON_OUTPUTS ${CMAKE_CURRENT_BINARY_DIR}/json/${filename})
endforeach()

# 讓你的 target 依賴這些 JSON 檔案
add_custom_target(copy_json ALL DEPENDS ${JSON_OUTPUTS})
add_dependencies(appmonopoly copy_json)

qt_add_qml_module(appmonopoly
    URI monopoly
    VERSION 1.0
    QML_FILES
        UI/Main.qml
        UI/DragonGate.qml
        UI/HorseRacing.qml
        UI/Turntable.qml
        UI/CardPopup.qml
        UI/Dice.qml
        UI/CheatCommandLine.qml
        UI/CheatCommandOpenBtn.qml
        UI/CardOpenBtn.qml
        UI/StateContainer.qml
        UI/RefreshPopup.qml
        UI/ShopPopup.qml
        UI/baseWidget/CostumBtn_Rec.qml
        UI/baseWidget/Standard_Text.qml
        UI/BuyLand_popUp.qml
        UI/UpgradeOrSell_popUp.qml
        UI/Message_popUp.qml
        UI/Bankruptcy_popUp.qml
        UI/EndPopUp.qml
        UI/Hospital_popup.qml
        SOURCES Dice/Dice.h
        SOURCES Dice/Dice.cpp
        RESOURCES Resources/resourse.qrc
        SOURCES Handler/EventHandler/eventHandler.h
        SOURCES Handler/EventHandler/eventHandler.cpp
        SOURCES Handler/EventHandler/eventHandlerGetterSetter.cpp
        SOURCES Land/Land.h
        SOURCES Land/Land.cpp
        SOURCES Map/map.h
        SOURCES Map/map.cpp
        SOURCES Handler/MapHandler/mapHandler.h
        SOURCES Player/Player.h
        SOURCES Player/Player.cpp
        SOURCES MovePoint/MovePoint.h
        SOURCES MovePoint/MovePoint.cpp
        SOURCES Handler/MapHandler/mapHandler.cpp
        SOURCES UseCardSetting/UseCardSetting.h
        SOURCES UseCardSetting/UseCardSetting.cpp
        SOURCES MiniGames/HorseRacing/HorseRacing.h
        SOURCES MiniGames/HorseRacing/HorseRacing.cpp
        SOURCES MiniGames/DragonGate/DragonGate.h
        SOURCES MiniGames/DragonGate/DragonGate.cpp
        SOURCES Hospital/Hospital.h
        SOURCES Hospital/Hospital.cpp
        SOURCES Shop/Shop.h
        SOURCES Shop/Shop.cpp
        SOURCES StateDisplay/StateDisplay.h
        SOURCES StateDisplay/StateDisplay.cpp
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
