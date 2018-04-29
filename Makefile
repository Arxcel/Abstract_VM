CC = clang++

NAME = avm

FLAGS = -std=c++11 -Wall -Wextra -Werror # -fsanitize=address

I_DIR = ./inc

S_DIR = ./src

O_DIR = obj

EXTENSIONS = $(addprefix $(I_DIR)/,$(EXT))

EXT = 

HEADERS =-I$(I_DIR)

SOURCES = main.cpp


SRCS = $(addprefix $(S_DIR)/,$(SOURCES))

OBJS = $(addprefix $(O_DIR)/,$(SOURCES:.cpp=.o))

all: obj $(NAME)

$(NAME): $(OBJS) $(EXTENSIONS)
		$(CC) -o $(NAME) $(OBJS) $(FLAGS) $(HEADERS)

obj:
	mkdir -p obj

$(O_DIR)/%.o: $(S_DIR)/%.cpp $(DEPS) $(EXTENSIONS)
		$(CC) -c -o $@ $< $(FLAGS) $(HEADERS)

clean:
		rm -f $(OBJS)
		rm -rf $(O_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all, obj, clean, fclean, re
.NOTPARALLEL:  all, obj, clean, fclean, re
.SILENT: