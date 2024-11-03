GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

SRCS =		main.c\
					parser.c\
					print.c\
					time.c\
					table.c\
					routine.c\


philo = philo

CC	= cc -g
RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -ggdb3 -g

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(philo):
		${CC} ${SRCS} -o ${philo}
		@printf "$(GREEN)    - Executable ready.\n$(RESET)"

all: $(philo)


clean:
		@printf "$(YELLOW)    - Objects removed.$(RESET)\n"

fclean: clean
	${RM} ${philo}
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"

re:	fclean all
	@printf "$(YELLOW)    - Objects removed.$(RESET)\n"
	@printf "$(GREEN)    - Makefile recompiled.$(RESET)\n"

.PHONY:	all clean fclean re

shit: re
	  clear
	  ./philo