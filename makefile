OBJS = process_input.o toHTML.o linkedList.o lex.yy.o
CC = gcc
CFLAGS = 
LIBS = -lfl
PARSER = parser.fl
FILES = process_input.c toHTML.c linkedList.c parser.fl process_input.h toHTML.h linkedList.h makefile

wiki2html:$(OBJS)
	$(CC) $(CFLAGS) -o wiki2html $(OBJS) $(LIBS)

linkedList.o:linkedList.c linkedList.h
	$(CC) $(CFLAGS) -c linkedList.c

process_input.o:process_input.c process_input.h linkedlist.h
	$(CC) $(CFLAGS) -c process_input.c

toHTML.o:toHTML.c toHTML.h process_input.h linkedlist.h
	$(CC) $(CFLAGS) -c toHTML.c

lex.yy.c:$(PARSER)
	flex $(PARSER)

lex.yy.o:lex.yy.c process_input.h linkedlist.h toHTML.h
	$(CC) $(CFLAGS) -c lex.yy.c

run:
	./wiki2html $(1) $(2) > /dev/null

clean:
	rm *.o

cleanAll:
	rm -r files
	rm *.html
	rm *.o
	rm wiki2html

install:
	cp wiki2html /usr/bin
	rm *.o
	rm wiki2html

remove:
	rm /usr/bin/wiki2html

debug::$(OBJS)
	$(CC) $(CFLAGS) -o wiki2html $(OBJS) $(LIBS) -g

tar:
	mkdir wiki2html
	cp -r relatorio wiki2html/relatorio
	cp $(FILES) wiki2html
	tar -pczf wiki2html.tar.gz wiki2html
	rm -r wiki2html

info:
	@echo "to compile, just run \"make\""
	@echo "\"make clean\" deletes all object files"
	@echo "\"make cleanAll\" deletes every file created"
	@echo "\"make install\" puts the executable file in the PATH (needs sudo)"
	@echo "\"make remove\" removes the executable from the PATH (needs sudo)"
	@echo "\"make tar\" compresses every file necessary for the build in a tar.gz file"