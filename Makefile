NAME =	ft_ls

FLAGS = -Wall -Werror -Wextra

SRC =	-lft							\
		-lftprintf						\
		./libft/libft.a					\
		./libft/ft_printf/libftprintf.a	\
		./*.c							\

INC =	-L./libft			\
		-L./libft/ft_printf	\
		-I./includes

OBJ =	./*.o \

all: ./*.c ${NAME}

${NAME}: ./*.c ./libft/*.c ./libft/ft_printf/*.c ./libft/libft.h ./libft/ft_printf/includes/ft_printf.h ./includes/ft_ls.h
	make -C ./libft/
	make -C ./libft/ft_printf
	gcc -o ${NAME} ${FLAGS} ${SRC} ${INC}

clean:
	make clean -C ./libft/
	make clean -C ./libft/ft_printf
	rm -f ${OBJ}

fclean: clean
	make fclean -C ./libft/
	make fclean -C ./libft/ft_printf
	rm -f ${NAME}

re: fclean all