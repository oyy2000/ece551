power.o: power.c
	gcc -pedantic -std=gnu99 -Wall -Werror -c power.c
test-power: power.o
	gcc -o test-power -pedantic -std=gnu99 -Wall -Werror test-power.c power.o
