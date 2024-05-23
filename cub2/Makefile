SRC = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parsing/parsing_1.c

OBJ = $(SRC:.c=.o)

LIBFT= libft/libft.a

NAME = cub

all: $(NAME) $(LIBFT)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -Lmlx_linux -lmlx_Linux  -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) #-fsanitize=address


$(LIBFT):
	make all -C ./libft

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all