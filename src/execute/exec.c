#include "minishell.h"

static int	is_built_in(char *cmd, t_builtin *built_in)
{
	int	i;

	i = 0;
	while (i < NUM_OF_BUILTIN)
	{
		if (!ft_strcmp(cmd, built_in[i].name))
			return (0);
		i++;
	}
	return (1);
}

static void	create_pipe(int *fdout, int *fdin)
{
	int fdpipe[2];

	pipe(fdpipe);
	*fdout = fdpipe[1];
	*fdin = fdpipe[0];
}

static void	redirect_io(t_shell *shell, int i, int *fdin, int *fdout)
{
	if (shell->group[i].in_fd)
		*fdin = shell->group[i].in_fd; /* already opened in_fd */
	dup2(*fdin, 0); /* redirect input */
	close (*fdin);
	if (i == shell->group_num - 1) /* last group */
	{
		/* check if there is a input redirection */
		if (!shell->out_fd)
			*fdout = dup(shell->std_out);
		else
			*fdout = shell->out_fd; /* already opened outfile */
	} else
		create_pipe(fdout, fdin); /* not last group */
	dup2(*fdout, 1); /* redirect output */
	close(*fdout);
}

static void	restore_io_defaults(t_shell *shell)
{
	dup2(shell->std_in, 0);
	dup2(shell->std_out, 1);
	close(shell->std_in);
	close(shell->std_out);
}

void	execute(t_shell *shell)
{
	int	fdin;
	int	fdout;
	int	i;

	i = 0;
	/* dup input fd if there is a redirection */
	if (!shell->group[0].in_fd)
		fdin = dup(shell->std_in);
	while (i < shell->group_num) {
		redirect_io(shell, i, &fdin, &fdout);
		if (!is_built_in(shell->group[i].cmd[0], shell->builtin))
			exec_builtin(shell, shell->group[i].cmd);
		else
			exec_bin(shell, shell->group[i].cmd);
		i++;
	}
	restore_io_defaults(shell);
}
