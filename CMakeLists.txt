cmake_minimum_required (VERSION 3.20)

project ("nt5")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src/external/cJSON)

file(GLOB NTRENDERER_SRC CONFIGURE_DEPENDS "src/renderer/src/*.c" "src/renderer/include/*/*.h")
add_subdirectory(src/renderer/raylib)

add_library(nt5renderer SHARED ${NTRENDERER_SRC})

target_include_directories(nt5renderer PRIVATE "src/renderer/include" "src/renderer/raylib/src")

target_link_libraries(nt5renderer raylib)

file(GLOB NTINSTALL_SRC CONFIGURE_DEPENDS "src/nt_install/src/*.c" "src/nt_install/include/*/*.h")

add_library(nt5install SHARED ${NTINSTALL_SRC})

target_include_directories(nt5install PRIVATE "src/nt_install/include" "src/renderer/include" "src/renderer/raylib/src" "src/external/cJSON")

target_link_libraries(nt5install nt5renderer cjson)


file(GLOB NTBOOT_SRC CONFIGURE_DEPENDS "src/boot/src/*.c" "src/boot/include/*/*.h")

add_library (nt5boot SHARED ${NTBOOT_SRC})

target_include_directories(nt5boot PRIVATE "src/boot/include" "src/renderer/include" "src/nt_install/include" "src/renderer/raylib/src" "src/external/cJSON")

target_link_libraries(nt5boot nt5renderer cjson nt5install)


file(GLOB NT_SRC CONFIGURE_DEPENDS "src/launcher/*.c")

add_executable(nt5 ${NT_SRC})

target_include_directories(nt5 PRIVATE "src/boot/include" "src/renderer/include")

target_link_libraries(nt5 nt5boot)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/ntresources)