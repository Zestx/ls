CC = gcc
CFLAGS = -Wall -Wextra -Werror --pedantic 
NAME = ft_ls
INCLUDES = ./includes/ft_ls.h
SRCS = ./srcs/*.c
OBJS = display.o ft_ls.o getstat.o list.o list_b.o parse.o sort.o util.o format.o

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft 
	$(CC) $(CFLAGS) $^ -I. ./libft/libft.a -o ft_ls

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -I. -c $^

clean:
	rm -rf *.o
	make fclean -C ./libft

fclean: clean
	rm -rf ft_ls

re: fclean all
