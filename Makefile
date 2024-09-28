# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 15:36:04 by yde-rudd          #+#    #+#              #
#    Updated: 2024/09/19 20:00:48 by yde-rudd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client
CC = cc
CFLAGS = -g -Wall -Werror -Wextra

FT_PRINTF_DIR = ./ft_printf
LIBFT_DIR = ./libft

SRC_SERVER = server.c
SRC_CLIENT = client.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(FT_PRINTF) $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) $(FT_PRINTF) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) $(FT_PRINTF) -o $(NAME_CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -fr $(OBJ_SERVER) $(OBJ_CLIENT)
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -fr $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
