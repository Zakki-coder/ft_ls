NAME = libftprintf.a

FLAGS = -Werror -Wextra -Wall

INC =	-I./includes/			\
	
SRC =	./ft_printf.c				\
		./put_string.c				\
		./put_pointer_address.c 	\
		./float_part_1.c			\
		./float_part_2.c			\
		./float_part_3.c			\
		./get_format_utilities.c	\
		./parser_part_1.c			\
		./parser_part_2.c			\
		./hexa.c					\
		./hexa_part_2.c				\
		./octal.c					\
		./octal_part_2.c			\
		./integer.c					\
		./integer_part_2.c			\
		./percent.c					\
		./get_argument_utilities.c	\
		./shared_utilities.c 		\

SRC2 =	../*.c	

OBJ =	./ft_printf.o				\
		./put_string.o				\
		./put_pointer_address.o 	\
		./float_part_1.o			\
		./float_part_2.o			\
		./float_part_3.o			\
		./get_format_utilities.o	\
		./parser_part_1.o			\
		./parser_part_2.o			\
		./hexa.o					\
		./hexa_part_2.o				\
		./octal.o					\
		./octal_part_2.o			\
		./integer.o					\
		./integer_part_2.o			\
		./percent.o					\
		./get_argument_utilities.o	\
		./shared_utilities.o 		\

OBJ2 =	./*.o	

${NAME}:
	gcc -c ${FLAGS} ${SRC} ${SRC2} ${INC}
	ar -rc ${NAME} ${OBJ} ${OBJ2}

all: ${NAME}

clean:
	rm -f ${OBJ} ${OBJ2} 

fclean: clean
	rm -f ${NAME}

re: fclean all
