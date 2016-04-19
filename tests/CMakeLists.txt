include(CTest)

include_directories("${PROJECT_SOURCE_DIR}/include")
link_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(test_list test_list.c)
target_link_libraries(test_list list)

add_executable(test_lines test_lines.c)
target_link_libraries(test_lines list)

add_test(test_list test_list)
add_test(test_lines test_lines 4 toto tata titi)
