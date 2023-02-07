NAME			=	philo
NAME_B			=	philo_bonus
SRCDIR			=	src/
OBJDIR			=	obj/
INCDIR			=	include/
BIN				=	bin/philo
REQUIRED_DIRS	=	${OBJDIR} ${OBJDIR_B} bin/
CFLAGS			=	-Wall -Werror -Wextra
CFLAGS			+=	-g -pthread -I ${INCDIR} -I ${INCDIR_B}
CC				=	cc
FILES			=	main.c utils.c parse.c routine.c locks.c
SRC				=	${addprefix ${SRCDIR}, ${FILES}}
OBJ				=	${addprefix ${OBJDIR}, ${FILES:.c=.o}}

SRCDIR_B		=	src_bonus/
OBJDIR_B		=	obj_bonus/
INCDIR_B		=	include_bonus/
BIN_B			=	bin/philo_bonus

FILES_B			=	main_bonus.c utils_bonus.c parse_bonus.c routine_bonus.c locks_bonus.c

SRC_B			=	${addprefix ${SRCDIR_B}, ${FILES_B}}
OBJ_B			=	${addprefix ${OBJDIR_B}, ${FILES_B:.c=.o}}


COLOR_WHITE		=	\e[00m
COLOR_GREEN		=	\e[32m
COLOR_BLUE		=	\e[34m
COLOR_RED		=	\e[91m

all: ${NAME}

bonus: ${BIN_B}

${REQUIRED_DIRS}:
	mkdir -p $@

${OBJDIR}%.o: ${SRCDIR}%.c
	@echo "$(COLOR_GREEN)Compiling $(COLOR_WHITE)$(<:.c=)"
	@${CC} ${CFLAGS} -c $< -o $@

${OBJDIR_B}%.o: ${SRCDIR_B}%.c
	@echo "$(COLOR_GREEN)Compiling $(COLOR_WHITE)$(<:.c=)"
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${REQUIRED_DIRS} ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${BIN}
	cp ${BIN} ${NAME}
	@echo "$(COLOR_GREEN)Compiled Succesfully$(COLOR_WHITE)"

${BIN_B}: ${REQUIRED_DIRS} ${OBJ_B}
	${CC} ${CFLAGS} ${OBJ_B} -o ${BIN_B}
	cp ${BIN_B} ${NAME_B}
	@echo "$(COLOR_GREEN)Compiled Succesfully$(COLOR_WHITE)"

clean:
	@echo "$(COLOR_BLUE)Removing all objects$(COLOR_WHITE)"
	rm -rf ${OBJDIR}
	rm -rf ${OBJDIR_B}

fclean: clean
	@echo "$(COLOR_BLUE)Removing $(NAME)$(COLOR_WHITE)"
	@echo "$(COLOR_BLUE)Removing $(NAME_B)$(COLOR_WHITE)"
	rm -rf ${NAME}
	rm -rf ${NAME_B}
	rm -rf ${BIN}
	rm -rf ${BIN_B}
	rm -rf bin/

re: fclean all

val: all
	valgrind --leak-check=full --show-leak-kinds=all ./philo 1 2 3 4

.PHONY: re fclean clean all