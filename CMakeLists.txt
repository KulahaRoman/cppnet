cmake_minimum_required(VERSION 3.8)

project(cppnet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CPPNET_SRC 
			src/${PROJECT_NAME}/machine.cpp
			src/${PROJECT_NAME}/machinehelper.cpp
			src/${PROJECT_NAME}/unsecuretcpconnection.cpp
			src/${PROJECT_NAME}/unsecuretcpconnector.cpp
			src/${PROJECT_NAME}/unsecuretcpacceptor.cpp

			src/${PROJECT_NAME}/packages/package.cpp
			src/${PROJECT_NAME}/packages/packagedecoder.cpp
			src/${PROJECT_NAME}/packages/packageencoder.cpp
			src/${PROJECT_NAME}/packages/auth/authrequestpackage.cpp
			src/${PROJECT_NAME}/packages/auth/authresponsepackage.cpp
			src/${PROJECT_NAME}/packages/sysinfo/sysinfopackage.cpp
			src/${PROJECT_NAME}/packages/sysinfo/systeminformation.cpp
)

if(WIN32)
  list(APPEND CPPNET_SRC src/${PROJECT_NAME}/packages/sysinfo/systeminformationprovider.cpp)
endif()

add_library(${PROJECT_NAME} STATIC ${CPPNET_SRC})

target_compile_definitions(${PROJECT_NAME} PRIVATE -D_WIN32_WINNT=0x0601 -D_CRT_SECURE_NO_WARNINGS -D_UNICODE -DUNICODE)

add_subdirectory(libs/cppstreams)
target_link_libraries(${PROJECT_NAME} PUBLIC cppstreams)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")