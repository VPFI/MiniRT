# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 13:59:42 by vperez-f          #+#    #+#              #
#    Updated: 2024/09/27 13:55:11 by vperez-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

END=\033[0m

NAME = rt

CFILES = main.c

HEADERS = includes/minirt.h

OFILES = $(CFILES:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR),$(OFILES))

OBJ_DIR = obj/

OBJ_PATH = obj

DIR_LIBFT = libft/ 

PATH_LFT = libft/libft.a

DIR_PTF = printf/

PATH_PTF = printf/libftprintf.a

DIR_MLX = minilibx_linux/

PATH_MLX = minilibx_linux/libmlx.a

CFLAGS = -Wall -Wextra -Werror -O3 #-fsanitize=address -fsanitize=leak

MLXFLAGS = -L -lmlx -lXext -lX11 -lm

CC = cc

ARLIB = ar rc

RM = rm -f

all: extra_make $(NAME)

extra_make:
	@printf "LIBFT: COMPILING...\n$(END)"
	@$(MAKE) -C libft/ --no-print-directory
	@printf "PRINTF: COMPILING...\n$(END)"
	@$(MAKE) -C printf/ --no-print-directory
	@printf "MINILIBX: COMPILING...\n$(END)"
	@$(MAKE) -C minilibx_linux/ --no-print-directory

$(NAME): $(OBJ) $(PATH_LFT) $(PATH_MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(PATH_LFT) $(PATH_PTF) $(PATH_MLX) $(MLXFLAGS) -o $(NAME)
	@printf "\n$(NAME) COMPILED!\n$(END)"

$(OBJ_DIR)%.o: src/%.c $(DIR_LFT) $(DIR_PTF) $(DIR_MLX) fdf.h Makefile
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C libft/ clean --no-print-directory
	@$(MAKE) -C printf/ clean --no-print-directory
	@$(MAKE) -C minilibx_linux/ clean --no-print-directory
	@$(RM) $(OBJ)

fclean:	clean
	@$(MAKE) -C libft/ fclean --no-print-directory
	@$(MAKE) -C printf/ fclean --no-print-directory
	@$(RM) $(NAME)
	@rm -rf $(OBJ_PATH)

re:	fclean all

.PHONY: all clean fclean re