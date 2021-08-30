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

/*
**	@brief	minishell start here
*/
int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*str;
	int		i;

	ft_init_data(&data, env);
	data.counter = 0;
	while (TRUE)
	{
		str = readline(SHELL_FW);
//		if (!ft_strcmp(str, "exit"))
//			break ;
		add_history(str);
		if (!ft_parsing(&data, str))
		{
			printf("|%s|\n", data.cmd_start->ful_cmd);
			if (ft_buildin(&data))
			{
				free(str), str = NULL;
				continue ;
			}
			else
				ft_start_cmd(&data);
			free(data.rez), data.rez = NULL;
		}
		free(str), str = NULL;
	}
//	if (str)
//		free(str), str = NULL;
////	ft_print_data(&data);
//	ft_free_data(&data);
////	sleep (20);
//	return (0);
}
