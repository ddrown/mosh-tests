test: test.c read.c read.h
	gcc -o test test.c read.c

run: test
	echo 1 >.savefile
	sh -c './test 1 & ./test 1 & ./test 1 & ./test 1 & wait'
