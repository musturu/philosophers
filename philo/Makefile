# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -pthread

# Directories
SRCDIR = srcs/
OBJDIR = objs/

# Libraries

# Source files
SRC = actions.c validation.c init.c philo.c thread.c utils.c monitor.c free_memory.c

SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJDIR), $(OBJ)) 

# Executable name
NAME = philo

all: $(NAME) 

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		

$(OBJDIR):
	mkdir -p $@


clean:
	rm -rf $(OBJDIR)


fclean: clean
	rm -f $(NAME)


re: fclean all


git:
	make fclean
	git add .
	git commit -m "auto-commit"
	git push


.PHONY: all clean fclean re
