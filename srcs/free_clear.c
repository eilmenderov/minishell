#include "head_minishell.h"

void	ft_free_cmd(t_cmd *do_cmd)
{
	t_cmd	*tmp;

	if (!do_cmd)
		return ;
	if (do_cmd->fd_inf > 0)
		close(do_cmd->fd_inf), do_cmd->fd_inf = -1;
	if (do_cmd->fd_outf > 0)
		close(do_cmd->fd_outf), do_cmd->fd_outf = -1;
	if (do_cmd->dino)
		free(do_cmd->dino), do_cmd->dino = NULL;
	if (do_cmd->arg)
		ft_free_split(do_cmd->arg), do_cmd->arg = NULL;
	if (do_cmd->ful_cmd)
		free(do_cmd->ful_cmd), do_cmd->ful_cmd = NULL;
	do_cmd->cmd = NULL;
	tmp = do_cmd->next;
	do_cmd->data->cmd_start = tmp;
	free(do_cmd), do_cmd = NULL;
}

/*
**	@brief	Free memory which was allocated
**	
**	@param	data	struct t_data
*/
void	ft_free_data(t_data *data)
{
	t_env	*tmp;
	t_env	*buf;

	tmp = data->beg_env;
	data->beg_env = NULL;
	while (tmp)
	{
		if (tmp->key)
			free(tmp->key), tmp->key = NULL;
		if (tmp->val)
			free(tmp->val), tmp->val = NULL;
		buf = tmp;
		tmp = tmp->next;
		free(buf);
	}
	ft_clean_all(NULL, data->cmd_start, 0);
	data = NULL;
}

void	ft_clean_all(char *str, t_cmd *start, int i)
{
	t_cmd	*tmp;

	if (str)
		free(str), str = NULL;
	if (!start)
		return ;
	if (start->data->rez)
		free(start->data->rez), start->data->rez = NULL;
	start->data->total_cmd = 0;
	start->data->count = 0;
	close(start->data->fd_in), close(start->data->fd_out);
	if (start->data->all_pid)
		free(start->data->all_pid), start->data->all_pid = NULL;
	while (start->data->fd_pipes && start->data->fd_pipes[i])
		free(start->data->fd_pipes[i]), start->data->fd_pipes[i] = NULL, i++;
	if (start->data->fd_pipes)
		free(start->data->fd_pipes), start->data->fd_pipes = NULL;
	tmp = start;
	tmp->data->cmd_start = NULL;
	while (tmp)
	{
		start = tmp->next, ft_free_cmd(tmp);
		tmp = start;
	}
}
