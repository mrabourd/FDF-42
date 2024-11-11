# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrabourd <mrabourd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 15:30:31 by mrabourd          #+#    #+#              #
#    Updated: 2023/02/27 16:45:59 by mrabourd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf

CC			= cc

CFLAGS 		= -Wall -Werror -Wextra

SRC			= 	main.c \
				get_next_line.c \
				get_next_line_utils.c \
				create_map.c \
				map_utils.c \
				render.c \
				iso.c \
				parallele.c \
				hook.c \
				mouse_hook.c \
				ft_atoi.c \
				exit.c 

SRC_ALL		= ${addprefix ${SRC_DIR},${SRC}}

SRC_DIR		= src/

OBJ_DIR		= obj/

LIBFT_DIR	= libft

OBJ_ALL		= ${SRC_ALL:.c=.o}

OBJ			= ${subst ${SRC_DIR}, ${OBJ_DIR}, ${OBJ_ALL}}

all	:	make_lib ${NAME}

make_lib : 
	@make -C ${LIBFT_DIR}

$(NAME) : ${OBJ} 
	make -C mlx_linux
	${CC} ${OBJ} ${CFLAGS} libft/libft.a -L./mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

${OBJ_DIR}%.o: ${SRC_DIR}%.c
	$(CC) ${CFLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean :
	rm -f ${OBJ}

fclean : clean
	make -C ${LIBFT_DIR} fclean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re