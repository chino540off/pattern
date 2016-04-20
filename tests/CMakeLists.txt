include(CTest)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

add_executable(test_list test_list.c)
target_link_libraries(test_list list)

add_executable(test_cluster test_cluster.c)
target_link_libraries(test_cluster cluster list ${CMAKE_THREAD_LIBS_INIT})

add_test(test_list_001 test_list)
add_test(test_cluster_001 test_cluster toto tata titi)
add_test(test_cluster_002 test_cluster toto titi tata blabla)
add_test(test_cluster_003 test_cluster toto tata titi lkhe mlksd flkdf skf kmf fdfsf)
