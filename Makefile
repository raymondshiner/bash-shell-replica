all:	lab7

lab7:	cscd340Lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./linkedlist/linkedList.o ./linkedlist/listUtils.o ./words/word.o ./alias/alias.o
	gcc -g cscd340Lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./linkedlist/linkedList.o ./linkedlist/listUtils.o ./words/word.o ./alias/alias.o -o lab7

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

linkedList.o: ./linkedlist/linkedList.c ./linkedlist/linkedList.h
	gcc -g -c ./linkedlist/linkedList.c

listUtils.o: ./linkedlist/listUtils.c ./linkedlist/listUtils.h
	gcc -g -c ./linkedlist/listUtils.c

word.o: ./words/word.c ./words/word.h
	gcc -g -c ./words/words.c

alias.o: ./alias/alias.c ./alias/alias.h
	gcc -g -c ./alias/alias.c

clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./linkedlist/linkedList.o
	rm ./linkedlist/listUtils.o
	rm ./words/word.o
	rm ./alias/alias.o
	rm lab7
	
