NAME		= n-puzzle

PURESRCS	= parse.cpp \
				Board.cpp \
				State.cpp \
				main.cpp

SRCS		= $(addprefix srcs/, $(PURESRCS))

OBJS		= $(addprefix objs/, $(PURESRCS:.cpp=.o))

CFLAGS		= -Wall -Wextra -Werror -I. -fsanitize=address -g

all:		${NAME}

$(NAME):	${OBJS}
			g++ ${CFLAGS} -o ${NAME} ${OBJS}

objs/%.o:	srcs/%.cpp
			@mkdir -p objs
			g++ $(CFLAGS) -o $@ -c $<

clean:
			rm -rf objs

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re