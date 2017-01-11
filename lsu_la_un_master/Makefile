NAME = ft_ls
SRC = ls1.c
OBJ = $(SRC:.c=.o)
all:
	make -C libft/ fclean
	make -C libft/
	gcc -Wall -Wextra -Werror -I libft/includes  -I includes -c $(SRC)
	gcc -o $(NAME) $(OBJ) -L libft/ -lft
clean:
	rm -rf $(OBJ)
	make -C libft/ clean
fclean: clean
	rm -rf $(NAME)
re: fclean all
	