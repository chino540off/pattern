find_program(BASH bash)

foreach(nt RANGE 2 5)
	foreach(notest 0001 0002 0003 0004)
		add_test(test_pattern_${notest}_${nt}
			${BASH} ${CMAKE_CURRENT_SOURCE_DIR}/utest.sh
					${CMAKE_BINARY_DIR}/src/pattern
					${CMAKE_CURRENT_SOURCE_DIR}
					${notest}
					${nt})
	endforeach(notest)
endforeach(nt)
