project(PluginCreate LANGUAGES CXX)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

# 头文件目录
include_directories("./../")
include_directories(${HEAD_PATH}/Tools)
include_directories(${HEAD_PATH}/Tools/PluginCreate)


file(GLOB H_PluginCreate "${HEAD_PATH}/Tools/PluginCreate/*.h")
file(GLOB CPP_PluginCreate "./*.cpp")
file(GLOB UI_PluginCreate "./*.ui")

add_library(PluginCreate SHARED
    ${H_PluginCreate}
    ${CPP_PluginCreate}
    ${UI_PluginCreate}
)

# 设置库名称
# set_target_properties(PluginCreate PROPERTIES
#     OUTPUT_NAME "MPluginCreate"
#     DEBUG_POSTFIX "_d"
#     RELEASE_POSTFIX ""
# )

target_link_libraries(PluginCreate PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(PluginCreate PRIVATE
    ${LIB_PATH}/SystemConfig.lib
    ${LIB_PATH}/jsoncpp_static.lib
)

target_compile_definitions(PluginCreate PRIVATE PLUGIN_CREATE_LIBRARY)