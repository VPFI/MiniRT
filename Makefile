# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 13:59:42 by vperez-f          #+#    #+#              #
#    Updated: 2024/12/06 22:00:09 by vpf              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CFILES = main.c mlx_utils.c bresenham_font.c font.c vect_functions.c file_selector.c

HEADERS = includes/miniRT.h

OFILES = $(CFILES:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR),$(OFILES))

OBJ_DIR = obj/

DIR_LIBFT = libft/ 

PATH_LFT = libft/libft.a

DIR_PTF = printf/

PATH_PTF = printf/libftprintf.a

MLX_VERSION = 2.4.1

MLX_URL = https://github.com/codam-coding-college/MLX42/archive/refs/tags/v2.4.1.tar.gz

DIR_MLX	 = mlx/

BUILD_DIR_MLX = mlx/MLX42/build/

PATH_MLX = $(BUILD_DIR_MLX)libmlx42.a

CFLAGS = -Wall -Wextra -Werror -O3 #-g -fsanitize=address -fsanitize=leak #-fsanitize=thread

MLXFLAGS = -L -lmlx42 -lXext -lX11 -lm -lglfw

CC = cc

ARLIB = ar rc

RM = rm -f

VERBOSE = false;

all: $(NAME)

$(NAME): extra_make $(OBJ) $(PATH_LFT) $(PATH_PTF) $(PATH_MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(PATH_LFT) $(PATH_PTF) $(PATH_MLX) $(MLXFLAGS) -o $(NAME)
	@printf "\n$(NAME) COMPILED!\n"

extra_make: $(PATH_MLX)
	@printf "LIBFT: COMPILING...\n"
	@$(MAKE) -C $(DIR_LIBFT) --no-print-directory
	@printf "PRINTF: COMPILING...\n"
	@$(MAKE) -C $(DIR_PTF) --no-print-directory
	@printf "MINILIBX: COMPILING...\n"
	@$(MAKE) -C $(BUILD_DIR_MLX) --no-print-directory

$(OBJ_DIR)%.o: src/%.c $(HEADERS) Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(DIR_MLX)MLX42:
	@printf "Downloading MLX...\n"
	@curl -sOL $(MLX_URL)
	@tar -xpf v$(MLX_VERSION).tar.gz
	@rm -rf v$(MLX_VERSION).tar.gz
	@mkdir -p $(DIR_MLX)
	@mv -f MLX42-$(MLX_VERSION) MLX42
	@mv -f MLX42 $(DIR_MLX)
	@echo "MLX downloaded successfully\n"

$(PATH_MLX): $(DIR_MLX)MLX42
	@echo "Creating MLX"
	@cd mlx/MLX42 && cmake -B build && cmake --build build --parallel --config Release

clean:
	@$(MAKE) -C libft/ clean  --no-print-directory
	@$(MAKE) -C printf/ clean --no-print-directory
	@$(RM) $(OBJ)
	@printf "MiniRT: Object files removal successful!\n"

fclean:
	@$(MAKE) -C libft/ fclean --no-print-directory
	@$(MAKE) -C printf/ fclean --no-print-directory
	@$(RM) $(OBJ)
	@$(RM) $(NAME)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BUILD_DIR_MLX)
	@printf "MiniRT: Exe && MLX build removal successful!\n"

cleanMLX:
	@rm -rf $(DIR_MLX)
	@printf "MiniRT: MLX complete removal successful!\n"

cleanALL: fclean cleanMLX
	@printf "MiniRT: Total clean successful!\n"

re:	fclean all

.PHONY: all clean fclean re