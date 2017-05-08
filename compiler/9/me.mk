c_f = $(wildcard *.c)
c_h = $(wildcard *.h)

pre:
	flex  c--.lex
	sh -c "bison -d c--.y"

run: pre obj exe
	
.ONESHELL:
obj:
	@c_files="$(shell find . -name '*.c')" && \
	echo gcc -g -O2  -c "$${c_files}" &&\
	gcc -g -O2   -c $${c_files}

.ONESHELL:
exe:
	@c_headers="$(shell find . -name '*.o')" &&\
	echo gcc -g -O2  $${c_headers} -o  a.exe &&\
	gcc -g -O2 $${c_headers} -o a.exe 


clea:
	rm -rf a.out c--.tab.h c--.tab.c lex.yy.c *.o *~ *.exe *.s

lint:$(c_f)
	splint $^	

test: $(c_files)
	$(CC) -c $^
	$(CC) -c $<
	$(CC) -c $?
	rm -rf a.out c--.tab.h c--.tab.c lex.yy.c *.o *~ *.exe *.s
