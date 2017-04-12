compile:
	sh -c "bison exp.y"
	gcc -g -O2 *.c  
	./a.exe < test.txt

compile-opt:
	sh -c "bison exp.y"
	gcc -g -O2 -D=OPT *.c  
	./a.exe < test.txt