exp:
	flex exp.l
	yacc -d exp.y
	cc lex.yy.c y.tab.c -o exp 
	./exp
