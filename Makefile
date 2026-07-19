# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/14 11:30:00 by jnovais          #+#    #+#              #
#    Updated: 2026/07/16 10:00:00 by jnovais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= libs/libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= libs/mlx_linux
MLX			= $(MLX_DIR)/libmlx.a

SRCS		= src/main.c \
			  src/parser/parse_file.c \
			  src/parser/parse_config.c \
			  src/parser/parse_map.c
OBJS		= $(SRCS:.c=.o)
INCLUDES	= -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR)
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
