default:
	clear
	flex -l exp.l
	bison -dv exp.y 
	gcc -o exp exp.tab.c lex.yy.c -ll
	./exp