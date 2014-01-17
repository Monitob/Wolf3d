# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/14 17:46:32 by jbernabe          #+#    #+#              #
#    Updated: 2014/01/17 20:41:39 by jbernabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = wolf3d

SRC = main.c display_screen.c ft_open.c init_data.c  ray_position.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I./libft/

all: $(NAME)

$(NAME):	$(OBJ)
		@$(MAKE) -C libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)\
		-I/usr/X11/lib/include/ -L/usr/X11/lib -lmlx -lXext -lX11 \
		-L./libft/ -lft

%.o: %.c
		@$(CC) $(CFLAGS) -c $<
		@echo Compiling object  : $<

clean:		
		@$(MAKE) -C libft
		@rm -rf $(OBJ)

fclean:		clean
		@$(MAKE) -C libft
		@rm -rf $(NAME)

re:		fclean all

.PHONY : all clean re fclean
