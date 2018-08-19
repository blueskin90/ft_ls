# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 00:28:51 by toliver           #+#    #+#              #
#    Updated: 2017/11/09 19:49:39 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -c -Werror -Wextra -Wall

SRC_PATH = . 

HEADER_PATH = .

FILES = atoi \
		bzero \
		isalnum \
		isalpha \
		isascii \
		isdigit \
		isprint \
		itoa \
		memalloc \
		memccpy \
		memchr \
		memcmp \
		memcpy \
		memdel \
		memmove \
	   	memset \
		putchar \
		putchar_fd \
		putendl \
		putendl_fd \
		putnbr \
		putnbr_fd \
		putstr \
		putstr_fd \
		putendl \
		putendl_fd \
		putnbr \
		putnbr_fd \
		putstr \
		putstr_fd \
		strcat \
		strchr \
		strclr \
		strcmp \
		strcpy \
		strdel \
		strdup \
		strequ \
		striter \
		striteri \
		strjoin \
		strlcat \
		strlen \
		strmap \
		strmapi \
		strncat \
		strncmp \
		strncpy \
		strnequ \
		strnew \
		strnstr \
		strrchr \
		strsplit \
		strstr \
		strsub \
		strtrim \
		tolower \
		toupper \
		lstnew	\
		lstdelone \
		lstdel \
		lstadd \
		lstiter \
		lstmap \

SRC = $(addprefix ft_,$(addsuffix .c, $(FILES)))

OBJ = $(addprefix ft_,$(addsuffix .o,$(FILES)))  

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) -I$(HEADER_PATH)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
