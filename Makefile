# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 13:59:42 by vperez-f          #+#    #+#              #
#    Updated: 2024/11/26 20:26:58 by vperez-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CFILES = main.c mlx_utils.c bresenham_font.c font.c vect_functions.c file_selector.c

HEADERS = includes/miniRT.h

OFILES = $(CFILES:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR),$(OFILES))

OBJ_DIR = obj/

OBJ_PATH = obj

DIR_LIBFT = libft/ 

PATH_LFT = libft/libft.a

DIR_PTF = printf/

PATH_PTF = printf/libftprintf.a

DIR_MLX	 = ./mlx/MLX42/build

PATH_MLX = $(DIR_MLX)/libmlx42.a

CFLAGS = -Wall -Wextra -Werror -O3 #-g -fsanitize=address -fsanitize=leak #-fsanitize=thread

MLXFLAGS = -L -lmlx42 -lXext -lX11 -lm -lglfw

CC = cc

ARLIB = ar rc

RM = rm -f

all: $(NAME)

$(NAME): extra_make $(OBJ) $(PATH_LFT) $(PATH_MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(PATH_LFT) $(PATH_PTF) $(PATH_MLX) $(MLXFLAGS) -o $(NAME)
	@printf "\n$(NAME) COMPILED!\n"

extra_make: create_mlx
	@printf "LIBFT: COMPILING...\n"
	@$(MAKE) -C $(DIR_LIBFT) --no-print-directory
	@printf "PRINTF: COMPILING...\n"
	@$(MAKE) -C $(DIR_PTF) --no-print-directory
	@printf "MINILIBX: COMPILING...\n"
	@$(MAKE) -C $(DIR_MLX) --no-print-directory

$(OBJ_DIR)%.o: src/%.c $(DIR_LFT) $(DIR_PTF) $(DIR_MLX) $(HEADERS) Makefile
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

create_mlx: 
	@echo "Creating MLX"
	@cd mlx/MLX42 && cmake -B build && cmake --build build --parallel --config Release

clean:
	@$(MAKE) -C libft/ clean --no-print-directory
	@$(MAKE) -C printf/ clean --no-print-directory
	@$(RM) $(OBJ)

fclean:	clean
	@$(MAKE) -C libft/ fclean --no-print-directory
	@$(MAKE) -C printf/ fclean --no-print-directory
	@$(RM) $(NAME)
	@rm -rf $(OBJ_PATH)
	@rm -rf mlx/MLX42/build

re:	fclean all

.PHONY: all clean fclean re