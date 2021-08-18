#ifndef HEAD_MINISHELL_H
# define HEAD_MINISHELL_H

# include "../libft/srcs/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h> 
# include <term.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>

# define SHELL_FW "\033[32mminishell$ \033[0m"

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}				t_env;

typedef struct s_data
{
	int			error;
	char 		*str_cmd;
	t_env		*beg_env;
}				t_data;



/* v_minishell_utils.c */
void	v_pr_error(char *str, int error_code);
void	v_pool_env(t_data *data, char **env, int i);
void	v_init_data(t_data *data, char **env);
void	v_free_data(t_data *data);
void	v_print_data(t_data *data);

/* s_parser.c */
int		ft_parsing(t_data *data, char *str);

#endif