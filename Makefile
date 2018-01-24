NAME =  RTv1
LIB = libft/libft.a
SRCS =  src/main.c src/tools.c src/intersections.c src/raytracing.c \
		src/color.c src/tortus.c src/cylinder_cone.c src/scene.c \
		src/polynomials.c src/parsing.c src/extra.c src/recurtion.c \
		src/operations.c src/hyperboloid.c src/mtx_op.c src/camera.c
HEADERS = RTv1.h
FLAGS =  -Wall -Wextra -Werror -g
FLAGS_MLX = -lmlx -framework OpenGl -framework AppKit
LOCAL = -I minilibX -g -L minilibX
BINS = $(SRCS:.c=.o)
all: $(NAME)
lib:
	make -C libft/
libclean:
	make -C libft/ clean
libfclean:
	make -C libft/ fclean
$(NAME): $(BINS)
	gcc -o $(NAME) $(BINS) $(FLAGS) $(LOCAL) $(FLAGS_MLX) $(LIB)
%.o: %.c
	gcc $(FLAGS) -c -o $@ $<
clean:
	/bin/rm -f $(BINS)
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all