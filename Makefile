SRC = cub3d.c raycasting.c 

OBJ = $(SRC:.c=.o)

LIBFT= libft/libft.a

NAME = cub

all: $(NAME) $(LIBFT)

%.o: %.c
	$(CC)  -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -Lmlx_linux -lmlx_Linux  -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


$(LIBFT):
	make all -C ./libft

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all