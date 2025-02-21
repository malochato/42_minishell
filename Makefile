NAME = minishell

LIBFT_PATH = ./libs/libft/
LIBFT = $(LIBFT_PATH)libft.a

SRC_DIR = ./src/

PARSING_DIR = $(SRC_DIR)parsing/
PARSING_FILES = parsing_env.c
PARSING = $(addprefix $(PARSING_DIR), $(PARSING_FILES))

ENV_DIR = $(SRC_DIR)env/
ENV_FILES = env_manager.c utils_0.c utils_1.c
ENV = $(addprefix $(ENV_DIR), $(ENV_FILES))

BUILTINS_DIR = $(SRC_DIR)builtins/
BUILTINS_FILES = 	pwd.c env.c echo.c unset.c cd.c exit.c\
					export.c export_utils.c \
					utils.c builtins.c
					
BUILTINS = $(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES))

EXEC_DIR = $(SRC_DIR)exec/
EXEC_FILES = exec.c
EXEC = $(addprefix $(EXEC_DIR), $(EXEC_FILES))

SRC_FILES = main.c free_all.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))  $(PARSING) $(EXEC) $(BUILTINS) $(ENV)




OBJ_DIR = ./obj/
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC_DIR = ./includes/

CC = cc
FLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I$(LIBFT_PATH)

RM = rm -f

INCLUDE = minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo -n "Compilation "
	@for i in 1 2 3; do \
		echo -n "."; \
		sleep 0.35; \
	done
	@echo ""
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBFT_PATH) -lft -lreadline
	@echo "Compilation $(NAME) done"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory 
	@echo "LIBFT created"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

clean: 
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory > /dev/null 2>&1
	@$(RM) $(OBJ)
	@$(RM) -r $(OBJ_DIR)
	@echo "Clean done"

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory > /dev/null 2>&1
	@$(RM) $(NAME)
	@echo "Fclean done"

re: fclean all

.PHONY: clean all re fclean
