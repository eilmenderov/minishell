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
	if (!str || !ft_strcmp(str, ""))
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

static void	ft_clean_all(char *str)
{
	free (str), str = NULL;
}

/*
**	@brief	minishell start here
*/
int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*str;

	ft_init_data(&data, env);
	ft_signal();
	while (TRUE)
	{
		str = readline(SHELL_FW);
		if (g_stat == 100)
		{
			data.old_stat = 1;
			g_stat = 0;
		}
		if (ft_str_spec_case(str))
			continue ;
		add_history(str);
		if (!ft_parsing(&data, str))
		{
			printf("first_cmd : |%s|\n", data.cmd_start->ful_cmd);
			ft_start_cmd(&data);
			free(data.rez), data.rez = NULL;
		}
		ft_clean_all(str);
	}
}
