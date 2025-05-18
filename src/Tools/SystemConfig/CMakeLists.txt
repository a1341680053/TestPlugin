project(SystemConfig LANGUAGES CXX)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# 头文件目录
include_directories("./../")
include_directories(${HEAD_PATH}/Tools)
include_directories(${HEAD_PATH}/Tools/SystemConfig)


file(GLOB H_SystemConfig "${HEAD_PATH}/Tools/SystemConfig/*.h")
file(GLOB CPP_SystemConfig "./*.cpp")

add_library(SystemConfig SHARED
    ${H_SystemConfig}
    ${CPP_SystemConfig}
)

# 设置库名称
# set_target_properties(SystemConfig PROPERTIES
#     OUTPUT_NAME "MSystemConfig"
#     DEBUG_POSTFIX "_d"
#     RELEASE_POSTFIX ""
# )

target_link_libraries(SystemConfig PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)

target_compile_definitions(SystemConfig PRIVATE SYSTEMCONFIG_LIBRARY)