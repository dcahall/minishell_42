#include "minishell.h"

void	env(char **cmd, t_list **env_head)
{
	t_list	*head;

	(void)cmd;
	head = *env_head;
	while (env_head && head->content)
	{
		printf("%s%s\n", head->key, head->content);
		head = head->next;
	}
}
