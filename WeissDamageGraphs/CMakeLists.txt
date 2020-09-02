file(GLOB SOURCES
	"src/Effects/*.h"
	"src/Effects/*.cpp"
	"src/GUI/*.h"
	"src/GUI/*.cpp"
    "src/*.h"
    "src/*.cpp"
)

add_executable(
    WeissDamageGraphs
        ${SOURCES}
)

find_package(PythonLibs 2.7 REQUIRED)

target_include_directories(WeissDamageGraphs PRIVATE 
	${PYTHON_INCLUDE_DIRS}
	"D:/nana/include"
)
target_link_libraries(WeissDamageGraphs 
	${PYTHON_LIBRARIES}
	"D:/Miniconda2/Lib/site-packages/numpy/core/lib/npymath.lib"
	"D:/nana/build/bin/nana_v141_Release_x64.lib"
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Logger.py ${CMAKE_CURRENT_BINARY_DIR}/Logger.py COPYONLY)