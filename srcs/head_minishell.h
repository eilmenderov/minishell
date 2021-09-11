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
# define PWD_LEN	1024

# define ERR_MALC		"Error : malloc error"
# define ERR_RDL		"Error : readline error"
# define ERR_GNL		"Error : get_next_line error"
# define ERR_FORK		"Error : fork error"
# define ERR_PIPE		"Error : pipe error"
# define ERR_DUP		"Error : dup2 error"
# define PID_EXEP		"[Sorry, we're not allowed to use func getpid]"
# define ERR_SH_NEWL	"minishell: syntax error near unexpected token newline"
# define ERR_SH_TKN		"minishell: syntax error near unexpected token "
# define ERR_CMD		"minishell: command not found: "
# define ERR_NFD		"minishell: No such file or directory"
# define ERR_EXP		"Error: export: not a valid identifier"

extern int	g_stat;

typedef struct s_env
{
	int				print;
	char			*key;
	char			*val;
	unsigned char	visible;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**arg;
	char			*ful_cmd;
	char			*dino;
	int				num_start;
	int				fd_inf;
	int				fd_outf;
	int				tmp_fd[2];
	pid_t			pid;
	unsigned char	delim;
	struct s_data	*data;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_data
{
	int				fl;
	int				count;
	unsigned char	ret_val;
	unsigned char	error;
	int				fd_in;
	int				fd_out;
	int				total_cmd;
	int				**fd_pipes;
	int				shlvl;
	int				old_stat;
	int				*all_pid;
	char			*tmp;
	char			**env;
	char			*rez;
	t_env			*beg_env;
	t_cmd			*cmd_start;
}				t_data;

/* builtins_utils.c 5/5 */
void	ft_change_oldpwd(t_cmd *cmd, int fl);
int		ft_cd(t_cmd *cmd, t_env *tmp);
int		ft_chek_env_key(char *str, int fl);
int		ft_change_env(t_cmd *cmd, char *str, int visib, int len);

/* builtins.c 3/5 */
t_env	*ft_find_key(t_env *env);
void	ft_start_own_prog(t_cmd *cmd, int fl);
int		ft_buildin(t_cmd *cmd, int fl);

/* cmd_multiple.c 4/5 */
void	ft_multiple_cmd(t_cmd *cmd, int i);

/* cmd_utils.c 5/5 */
char	*ft_find_cmd(t_cmd *do_cmd);
t_cmd	*ft_pool_new_cmd(t_data *data, char *str, int *i);
int		ft_pool_cmd(t_data *data, char *str, int *i);

/* cmd.c 3/5 */
void	ft_wait_all_cmd(t_data *data);
void	ft_start_cmd(t_data *data);

/* export.c 5/5 */
int		ft_export(t_cmd *cmd, int i);

/* free_clear.c 3/5 */
void	ft_free_cmd(t_cmd *do_cmd);
void	ft_free_data(t_data *data);
void	ft_clean_all(char *str, t_cmd *start);

/* here_doc.c 2/5 */
int		ft_here_doc(t_data *data, char *str, int *i, char *stoper);

/* minishell_utils.c 5/5 */
t_env	*ft_new_env(char *key, char *val, unsigned char visible);
void	ft_init_data(t_data *data, char **env, t_env *tmp);
char	**ft_proc_envp(t_data *data);
void	ft_env_to_char(t_data *data);

/* minishell.c 3/5 */
int		ft_pr_error(char *str, int error_code, char c, int fl);

/* own_progc.c 5/5 */
void	ft_echo(t_cmd *cmd);
int		ft_pwd(t_data *data, int fl, t_cmd *cmd);
int		ft_env(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
int		ft_unset(t_cmd *cmd, int i);

/* pars_dollar.c 5/5 */
char	*ft_normal(char *str, int *i, char *rez, char *stop);
char	*ft_dollar(t_data *data, char *str, int *i, char *rez);

/* parser.c 5/5 */
void	ft_hadle_str(t_data *data, char *str, int *i);
char	*ft_proc_open(t_data *data, char *str, int *i, char *rez);
int		ft_parsing(t_data *data, char *str, int i);

/* pipes_redir.c 4/5 */
void	ft_create_pipes(t_data *data);
void	ft_close_pipes(t_data *data, t_cmd *cmd, int fl);
void	ft_redirects(t_cmd *cmd, int fl);
int		ft_redir_helper(t_data *data);

/* proc_redirects.c 5/5 */
int		ft_redir(t_data *data, char *str, int *i);

/* signal.c 4/5 */
void	ft_signal(void);
void	ft_signal_cmd(void);

#endif
