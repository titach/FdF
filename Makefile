NAME	= fdf
CFLAGS	= -Wextra -Wall -Werror -g
LIBMLX	= ./MLX42
LIBFT	= ./libft

HEADERS	= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS	=	main.c \
			get_next_line.c \
			set_up_color.c \
			ft_free.c \
			check_file_msg.c \
			utils.c \
			build_grid.c \
			start_grid.c

OBJS	= ${SRCS:.c=.o}

all: libmlx $(NAME) 

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) -L. $(LIBFT)/libft.a

%.o: %.c $(HEADER_FILE)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)  && printf "Compiling: $(notdir $<)"

clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)

re: clean all

.PHONY: all clean fclean re libmlx