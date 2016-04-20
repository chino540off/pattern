include(CTest)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

add_executable(test_list test_list.c)
target_link_libraries(test_list list)

add_executable(test_mapper test_mapper.c)
target_link_libraries(test_mapper mapper list ${CMAKE_THREAD_LIBS_INIT})

add_test(test_list_001 test_list)
add_test(test_mapper_001 test_mapper toto tata titi)
add_test(test_mapper_002 test_mapper toto titi tata blabla)
add_test(test_mapper_003 test_mapper toto tata titi lkhe mlksd flkdf skf kmf fdfsf)
