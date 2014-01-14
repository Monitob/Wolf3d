
CC = gcc #-Wall -Wextra -Werror

NAME = wolf3d

SRC = main.c

OBJ = $(SRC:.c=.o)

CFLAGS =  -I../../../lib42/minilibx/ -I./../../../lib42/libft/

all: $(NAME)

$(NAME):	$(OBJ)
		@$(MAKE) -C ../../../lib42/libft/
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)\
		-L/usr/X11/lib -lmlx -lXext -lX11 \
		-I/usr/X11/lib/include/ \
		-L../../../lib42/minilibx/ \
		-L../../../lib42/libft/

%.o: %.c
		@$(CC) $(CFLAGS) -c $<
		@echo Compililing object  : $<

clean:		
		@$(MAKE) -C ../../../lib42/libft/
		@rm -rf $(OBJ)

fclean:		clean
		@$(MAKE) -C ../../../lib42/libft/
		@rm -rf $(NAME)

re:		fclean all

.PHONY : all clean re fclean
