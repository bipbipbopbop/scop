# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhache <jhache@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/03 10:02:52 by jhache            #+#    #+#              #
#    Updated: 2021/01/31 01:36:19 by jhache           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := scop

# Basic definitions
SRC_PATH := source
OBJ_PATH := .bin
INC_PATH := $(SRC_PATH)# additionnal path, the other (implicit) one being the path of the currently compiled source file
LIB_PATH := library

# Libraries
LIBSDL_NAME := SDL2
LIBSDL_PATH := $(LIB_PATH)/SDL2-2.0.14
LIBSDL := $(LIBSDL_PATH)/lib/lib$(LIBSDL_NAME).a

LIB := $(LIBSDL)

# Compiler
CC := g++
CCFLAGS := -Wall -Werror -Wextra -g3 `$(LIBSDL_PATH)/sdl2-config --cflags`
LDFLAGS := `$(LIBSDL_PATH)/sdl2-config --libs`
INCFLAGS := $(addprefix -iquote , $(INC_PATH))


# Commands
RM := rm -f
RMDIR := rm -Rdf
MKDIR := mkdir -p


# Files
SRC_NAME :=	main.cpp \
			parsing/obj_wavefront/Lexer.cpp

SRC :=	$(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ :=	$(addprefix $(OBJ_PATH)/, $(SRC_NAME:.cpp=.o))

OBJ_DIRS := $(sort $(dir $(OBJ)))


# Rules
all: $(LIB) $(NAME)

$(LIBSDL): $(LIBSDL_PATH).zip
	unzip -u $< -d $(LIB_PATH) > $(LIB_PATH)/unzip.log
	cd $(LIBSDL_PATH) && ./configure --prefix $(CURDIR)/$(LIBSDL_PATH)
	make -C $(LIBSDL_PATH)
	make -C $(LIBSDL_PATH) install

$(NAME): $(OBJ_DIRS) $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $(OBJ)

$(OBJ_DIRS):
	$(MKDIR) $(OBJ_PATH) $@

$(OBJ_PATH)/%.o: $(addprefix $(SRC_PATH)/, %.cpp)
	$(CC) $(CCFLAGS) -MMD -MF $(<:.cpp=.d) $(INCFLAGS) -c $< -o $@


#add dependencies files (*.d)
DEP_FILES = $(SRC:%.cpp=%.d)
-include $(DEP_FILES)


clean:
	$(RM) $(OBJ)
	$(RMDIR) $(OBJ_DIRS)
	$(RM) $(DEP_FILES)

fclean: clean
	$(RM) $(NAME)
lclean: fclean
	$(RMDIR) $(LIB)

re: fclean all


.PHONY: all clean fclean re