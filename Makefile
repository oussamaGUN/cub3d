SRC = cub3d.c raycasting/map_drawing.c

OBJ = $(SRC:.c=.o)

NAME = cub

all: $(NAME)

%.o: %.c
	$(CC)  -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux  -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all