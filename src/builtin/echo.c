#include "minishell.h"

void	echo(char **cmd, t_list **env_head)
{
	int	i;
	int n_flag;

	(void)env_head;
	i = 1;
	n_flag = 1;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		i++;
		n_flag = 0;
	}
	while (cmd[i]) {
		ft_putstr_fd(cmd[i++], STDOUT_FILENO);
		if (cmd[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}