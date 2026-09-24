# Included after upstream has assembled the game and Proton source lists.
target_include_directories(RTDinkApp PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
find_package(PkgConfig REQUIRED)
pkg_check_modules(SWITCH_DEPS REQUIRED SDL2_mixer libcurl libpng zlib)
target_include_directories(RTDinkApp SYSTEM PRIVATE ${SWITCH_DEPS_INCLUDE_DIRS})
target_link_directories(RTDinkApp PRIVATE ${SWITCH_DEPS_STATIC_LIBRARY_DIRS})
target_link_libraries(RTDinkApp PRIVATE GLESv1_CM bz2 ${SWITCH_DEPS_STATIC_LIBRARIES})
set_target_properties(RTDinkApp PROPERTIES OUTPUT_NAME DinkSmallwood
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
nx_generate_nacp(DinkSmallwood.nacp
    NAME "Dink Smallwood HD (Homebrew)" AUTHOR "RTsoft / Switch port" VERSION "0.3.2")
nx_create_nro(RTDinkApp NACP DinkSmallwood.nacp
    ICON "${CMAKE_CURRENT_LIST_DIR}/icon.jpg")
