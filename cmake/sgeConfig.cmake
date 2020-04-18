include(CMakeFindDependencyMacro)

if(UNIX)
    find_dependency(X11 REQUIRED)
endif()

include("${CMAKE_CURRENT_LIST_DIR}/sgeTargets.cmake")