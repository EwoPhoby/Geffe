CC = gcc
CFLAGS = -Wall -ansi -c
LDFLAGS=
EXEC_NAME = dm_crypto
OBJ_FILES = lfsr.c

all : $(EXEC_NAME)

run :$(EXEC_NAME)
	./$(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) 


clean :
	rm $(EXEC_NAME) 

git:
	git add .
	git commit -a --allow-empty-message -m ''
	git push

install:
	git clone https://github.com/raysan5/raylib.git raylib
	cd raylib/src/
	make PLATFORM=PLATFORM_DESKTOP

organisation:
	xdg-open organisation.txt

rapport:
	xdg-open rapport.pdf