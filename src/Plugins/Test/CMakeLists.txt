project(Test LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

# 头文件目录
include_directories(${HEAD_PATH}/Base/PluginBase)
include_directories(${HEAD_PATH}/Plugins)

file(GLOB H_Test "./*.h")
file(GLOB CPP_Test "./*.cpp")
file(GLOB UI_Test "./*.ui")

add_library(Test SHARED
    ${H_Test}
    ${CPP_Test}
    ${UI_Test}
)

target_link_libraries(Test PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    # Qt${QT_VERSION_MAJOR}::Xml
)

target_link_libraries(Test PRIVATE
    ${LIB_PATH}/PluginBase.lib
)

set_target_properties(Test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/plugins
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/plugins
)

target_compile_definitions(Test PRIVATE PLUGIN_MANAGE_LIBRARY)