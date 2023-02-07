cmake_minimum_required(VERSION 3.16)

project(IdlConverter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "-no-pie")

list(APPEND CMAKE_PREFIX_PATH "/usr/local/Qt6")

find_package(Qt6 COMPONENTS Widgets REQUIRED)
qt_standard_project_setup()

add_executable(idlconverter
    src/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
    src/aboutdialog.ui
    src/aboutdialog.cpp
    src/licensedialog.ui
    src/licensedialog.cpp
)

target_link_libraries(idlconverter PRIVATE Qt6::Widgets)

install(
    TARGETS idlconverter 
    RUNTIME DESTINATION bin
)

install(
    FILES module/linux/idl2xml
    PERMISSIONS OWNER_EXECUTE
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    FILES resource/logo.png
    DESTINATION resource
)
