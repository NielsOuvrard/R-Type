##
## EPITECH PROJECT, 2023
## My Makefile
## File description:
## Makefile
##

SRC = src/*.cpp

NAME = map_editor
# -Wall -Wextra -Werror
CMACFLAGS += -g -g3 -std=c++20 -lncurses -I/opt/homebrew/Cellar/sfml/2.6.0/include -L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-window -lsfml-graphics -lsfml-system

all:
	@ export LIBRARY_PATH=/opt/homebrew/Cellar/sfml/2.6.0/lib/
	@ export C_INCLUDE_PATH=/opt/homebrew/include
	@ g++ -o $(NAME) $(SRC) $(CMACFLAGS) -I./include

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: $(NAME) clean fclean all re custom

