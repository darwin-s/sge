add_library(stb_image STATIC src/stb_image.c)
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(stb_image PROPERTIES POSITION_INDEPENDENT_CODE TRUE)