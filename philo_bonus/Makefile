
RST='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[1;36m'

SRC =	main_bonus.c \
		init_bonus.c \
		write_bonus.c \
		utils_bonus.c \
		parse_bonus.c \
		dinner_bonus.c \
		monitoring_bonus.c \
		sinchro_utils_bonus.c \
		safe_bonus.c \
		getters_setters_bonus.c \

OBJS = $(SRC:.c=.o)

HEAD = philo_bonus.h

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(HEAD)
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