NAME = philo

SRCS =  src/main.c \
		src/forks.c \
		src/utils.c \
		src/init.c \
		src/routines.c \
		src/actions.c \
		src/philo_utils.c \

# Define Colors
GREEN  := \033[1;32m  # Bold Green
YELLOW := \033[0;33m  # Non-bold Yellow
RED    := \033[0;31m  # Regular Red
BLUE   := \033[1;34m  # Bold Blue
PURPLE := \033[1;35m  # Bold Purple
BOLD   := \033[1m     # Bold Text
NC     := \033[0m     # No Color (Resets color and style)

OBJS = ${SRCS:.c=.o}

.SILENT: $(OBJS)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread
REMOVE = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BOLD)$(PURPLE)🍴Philo is now operative$(NC)"


clean:
	@$(REMOVE) $(OBJS)

fclean: clean
	@$(REMOVE) $(NAME)
	@echo "$(BOLD)$(GREEN)🧹Everything cleaned up!$(NC)"

re: fclean all

clear:
	@clear

.PHONY: all clean fclean re clear
