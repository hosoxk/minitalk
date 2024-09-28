NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
SRCS = ft_printf.c \
	   ft_printf_char.c \
	   ft_printf_string.c \
	   ft_printf_int.c \
	   ft_printf_hexa.c \
	   ft_printf_unsigned.c \
	   ft_printf_pointer.c

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${AR} ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS}
	echo "Deleting .o files."

fclean: clean
	${RM} ${NAME}
	echo "Deleting .o files & ${NAME}"

re: fclean all

.PHONY: re all clean fclean
