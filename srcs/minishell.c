#include "head_minishell.h"

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

static void	ft_str_spec_case(char *str)
{
	if (!str)
		ft_pr_error(ERR_MALC, -1, 0, 0);
	free(str), str = NULL;
}

/*
**	@brief	minishell start here
*/
int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*str;

	ft_init_data(&data, env);
	while (TRUE)
	{
		str = readline(SHELL_FW);
		if (!ft_strcmp(str, "") || !str)
		{
			ft_str_spec_case(str);
			continue ;
		}
		add_history(str);
		if (!ft_parsing(&data, str))
		{
			ft_start_cmd(&data);
			free(data.rez), data.rez = NULL;
		}
		free(str), str = NULL;
	}
}
