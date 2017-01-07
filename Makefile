NAME = ft_ls
SRC = ft_ls.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra

all:
	gcc  $(SRC)  libft/libft.a -o ft_ls

clean:
	make -C libft/ clean

fclean:	clean
		rm  $(NAME)

re: fclean all