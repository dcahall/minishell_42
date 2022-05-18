/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <dcahall@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:09:15 by cvine             #+#    #+#             */
/*   Updated: 2022/05/18 16:43:36 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
updates working directory value in local envp
of the specified variable "var"
*/

static void	update_wd_value(t_list *envp, char *var)
{
	t_list	*pwd;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	pwd = get_envp(envp, var);
	if (!pwd)
	{
		ft_putstr_fd("pwd is NULL", 1);
		return ;
	}
	free(pwd->content);
	pwd->content = ft_strdup(cwd);
}

/* changes directory into a specified path */

static void	change_to_path(const char *path, t_list *envp)
{
	update_wd_value(envp, "OLDPWD=");
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(path);
		g_exit_status = EXIT_FAILURE;
	}
}

/*
Changes directory into a specified path.
For special chars indicating home or oldpwd it's checking wether they are set
*/

static void	change_dir(const char *path, t_list *envp, char *errmsg)
{
	if (!path)
	{
		error_occured("cd", errmsg);
		g_exit_status = EXIT_FAILURE;
		return ;
	}
	change_to_path(path, envp);
}

void	cd(char **cmd, t_list **envp)
{
	char	*path;

	g_exit_status = EXIT_SUCCESS;
	if (!cmd[1] || !ft_strcmp(cmd[1], "~") || !ft_strcmp(cmd[1], "--"))
		change_dir(get_envp_value(*envp, "HOME="), *envp, "HOME not set");
	else if (!ft_strncmp(cmd[1], "-", 1))
	{
		path = get_envp_value(*envp, "OLDPWD=");
		change_dir(path, *envp, "OLDPWD not set");
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
		change_to_path(cmd[1], *envp);
	update_wd_value(*envp, "PWD=");
}
