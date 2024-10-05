CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb -g3
INCLUDES = -I/usr/include -Ilibft -Ignl -Iftprintf -O3 
SRCS = main.c
NAME = pipex
OBJS = $(SRCS:.c=.o)
GNL_DIR = ./gnl
GNL_LIB = $(GNL_DIR)/libgnl.a
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
FTPRINTF_DIR = ./ftprintf
FTPRINTF_LIB = $(FTPRINTF_DIR)/libftprintf.a
LFLAGS = -Ilibft -L./libft -lft -Ignl -L./gnl -lgnl -Iftprintf -L./ftprintf -lftprintf
 
all: $(LIBFT_LIB) $(FTPRINTF_LIB) $(GNL_LIB) $(NAME)
 
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
 
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(FTPRINTF_LIB):
	@make -C $(FTPRINTF_DIR)

$(GNL_LIB):
	@make -C $(GNL_DIR)

clean:
	rm -f $(OBJS)
	cd $(LIBFT_DIR) && make clean
	cd $(FTPRINTF_DIR) && make clean
	cd $(GNL_DIR) && make clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT_DIR) && make fclean
	cd $(FTPRINTF_DIR) && make fclean
	cd $(GNL_DIR) && make fclean

re: fclean all

.PHONY: all clean fclean re
