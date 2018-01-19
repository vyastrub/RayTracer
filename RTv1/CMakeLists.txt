cmake_minimum_required(VERSION 3.7)
project(RTv1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES
        color.c
        intersections.c
        main.c
        raytracing.c
        tools.c
        scene.c
        polynomials.c
        tortus.c
        cylinder_cone.c
        ini.h
        test.ini
        libft/ft_bzero.c
        libft/ft_putstr.c
        libft/ft_strdup.c
        libft/ft_strjoin.c
        libft/ft_memcpy.c
        libft/ft_putchar.c
        libft/ft_strlen.c
        libft/ft_strnew.c
        libft/ft_memalloc.c
        libft/ft_memset.c
        libft/ft_atoi.c
        libft/ft_strcmp.c
        parsing.c
        extra.c
        recurtion.c
        operations.c
        hyperboloid.c
        mtx_op.c
        camera.c) # sources

add_executable(RTv1 ${SOURCE_FILES}) # compilation

target_link_libraries(RTv1  -lmlx "-framework OpenGL" "-framework AppKit") # linkage
