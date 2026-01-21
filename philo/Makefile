# -----------------------------------Makefile------------------------------------
NAME	= philo 

DEBUG	= debug

# -----------------------------------Sources-------------------------------------

HEADER		=	includes/philo.h 

SRCS		=	main.c \
				philo_init.c \
				philo_utils.c \
				philo_utils_2.c \
				philo_routine.c \

SRC			=	${addprefix sources/, ${SRCS}}

OBJS_DIR	=	objects

OBJS		=	${addprefix ${OBJS_DIR}/, ${SRC:.c=.o}}

# -----------------------------------Compilation---------------------------------

CC			= cc

FLAGS		= -Wall -Wextra -Werror -pthread -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3

RM			= rm -f

FSANITIZE	= -fsanitize=thread -g

# -----------------------------------Libraries-----------------------------------

INCLUDES	= -I ./includes \

# -----------------------------------Rules---------------------------------------

all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
		${CC} ${FLAGS} ${OBJS} -o ${NAME} 

${OBJS_DIR}/%.o: %.c
		@mkdir -p $(dir $@)
		${CC} ${FLAGS} -c ${INCLUDES} $< -o $@

debug: ${FT} ${OBJS} ${HEADER}
		${CC} ${FLAGS} ${FSANITIZE} ${OBJS} -o ${DEBUG}

re: fclean all

clean:
		@${RM} -r ${OBJS_DIR}
		@echo "It's clean."

fclean: clean
		@${RM} ${NAME}
		@${RM} ${DEBUG}
		@echo "It's like mega clean mate."

# -----------------------------------.phony-------------------------------------

.PHONY: all clean fclean re debug batman joker gotham
