# build URL Browser
project (urlbrowser)

# set minimum cmake version
cmake_minimum_required (VERSION 2.8)

# verbose ouptut
set (CMAKE_VERBOSE_MAKEFILE off)

# set the build postfix extension
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set (CMAKE_DEBUG_POSTFIX "d")
endif ()

# supress developer warnings
cmake_policy (SET CMP0015 NEW)

# set developer warnings
if (WIN32)
	add_definitions (-D_CRT_SECURE_NO_WARNINGS)
else ()
	set (CMAKE_CXX_FLAGS "-Wall")
endif ()

# include directory
include_directories (
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_BINARY_DIR}"
)

# add Qt
find_package (Qt4 COMPONENTS QtCore QtGui QtWebKit QtNetwork REQUIRED)
include (${QT_USE_FILE})
add_definitions (${QT_DEFINITIONS})
set (EXTRA_LIBS ${EXTRA_LIBS} QtCore)
set (EXTRA_LIBS ${EXTRA_LIBS} QtGui)
set (EXTRA_LIBS ${EXTRA_LIBS} QtNetwork)
set (EXTRA_LIBS ${EXTRA_LIBS} QtWebKit)

#
# library for project
#

# add the library
qt4_wrap_cpp (HEADERS_MOC "include/urlbrowser.h")
add_library (urlbrowser SHARED src/urlbrowser.cpp ${HEADERS_MOC})
target_link_libraries (urlbrowser ${EXTRA_LIBS})


#
# demo app for project
#

# wrap headers for qt
qt4_wrap_cpp (HEADERS_MOC "include/mainwindow.h")

# add project library into demo app
include_directories ("${PROJECT_SOURCE_DIR}/include")
link_directories ("${PROJECT_SOURCE_DIR}/src")
set (EXTRA_LIBS ${EXTRA_LIBS} urlbrowser)

# create demo executable
add_executable (demoapp
	src/main.cpp
	src/mainwindow.cpp
	${HEADERS_MOC}
)
target_link_libraries (demoapp ${EXTRA_LIBS})

