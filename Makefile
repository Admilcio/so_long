NAME    = so_long.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror 
SRCS    = ./source/source/check_collectibles.c ./source/source/end_screen.c \
        ./source/source/check_border.c ./source/source/generate_map_array.c \
        ./source/source/map_printer.c ./source/source/movements.c \
        ./source/source/movements_utils.c ./source/source/get_next_line.c \
        ./source/source/get_next_line_utils.c ./source/source/ft_init_loop.c \
        ./source/source/errors.c ./source/utils/ft_split.c \
        ./source/utils/ft_strlen.c ./source/utils/ft_strjoinfree.c \
        ./source/utils/ft_strnstr.c ./source/utils/ft_putchar_lenght.c \
        ./source/utils/ft_strncmp.c ./source/utils/ft_memcpy.c \
        ./source/source/map_initializer.c ./source/source/read_player_and_collect.c \
        ./source/utils/ft_printf.c ./source/utils/ft_numbers.c \
        ./source/utils/ft_words.c ./source/utils/ft_strstr.c
OBJS    = $(SRCS:.c=.o)
PROGRAM = so_long

all: $(NAME) program

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

program: $(NAME)
		$(CC) $(CFLAGS) -o $(PROGRAM) main.c $(NAME) mlx/libmlx.a -lXext -lX11

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME) $(PROGRAM)

re: fclean all

.PHONY: all clean fclean re program

.SILENT:
