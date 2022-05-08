#include "minishell.h"

void	init_builtin(t_shell *shell)
{
	shell->builtin[0].name = "cd";
	shell->builtin[0].func_ptr = cd;
	shell->builtin[1].name = "pwd";
	shell->builtin[1].func_ptr = pwd;
	shell->builtin[2].name = "env";
	shell->builtin[2].func_ptr = env;
	shell->builtin[3].name = "echo";
	shell->builtin[3].func_ptr = echo;
	shell->builtin[4].name = "export";
	shell->builtin[4].func_ptr = export;
	shell->builtin[5].name = "exit";
	shell->builtin[5].func_ptr = ft_exit;
	shell->builtin[6].name = "unset";
	shell->builtin[6].func_ptr = unset;
}