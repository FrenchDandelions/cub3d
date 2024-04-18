NAME = cub3d
VERMILION_RED=\033[1;31m
AZURE_BLUE=\033[1;34m
GOLD_COLOR=\033[38;5;220m
GREEN=\033[0;32m
RESET=\033[0m
LIB_DIR = ./libft/
LIB_FILE = $(LIB_DIR)libft.a
MLX_DIR = ./minilibx-linux/
MLX_FILE = $(MLX_DIR)libmlx.a
SRC_FILES = srcs/main.c \
			srcs/get_map_list.c \
			srcs/get_map_list_utils.c \
			srcs/check_access.c \
			srcs/check_elements.c \
			srcs/check_file_name.c \
			srcs/fill_map.c \
			srcs/fill_map_utils.c \

OBJECTS = $(SRC_FILES:.c=.o)
INCLUDE = ./includes/cub3d.h ./libft/libft.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I -L$(LIB_DIR) -Ilibft
LDFLAGS = -L./minilibx-linux/ -lmlx_Linux -lX11 -lXext -lm
MLX_EX = $(MLX_FILE) $(LDFLAGS)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)  

$(MLX_FILE) :
	@if [ ! -f "$(MLX_FILE)" ]; then \
		echo "$(GREEN)Compiling Minilibx...$(RESET)"; \
		make -sC $(MLX_DIR) > /dev/null 2>&1; \
	fi

$(MLX_DIR) :
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "$(VERMILION_RED)Cloning minilibx-linux...$(RESET)"; \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR) > /dev/null 2>&1; \
	fi

$(LIB_FILE): 
	make -C $(LIB_DIR)

$(NAME) : $(MLX_DIR) $(MLX_FILE) $(LIB_FILE) $(OBJECTS) $(INCLUDE) Makefile
	@echo "$(GOLD_COLOR)Compiling cub3d...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) -g3 -Ilibft $(OBJECTS) $(LIB_FILE) $(MLX_EX)
	@echo "$(GOLD_COLOR)cub3d compiled ! :)$(RESET)"

clean:
	@echo "$(AZURE_BLUE)Cleaning in progress...$(RESET)"
	@rm -f $(OBJECTS)
	@make clean -sC $(LIB_DIR)
	@echo "$(AZURE_BLUE)Cleanup done ! :)$(RESET)"

fclean: clean
	@echo "$(AZURE_BLUE)Deep cleaning in progress...$(RESET)"
	@rm -f $(NAME)
	@make fclean -sC $(LIB_DIR)
	@echo "$(AZURE_BLUE)Deep Cleaning over ! :)$(RESET)"

uclean : fclean
	@echo "$(VERMILION_RED)Ultimate cleaning in progress...$(RESET)"
	@rm -rf $(MLX_DIR)
	@echo "$(VERMILION_RED)Ultimate cleaning over! $(RESET)"

re: fclean $(NAME)

mlx_re: uclean $(NAME)

.PHONY: all clean fclean uclean re mlx_re