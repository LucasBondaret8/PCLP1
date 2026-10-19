build:
	gcc battleships.c -o battleships -Wall -Wextra -std=c99
clean:
	rm -f battleships

.PHONY: pack clean