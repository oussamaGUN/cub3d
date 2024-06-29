SRC = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parsing/parsing.c parsing/reading_texture.c \
		parsing/map_parsing.c parsing/map_rules.c parsing/parsing_tools.c

OBJ = $(SRC:.c=.o)

LIBFT= libft/libft.a

NAME = cub

all: $(NAME) $(LIBFT)

%.o: %.c
	@$(CC) -c $< -o $@
	@echo "Compiled" $< "successfully"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME) #-fsanitize=address Lmlx_linux -lmlx_Linux  -Imlx_linux -lXext -lX11 -lm -lz
	@echo "Cub3D compiled"


$(LIBFT):
	make all -C ./libft
	@echo "Libft compiled"

clean:
	@rm -rf $(OBJ)
	@echo "Objects removed"

fclean: clean
	@rm -rf $(NAME)
	@echo "Cub3D removed"

re: fclean all
	@echo "Cub3D recompiled"