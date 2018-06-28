# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/14 14:31:18 by jmlynarc          #+#    #+#              #
#    Updated: 2018/06/28 16:01:09 by jmlynarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
ASSOCIATED_REP = $(NAME).dSYM

LIBFT_REP = libft
LIBFT = $(LIBFT_REP)/libft.a

INCLUDE_FLAG = -I includes/

SRCS_REP = srcs/
SRCS = main.c \
		env_init.c \
		exit.c \
		graphic_manager.c \
		camera.c \
		map_init.c \
		map_check.c\
		tools.c \
		pixel_drawing.c \
		texturing.c \
		line_drawing.c \
		textures_init.c \
		deinit.c \
		raycasting.c \
		loop.c

SRC = $(addprefix $(SRCS_REP), $(SRCS))

O_SRCS = $(SRC:.c=.o)

W_FLAGS = -Wall -Werror -Wextra

MLX_FLAGS = -I ~/Library -g -L ~/Library -lmlx -framework OpenGL -framework \
			AppKit

MATH_FLAG = -lm

DEBUG_FLAG = -fsanitize=address

%.o: %.c
	@gcc $(W_FLAGS) $(INCLUDE_FLAG) -c $< -o $@

$(NAME): $(O_SRCS)
	make -C $(LIBFT_REP)
	gcc $(INCLUDE_FLAG) $(MLX_FLAGS) $(MATH_FLAG) $(SRC) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	make clean -C $(LIBFT_REP)
	rm -rf $(O_SRCS)

fclean: clean
	make fclean -C $(LIBFT_REP)
	rm -rf $(NAME) $(ASSOCIATED_REP)

re: fclean all

.PHONY: clean fclean re all
