PROJECT(rxcalc LANGUAGES CXX C VERSION 0.7.0)
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
cmake_policy(VERSION 3.10)

set(RXCALC_VERSION "${PROJECT_VERSION}")

message(STATUS "Configuring RxCalc: VERSION ${RXCALC_VERSION}")

set(PROJECT_VENDOR "Vyacheslav Verkhovin. This program is licensed under the GNU GPL")
set(PROJECT_COPYRIGHT_YEAR "2014")
set(PROJECT_DOMAIN_FIRST "qucs")
set(PROJECT_DOMAIN_SECOND "org")



#SET(CMAKE_BUILD_TYPE Debug)

add_compile_definitions(APP_VERSION="${RXCALC_VERSION}")
add_compile_definitions(APP_NAME="RxCalc")

SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

#configure the header config.h
#CONFIGURE_FILE (
#    "${PROJECT_SOURCE_DIR}/../config.h.cmake"
#    "${PROJECT_BINARY_DIR}/config.h"
#)

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

find_package(Qt6 REQUIRED COMPONENTS Core  Widgets Svg SvgWidgets PrintSupport)
  include_directories(
      ${Qt6Core_INCLUDE_DIRS}
      ${Qt6Widgets_INCLUDE_DIRS}
      ${Qt6Svg_INCLUDE_DIRS}
      ${Qt6SvgWidgets_INCLUDE_DIRS}
      ${Qt6PrintSupport_INCLUDE_DIRS}
      )

set(QT_VERSION ${Qt6Core_VERSION})

if (${QT_VERSION} VERSION_LESS "6.7.0")
    set(CMAKE_CXX_STANDARD 17)
else()
    set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_definitions(_CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS)
        add_compile_options(/permissive- /Zc:__cplusplus /Zc:preprocessor /MP /Od /vmg)
        add_compile_options(/wd4244 /wd4267 /wd4312)
    else()
        add_compile_options(-Wall -Wextra -O0 -g)
        if (CMAKE_CXX_COMPILER_ID MATCHES "^AppleClang$|^Clang$")
            add_compile_options(-Wno-ignored-attributes)
        endif()
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_definitions(_CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS)
        string(REGEX REPLACE "/W1" "/w" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        add_compile_options(/permissive- /Zc:__cplusplus /Zc:preprocessor /MP /vmg)
        add_link_options(/OPT:REF /OPT:ICF)
    else()
        add_compile_options(-w)
    endif()
endif()

ADD_DEFINITIONS(${QT_DEFINITIONS})

SET(RXCALC_SRCS
	sources/main.cpp
    sources/rxcalc.cpp
    sources/stage.cpp
    sources/system.cpp
    sources/rxtable.cpp
    sources/rxtablecell.cpp
)

SET(RXCALC_MOC_HDRS
    sources/main.h
    sources/rxcalc.h
    sources/stage.h
    sources/system.h
    sources/rxtable.h
    sources/rxtablecell.h
)

SET(RESOURCES resources/images.qrc)
QT6_WRAP_CPP(RXCALC_MOC_SRCS ${RXCALC_MOC_HDRS})
QT6_ADD_RESOURCES(RESOURCES_SRCS ${RESOURCES})



IF(APPLE)
  # set information on Info.plist file
	SET(MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME} ${PROJECT_VERSION}")
  SET(MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_NAME} ${PROJECT_VERSION}")
  SET(MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_NAME} ${PROJECT_VERSION}")
  SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}")
  SET(MACOSX_BUNDLE_COPYRIGHT "${PROJECT_COPYRIGHT_YEAR} ${PROJECT_VENDOR}")
  SET(MACOSX_BUNDLE_GUI_IDENTIFIER "${PROJECT_DOMAIN_SECOND}.${PROJECT_DOMAIN_FIRST}")
  SET(MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}")
  SET(MACOSX_BUNDLE_ICON_FILE rxcalc.icns)

  # set where in the bundle to put the icns file
  SET_SOURCE_FILES_PROPERTIES(mac/rxcalc.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
  # include the icns file in the target
  SET(RXCALC_SRCS ${RCALC_SRCS} mac/rxcalc.icns)

ENDIF(APPLE)

ADD_EXECUTABLE(rxcalc MACOSX_BUNDLE WIN32
	${RXCALC_SRCS} ${RXCALC_MOC_SRCS}
  ${RESOURCES_SRCS} )


TARGET_LINK_LIBRARIES(rxcalc Qt6::Core Qt6::Widgets Qt6::Svg Qt6::SvgWidgets Qt6::PrintSupport)


SET_TARGET_PROPERTIES(rxcalc PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

INSTALL(TARGETS rxcalc
    BUNDLE DESTINATION bin COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
    )

