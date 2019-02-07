CC=gcc
CFLAGS= -Wall -Wextra -Werror --pedantic

all: ft_ls clean

ft_ls: ft_ls.o getstat.o display.o util.o list.o list_b.o sort.o
	make -C ./libft 
	$(CC) $(CFLAGS) $^ -I. ./libft/libft.a -o ft_ls

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $^

clean:
	rm -rf *.o

fclean: clean
	rm -rf ft_ls

re: fclean all
