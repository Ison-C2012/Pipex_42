NAME:= ipc

SRCDIR:= src
LIBDIR:= lib
OBJDIR:= obj

SRC:= main/ipc04.c envp.c get_pathname.c interpret_status.c
LIB:= libft.a
OBJ:= $(SRC:%.c=$(OBJDIR)/%.o)

CFLAGS:= -Wall -Werror -Wextra
IFLAGS:= -I inc

$(NAME): $(OBJ)
	$(CC) $^ $(LIBDIR)/$(LIB) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@

all: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
