SRCS	=	minishell.c v_minishell_utils.c

BONUS	=	

SRCS_DIR = ./srcs/

SRCS_BONUS_DIR = ./srcs_bonus/

OBJS	=	${addprefix ${SRCS_DIR}, ${SRCS:.c=.o}}

BONUS_OBJS = ${addprefix ${SRCS_BONUS_DIR}, ${BONUS:.c=.o}}

NAME = minishell

USER = vleida

B_NAME = minishell_b

HEADER = ./srcs/head_minishell.h


LIBS_MAC	=  ./libft/libft.a -L /Users/${USER}/.brew/opt/readline/lib

INCLUDE		=  -I /Users/${USER}/.brew/opt/readline/include


LOGDATE		= $(shell date)

CC = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

# COLORS

GREEN	= \033[0;32m
YELO	= \033[0;33m
BLUE	= \033[0;34m
NEW		= \033[0;35m
SHALLOW = \033[0m

# END COLORS

.PHONY: all clean fclean re bonus norm libft readline pull push

all:		${NAME}

%.o:%.c		${HEADER}
			@${CC} ${CFLAGC} -c $< -o ${<:.c=.o}

libft:		
			@make -C ./libft/

${NAME}:	${OBJS} ${HEADER}
			@make -C ./libft/
			@${CC} ${CFLAGC} -o ${NAME} ${OBJS} ${LIBS_MAC} ${INCLUDE} 
			@echo "${GREEN}${NAME} compile!${SHALLOW}"

readline:	
			@brew install readline

norm:
			@echo "${GREEN}|-----Chek NORMs!-----|${NEW}"
			@norminette ./srcs/
			@norminette ./libft/
#			@norminette ./srcs_bonus/
			@echo "${GREEN}|-----Chek ended!-----|${SHALLOW}"

clean:		
			@${RM} ${OBJS} ${BONUS_OBJS}
			@make clean -C ./libft/
			@echo "${BLUE}clean done!${SHALLOW}"

fclean:		
			@${RM} ${OBJS} ${BONUS_OBJS} ${NAME} ${B_NAME}
			@make fclean -C ./libft/
			@echo "${YELO}fclean done!${SHALLOW}"

pull:		fclean
			@git pull
			@echo "${GREEN}|-----Pull done!-----|${SHALLOW}"

push:		fclean
			@git pull
			@git add .
			@git commit -m "${LOGDATE}"
			@git push
			@echo "${GREEN}|-----Push done!-----|${SHALLOW}"

# bonus:		${BONUS_OBJS} ${HEADER}
# 			@make -C ./libft/
# 			@${CC} ${CFLAGC} -o ${B_NAME} ${BONUS_OBJS} ${OBJS} ${LIBS_MAC} ${INCLUDE} 
# 			@echo "${NEW}${B_NAME} compile!${SHALLOW}"

re:			fclean all