include(CTest)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

add_executable(test_slist test_slist.c)
target_link_libraries(test_slist slist)

add_executable(test_cluster test_cluster.c)
target_link_libraries(test_cluster cluster slist ${CMAKE_THREAD_LIBS_INIT})

add_test(test_slist_001 test_slist)
add_test(test_cluster_001 test_cluster toto tata titi)
add_test(test_cluster_002 test_cluster toto titi tata blabla)
add_test(test_cluster_003 test_cluster toto tata titi lkhe mlksd flkdf skf kmf fdfsf)
