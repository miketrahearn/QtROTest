cmake_minimum_required(VERSION 3.24)

find_package(Qt6 REQUIRED COMPONENTS Quick RemoteObjects)

qt_standard_project_setup(REQUIRES 6.10)

set(USE_MANUAL_TYPE_REGISTRATION ON)
set(REPC_QML_ARG)

if(NOT ${USE_MANUAL_TYPE_REGISTRATION})
    #use the new QML argument for automatic QML type registration
    set(REPC_QML_ARG QML)
endif()

# Define the QML Module
qt_add_qml_module(ui
    URI ui
    VERSION 1.0
    DEPENDENCIES
        QtRemoteObjects # required for QML tooling
    STATIC
    SOURCES
        Backend.h
        Backend.cpp
        VehicleService.h
        VehicleService.cpp
        SOURCES RegistryModel.h RegistryModel.cpp
)

set(REP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../cas_qml_ui.rep")

qt_add_repc_merged(ui
    ${REPC_QML_ARG}
    SOURCES ${REP_FILE}
)

if(${USE_MANUAL_TYPE_REGISTRATION})
    target_sources(ui
        PRIVATE
            QMLTypeRegistration.h
    )

    set(REP_HEADER "${CMAKE_CURRENT_BINARY_DIR}/rep_cas_qml_ui_merged.h")

    # Enable AUTOMOC for the generated header so QML tooling see it
    set_source_files_properties(${REP_HEADER}
        PROPERTIES
            SKIP_AUTOMOC OFF
            SKIP_AUTOGEN OFF
    )
endif()

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(ui
    PUBLIC
        Qt6::Qml
        Qt6::RemoteObjects
)
