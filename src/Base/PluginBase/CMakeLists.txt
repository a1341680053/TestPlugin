project(PluginBase LANGUAGES CXX)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Xml)

# 头文件目录
include_directories(${HEAD_PATH}/Base/PluginBase)
include_directories(${HEAD_PATH}/XML)

file(GLOB H_PluginBase "${HEAD_PATH}/Base/PluginBase/*.h")
file(GLOB CPP_PluginBase "./*.cpp")

add_library(PluginBase SHARED
    ${CPP_PluginBase}
    ${H_PluginBase}
)

# 设置库名称
set_target_properties(PluginBase PROPERTIES
    OUTPUT_NAME "PluginBase"
    DEBUG_POSTFIX ""
    RELEASE_POSTFIX ""
)

target_link_libraries(PluginBase PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
)

target_compile_definitions(PluginBase PRIVATE PLUGIN_BASE_LIBRARY)