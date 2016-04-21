find_program(BASH bash)

foreach(nt RANGE 2 50)
	foreach(notest 0001 0002 0003 0004)
		add_test(pattern_test_${notest}_${nt}
			${BASH} ${CMAKE_CURRENT_SOURCE_DIR}/utest.sh
					${CMAKE_BINARY_DIR}/src/pattern
					${CMAKE_CURRENT_SOURCE_DIR}
					${notest}
					${nt})
	endforeach(notest)
endforeach(nt)
