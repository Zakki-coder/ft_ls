NAME =	ft_ls

FLAGS = -Wall -Werror -Wextra

SRC =	./libft/libft.a	\
		./*.c			\
	
OBJ =	./*.o \

all: ${NAME}

${NAME}:
	make -C ./libft/
#	gcc -o ${NAME} ${FLAGS} ${SRC} 
	/usr/local/bin/gcc-11 -o ${NAME} ${FLAGS} ${SRC} 

clean:
	make clean -C ./libft/
	rm -f ${OBJ}

fclean:
	make fclean -C ./libft/
	rm -f ${NAME}

re: fclean all