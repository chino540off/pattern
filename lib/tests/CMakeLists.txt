include(CTest)

include_directories("${PROJECT_SOURCE_DIR}/lib/include")

add_executable(test_slist test_slist.c)
target_link_libraries(test_slist slist)

add_executable(test_cluster test_cluster.c)
target_link_libraries(test_cluster cluster slist ${CMAKE_THREAD_LIBS_INIT})

add_test(test_slist_001		test_slist)
foreach(loop_var RANGE 1 200)
	add_test(test_cluster_${loop_var}	test_cluster ${loop_var})
endforeach(loop_var)
