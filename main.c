
#include "minishell.h"

volatile int	g_SHLVL = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char *line;

	(void) argc;
	(void) argv;
	init_shell(&shell, envp);
	setup_signals();
	while (1)
	{
		line = readline("mini(s)hell> ");

		if (!line) // Ctrl+D
			end(&shell, NULL);

		if (*line)
		{
			add_history(line);

    if(!line) // Ctrl+D
      end(&shell, NULL);

    if(*line)
    {
      add_history(line);

      // t_cmd *cmd = init_single_cmd(&shell, line);
      t_token *tokens = tokenizer(line);

      t_cmd *cmds = parse_tokens(tokens);

      // t_token *temp = tokens;
      // t_cmd *curr_cmd = cmds;
      // int cmd_idx = 1;
  
      execute_cmd_chain(&shell, cmds);
      /* while (curr_cmd)
      {
        printf("Komenda %d \n",cmd_idx++);
        if(curr_cmd->args)
        {
          for (int i =0; curr_cmd->args[i]; i++)
            printf("Arg[%d]: %s\n",i , curr_cmd->args[i]);
        }

        t_redir *r = curr_cmd->redirs;
        while(r)
        {
          printf("redir: type=%d, file=%s\n",r->type,r->file);
          r = r->next;
        }
         curr_cmd = curr_cmd->next; */
        // printf("Token: Type=%d, Value=[%s]\n", temp->type, temp->value);
        // temp = temp->next;
      // }
      // execute_command(&shell, cmd);
      // free_split(cmd->args);
      // free(cmd);
      // free_cmds(cmds);
      free_tokens(tokens);
      free(line);
      }
    }
  }
}