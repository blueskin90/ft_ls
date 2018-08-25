# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/12 01:24:53 by toliver           #+#    #+#              #
#    Updated: 2018/08/25 20:30:46 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -Werror -Wextra -Wall

FILES = ft_ls \
		init \
		parsing \
		error \
		list_handling \
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
	gcc -o $(NAME) $(OBJS) $(FLAGS) $(LIBS) $(INCLUDES)

%.o: srcs/%.c $(HEADERS)
	gcc -o $@ -c $< $(FLAGS) $(INCLUDES)

clean:
	make clean -C libs/libft/
	make clean -C libs/ft_printf/
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libs/libft/
	make fclean -C libs/ft_printf/
	rm -rf $(NAME)

re: fclean all
