## Project phase 4 - hy340
## File: makefile

## *********** Group members: *******************


##      Names        | A.M. |      emails
## -----------------------------------------------

## Kostas Goumas     | 2746 | goumas@csd.uoc.gr



built:
	flex scanner.l
	bison -d -v parser.y
	gcc -g -w lex.yy.c variables.c parser.tab.c phase4Target.c

clean:
	rm lex.yy.c
	rm parser.output
	rm parser.tab.c
	rm parser.tab.h
	rm a.out