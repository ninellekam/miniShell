SRCS	= *.c

OBJS	= $(SRCS:.c=.o)

HEADER	= includes

CC	= gcc

CFLAGS	= -Werror -Wall -Wextra -c

NAME	= miniShell

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME):	${OBJS}
	@$(CC) $(CFLAGS) ${OBJS} \
	-I$(HEADER) -o $(NAME)

clean:
	@rm -f *.o

fclean:	clean
	rm -rf $(NAME)

re:		fclean all

.PHONY: all fclean clean re
