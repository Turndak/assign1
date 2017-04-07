OBJS = scanner.o sll.o dll.o stack.o queue.o integer.o real.o string.o comparator.o sqsort.o readIn.o

OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : sqsort

sqsort : $(OBJS)
	gcc $(LOPTS) -o sqsort $(OBJS)

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

stack.o : stack.c stack.h
	gcc $(OOPTS) stack.c

comparator.o : comparator.c comparator.h
	gcc $(OOPTS) comparator.c

queue.o : queue.c queue.h
	gcc $(OOPTS) queue.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

readIn.o : readIn.c readIn.h
	gcc $(OOPTS) readIn.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

sqsort.o : sqsort.c integer.h real.h string.h sll.h dll.h stack.h queue.h comparator.h scanner.h readIn.h
	gcc $(OOPTS) -c sqsort.c

clean   :
	rm -f *.o sqsort

test :
	echo running sqsort on random integers with no repeats
	./sqsort -d testInteger1.txt
	echo running sqort on random integers with repeats
	./sqsort -d testInteger2.txt
	echo running sqort on homogenized integer list with two non-homogeneous embedded sequential integer
	./sqsort -d testInteger3.txt
	echo running sqort on homogenized integer list
	./sqsort -d testInteger4.txt
	echo running sqsort on reals with no repeats
	./sqsort -r testReal1.txt
	echo running sqsort on reals with repeats
	./sqsort -r testReal2.txt
	echo running sqsort on strings with no repeats
	./sqsort -s testString1.txt
	echo running sqsort on strings with repeats
	./sqsort -s testString2.txt

test1 :
	echo running sqsort on integer ex 1 from assigment instructions
	./sqsort -d t-int1.txt
	echo running sqsort on integer ex 2 from ass instructions
	./sqsort -d t-int2.txt
	echo running sqsort on random integers some reapeats
	./sqsort -d t-int3.txt
	echo running sqsort on all but one integer the same
	./sqsort -d t-int4.txt
	echo running sqsort on mostly the same integers
	./sqsort -d t-int5.txt
	echo running sqsort on real ex
	./sqsort -r t-real1.txt
	echo running sqsort on real all similar
	./sqsort -r t-real2.txt
	echo running sqsort on real all but 1 similar
	./sqsort -r t-real3.txt
	echo running sqsort on string ex
	./sqsort -s t-str1.txt
	echo running sqsort on string similar
	./sqsort -s t-str2.txt
	echo running sqsort on string all but 1 similar
	./sqsort -s t-str3.txt