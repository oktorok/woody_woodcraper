.PHONY : all clean fclean re check_libft

MAKEFLAGS += --silent

GCC = gcc

NAME = woody_woodpacker

FLAGS = -g #-Wall -Wextra -Werror

OBJ_DIR := objects/

SRC_DIR = src/

FILES_DIR := files_list/

FILE_LIST_FULL := $(shell ls -d $(FILES_DIR)*)

FILE_LIST_NOEXT := $(basename $(shell ls files_list))
FILE_LIST_NOEXT := $(patsubst %,:$(SRC_DIR)%,$(FILE_LIST_NOEXT))

SRC := $(shell cat $(FILE_LIST_FULL)| grep "\.c")

HEADERS := $(shell cat files_list/headers.txt)

INCLUDES_DIR = includes

VPATH := $(SRC_DIR)$(FILE_LIST_NOEXT)

LIBFT_PATH = libft/
LIBFT_HEADERS = $(LIBFT_PATH)includes
LIBFT = libft.a

HEADER_PATH = $(patsubst %.h, $(INCLUDES_DIR)/%.h, $(HEADERS))

OBJ = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

MODE = 1

ifeq ($(MODE), 0)

all: $(NAME)

$(NAME): $(OBJ)

$(OBJ_DIR)%.o : %.c $(HEADER_PATH)
	@printf "\r                                          "
	@printf "\r\033[92m--->Compiling $(@F)\033[0m"
	@$(GCC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIBFT_HEADERS) -c $<
	@mkdir -p $(OBJ_DIR)
	@mv -f $(@F) $(OBJ_DIR)

else

all: check_libft $(NAME)

$(NAME) : $(OBJ) $(LIBFT_PATH)$(LIBFT)
	@$(GCC) $(OBJ) -L$(LIBFT_PATH) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(HEADER_PATH) %.c
	@printf "\033[92mCompiling $(NAME)...\033[0m\n"
	@$(MAKE) MODE=0
	@printf "\r                                          "
	@printf "\r\033[92mDone $(NAME)[\xE2\x9C\x94]\n\033[0m"

endif

check_libft:
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@printf "\033[92m<< Cleaning $(NAME) >>\n\033[0m"
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@printf "\r\033[92m<< Fcleaning $(NAME) >>\n\033[0m"
	@rm -f $(NAME)

re:	fclean
	@$(MAKE)
