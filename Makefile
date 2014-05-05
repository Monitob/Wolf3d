# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/04 22:30:52 by jbernabe          #+#    #+#              #
#    Updated: 2014/04/26 22:35:24 by jbernabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = wolf3d

CFLAGS = -g --debug -I ../minilibx/  -Wall -Wextra -Werror -I./libft/ 

LIBMLX	= -L../minilibx/ -L/usr/X11/lib/ -L/usr/X11/lib -lXext -lX11 -lmlx -lm
#-L/usr/X11/lib/ -L/usr/X11/lib -lXext -lX11 -lmlx -lm



PATH_SRC = ./src
PATH_OBJ = ./objs
PATH_INC = ./includes

SRC = main.c display_screen.c ft_open.c init_data.c  ray_position.c

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all:  lib $(NAME)

lib:
		@make -C libft

$(NAME): $(OBJ)
		@$(MAKE) -C libft
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L./libft/  \
		$(LIBMLX) -L/usr/lib/ -lft

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/, %.c)
	@mkdir -p $(PATH_OBJ)
	@$(CC) $(CFLAGS) -o $@ -I $(PATH_INC) -Ilibft -c $<
	@echo Compiling object : $<

clean:
	@$(MAKE) -C libft $@
	@rm -f $(OBJ)

fclean:	clean
	@$(MAKE) -C libft $@
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: fclean all

.PHONY: re, clean, fclean
