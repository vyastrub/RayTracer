#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vyastrub <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 10:26:37 by vyastrub          #+#    #+#              #
#    Updated: 2016/12/09 16:06:40 by vyastrub         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRC = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_memcpy.c \
ft_isprint.c ft_memset.c ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c \
ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_bzero.c \
ft_strncpy.c ft_strnstr.c ft_strrchr.c  ft_strstr.c ft_tolower.c ft_toupper.c \
ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c ft_memdel.c \
ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_atoi.c \
ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
ft_swap.c ft_range.c ft_strcapitalize.c ft_str_is_alpha.c ft_str_is_numeric.c \
get_next_line.c

OBJ = $(SRC:.c=.o)

TMP = $(SRC:.c=.c~)

INC = libft.h

WWW = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o: %.c -I $(INC)
	gcc $(WWW) -c $<  

clean:
	rm -f $(OBJ)
	rm -f $(TMP)

fclean: clean
	rm -f $(NAME)

re: fclean all 