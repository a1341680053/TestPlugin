project(SettingPlugin LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Xml)

# 头文件目录
include_directories(${HEAD_PATH}/Base/PluginBase)
include_directories(${HEAD_PATH}/Plugins)

file(GLOB H_SettingPlugin "./*.h")
file(GLOB CPP_SettingPlugin "./*.cpp")
file(GLOB UI_SettingPlugin "./*.ui")

add_library(SettingPlugin SHARED
    ${H_SettingPlugin}
    ${CPP_SettingPlugin}
    ${UI_SettingPlugin}
)

target_link_libraries(SettingPlugin PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
)

target_link_libraries(SettingPlugin PRIVATE
    ${LIB_PATH}/PluginBase.lib
)

# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/plugins)

set_target_properties(SettingPlugin PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins
)

target_compile_definitions(SettingPlugin PRIVATE PLUGIN_SETTING_LIBRARY)

