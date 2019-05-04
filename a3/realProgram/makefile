.PHONY:	run
run:	exp
	./exp
exp:	exp.l exp.y
	flex exp.l
	yacc -d exp.y
	cc lex.yy.c y.tab.c -o exp

clean:
	-rm *.o $(objects) exp
