cmake_minimum_required(VERSION 3.6)

set(APP_NAME BrawlStars)

project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
   
     Classes/AppDelegate.cpp
     Classes/Character.cpp
     Classes/Weapon.cpp
     Classes/FSM.cpp
   
     Classes/BSLayer/FightControllerLayer.cpp
     Classes/BSLayer/BrawlStarsMenu.cpp
   
     Classes/BSScene/FightScene.cpp
     Classes/BSScene/StartScene.cpp
     Classes/BSScene/BaseScene.cpp
     Classes/BSScene/PauseScene.cpp
     Classes/BSScene/ScoreScene.cpp
     Classes/BSScene/RoomScene.cpp

     Classes/Entity/Hero/Hero.cpp
     Classes/Entity/Hero/Player.cpp 
     Classes/Entity/Hero/AI.cpp
     Classes/Entity//Box.cpp
     Classes/Entity/Entity.cpp
    
     Classes/State/State.cpp
     Classes/State/StateWander.cpp
     Classes/State/StateTrace.cpp
     Classes/State/StateRunAway.cpp
     Classes/State/StateAttackBox.cpp

     Classes/Util/AnimationUtils.cpp
     Classes/Util/ProgressView.cpp
     Classes/Util/TimeCounter.cpp
     Classes/Util/PathFinding.cpp
     Classes/Util/NotifyUtil.cpp
     Classes/Util/MathUtils.cpp
     )
list(APPEND GAME_HEADER

     Classes/AppDelegate.h
     Classes/Character.h
     Classes/Weapon.h
     Classes/FSM.h
   
     Classes/BSLayer/FightControllerLayer.h
     Classes/BSLayer/BrawlStarsMenu.h
   
     Classes/BSScene/FightScene.h
     Classes/BSScene/StartScene.h
     Classes/BSScene/BaseScene.h
     Classes/BSScene/PauseScene.h
     Classes/BSScene/ScoreScene.h
     Classes/BSScene/RoomScene.h

     Classes/Entity/Hero/Hero.h
     Classes/Entity/Hero/Player.h
     Classes/Entity/Hero/AI.h
     Classes/Entity//Box.h
     Classes/Entity/Entity.h
    
     Classes/State/State.h
     Classes/State/StateWander.h
     Classes/State/StateTrace.h
     Classes/State/StateRunAway.h
     Classes/State/StateAttackBox.h
     Classes/State/EnumStateType.h

     Classes/Util/AnimationUtils.h
     Classes/Util/ProgressView.h
     Classes/Util/TimeCounter.h
     Classes/Util/PathFinding.h
     Classes/Util/NotifyUtil.h
     Classes/Util/MathUtils.h


     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if(MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                              )
    elseif(IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
        set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "")
        set_xcode_property(${APP_NAME} CODE_SIGN_IDENTITY "iPhone Developer")
    endif()
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    set(APP_RES_DIR "$<TARGET_FILE_DIR:${APP_NAME}>/Resources")
    cocos_copy_target_res(${APP_NAME} COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
