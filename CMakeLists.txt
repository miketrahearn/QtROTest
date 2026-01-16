cmake_minimum_required(VERSION 3.24)

project(QtROTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(find_local_qtremoteobjects.cmake)

find_package(Qt6 REQUIRED COMPONENTS Quick RemoteObjects)

# Add this debug line to check which Qt Remote Objects we are using
message(STATUS "RESOLVED Qt6RemoteObjects_DIR: ${Qt6RemoteObjects_DIR}")

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appQtROTest
    main.cpp
)

qt_add_qml_module(appQtROTest
    URI QtROTest
    DEPENDENCIES
        QtRemoteObjects
    QML_FILES
        Main.qml
)

# To test a replica and source in the same executable we need to use "merged"

add_subdirectory(ui)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQtROTest PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQtROTest
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQtROTest
    PRIVATE
        Qt6::Quick
        Qt6::RemoteObjects
        ui
)

include(GNUInstallDirs)
install(TARGETS appQtROTest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
