include(CTest)

include_directories("${PROJECT_SOURCE_DIR}/lib/include")

add_executable(test_slist test_slist.c)
target_link_libraries(test_slist slist)

add_executable(test_hashmap test_hashmap.c)
target_link_libraries(test_hashmap hashmap)

add_executable(test_cluster test_cluster.c)
target_link_libraries(test_cluster cluster slist ${CMAKE_THREAD_LIBS_INIT})

add_test(test_slist_001		test_slist)
add_test(test_hashmap_001	test_hashmap)
foreach(nt RANGE 1 50)
	add_test(test_cluster_${nt}	test_cluster ${nt})
endforeach(nt)
