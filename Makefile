NAME := PackageSaver

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
#
# INCS        header file locations
#
# SRC_DIR     source directory
# SRCS        source files
#
# BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
#
# CC          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name

INCS := include

SRC_DIR := src
SRCS := PkgSaver.c main.c
SRCS := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR := .build
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CC := gcc
CFLAGS := -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
CPPFLAGS := $(addprefix -I,$(INCS))

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKE      quietly make
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKE        := $(MAKE) --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)


#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:
