project(ToolsLib LANGUAGES CXX)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

# 头文件目录
include_directories("./../")
include_directories(${HEAD_PATH}/Tools)
include_directories(${HEAD_PATH}/Tools/ToolsLib)
include_directories(${HEAD_PATH}/GDAL)


file(GLOB H_ToolsLib "${HEAD_PATH}/Tools/ToolsLib/*.h")
file(GLOB CPP_ToolsLib "./*.cpp")
# file(GLOB UI_ToolsLib "./*.ui")

add_library(ToolsLib SHARED
    ${H_ToolsLib}
    ${CPP_ToolsLib}
    # ${UI_ToolsLib}
)

# 设置库名称
# set_target_properties(ToolsLib PROPERTIES
#     OUTPUT_NAME "MToolsLib"
#     DEBUG_POSTFIX "_d"
#     RELEASE_POSTFIX ""
# )

target_link_libraries(ToolsLib PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(ToolsLib PRIVATE
    ${LIB_PATH}/gdal_i.lib
)

target_compile_definitions(ToolsLib PRIVATE TOOLS_LIBRARY)