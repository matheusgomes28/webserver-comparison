
find_package(oatpp REQUIRED)
find_package(fmt REQUIRED)

add_executable(webapp main.cpp)

if (BUILD_DENSE_MAP)
    find_package(unordered_dense REQUIRED)
    message(STATUS "building with dense map")
    target_compile_definitions(webapp PRIVATE BUILD_DENSE_MAP)
    target_link_libraries(webapp PRIVATE unordered_dense::unordered_dense)
else()
    if (BUILD_STD_UNORDERED_MAP)
        message(STATUS "building with std::unordered_map")
        target_compile_definitions(webapp PRIVATE BUILD_STD_UNORDERED_MAP)
    else()
        message(STATUS "building with std::map")
        target_compile_definitions(webapp PRIVATE BUILD_STD_MAP)
    endif()
endif()


if (BUILD_STD_MAP)
    message(STATUS "building with CMAKE")
endif()

option(BUILD_STD_UNORDERED_MAP "build with std::unordered_map" Off)
option(BUILD_DENSE_MAP "build with ankerl::unordered_dense::map" Off)

target_link_libraries(webapp PRIVATE fmt::fmt oatpp::oatpp)
