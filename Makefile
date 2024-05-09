NAME = cub3D
NAMEB = cub3D_bonus

VERMILION_RED=\033[1;31m
AZURE_BLUE=\033[1;34m
GOLD_COLOR=\033[38;5;220m
GREEN=\033[0;32m
RESET=\033[0m

LIB_DIR = ./libft/
LIB_FILE = $(LIB_DIR)libft.a
MLX_DIR = ./minilibx-linux/
MLX_FILE = $(MLX_DIR)libmlx.a

SRC_FILES = srcs/main/main.c \
			srcs/parsing/get_map_list.c \
			srcs/parsing/get_map_list_utils.c \
			srcs/parsing/check_access.c \
			srcs/parsing/check_elements.c \
			srcs/parsing/check_file_name.c \
			srcs/parsing/fill_map.c \
			srcs/parsing/fill_map_utils.c \
			srcs/parsing/rgb_utils.c \
			srcs/parsing/rgb.c \
			srcs/mlx/start.c \
			srcs/mlx/free_objects.c \
			srcs/mlx/move.c \
			srcs/mlx/rotate.c \
			srcs/raycasting/raycast.c \

SRC_BONUS = srcs_bonus/main/main.c \
			srcs_bonus/parsing/get_map_list.c \
			srcs_bonus/parsing/get_map_list_utils.c \
			srcs_bonus/parsing/check_access.c \
			srcs_bonus/parsing/check_elements.c \
			srcs_bonus/parsing/check_file_name.c \
			srcs_bonus/parsing/fill_map.c \
			srcs_bonus/parsing/fill_map_utils.c \
			srcs_bonus/parsing/rgb_utils.c \
			srcs_bonus/parsing/rgb.c \

OBJECTS = $(SRC_FILES:.c=.o)
DEP = $(SRC_FILES:.c=.d)
OBJECTSB = $(SRC_BONUS:.c=.o)
DEPB = $(SRC_BONUS:.c=.d)

INCLUDE = ./includes/cub3d.h ./libft/libft.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -I -L$(LIB_DIR) -Ilibft -MMD -MP
LDFLAGS = -L./minilibx-linux/ -lmlx_Linux -lX11 -lXext -lm
MLX_EX = $(MLX_FILE) $(LDFLAGS)

INCLUDES := includes \
	libft

INCLUDES_FLAGS := $(addprefix -I , $(INCLUDES))

.c.o:
	@$(CC) $(CFLAGS) $(INCLUDES_FLAGS) -c $< -o $@

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
	$(CC) $(CFLAGS) -o $(NAME) $(INCLUDES_FLAGS) $(OBJECTS) $(LIB_FILE) $(MLX_EX)
	@echo "$(GOLD_COLOR)cub3d compiled ! :)$(RESET)"

$(NAMEB) : $(MLX_DIR) $(MLX_FILE) $(LIB_FILE) $(OBJECTSB) $(INCLUDE) Makefile
	@echo "$(GOLD_COLOR)Compiling cub3d_bonus...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAMEB) $(INCLUDES_FLAGS) $(OBJECTSB) $(LIB_FILE) $(MLX_EX)
	@echo "$(GOLD_COLOR)cub3d_bonus compiled ! :)$(RESET)"

bonus : $(NAMEB)

clean:
	@echo "$(AZURE_BLUE)Cleaning in progress...$(RESET)"
	@rm -f $(OBJECTS)
	@rm -f $(OBJECTSB)
	@rm -f $(DEP)
	@rm -f $(DEPB)
	@make clean -sC $(LIB_DIR)
	@echo "$(AZURE_BLUE)Cleanup done ! :)$(RESET)"

fclean: clean
	@echo "$(AZURE_BLUE)Deep cleaning in progress...$(RESET)"
	@rm -f $(NAME)
	@rm -f $(NAMEB)
	@make fclean -sC $(LIB_DIR)
	@echo "$(AZURE_BLUE)Deep Cleaning over ! :)$(RESET)"

uclean : fclean
	@echo "$(VERMILION_RED)Ultimate cleaning in progress...$(RESET)"
	@rm -rf $(MLX_DIR)
	@echo "$(VERMILION_RED)Ultimate cleaning over! $(RESET)"

re: fclean $(NAME)

cre:
	@clear
	@make re --no-print-directory

mlx_re: uclean $(NAME)

.PHONY: all clean fclean uclean re mlx_re bonus
