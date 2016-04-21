bin=$1
dir_tests=$2
no_test=$3
nt=$4

$bin $dir_tests/refs/${no_test}.txt 1 `cat $dir_tests/refs/${no_test}.args` > /tmp/pattern_${no_test}_${nt}.ref || exit 1
$bin $dir_tests/refs/${no_test}.txt $nt `cat $dir_tests/refs/${no_test}.args` > /tmp/pattern_${no_test}_${nt}.test || exit 1

diff /tmp/pattern_${no_test}_${nt}.ref /tmp/pattern_${no_test}_${nt}.test
