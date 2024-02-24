cmake_minimum_required(VERSION 3.5)

project(3D_Viewer VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        display.cpp
        display.h
        giflib/dgif_lib.c
        giflib/egif_lib.c
        giflib/gif_err.c
        giflib/gif_font.c
        giflib/gif_hash.c
        giflib/gif_hash.h
        giflib/gif_lib.h
        giflib/gif_lib_private.h
        giflib/gifalloc.c
        giflib/quantize.c
        gifimage/qgifglobal.h
        gifimage/qgifimage_p.h
        gifimage/qgifimage.h
        gifimage/qgifimage.cpp

        ../Backend/back.h
#        ../Backend/athen.c
#        ../Backend/files.c
#        ../Backend/free.c
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3D_Viewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3D_Viewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3D_Viewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3D_Viewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

add_library(viewer STATIC IMPORTED)
set_target_properties(viewer PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../viewer.a)

target_link_libraries(3D_Viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3D_Viewer PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(3D_Viewer PRIVATE viewer)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.3D_Viewer)
endif()
set_target_properties(3D_Viewer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS 3D_Viewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3D_Viewer)
endif()
