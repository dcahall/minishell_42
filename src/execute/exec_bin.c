/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:04:03 by cvine             #+#    #+#             */
/*   Updated: 2022/05/09 11:44:31 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_to_bin(t_list *envp, char **cmd)
{
	char	*path;
	char	**all_paths;

	all_paths = ft_split(get_envp_value(envp, "PATH="), ':');
	while (*all_paths)
	{
		path = ft_strjoin(*all_paths, "/");
		path = ft_strjoin(path, *cmd);
		if (!access(path, F_OK | X_OK))
			return (path);
		free(path);
		all_paths++;
	}
	error_occured(*cmd, CMD_NOT_FOUND);
	exit(EXIT_CMD_NOT_FOUND);
}

void	exec_bin(t_shell *shell, char **cmd)
{
	int		pid;
	int		status;
	char	*bin_path;

	bin_path = path_to_bin(shell->env_lst, cmd);
	pid = fork();
	if (!pid)
	{
		execve(bin_path, cmd, shell->env_str);
		error_occured(*cmd, strerror(errno));
		exit(EXIT_CMD_NOT_FOUND);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
