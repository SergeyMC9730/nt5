cmake_minimum_required (VERSION 3.20)

project ("nt5")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# debug: address sanitizer
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address,leak")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,leak")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address,leak")

# external:cJSON
# add_subdirectory(src/external/cJSON)

# external:libarchive
add_subdirectory(src/external/libarchive)

# external:cterm
add_subdirectory(src/external/cterm)

# external:libfuzzy
file(GLOB LIBFUZZY_SRC CONFIGURE_DEPENDS "src/external/libpe/libfuzzy/*.c")
add_library (fuzzy SHARED ${LIBFUZZY_SRC})
target_include_directories(fuzzy PRIVATE 
    "src/external/libpe/libfuzzy"
)

# external:libudis86
file(GLOB LIBUDIS86_SRC CONFIGURE_DEPENDS "src/external/libpe/libudis86/*.c")
add_library (udis86 SHARED ${LIBFUZZY_SRC})
target_include_directories(udis86 PRIVATE 
    "src/external/libpe/libudis86"
)

# external:libpe
file(GLOB LIBPE_SRC CONFIGURE_DEPENDS "src/external/libpe/*.c")
add_library(pe SHARED ${LIBPE_SRC})
target_include_directories(pe PRIVATE 
    "src/external/libpe/include"
    "src/external/libfuzzy"
    "src/external/libpe/libudis86"
)
target_link_libraries(pe fuzzy udis86 ssl)

# external:raylib
add_subdirectory(src/renderer/raylib)

# external:inih
file(GLOB LIBINIH_SRC CONFIGURE_DEPENDS "src/external/inih/*.c")
add_library(inih SHARED ${LIBINIH_SRC})
target_include_directories(inih PRIVATE 
    "src/external/inih"
)

# external:rvideo
set(RVIDEO_SRC "src/external/raylib-video/rvideo.c")
add_library(rvideo SHARED ${RVIDEO_SRC})
target_include_directories(rvideo PRIVATE
    "src/external/raylib-video"
    "src/renderer/raylib/src"
)
target_link_libraries(rvideo avformat avcodec swscale avutil)

# nt5language
file (GLOB NTLANGUAGE_SRC CONFIGURE_DEPENDS "src/language/src/*.c")
add_library(nt5language SHARED ${NTLANGUAGE_SRC})
target_include_directories(nt5language PRIVATE
    "src/arrays/include" 
    "src/language/include"
)

# nt5arrays
file (GLOB NTARRAYS_SRC CONFIGURE_DEPENDS "src/arrays/src/*.c", "src/arrays/include/*/*.c")
add_library(nt5arrays SHARED ${NTARRAYS_SRC})
target_include_directories(nt5arrays PRIVATE 
    "src/arrays/include" 
    "src/renderer/raylib/src"
)

# nt5tools
file(GLOB NTTOOLS_SRC CONFIGURE_DEPENDS "src/nt_tools/src/*.c" "src/nt_tools/include/*/*.h")
add_library (nt5tools SHARED ${NTTOOLS_SRC})
target_include_directories(nt5tools PRIVATE 
    "src/nt_tools/include"
    "src/global/include"
    "src/external/cJSON"
)
target_link_libraries(nt5tools cjson)

# nt5renderer
file(GLOB NTRENDERER_SRC CONFIGURE_DEPENDS "src/renderer/src/*.c" "src/renderer/include/*/*.h")
add_library(nt5renderer SHARED ${NTRENDERER_SRC})
target_include_directories(nt5renderer PRIVATE 
    "src/renderer/include"
    "src/renderer/raylib/src"
    "src/nt_tools/include"
    "src/arrays/include"
    "src/language/include"

    "src/external/inih"
    "src/external/raylib-video"
)
target_link_libraries(nt5renderer raylib rvideo nt5arrays inih nt5tools nt5language)

# nt5tui
file(GLOB NTTUI_SRC CONFIGURE_DEPENDS "src/ntldr_tui/src/*.c" "src/ntldr_tui/include/*/*.h")
add_library(nt5tui SHARED ${NTTUI_SRC})
target_include_directories(nt5tui PRIVATE 
    "src/ntldr_tui/include" 
    "src/renderer/raylib/src"
    "src/nt_tools/include"
    "src/arrays/include"
)
target_link_libraries(nt5tui raylib nt5tools)

# pe-viewer
file(GLOB PEVIEWER_SRC CONFIGURE_DEPENDS "src/pe_viewer/src/*.c" "src/pe_viewer/include/*/*.h")
add_executable(pe-viewer ${PEVIEWER_SRC})
target_include_directories(pe-viewer PRIVATE 
    "src/pe_viewer/include"
    "src/ntldr_tui/include" 
    "src/renderer/include"
    "src/renderer/raylib/src"
    "src/external/libpe/include"
    "src/arrays/include"
)
target_link_libraries(pe-viewer nt5tui nt5renderer pe nt5arrays)


# nt5install
file(GLOB NTINSTALL_SRC CONFIGURE_DEPENDS "src/nt_install/src/*.c" "src/nt_install/include/*/*.h")
add_library(nt5install SHARED ${NTINSTALL_SRC})
target_include_directories(nt5install PRIVATE 
    "src/nt_install/include" 
    "src/nt_tools/include" 
    "src/renderer/include" 
    "src/renderer/raylib/src" 
    "src/external/cJSON" 
    "src/external/libarchive/libarchive"
    "src/ntldr_tui/include"
    "src/arrays/include"
    "src/global/include"
    "src/language/include"
)
target_link_libraries(nt5install nt5renderer nt5tui cjson archive nt5tools nt5arrays)

# nt5boot
file(GLOB NTBOOT_SRC CONFIGURE_DEPENDS "src/boot/src/*.c" "src/boot/include/*/*.h")
add_library (nt5boot SHARED ${NTBOOT_SRC})
target_include_directories(nt5boot PRIVATE 
    "src/boot/include" 
    "src/renderer/include" 
    "src/nt_install/include" 
    "src/renderer/raylib/src" 
    "src/ntldr_tui/include"  
    "src/external/cJSON" 
    "src/arrays/include" 
    "src/external/libpe/include"
    "src/external"
    "src/nt_tools/include"
    "src/global/include"
    "src/language/include"
)
target_link_libraries(nt5boot nt5renderer cjson nt5install pe cterm)

# nt5
file(GLOB NT_SRC CONFIGURE_DEPENDS "src/launcher/*.c")
add_executable(nt5 ${NT_SRC})
target_include_directories(nt5 PRIVATE 
    "src/boot/include" 
    "src/renderer/include"
    "src/arrays/include"
)
target_link_libraries(nt5 nt5boot)

# cterm modules

# logo
file (GLOB NTMOD_LOGO_SRC CONFIGURE_DEPENDS "src/modules/logo/src/*.c")
add_library(ntmod_logo ${NTMOD_LOGO_SRC})
target_include_directories(ntmod_logo PRIVATE 
    "src/renderer/include" 
    "src/modules/logo/include" 
    "src/external" 
    "src/renderer/raylib/src" 
    "src/nt_tools/include"
    "src/global/include"
    "src/arrays/include"
    "src/language/include" 
)
target_link_libraries(ntmod_logo nt5renderer raylib)

# oobe
file (GLOB NTMOD_OOBE_SRC CONFIGURE_DEPENDS "src/modules/oobe/src/*.c")
add_library(ntmod_oobe ${NTMOD_OOBE_SRC})
target_include_directories(ntmod_oobe PRIVATE 
    "src/renderer/include" 
    "src/modules/oobe/include" 
    "src/external" 
    "src/renderer/raylib/src" 
    "src/nt_tools/include"
    "src/global/include"
    "src/arrays/include"
    "src/nt_tools/include"
    "src/external/raylib-video"
    "src/language/include"
)
target_link_libraries(ntmod_oobe nt5renderer raylib)

# notify
file (GLOB NTMOD_NOTIFY_SRC CONFIGURE_DEPENDS "src/modules/notify/src/*.c")
add_library(ntmod_notify ${NTMOD_NOTIFY_SRC})
target_include_directories(ntmod_notify PRIVATE 
    "src/renderer/include" 
    "src/modules/notify/include" 
    "src/external" 
    "src/renderer/raylib/src" 
    "src/nt_tools/include"
    "src/global/include"
    "src/arrays/include"
    "src/nt_tools/include"
    "src/external/raylib-video"
)
target_link_libraries(ntmod_notify nt5renderer raylib)

# logonui
file (GLOB NTMOD_LOGONUI_SRC CONFIGURE_DEPENDS "src/modules/logonui/src/*.c")
add_library(ntmod_logonui ${NTMOD_LOGONUI_SRC})
target_include_directories(ntmod_logonui PRIVATE 
    "src/renderer/include" 
    "src/modules/logonui/include" 
    "src/external" 
    "src/renderer/raylib/src" 
    "src/nt_tools/include"
    "src/global/include"
    "src/arrays/include"
    "src/nt_tools/include"
    "src/language/include"
)
target_link_libraries(ntmod_logonui nt5renderer raylib)

# explorer
file (GLOB NTMOD_EXPLORER_SRC CONFIGURE_DEPENDS "src/modules/explorer/src/*.c")
add_library(ntmod_explorer ${NTMOD_EXPLORER_SRC})
target_include_directories(ntmod_explorer PRIVATE 
    "src/renderer/include" 
    "src/modules/explorer/include" 
    "src/external" 
    "src/renderer/raylib/src" 
    "src/nt_tools/include"
    "src/global/include"
    "src/arrays/include"
    "src/nt_tools/include"
    "src/language/include"
    "src/ntldr_tui/include"
)
target_link_libraries(ntmod_explorer nt5renderer raylib nt5tui)

# copy nt resources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/ntresources
)

# copy cterm binaries
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/src/external/cterm/applications $<TARGET_FILE_DIR:${PROJECT_NAME}>/applications
)

# copy nt modules to cterm folder
add_custom_command(TARGET ntmod_logo POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/libntmod_logo.so $<TARGET_FILE_DIR:${PROJECT_NAME}>/applications/libntmod_logo.so
)
add_custom_command(TARGET ntmod_oobe POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/libntmod_oobe.so $<TARGET_FILE_DIR:${PROJECT_NAME}>/applications/libntmod_oobe.so
)
add_custom_command(TARGET ntmod_notify POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/libntmod_notify.so $<TARGET_FILE_DIR:${PROJECT_NAME}>/applications/libntmod_notify.so
)
add_custom_command(TARGET ntmod_logonui POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/libntmod_logonui.so $<TARGET_FILE_DIR:${PROJECT_NAME}>/applications/libntmod_logonui.so
)
add_custom_command(TARGET ntmod_explorer POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/libntmod_explorer.so $<TARGET_FILE_DIR:${PROJECT_NAME}>/applications/libntmod_explorer.so
)