NAME:= ipc

SRCDIR:= src
LIBDIR:= lib
OBJDIR:= obj

SRC:= envp.c ipc02.c
LIB:= libft.a
OBJ:= $(SRC:%.c=$(OBJDIR)/%.o)

CFLAGS:= -Wall -Werror -Wextra
IFLAGS:= -I inc

$(NAME): $(OBJ)
	$(CC) $^ $(LIBDIR)/$(LIB) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir @)
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@

all: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
