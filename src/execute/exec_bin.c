/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvine <cvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:04:03 by cvine             #+#    #+#             */
/*   Updated: 2022/05/16 16:18:14 by cvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	memfree(char *tmp, char *path, char **env_paths)
{
	int	i;

	i = 0;
	free(path);
	free(tmp);
	if (!env_paths)
		return ;
	while (env_paths[i])
		free(env_paths[i++]);
	free(env_paths);
}

static char	*path_to_bin(t_list *envp, char **cmd)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**env_paths;

	i = 0;
	if (ft_strchr(cmd[0], '/') && !access(cmd[0], F_OK | X_OK))
			return (cmd[0]);
	env_paths = ft_split(get_envp_value(envp, "PATH="), ':');
	while (env_paths[i])
	{
		tmp = ft_strjoin(env_paths[i], "/");
		path = ft_strjoin(tmp, *cmd);
		if (!access(path, F_OK | X_OK))
			return (path);
		memfree(tmp, path, NULL);
		i++;
	}
	memfree(NULL, NULL, env_paths);
	error_occured(*cmd, CMD_NOT_FOUND);
	return (NULL);
}

void	exec_bin(t_shell *shell, char **cmd)
{
	int		pid;
	int		status;
	char	*bin_path;

	g_exit_status = 0;
	bin_path = path_to_bin(shell->env_lst, cmd);
	if (!bin_path)
		return ;
	pid = fork();
	if (!pid)
	{
		execve(bin_path, cmd, shell->env_str);
		error_occured(*cmd, strerror(errno));
		return ;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
