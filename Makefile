NAME 	= so_long.a

CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror

SRCS 	= ./source/ft_check_door.c ./source/ft_display.c ./source/ft_init_loop.c ./source/ft_render_map.c ./source/ft_printf.c ./source/get_next_line.c ./source/ft_check_collectables.c

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
