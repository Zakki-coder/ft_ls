NAME =	ft_ls

FLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

SRC =	-lft							\
		-lftprintf						\
		./libft/libft.a					\
		./libft/ft_printf/libftprintf.a	\
		./*.c							\

INC =	-L./libft			\
		-L./libft/ft_printf	\
		-I./includes

OBJ =	./*.o \

all: ${NAME}

${NAME}:
	make -C ./libft/
	make -C ./libft/ft_printf
	gcc -o ${NAME} ${FLAGS} ${SRC} ${INC}

debug: 
	make -C ./libft/
	gcc -o ${NAME} ${FLAGS} ${SRC} ${INC} -g

clean:
	make clean -C ./libft/
	make clean -C ./libft/ft_printf
	rm -f ${OBJ}

fclean: clean
	make fclean -C ./libft/
	make fclean -C ./libft/ft_printf
	rm -f ${NAME}

re: fclean all