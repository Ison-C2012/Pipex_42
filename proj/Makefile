NAME := pipex

RULE := all

CC := cc
CFLAGS := -Wall -Wextra -Werror
IFLAGS := -Iincludes

SRCDIR := srcs
OBJDIR := objs
ARCDIR := libft

SRCS	:= 	main.c \
			pipex.c \
			process.c \
			exec.c \
			wait.c \
			helper.c
OBJS	:= $(SRCS:%.c=$(OBJDIR)/%.o)
ARCS	:= libft.a

all: $(NAME)

debug: RULE=debug
debug: CC=gcc
debug: CFLAGS=-g3 -Wall -Wextra -Werror
debug: $(NAME)

memory: RULE=memory
memory: CC=gcc -O0
memory: CFLAGS=-Wall -Wextra -Werror -fsanitize=address
memory: $(NAME)

$(NAME): $(OBJS)
	@make -C $(ARCDIR) $(RULE)
	$(CC) $(CFLAGS) $^ $(ARCDIR)/$(ARCS) $(IFLAGS) $(MLXFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@

clean:
	@make -C $(ARCDIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	@make -C $(ARCDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
