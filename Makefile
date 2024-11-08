GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

SRCS =		main.c\
					parser.c\
					time.c\
					table.c\
					philo_routine.c\
					actions.c\
					fork.c\
					monitor.c


philo = philo

CC	= cc -g
RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror -pthread

#NUMBERS = $(PHILOS) $(DIE) $(EAT) $(SLEEP) 7

#NUMBERS					=	1 800 200 200   # The philosopher should not eat and should die
#NUMBERS					=	5 800 200 200   # No philosopher should die.
#NUMBERS					=	5 900 200 200 7 # No philosopher should die.
#NUMBERS					=	4 410 200 200   # No philosopher should die.
#NUMBERS					=	4 310 200 100 7 # One philosopher should die.

#NUMBERS					=	4 10 200 100	#One philosopher should die

#NUMBERS					=	5 410 200 100 7 # One philosopher should die.
#NUMBERS					=	5 120 80 80 	# Moana tolds all will die
#NUMBERS					=	2 200 50 50 1
#NUMBERS					=	50 1000 60 60 1
#NUMBERS					=	2 110 50 50 2

#NUMBERS					=	4 200 205 200	# One should die
#NUMBERS					=	4 410 200 200 10	# No one should die. Stop after 10
#NUMBERS					=	-5 600 200 200	# ERROR - CRASH
#NUMBERS					=	5 -5 200 200	# ERROR - CRASH
#NUMBERS					=	4 600 -5 200	# ERROR - CRASH
#NUMBERS					=	5 600 200 -5	# ERROR - CRASH
#NUMBERS					=	4 600 200 200 -5	# ERROR - CRASH
#NUMBERS					=	5 600 150 150	# No one should die
#NUMBERS					=	4 410 200 200	# No one should die
#NUMBERS					=	100 800 200 200	# No one should die
#NUMBERS					=	105 800 200 200	# No one should die

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