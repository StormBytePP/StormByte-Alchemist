set(CMAKE_AUTOUIC 	ON)
set(CMAKE_AUTOMOC 	ON)
set(CMAKE_AUTORCC 	ON)
set(DIST_DIR		"${CMAKE_BINARY_DIR}/dist")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES Alchemist_es_ES.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Alchemist
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    target_compile_features(Alchemist PRIVATE cxx_std_20)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Alchemist APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Alchemist SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Alchemist
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Alchemist PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Alchemy)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.StormByte.Alchemist)
endif()
set_target_properties(Alchemist PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Alchemist
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
if (WIN32)
	include(ConfigQtInstaller)
	qt_generate_deploy_app_script(
    		TARGET Alchemist
    		OUTPUT_SCRIPT deploy_script
    		NO_UNSUPPORTED_PLATFORM_ERROR
	)
	install(SCRIPT ${deploy_script})
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Alchemist)
endif()
