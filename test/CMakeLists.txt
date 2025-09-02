add_executable(test_basic test_basic.cpp)

target_link_libraries(test_basic PRIVATE calculator_lib)

add_test(NAME BasicTest COMMAND test_basic)