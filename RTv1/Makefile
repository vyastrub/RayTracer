#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsydorch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/12 08:42:30 by vsydorch          #+#    #+#              #
#    Updated: 2017/04/19 10:10:10 by vsydorch         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =  RTv1
SRCS =  main.c tools.c intersections.c raytracing.c color.c tortus.c\
cylinder_cone.c scene.c polynomials.c parsing.c extra.c recurtion.c operations.c\
hyperboloid.c mtx_op.c camera.c\
libft/ft_bzero.c libft/ft_putstr.c libft/ft_strdup.c libft/ft_strjoin.c \
libft/ft_memcpy.c libft/ft_putchar.c libft/ft_strlen.c libft/ft_strnew.c \
libft/ft_memalloc.c libft/ft_memset.c libft/ft_atoi.c libft/ft_strcmp.c
FLAGS =  -g
FLAGS_MLX = -lmlx -framework OpenGl -framework AppKit
LOCAL = -I minilibX -g -L minilibX
BINS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(BINS)
	gcc -o $(NAME) $(BINS) $(FLAGS) $(LOCAL) $(FLAGS_MLX)
%.o: %.c
	gcc $(FLAGS) -c -o $@ $<
clean: 
	/bin/rm -f $(BINS)
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all