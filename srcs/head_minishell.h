#ifndef HEAD_MINISHELL_H
# define HEAD_MINISHELL_H

# include "../libft/srcs/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termios.h>
# include <curses.h> 
# include <term.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>

# define SHELL_FW "\033[32mminishell$ \033[0m"

# define STDIN		0
# define STDOUT		1
# define FALSE		0
# define TRUE		1

# define ERR_MALC		"Error : malloc error"		//exit_code -1
# define ERR_RDL		"Error : readline error"	//exit_code -2
# define ERR_FORK		"Error : fork error"		//exit_code -3
# define ERR_PIPE		"Error : pipe error"		//exit_code -4
# define ERR_DUP		"Error : dup2 error"		//exit_code -5
# define PID_EXEP		"[Sorry, we're not allowed to use func getpid]"
# define ERR_SH_NEWL	"minishell: syntax error near unexpected token 'newln'"
# define ERR_SH_TKN		"minishell: syntax error near unexpected token "
# define ERR_COMM		"command not found: "

typedef struct s_env
{
	char			*key;
	char			*val;
	unsigned char	visible;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**arg;
	pid_t			pid;
	unsigned char	is_fork;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data
{
	unsigned char	error;
	int				fd_in;
	int				fd_out;
	unsigned int	shlvl;
	char			*str_cmd;
	char 			**envp;
	t_env			*beg_env;
	t_cmd			*cmd_start;
}				t_data;

/* v_minishell_utils.c */
void	v_pr_error(char *str, int error_code, char c, int fl);
void	v_pool_env(t_data *data, char **env, int i, size_t len);
void	v_init_data(t_data *data, char **env);
void	v_free_data(t_data *data);
void	v_print_data(t_data *data);

/* s_parser.c */
int		ft_parsing(t_data *data, char *str);
char	*ft_almost_all(t_data *data, char *str, int *i, char *rez);
char	*ft_proc_open(t_data *data, char *str, int *i, char *rez);

/* v_pars_dollar.c */
char	*ft_normal(char *str, int *i, char *rez, char *stop);
char	*ft_dollar(t_data *data, char *str, int *i, char *rez);

/* v_pars_cpec.c */
char	*ft_redir(t_data *data, char *str, int *i, char *rez);

/* s_find_command.c*/
void ft_find_command(t_data *data, char *rez, int i);

#endif