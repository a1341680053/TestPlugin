cmake_minimum_required(VERSION 3.5)

project(TestPlugin VERSION 0.1 LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译器编码选项
if (MSVC)
    # MSVC 编译器：强制使用 UTF-8 编码（Visual Studio 2015 及以上）
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
else()
    # GCC/Clang 编译器：设置输入和输出编码为 UTF-8
    add_compile_options(-finput-charset=UTF-8)
    add_compile_options(-fexec-charset=UTF-8)
endif()


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(HEAD_PATH ${CMAKE_SOURCE_DIR}/include)
set(LIB_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})

set(EV_GLOBE_SDK $ENV{EV_Globesdk_Debugdll64}/..)
set(EV_GLOBE_RUN $ENV{EV_Globesdk_Bin64})

set(ENV{PATH} "$ENV{PATH}:${EV_GLOBE_RUN}")

add_subdirectory(src)