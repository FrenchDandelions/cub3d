NAME = cub3d
VERMILION_RED=\033[1;31m
AZURE_BLUE=\033[1;34m
GOLD_COLOR=\033[38;5;220m
GREEN=\033[0;32m
RESET=\033[0m
LIB_DIR = ./libft/
LIB_FILE = $(LIB_DIR)libft.a
SRC_FILES = srcs/main.c \
			srcs/get_map.c \
			srcs/check_file_name.c \
			srcs/fill_map.c \
			srcs/fill_map_utils.c \

OBJECTS = $(SRC_FILES:.c=.o)
INCLUDE = ./includes/cub3d.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I -Ilibft 

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)  

$(LIB_FILE): 
	make -C $(LIB_DIR)

$(NAME) : $(LIB_FILE) $(OBJECTS) $(INCLUDE) Makefile
	@echo "$(GOLD_COLOR)Compiling cub3d...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) -g3 -Ilibft -lreadline $(OBJECTS) $(LIB_FILE)
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

re: fclean $(NAME)

.PHONY: all clean fclean re