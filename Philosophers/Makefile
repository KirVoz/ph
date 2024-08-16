
RST='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[1;36m'

SRC =	main.c \
		init.c \
		write.c \
		utils.c \
		parse.c \
		dinner.c \
		monitor.c \
		sinchro_utils.c \
		safe_functions.c \
		getters_setters.c \

OBJS = $(SRC:.c=.o)

HEAD = philo.h

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@echo "${GREEN}Building $(NAME)...${RST}"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${CYAN}Done 🍱${RST}"
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	@$(RM) $(NAME)
	@echo "${RED}Completed! 🧼   (fclean)${RST}"

clean:
	@$(RM) - $(NAME)
	@rm -f ${OBJS}
	@echo "${YELLOW}Completed! 🧽    (clean)${RST}"

re: 	fclean all

.PHONY: all clean fclean re