NAME = stockholm

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lsodium

SRC = main.c \
	  Encrypt.c \
	  Decrypt.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
