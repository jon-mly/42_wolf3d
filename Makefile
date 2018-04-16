# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmlynarc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/14 14:31:18 by jmlynarc          #+#    #+#              #
#    Updated: 2018/04/14 14:31:19 by jmlynarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
ASSOCIATED_REP = $(NAME).dSYM

LIBFT_REP = libft
LIBFT = $(LIBFT_REP)/libft.a

INCLUDE_FLAG = -I includes/

SRCS_REP = srcs/
SRCS = $(SRCS_REP)main.c \
		$(SRCS_REP)env_init.c \
		$(SRCS_REP)exit.c \
		$(SRCS_REP)graphic_manager.c \
		$(SRCS_REP)camera.c \
		$(SRCS_REP)map_init.c \
		$(SRCS_REP)tools.c \
		$(SRCS_REP)pixel_drawing.c \
		$(SRCS_REP)texturing.c \
		$(SRCS_REP)line_drawing.c \
		$(SRCS_REP)textures_init.c \
		$(SRCS_REP)deinit.c \
		$(SRCS_REP)raycasting.c \
		$(SRCS_REP)loop.c

O_SRCS = $(SRCS:.c=.o)

W_FLAGS = -Wall -Werror -Wextra

MLX_FLAGS = -I ~/Library -g -L ~/Library -lmlx -framework OpenGL -framework \
			AppKit

MATH_FLAG = -lm

%.o: %.c
	@gcc $(W_FLAGS) -c $< -o $@

$(NAME):
	make -C $(LIBFT_REP)
	gcc $(INCLUDE_FLAG) $(MLX_FLAGS) $(MATH_FLAG) $(SRCS) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	make clean -C $(LIBFT_REP)
	rm -rf $(O_SRCS)

fclean: clean
	make fclean -C $(LIBFT_REP)
	rm -rf $(NAME) $(ASSOCIATED_REP)

re: fclean all

.PHONY: clean fclean re all
