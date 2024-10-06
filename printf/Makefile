# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 17:34:45 by vperez-f          #+#    #+#              #
#    Updated: 2024/10/05 16:20:23 by vpf              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = ft_printf.c print_hexa.c print_num.c print_ptr.c print_text.c\

OFILES = $(CFILES:%.c=%.o)

OBJ = $(OFILES)

CFLAGS = #-Wall -Wextra -Werror

CC = cc

ARLIB = ar rc

RM = rm -f

NAME = libftprintf.a

%.o: %.c 	 ft_printf.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	$(ARLIB) $(NAME) $(OFILES)
	
clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
