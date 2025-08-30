cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 23)
set(PROJECT_NAME soulver-cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C CXX)

set(SOULVER_CORE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/swift/Vendor/SoulverCore-linux/libSoulverCoreDynamic.so")
set(SOULVER_RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/swift/Vendor/SoulverCore-linux/SoulverCore_SoulverCore.resources/")
set(SOULVER_WRAPPER_LIB "${CMAKE_CURRENT_BINARY_DIR}/swift_output/libSoulverWrapper.so")

add_custom_command(
	OUTPUT ${SOULVER_WRAPPER_LIB} 
    COMMAND swift build -c release --build-path ${CMAKE_CURRENT_BINARY_DIR}/swift_build
    COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_BINARY_DIR}/swift_build/release/libSoulverWrapper.so ${SOULVER_WRAPPER_LIB} 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/swift
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/swift/Package.swift
    COMMENT "Building Swift module..."
)

add_custom_target(build_swift_module ALL
	DEPENDS ${SOULVER_WRAPPER_LIB} 
)

add_library(SoulverCore SHARED IMPORTED)
set_target_properties(SoulverCore PROPERTIES
	IMPORTED_LOCATION ${SOULVER_CORE_LIB}
)

install(FILES "${SOULVER_CORE_LIB}" "${SOULVER_WRAPPER_LIB}"
    DESTINATION lib
    COMPONENT Runtime
)

install(FILES src/core.hpp
	DESTINATION include/soulver-cpp
	COMPONENT Development
)

set(SOULVER_SHARE ${CMAKE_INSTALL_PREFIX}/share/soulver-core)

make_directory(${SOULVER_SHARE})

install(DIRECTORY ${SOULVER_RESOURCES} DESTINATION ${SOULVER_SHARE}/resources COMPONENT Runtime)

