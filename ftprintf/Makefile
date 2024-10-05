CC = cc
CFLAGS = -Wall -Werror -Wextra -ggdb
SRCS = ft_print_char.c \
ft_print_string.c \
ft_print_int.c \
ft_print_hexa.c \
ft_print_unsigned.c \
ft_print_pointer.c \
ft_printf.c 
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a
AR = ar rcs

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS) 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
