NAME		= n-puzzle

PURESRCS	= parse.cpp \
				Board.cpp \
				State.cpp \
				main.cpp

PURESRCS_DB	= compute_db.cpp \
				Board.cpp \
				State.cpp
	
SRCS		= $(addprefix srcs/, $(PURESRCS))
SRCS_DB		= $(addprefix srcs/, $(PURESRCS_DB))

OBJS		= $(addprefix objs/, $(PURESRCS:.cpp=.o))
OBJS_DB		= $(addprefix objs/, $(PURESRCS_DB:.cpp=.o))

CFLAGS		= -Wall -Wextra -Werror -I. -fsanitize=address -g -I../boost/boost

all:		${NAME}

$(NAME):	${OBJS}
			c++ ${CFLAGS} -o ${NAME} ${OBJS}

compute_db:	${OBJS_DB}
			c++ ${CFLAGS} -o ${NAME} ${OBJS_DB}

objs/%.o:	srcs/%.cpp
			@mkdir -p objs
			c++ $(CFLAGS) -o $@ -c $<

clean:
			rm -rf objs

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re