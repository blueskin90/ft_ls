# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/12 01:24:53 by toliver           #+#    #+#              #
#    Updated: 2018/08/29 22:22:59 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CFLAGS = -Werror -Wextra -Wall -g3 -fsanitize=address,undefined

FILES = ft_ls \
		init \
		parsing \
		error \
		list_handling \
		get_list \
		get_infos \
		get_functions \
		print_long \
		print_long2 \
		recursive \
		print_list \
		node_handling \
		node_move \
		printing \

SRC = $(addsuffix .c, $(FILES))

SRC_PATH = ./srcs/

SRCS = $(addprefix $(SRC_PATH),$(SRC))

OBJ_PATH = ./

OBJS = $(addprefix $(OBJ_PATH),$(SRC:.c=.o))

INCLUDES = -I./includes/ -I./libs/libft/ -I./libs/ft_printf/includes/

HEADERS = ./includes/ft_ls.h

LIBS = libs/ft_printf/libftprintf.a \
	   libs/libft/libft.a

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	make -C libs/libft/
	make -C libs/ft_printf/
	gcc -o $(NAME) $(OBJS) $(CFLAGS) $(LIBS) $(INCLUDES)

%.o: srcs/%.c $(HEADERS)
	gcc -o $@ -c $< $(CFLAGS) $(INCLUDES)

clean:
	make clean -C libs/libft/
	make clean -C libs/ft_printf/
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libs/libft/
	make fclean -C libs/ft_printf/
	rm -rf $(NAME)

re: fclean all
