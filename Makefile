NAME		= cub3D
NAME_BONUS	= cub3D_bonus
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT_DIR	= ./libs/libft
LIBFT		= $(LIBFT_DIR)/libft.a
INC		= -I./includes -I$(LIBFT_DIR)

# ─── OS Detection ─────────────────────────────────────────────────────────────
UNAME_S		:= $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    MLX_DIR	= ./libs/minilibx-linux
    MLX_LNK	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
    MLX_INC	= -I$(MLX_DIR)
else
    MLX_DIR	= ./libs/minilibx_macos_metal/minilibx_mms_20200219
    MLX_LNK	= -L$(MLX_DIR) -lmlx -framework AppKit -framework Metal
    MLX_INC	= -I$(MLX_DIR)
endif

# ─── Sources ───────────────────────────────────────────────────────────────────
SRC_DIR		= src

SRC		= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/parser/parse_config.c \
		  $(SRC_DIR)/parser/parse_file.c \
		  $(SRC_DIR)/parser/read_map_file.c \
		  $(SRC_DIR)/parser/parse_map.c \
		  $(SRC_DIR)/parser/normalize_map.c \
		  $(SRC_DIR)/parser/validate_map.c \
		  $(SRC_DIR)/engine/raycasting.c \
		  $(SRC_DIR)/engine/renderer.c \
		  $(SRC_DIR)/engine/textures.c \
		  $(SRC_DIR)/player/init_player.c \
		  $(SRC_DIR)/player/movement.c \
		  $(SRC_DIR)/player/process_movement.c \
		  $(SRC_DIR)/utils/error.c \
		  $(SRC_DIR)/utils/memory.c

OBJ		= $(SRC:.c=.o)

SRC_BONUS	= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/parser/parse_config.c \
		  $(SRC_DIR)/parser/parse_file.c \
		  $(SRC_DIR)/parser/read_map_file.c \
		  $(SRC_DIR)/parser/parse_map.c \
		  $(SRC_DIR)/parser/normalize_map.c \
		  $(SRC_DIR)/parser/validate_map.c \
		  $(SRC_DIR)/engine/raycasting.c \
		  $(SRC_DIR)/engine/renderer_bonus.c \
		  $(SRC_DIR)/engine/minimap_bonus.c \
		  $(SRC_DIR)/engine/textures.c \
		  $(SRC_DIR)/player/init_player.c \
		  $(SRC_DIR)/player/movement.c \
		  $(SRC_DIR)/player/process_movement.c \
		  $(SRC_DIR)/utils/error.c \
		  $(SRC_DIR)/utils/memory.c

OBJ_BONUS	= $(SRC_BONUS:.c=.o)

# ─── Rules ─────────────────────────────────────────────────────────────────────
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
ifeq ($(UNAME_S), Linux)
	@make -C $(MLX_DIR) --silent
else
	@if [ ! -f "$(MLX_DIR)/libmlx.dylib" ]; then \
		sed -i.bak 's/CGAssociateMouseAndMouseCursorPosition(UInt32(1))/CGAssociateMouseAndMouseCursorPosition(boolean_t(1))/g' $(MLX_DIR)/interface.swift; \
		( \
			swiftc -parse-as-library -emit-module -emit-module-path $(MLX_DIR)/mlx_image.swiftmodule -module-name mlx_image -module-link-name mlx_image $(MLX_DIR)/mlx_image.swift && \
			swiftc -parse-as-library -emit-module -emit-module-path $(MLX_DIR)/mlx_window.swiftmodule -module-name mlx_window -module-link-name mlx_window $(MLX_DIR)/mlx_window.swift -I$(MLX_DIR) && \
			swiftc -parse-as-library -emit-module -emit-module-path $(MLX_DIR)/mlx_init.swiftmodule -module-name mlx_init -module-link-name mlx_init $(MLX_DIR)/mlx_init.swift -I$(MLX_DIR) && \
			swiftc -parse-as-library -c $(MLX_DIR)/interface.swift -o $(MLX_DIR)/interface.o -I$(MLX_DIR) && \
			swiftc -parse-as-library -c $(MLX_DIR)/mlx_image.swift -o $(MLX_DIR)/mlx_image.o -I$(MLX_DIR) && \
			swiftc -parse-as-library -c $(MLX_DIR)/mlx_window.swift -o $(MLX_DIR)/mlx_window.o -I$(MLX_DIR) && \
			swiftc -parse-as-library -c $(MLX_DIR)/mlx_init.swift -o $(MLX_DIR)/mlx_init.o -I$(MLX_DIR) && \
			cc -O3 -c $(MLX_DIR)/mlx_xpm.c -o $(MLX_DIR)/mlx_xpm.o -I$(MLX_DIR) && \
			cc -O3 -c $(MLX_DIR)/mlx_png.c -o $(MLX_DIR)/mlx_png.o -I$(MLX_DIR) && \
			cc -O3 -c $(MLX_DIR)/mlx_string_put.c -o $(MLX_DIR)/mlx_string_put.o -I$(MLX_DIR) && \
			swiftc -o $(MLX_DIR)/libmlx.dylib -emit-library $(MLX_DIR)/interface.o $(MLX_DIR)/mlx_image.o $(MLX_DIR)/mlx_window.o $(MLX_DIR)/mlx_init.o $(MLX_DIR)/mlx_xpm.o $(MLX_DIR)/mlx_png.o $(MLX_DIR)/mlx_string_put.o -lz \
		); \
		STATUS=$$?; \
		if [ -f "$(MLX_DIR)/interface.swift.bak" ]; then mv $(MLX_DIR)/interface.swift.bak $(MLX_DIR)/interface.swift; fi; \
		exit $$STATUS; \
	fi
	@cp $(MLX_DIR)/libmlx.dylib .
endif
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LNK) -o $(NAME)
	@echo "✓ $(NAME) built successfully"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJ_BONUS)
ifeq ($(UNAME_S), Linux)
	@make -C $(MLX_DIR) --silent
else
	@if [ ! -f "$(MLX_DIR)/libmlx.dylib" ]; then \
		sed -i.bak 's/CGAssociateMouseAndMouseCursorPosition(UInt32(1))/CGAssociateMouseAndMouseCursorPosition(boolean_t(1))/g' $(MLX_DIR)/interface.swift; \
		( \
			swiftc -parse-as-library -emit-module -emit-module-path $(MLX_DIR)/mlx_image.swiftmodule -module-name mlx_image -module-link-name mlx_image $(MLX_DIR)/mlx_image.swift && \
			swiftc -parse-as-library -emit-module -emit-module-path $(MLX_DIR)/mlx_window.swiftmodule -module-name mlx_window -module-link-name mlx_window $(MLX_DIR)/mlx_window.swift -I$(MLX_DIR) && \
			swiftc -parse-as-library -emit-module -emit-module-path $(MLX_DIR)/mlx_init.swiftmodule -module-name mlx_init -module-link-name mlx_init $(MLX_DIR)/mlx_init.swift -I$(MLX_DIR) && \
			swiftc -parse-as-library -c $(MLX_DIR)/interface.swift -o $(MLX_DIR)/interface.o -I$(MLX_DIR) && \
			swiftc -parse-as-library -c $(MLX_DIR)/mlx_image.swift -o $(MLX_DIR)/mlx_image.o -I$(MLX_DIR) && \
			swiftc -parse-as-library -c $(MLX_DIR)/mlx_window.swift -o $(MLX_DIR)/mlx_window.o -I$(MLX_DIR) && \
			swiftc -parse-as-library -c $(MLX_DIR)/mlx_init.swift -o $(MLX_DIR)/mlx_init.o -I$(MLX_DIR) && \
			cc -O3 -c $(MLX_DIR)/mlx_xpm.c -o $(MLX_DIR)/mlx_xpm.o -I$(MLX_DIR) && \
			cc -O3 -c $(MLX_DIR)/mlx_png.c -o $(MLX_DIR)/mlx_png.o -I$(MLX_DIR) && \
			cc -O3 -c $(MLX_DIR)/mlx_string_put.c -o $(MLX_DIR)/mlx_string_put.o -I$(MLX_DIR) && \
			swiftc -o $(MLX_DIR)/libmlx.dylib -emit-library $(MLX_DIR)/interface.o $(MLX_DIR)/mlx_image.o $(MLX_DIR)/mlx_window.o $(MLX_DIR)/mlx_init.o $(MLX_DIR)/mlx_xpm.o $(MLX_DIR)/mlx_png.o $(MLX_DIR)/mlx_string_put.o -lz \
		); \
		STATUS=$$?; \
		if [ -f "$(MLX_DIR)/interface.swift.bak" ]; then mv $(MLX_DIR)/interface.swift.bak $(MLX_DIR)/interface.swift; fi; \
		exit $$STATUS; \
	fi
	@cp $(MLX_DIR)/libmlx.dylib .
endif
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(MLX_LNK) -o $(NAME_BONUS)
	@echo "✓ $(NAME_BONUS) built successfully"

$(LIBFT):
	@make -C $(LIBFT_DIR) --silent

%.o: %.c
	$(CC) $(CFLAGS) $(INC) $(MLX_INC) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR) --silent
	rm -f $(OBJ) $(OBJ_BONUS)
	@echo "✓ Objects cleaned"

fclean: clean
	@make clean -C $(MLX_DIR) --silent
	@make fclean -C $(LIBFT_DIR) --silent
	rm -f $(NAME) $(NAME_BONUS)
	rm -f libmlx.dylib
	@echo "✓ Binary removed"

re: fclean all

norm:
	@norminette $(SRC_DIR)/ includes/ | grep -E "^Error" || echo "✓ Norminette: no errors"

.PHONY: all clean fclean re norm bonus
