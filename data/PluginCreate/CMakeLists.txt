project(TestPlugin LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

# 头文件目录
include_directories(${HEAD_PATH}/Base/PluginBase)
include_directories(${HEAD_PATH}/Plugins)

file(GLOB H_TestPlugin "./*.h")
file(GLOB CPP_TestPlugin "./*.cpp")
file(GLOB UI_TestPlugin "./*.ui")

add_library(TestPlugin SHARED
    ${H_TestPlugin}
    ${CPP_TestPlugin}
    ${UI_TestPlugin}
)

# 设置库名称
# set_target_properties(TestPlugin PROPERTIES
#     OUTPUT_NAME "libTestPlugin"
#     DEBUG_POSTFIX "_d"
#     RELEASE_POSTFIX ""
# )

target_link_libraries(TestPlugin PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(TestPlugin PRIVATE
    ${LIB_PATH}/PluginBase.lib
)

set_target_properties(TestPlugin PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins
)

target_compile_definitions(TestPlugin PRIVATE PLUGIN_MANAGE_LIBRARY)