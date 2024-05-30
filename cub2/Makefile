SRC = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parsing/parsing.c parsing/reading_texture.c \
		parsing/map_parsing.c parsing/map_rules.c parsing/parsing_tools.c

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