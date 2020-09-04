add_subdirectory(physfs EXCLUDE_FROM_ALL)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_library(SDL2 SHARED IMPORTED GLOBAL)
    if(MSVC)
        set_target_properties(SDL2 PROPERTIES
                IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/sdl2/msvc/bin/SDL2.dll
                IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/sdl2/msvc/lib/SDL2.lib
                INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/sdl2/include)
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sdl2/msvc/bin/SDL2.dll
                DESTINATION ${CMAKE_BINARY_DIR}/binaries)
    elseif(MINGW)
        set_target_properties(SDL2 PROPERTIES
                IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/sdl2/mingw/bin/SDL2.dll
                IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/sdl2/mingw/lib/SDL2.dll.lib
                INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/sdl2/include)
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sdl2/mingw/bin/SDL2.dll
                DESTINATION ${CMAKE_BINARY_DIR}/binaries)
    endif()
endif()