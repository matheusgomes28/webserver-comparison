
find_package(oatpp REQUIRED)
find_package(fmt REQUIRED)
add_executable(webapp main.cpp)

target_link_libraries(webapp PRIVATE fmt::fmt oatpp::oatpp)
