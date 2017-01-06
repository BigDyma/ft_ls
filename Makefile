NAME = ft_ls
SRC = ft_ls.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra

all:
	gcc $(CFLAGS) $(SRC) libft/libft.a
	ar rc $(NAME) $? $(OBJ)
	ranlib $(NAME)

clean:
	make -C libft/ clean

fclean:	clean
		rm  $(NAME)

re: fclean all