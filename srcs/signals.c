#include "head_minishell.h"

/*
**	@brief	for ctrl+C in main	
*/
static void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_stat = 1;
}

/*
**	@brief	for ctrl+C and ctrl + \ in 'ft_signal_run_cmd'
*/
void	ft_signal_pipe(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_IGN);
}

/*
**	@brief	signal handlers in main state
*/
void	ft_signal(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, SIG_IGN);
}

/*
**	@brief	signal handlers in 'ft_run_cmd'
*/
void	ft_signal_cmd(void)
{
	signal(SIGINT, ft_signal_pipe);
	signal(SIGQUIT, ft_signal_pipe);
}
