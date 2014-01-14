# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/14 17:46:32 by jbernabe          #+#    #+#              #
#    Updated: 2014/01/14 21:57:42 by jbernabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -Wall -Wextra -Werror

NAME = wolf3d

SRC = main.c display_screen.c ft_open.c

OBJ = $(SRC:.c=.o)

CFLAGS = -I./libft/

all: $(NAME)

$(NAME):	$(OBJ)
		@$(MAKE) -C libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)\
		-L/usr/X11/lib -lmlx -lXext -lX11 \
		-I/usr/X11/lib/include/ \
		-L./libft/

%.o: %.c
		@$(CC) $(CFLAGS) -c $<
		@echo Compililing object  : $<

clean:		
		@$(MAKE) -C libft
		@rm -rf $(OBJ)

fclean:		clean
		@$(MAKE) -C libft
		@rm -rf $(NAME)

re:		fclean all

.PHONY : all clean re fclean
