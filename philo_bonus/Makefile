NAME			=	philo_bonus
SRCDIR			=	src/
OBJDIR			=	obj/
INCDIR			=	include/
BIN				=	bin/philo_bonus
REQUIRED_DIRS	=	${OBJDIR} ${OBJDIR_B} bin/
CFLAGS			=	-Wall -Werror -Wextra
CFLAGS			+=	-g -pthread -I ${INCDIR}
CC				=	cc
FILES			=	init_bonus.c	\
					main_bonus.c	\
					utils_bonus.c	\
					parse_bonus.c	\
					routine_bonus.c	\
					locks_bonus.c
SRC				=	${addprefix ${SRCDIR}, ${FILES}}
OBJ				=	${addprefix ${OBJDIR}, ${FILES:.c=.o}}

COLOR_WHITE		=	\e[00m
COLOR_GREEN		=	\e[32m
COLOR_BLUE		=	\e[34m
COLOR_RED		=	\e[91m

all: ${NAME}

${REQUIRED_DIRS}:
	mkdir -p $@

${OBJDIR}%.o: ${SRCDIR}%.c
	@echo "$(COLOR_GREEN)Compiling $(COLOR_WHITE)$(<:.c=)"
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${REQUIRED_DIRS} ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${BIN}
	cp ${BIN} ${NAME}
	@echo "$(COLOR_GREEN)Compiled Succesfully$(COLOR_WHITE)"

clean:
	@echo "$(COLOR_BLUE)Removing all objects$(COLOR_WHITE)"
	rm -rf ${OBJDIR}

fclean: clean
	@echo "$(COLOR_BLUE)Removing $(NAME)$(COLOR_WHITE)"
	rm -rf ${NAME}
	rm -rf ${BIN}
	rm -rf bin/

re: fclean all

val: all
	valgrind --leak-check=full --show-leak-kinds=all ./philo_bonus 5 500 200 200

.PHONY: re fclean clean all