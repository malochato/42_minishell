NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIB = ar rcs
RM = rm -f
OBJ = $(SRC:.c=.o)
INCLUDE = libft.h get_next_line.h
SRC = ft_atoi.c ft_lstclear_bonus.c ft_memset.c ft_strlcpy.c \
	  ft_bzero.c ft_lstdelone_bonus.c ft_putchar_fd.c ft_strlen.c \
	  ft_calloc.c ft_lstiter_bonus.c ft_putendl_fd.c ft_strmapi.c \
	  ft_isalnum.c ft_lstlast_bonus.c ft_putnbr_fd.c ft_strncmp.c \
	  ft_isalpha.c ft_lstmap_bonus.c ft_putstr_fd.c ft_strnstr.c \
	  ft_isascii.c ft_lstnew_bonus.c ft_split.c ft_strrchr.c \
	  ft_isdigit.c ft_lstsize_bonus.c ft_strchr.c ft_strtrim.c \
	  ft_isprint.c ft_memchr.c ft_strdup.c ft_substr.c \
	  ft_itoa.c ft_memcmp.c ft_striteri.c ft_tolower.c \
	  ft_lstadd_back_bonus.c ft_memcpy.c ft_strjoin.c ft_toupper.c \
	  ft_lstadd_front_bonus.c ft_memmove.c ft_strlcat.c get_next_line.c \
	  ft_strndup.c

BONUS_OBJ = $(BONUS_SRC:.c=.o)

BONUS_SRC = ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstmap_bonus.c ft_lstadd_front_bonus.c  \
			ft_lstiter_bonus.c ft_lstnew_bonus.c \
			ft_lstclear_bonus.c ft_lstlast_bonus.c \
			ft_lstsize_bonus.c

FT_PRINTF_DIR = ft_printf

all: $(NAME)

$(NAME): $(OBJ) $(BONUS_OBJ)
	@$(MAKE) -C $(FT_PRINTF_DIR)
	@cp $(FT_PRINTF_DIR)/libftprintf.a $(NAME)
	@$(LIB) $(NAME) $(OBJ) $(BONUS_OBJ)

%.o: %.c $(INCLUDE)
	@$(CC) $(FLAGS) -c -o $@ $<

clean: 
	@$(MAKE) -C $(FT_PRINTF_DIR) clean
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@echo "Clean done"

fclean: clean
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean
	@$(RM) $(NAME)
	@echo "Fclean done"

re: fclean all

.PHONY: clean all re fclean