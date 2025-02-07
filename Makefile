NAME = minishell

LIBFT_PATH = ./libs/libft/
LIBFT = $(LIBFT_PATH)libft.a

SRC_DIR = ./src/
SRC_FILES = main.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = ./obj/
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC_DIR = ./includes/

CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I$(INC_DIR)

RM = rm -f

INCLUDE = minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBFT_PATH) -lft
	@echo "Compilation done"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory 
	@echo "LIBFT created"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c -o $@ $<

clean: 
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory > /dev/null 2>&1
	@$(RM) $(OBJ)
	@echo "Clean done"

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory > /dev/null 2>&1
	@$(RM) $(NAME)
	@echo "Fclean done"

re: fclean all

.PHONY: clean all re fclean
