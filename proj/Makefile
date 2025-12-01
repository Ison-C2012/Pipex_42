NAME := pipex

CC := cc
CFLAGS := -Wall -Wextra -Werror
IFLAGS := -Iincludes

SRCDIR := srcs
OBJDIR := objs
ARCDIR := libft

SRCS	:= 	main.c \
			exit.c \
			pipex.c
OBJS	:= $(SRCS:%.c=$(OBJDIR)/%.o)
ARCS	:= libft.a

$(NAME): $(OBJS)
	@make -C $(ARCDIR)
	$(CC) $(CFLAGS) $^ $(ARCDIR)/$(ARCS) $(IFLAGS) $(MLXFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@

all: $(NAME)

clean:
	@make -C $(ARCDIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	@make -C $(ARCDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
