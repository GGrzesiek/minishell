
#include "minishell.h"

extern int g_SHLVL;

void handle_sigint(int sig)
{
	(void)sig;
  if(g_SHLVL == 0)
  {
    write(1,"\n",1);
    rl_on_new_line();
    rl_replace_line("",0);
    rl_redisplay();
  }
}

void handle_sigquit(int sig)
{
  (void) sig;
  if (g_SHLVL == 0)
  {
    rl_on_new_line();
    rl_replace_line("",1);
    rl_redisplay();
  }
}

void setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit); // 'Ctrl+\'
}