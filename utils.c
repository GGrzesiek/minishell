
#include "minishell.h"

t_cmd *init_single_cmd(t_shell *shell, char *line)
{
    char **args;
    t_cmd *new;

    args = ft_split(line, ' ');
    new = (t_cmd *) malloc(sizeof(t_cmd));
    if(!args || !new)
      end(shell, "single cmd init malloc error\n");
    new->args=args;
    return (new);
}