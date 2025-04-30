find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Xml)

# 头文件目录
include_directories(${HEAD_PATH}/MainWindow)
include_directories(${HEAD_PATH}/Tools)
include_directories(${HEAD_PATH}/Base/PluginBase)
include_directories(${HEAD_PATH}/Plugins)
include_directories(${EV_GLOBE_SDK}/Dependencies/include)


file(GLOB H_MainWindow "${HEAD_PATH}/MainWindow/*.h")
file(GLOB CPP_MainWindow "./*.cpp")
file(GLOB UI_MainWindow "./*.ui")

set(PROJECT_SOURCES
    ${CPP_MainWindow}
    ${H_MainWindow}
    ${UI_MainWindow}
)
# 包含源文件目录，用于提升控件时可以找到源文件目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TestPlugin
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TestQt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TestPlugin SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TestPlugin
            ${PROJECT_SOURCES}
        )
    endif()
endif()


target_link_libraries(TestPlugin PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    )
    
target_link_libraries(TestPlugin PRIVATE
    ${LIB_PATH}/PluginBase.lib
    ${LIB_PATH}/PluginCreate.lib
)


if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TestPlugin)
endif()
set_target_properties(TestPlugin PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE   #设置为TRUE则不显示控制台输出
)

include(GNUInstallDirs)
install(TARGETS TestPlugin
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TestPlugin)
endif()
