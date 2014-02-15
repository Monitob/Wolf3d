# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/11 16:51:17 by jbernabe          #+#    #+#              #
#    Updated: 2014/02/13 15:45:05 by jbernabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g --debug -Wall -Wextra -Werror -I./libft/ -I../minilibx/

LIBMLX	= -L/usr/X11/lib/include/ -L/usr/X11/lib -lXext -lX11 -lmlx

PATH_SRC = ./src
PATH_OBJ = ./objs
PATH_INC = ./includes

NAME = rtv_bin 

SRC = main.c ray.c fcn_op.c

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

lib:
		@make -C libft 

all:  lib $(NAME)

$(NAME): $(OBJ)
		@$(MAKE) -C libft
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L./libft/  \
		$(LIBMLX) -lft

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

re:	clean fclean all 

.PHONY: all 
