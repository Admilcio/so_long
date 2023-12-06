NAME 	= so_long.a

CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror

SRCS 	= ./source/check_path.c ./source/end_screen.c ./source/generate_map_array.c ./source/map_printer.c ./source/movements.c ./source/get_next_line.c ./source/get_next_line_utils.c ./source/ft_init_loop.c ./source/errors.c ./utils/ft_itoa.c ./utils/ft_split.c ./utils/ft_strlen.c ./utils/ft_strjoinfree.c ./utils/ft_strnstr.c ./utils/ft_putchar_lenght.c ./utils/ft_strncmp.c ./utils/ft_memcpy.c ./source/map_initializer.c ./source/read_player_and_collect.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re program

.SILENT:
