project(is_land_sea LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Test)

# 头文件目录
include_directories(${HEAD_PATH}/Tools)

add_executable(is_land_sea test_land_sea.cpp)

target_link_libraries(is_land_sea PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    ${LIB_PATH}/ToolsLib.lib
)

target_link_libraries(is_land_sea PRIVATE  Qt${QT_VERSION_MAJOR}::Test)


add_test( 
    NAME is_land_sea_test
    COMMAND is_land_sea
)