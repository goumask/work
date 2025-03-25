## Project phase 3 - hy340
## File: makefile

## ************ Group members: ********************


##      Names        | A.M. |      emails
## -----------------------------------------------
## Eliezer Smaragdis | 4242 | csd4242@csd.uoc.gr
## Kostas Goumas     | 2746 | goumas@csd.uoc.gr



built:
	flex scanner.l
	bison -d -v parser.y
	gcc lex.yy.c parser.tab.c

rm:
	rm lex.yy.c;
	rm parser.output;
	rm parser.tab.c;
	rm parser.tab.h;
	rm a.out;
