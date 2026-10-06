cmake_minimum_required(VERSION 3.19)
project(TodoConsole LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(TodoConsole
    main.cpp
    Task.h
    Storage.h Storage.cpp
    .gitignore
)

target_link_libraries(TodoConsole
    PRIVATE
        Qt::Core
)

install(TARGETS TodoConsole
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
