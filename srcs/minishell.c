#include "head_minishell.h"

int	g_stat;

/*
**	@brief	Print struct data
*/
static void	ft_print_data(t_data *data)
{
	t_env	*tmp;

	printf("err_fl = %d\n", data->error);
	tmp = data->beg_env;
	while (tmp)
	{
		printf("%-30s%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}

static int	ft_str_spec_case(char *str)
{
	if (!ft_strcmp(str, ""))
	{
		if (str)
			free(str), str = NULL;
		return (1);
	}
	if (ft_strlen(str) == ft_how_many_char(str, ' '))
	{
		free(str);
		return (1);
	}
	return (0);
}

static void	ft_clean_all(char *str, t_cmd *start)
{
	t_cmd	*tmp;

	free (str), str = NULL;
	if (!start)
		return ;
	tmp = start;
	tmp->data->cmd_start = NULL;
	while (tmp)
	{
		start = tmp->next;
		ft_free_cmd(tmp);
		tmp = start;
	}
}

/*
**	@brief	Print errors fd = 2
**	
**	@param	str			message
**	@param	error_code	error code
**	@param	c			if fl = 1, char for message
**	@param	fl			if fl = 0 -> exit else if fl = 1 print message with c
**						else fl = 2 print str with newline
**	@return	int			error_code value
*/
int	ft_pr_error(char *str, int error_code, char c, int fl)
{
	if (!fl)
		ft_putendl_fd(str, 2), exit(error_code);
	else if (fl == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\'', 2);
		ft_putchar_fd(c, 2);
		ft_putendl_fd("'", 2);
	}
	else if (fl == 2)
		ft_putendl_fd(str, 2);
	else if (fl == 3)
	{
		ft_putstr_fd("minishell: ", 2), ft_putstr_fd(str, 2);
		ft_putendl_fd(": command not found", 2);
	}
	else if (fl == 4)
	{
		ft_putstr_fd("minishell: cd: ", 2), ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2), ft_putendl_fd(strerror(errno), 2);
	}
	return (error_code);
}

/*
**	@brief	minishell start here
*/
int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*str;

	ft_init_data(&data, env), ft_signal();
	while (TRUE)
	{
		str = readline(SHELL_FW);
		if (g_stat == 130)
		{
			data.old_stat = 1;
			g_stat = 0;
		}
		if (!str)
			str = ft_strdup("exit");
		if (ft_str_spec_case(str))
			continue ;
		add_history(str);
		if (!ft_parsing(&data, str))
		{
			ft_start_cmd(&data), ft_signal();
			free(data.rez), data.rez = NULL;
		}
		ft_clean_all(str, data.cmd_start);
	}
}
