#include "head_minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*str;
	int		i;

	v_init_data(&data, env);
	while (TRUE)
	{
		str = readline(SHELL_FW);
		if (!str || !ft_strncmp(str, "exit", 5))
			break ;
		add_history(str);
		if (!ft_parsing(&data, str))
			printf("|%s|\n", data.str_cmd);
		// 	ft_run_cmd(&data);
		free(data.str_cmd), free(str), str = NULL;
	}
	if (str)
		free(str), str = NULL;
	v_print_data(&data);
	v_free_data(&data);
	// sleep (20);
	return (0);
}
