CC= gcc
CFLAGS= -Wall -g
DEPS= logo_type.h fonctions_logo.h


all : logo

logo : lex.yy.c logo.tab.c fonctions_logo.c
	$(CC) lex.yy.c logo.tab.c fonctions_logo.c -o logo -lm

test : test.o fonctions_logo.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lex.yy.c : logo.l
	flex logo.l

logo.tab.c : logo.y
	bison -d logo.y

clean :
	-rm *.o test *.tab.c *.tab.h *.yy.c logo logo.c output

archive : clean
	cd ..; tar -zcvf TP-LOGO_FLAMANT.tar LOGO; gzip -f TP-LOGO_FLAMANT.tar
