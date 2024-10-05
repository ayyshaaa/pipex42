CC = cc
CFLAGS = -Wall -Werror -Wextra -ggdb

SRCS = 	get_next_line.c \
		get_next_line_utils.c 

OBJS = $(SRCS:.c=.o)
NAME = libgnl.a
AR = ar rcs
LIBFT_DIR = ../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(LIBFT_LIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) -l:../libft/libft.a -o $(OBJS)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	cd $(LIBFT_DIR) && make clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT_DIR) && make fclean

re: fclean all

.PHONY: all clean fclean re