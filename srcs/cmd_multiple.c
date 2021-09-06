#include "head_minishell.h"

void	ft_multiple_cmd(t_cmd *cmd)
{
	int		pid;
	t_cmd	*tmp;

	// ft_create_pipes(cmd->data);
	// tmp = cmd;
	// while (tmp)
	// {
	// 	pid = fork();
	// 	if (pid < 0)
	// 		ft_pr_error(ERR_FORK, -1, 0, 0);
	// 	else if (!pid)
	// 	{
	// 		ft_close_pipes(tmp, tmp->num_start);
	// 		ft_child(tmp), exit(1);
	// 	}
	// 	tmp = tmp->next;
	// }
	// ft_close_pipes(cmd->data, -1);
	// exit(0);
	ft_wait_all_cmd(cmd->data);
	return ;
}
