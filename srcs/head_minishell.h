#ifndef HEAD_MINISHELL_H
# define HEAD_MINISHELL_H

# include "../libft/srcs/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
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

# define STDIN		0
# define STDOUT		1
# define FALSE		0
# define TRUE		1
# define PIPE		1
# define DOB_PIPE	2
# define DOB_AMPER	3
# define POINT_ZAP	4

# define ERR_MALC		"Error : malloc error"
# define ERR_RDL		"Error : readline error"
# define ERR_GNL		"Error : get_next_line error"
# define ERR_FORK		"Error : fork error"
# define ERR_PIPE		"Error : pipe error"
# define ERR_DUP		"Error : dup2 error"
# define PID_EXEP		"[Sorry, we're not allowed to use func getpid]"
# define ERR_SH_NEWL	"minishell: syntax error near unexpected token 'newln'"
# define ERR_SH_TKN		"minishell: syntax error near unexpected token "
# define ERR_CMD		"minishell: command not found: "

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
	char			*ful_cmd;
	pid_t			pid;
	unsigned char	delim;
	struct s_data	*data;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data
{
	int				counter;
	int 			ret_val;
	unsigned char	error;
	int				fd_in;
	int				fd_out;
	unsigned int	shlvl;
	char			**env;
	char			*rez;
	t_env			*beg_env;
	t_cmd			*cmd_start;
}				t_data;

/* minishell_utils.c */
int		ft_pr_error(char *str, int error_code, char c, int fl);
void	ft_pool_env(t_data *data, int i, size_t len);
void	ft_init_data(t_data *data, char **env);
void	ft_free_data(t_data *data);
char	**ft_proc_envp(t_data *data);

/* parser.c */
int		ft_parsing(t_data *data, char *str);
void	ft_hadle_str(t_data *data, char *str, int *i);
char	*ft_proc_open(t_data *data, char *str, int *i, char *rez);

/* pars_dollar.c */
char	*ft_normal(char *str, int *i, char *rez, char *stop);
char	*ft_dollar(t_data *data, char *str, int *i, char *rez);

/* proc_redirects.c */
int		ft_redir(t_data *data, char *str, int *i);

/* here_doc.c */
int		ft_here_doc(t_data *data, char *str, int *i);

/* cmd.c */
char	*ft_find_cmd(t_data *data, char *cmd);
void	ft_start_cmd(t_data *data);
int		ft_pool_cmd(t_data *data, char *str, int *i);
int		ft_pool_cmd_st(t_data *data, char *str, int *i);
void	ft_free_cmd(t_cmd *do_cmd, char *cmd);

/* biuld_in.c */
int		ft_buildin(t_data *data);

#endif
