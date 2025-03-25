## Project phase 3 - hy340
## File: README.txt

## ************ Group members: ********************


##      Names        | A.M. |      emails
## -----------------------------------------------
## Eliezer Smaragdis | 4242 | csd4242@csd.uoc.gr
## Kostas Goumas     | 2746 | goumas@csd.uoc.gr

*********** Compilation: *****************

make built

or

execute commands:

	flex scanner.l;
	bison -d -v parser.y;
	gcc lex.yy.c parser.tab.c;


************ Implementation: *****************

We have finished all project with total boolean evaluation.