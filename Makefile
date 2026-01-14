NAME = stockholm

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
LIBS = -lsodium

SRC_DIR = srcs
INC_DIR = incs
OBJ_DIR = objs

SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/Encrypt.c \
	  $(SRC_DIR)/Decrypt.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
