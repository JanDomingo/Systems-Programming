exp:	exp.l exp.y
	flex exp.l
	yacc -d --debug -t exp.y
	cc -o $@ lex.yy.c y.tab.c

clean:
	-rm *.o $(objects) exp
