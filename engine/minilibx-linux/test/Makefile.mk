
INC=%%%%

INCLIB=$(INC)/../lib

UNAME := $(shell uname)

CFLAGS= -I$(INC) -O3 -I.. -g

NAME= mlx-test
SRC = main.c
OBJ = $(SRC:%.c=%.o)

LFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm

ifeq ($(UNAME), Darwin)
	# mac
	CC = clang
else ifeq ($(UNAME), FreeBSD)
	# FreeBSD
	CC = clang
else
	# Linux and others...
	CC	= gcc
	# Add -lbsd only if libbsd is available on the system.
	# Try ldconfig (most Linuxes) or fallback to checking common lib paths.
	BSD_LIB := $(shell ldconfig -p 2>/dev/null | grep -q libbsd && echo yes || (ls /usr/lib*/libbsd* 2>/dev/null | grep -q . && echo yes))
	ifeq ($(BSD_LIB),yes)
		LFLAGS += -lbsd
	endif
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		:\n	$(SRC)\n"
	@printf "OBJ		:\n	$(OBJ)\n"

clean:
	rm -f $(NAME) $(OBJ) *~ core *.core

re: clean all
