#include "minishell.h"

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd *head;
	t_cmd *curr;
	t_token *tmp;

	head = NULL;
	curr = init_cmd();
	if (!curr)
		return (NULL);
	cmd_add_back(&head, curr);
	tmp = tokens;
	// TODO: Pelna obsluga "" oraz ''
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
		{
			curr = init_cmd();
			if (!curr)
				return (NULL);
			cmd_add_back(&head, curr);
		}
		else if (is_redir_token(tmp->type))
		{
			// TODO: obsluga przypadku gdy nie ma po redirze slowa
			if (tmp->next && tmp->next->type == TOKEN_WORD)
			{
				redir_add_back(&curr->redirs, new_redir(tmp->type,
						tmp->next->value));
				tmp = tmp->next;
			}
			else
				printf("syntax error");
		}
		else if (tmp->type == TOKEN_WORD)
		{
			add_arg(curr, tmp->value);
		}
		tmp = tmp->next;
	}
	return (head);
}