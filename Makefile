NAME		= cub3D
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
INC		= -I./includes

# ─── OS Detection ─────────────────────────────────────────────────────────────
UNAME_S		:= $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    MLX_DIR	= ./minilibx-linux
    MLX_LNK	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
    MLX_INC	= -I$(MLX_DIR)
else
    MLX_DIR	= ./minilibx_macos_metal/minilibx_mms_20200219
    MLX_LNK	= -L$(MLX_DIR) -lmlx -framework AppKit -framework Metal
    MLX_INC	= -I$(MLX_DIR)
endif

# ─── Sources ───────────────────────────────────────────────────────────────────
SRC_DIR		= src

SRC		= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/parser/parse_file.c \
		  $(SRC_DIR)/parser/parse_map.c \
		  $(SRC_DIR)/parser/parse_textures.c \
		  $(SRC_DIR)/parser/validate_map.c \
		  $(SRC_DIR)/engine/raycasting.c \
		  $(SRC_DIR)/engine/renderer.c \
		  $(SRC_DIR)/engine/textures.c \
		  $(SRC_DIR)/player/movement.c \
		  $(SRC_DIR)/player/collision.c \
		  $(SRC_DIR)/utils/error.c \
		  $(SRC_DIR)/utils/memory.c

OBJ		= $(SRC:.c=.o)

# ─── Rules ─────────────────────────────────────────────────────────────────────
all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(MLX_DIR) --silent
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LNK) -o $(NAME)
	@echo "✓ $(NAME) built successfully"

%.o: %.c
	$(CC) $(CFLAGS) $(INC) $(MLX_INC) -c $< -o $@

clean:
	@make clean -C $(MLX_DIR) --silent
	rm -f $(OBJ)
	@echo "✓ Objects cleaned"

fclean: clean
	rm -f $(NAME)
	@echo "✓ Binary removed"

re: fclean all

norm:
	@norminette $(SRC_DIR)/ includes/ | grep -E "^Error" || echo "✓ Norminette: no errors"

.PHONY: all clean fclean re norm
