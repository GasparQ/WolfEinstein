##
## Makefile for wolf 3d make file in /home/gaspar_q/rendu/Igraph/MUL_2014_wolf3d
## 
## Made by quentin gasparotto
## Login   <gaspar_q@epitech.net>
## 
## Started on  Tue Dec  2 13:31:45 2014 quentin gasparotto
## Last update Sat Dec 20 14:51:10 2014 quentin gasparotto
##

SRC=	wolf3d.c \
	event.c \
	get_graph.c \
	get_field.c \
	get_view.c \
	get_next_line.c \
	read_line.c \
	get_side.c \
	error.c \
	get_pos.c \
	my_putchar.c \
	my_putstr.c \
	my_strlen.c \
	collision_gestion.c \
	load_texture.c \
	load_text_color.c \
	home.c \
	mini_map.c \
	graph_function.c \
	sokoban.c \
	choose_block.c \

OBJ=	$(SRC:.c=.o)

NAME=	wolf3d

$(NAME):	$(OBJ)
	cc -Wall -Wextra -o $(NAME) $(OBJ)  -L/usr/lib64/ -lmlx -L/usr/lib64/X11 -lXext -lX11 -lm -I ./include

all:	$(NAME)

clean:
	rm $(OBJ)

fclean:	clean
	rm $(NAME)

re:	fclean all
