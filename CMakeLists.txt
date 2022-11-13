cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(allocator VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

add_executable(allocator_cli main.cpp )
add_library(allocator alloc.cpp alloc.h linked_list.h)

set_target_properties(allocator_cli allocator PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    )


target_include_directories(allocator
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(allocator_cli PRIVATE
    allocator
)


if (MSVC)
    target_compile_options(allocator_cli PRIVATE
        /W4
    )
    target_compile_options(allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS allocator_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT Alttaira@yandex.ru)
include(CPack)




##project(allocator VERSION ${PROJECT_VESRION})

#if($ENV{TRAVIS_BUILD_NUMBER})
#    project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#else()
#    project(allocator VERSION 0.0.1)
#endif()

#configure_file(version.h.in version.h)

#add_executable(allocator main.cpp alloc.cpp alloc.h linked_list.h)

#set_target_properties(allocator PROPERTIES
#        CXX_STANDARD 14
#        CXX_STANDARD_REQUIRED ON
#        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
#        )

#install(TARGETS allocator RUNTIME DESTINATION bin)

#set(CPACK_GENERATOR DEB)

#set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
#set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
#set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

## не знаю, на фига это надо, но в первой лекции было
#set(CPACK_PACKAGE_CONTACT Alttaira@yandex.ru)

## тесты не буду делать(((
#include(CPack)
