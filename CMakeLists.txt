cmake_minimum_required(VERSION 3.0.0)
project(Gateway_Extender VERSION 0.1.0)

##################################################
###		project directory and compiler option 	##
##################################################
set(CMAKE_CXX_FLAGS -pthread)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
add_compile_options(-std=c++14 -Wall -g)
include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(${PROJECT_SOURCE_DIR}/settings)
include_directories(${PROJECT_SOURCE_DIR}/commandService)
#include_directories(${PROJECT_SOURCE_DIR}/commandPull)

##################################################
###		boost block								##
##################################################
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
include_directories(${Boost_INCLUDE_DIRS})
set(BOOST_COMPONENTS system thread filesystem date_time regex serialization)
find_package (Threads REQUIRED)
find_package (Boost 1.65.1 COMPONENTS ${BOOST_COMPONENTS} REQUIRED)

##################################################
###		build block								##
##################################################
add_executable(${PROJECT_NAME} 
	./app.cpp 
	./starter.cpp
	./settings/settings.cpp
	./commandService/commandService.cpp
	./commandService/connectionClient.cpp
	./commandPull/commandHandler.cpp
	./commandPull/commandPull.cpp
)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

include(CPack)
