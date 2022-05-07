/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:04:03 by cvine             #+#    #+#             */
/*   Updated: 2022/05/07 11:04:24 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_error(char *cmd)
{
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static char	*path_to_bin(t_list *envp, char **cmd)
{
	char	**all_paths;
	char	*path;

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
	cmd_error(*cmd);
	return (NULL);
}

void	exec_bin(t_shell *shell, char **cmd)
{
	int		pid;
	char	*bin_path;

	bin_path = path_to_bin(shell->env_lst, cmd);
	pid = fork();
	if (!pid) {
		execve(bin_path, cmd, shell->env_str);
		perror("execve issue");
		exit(1);
	}
}
