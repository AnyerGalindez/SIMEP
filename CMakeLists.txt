cmake_minimum_required(VERSION 3.16)

project(SIMEP VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agregamos los componentes estándar requeridos
find_package(Qt6 REQUIRED COMPONENTS Quick PrintSupport)
find_package(Qt6 COMPONENTS Core Gui Widgets Positioning Location REQUIRED)

qt_standard_project_setup(REQUIRES 6.10)

if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appSIMEP
    main.cpp
)

qt_add_qml_module(appSIMEP
    URI SIMEP
    QML_FILES
        Main.qml

    SOURCES
        componenteproyecto.h componenteproyecto.cpp
        actividad.h actividad.cpp
        programa.h programa.cpp
        indicador.h indicador.cpp
        indicadornumerico.h indicadornumerico.cpp
        elementovisitor.h
        simulador.h simulador.cpp
        reportvisitorpdf.h reportvisitorpdf.cpp
        desastre.h desastre.cpp
        organizacion.h organizacion.cpp
        QML_FILES Main.qml
        QML_FILES
)

set_target_properties(appSIMEP PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Enlazamos las librerías
target_link_libraries(appSIMEP
    PRIVATE
        Qt6::Quick
        Qt6::PrintSupport
        Qt6::Core
            Qt6::Gui
            Qt6::Widgets
            Qt6::Positioning
            Qt6::Location
)

install(TARGETS appSIMEP
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)