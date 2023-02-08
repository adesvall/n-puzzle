NAME		= n-puzzle

PURESRCS	= parse.cpp \
				Board.cpp \
				State.cpp \
				main.cpp

SRCS		= $(addprefix srcs/, $(PURESRCS))

OBJS		= $(addprefix objs/, $(PURESRCS:.cpp=.o))

CFLAGS		= -Wall -Wextra -Werror -I. -fsanitize=address -g -I../boost/boost

all:		${NAME}

$(NAME):	${OBJS}
			c++ ${CFLAGS} -o ${NAME} ${OBJS}

objs/%.o:	srcs/%.cpp
			@mkdir -p objs
			c++ $(CFLAGS) -o $@ -c $<

clean:
			rm -rf objs

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re