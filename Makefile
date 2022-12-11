NAME	= base64

RM	= rm -rf

SRC	= src/main.c	\
	src/parse.c	\
	src/base64.c	\
	src/encode.c	\
	src/decode.c

OBJ	= $(SRC:.c=.o)

CC	= gcc

CFLAGS	+= -W -Wall -Wextra -Wshadow -I include

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
