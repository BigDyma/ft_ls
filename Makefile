NAME = ft_ls
SRC = ft_ls.c  ft_lsv.c
OBJ = $(SRC:.c=.o)
all:
	make -C libft/ fclean
	make -C libft/
	gcc -Wall -Wextra -Werror -c $(SRC)
	gcc -o $(NAME) $(OBJ) -L libft/ -lft
clean:
	rm -rf $(OBJ)
	make -C libft/ clean
fclean: clean
	rm -rf $(NAME)
re: fclean all