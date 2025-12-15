# TODO

- Makefile & Libft / Other projects include

- Learn functions

// we know
printf, malloc, free, write, open, read, close, 
kill, exit,

// pipex
access, fork, execve, dup, dup2, pipe,

// minitalk
wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, 

// command history
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,

// directory management
getcwd, chdir, 

// file management
stat, lstat, fstat, unlink, opendir, readdir, closedir, 

// error management 
strerror, perror, 

// session management
isatty, ttyname, ttyslot, ioctl, 
getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

- Command Execution
- Environment variables
- Directory management

# Faza 1: Szkielet (Wspólnie - 1-2 dni)
[v] Stworzenie repozytorium, Makefile i włączenie Libft.
[v] Prosta pętla while(1) z readline.
[v] Zdefiniowanie struktur danych w .h.
[v] Obsługa sygnałów w pętli głównej (pusta obsługa, byle nie crashowało).

# Faza 2: Podstawy (Praca równoległa - 3-5 dni)
[V] Osoba A: Pisze tokenizer, który dzieli input po spacjach, ale ignoruje spacje w cudzysłowach.
[v] Osoba B: Pisze prosty executor, który potrafi uruchomić jedną komendę (bez pipe'ów), np. /bin/ls. Implementuje szukanie w PATH.
[ ] Osoba A: Pisze tokenizer, który dzieli input po spacjach, ale ignoruje spacje w cudzysłowach.
[v] Osoba B: Pisze prosty executor, który potrafi uruchomić jedną komendę (bez pipe'ów), np. /bin/ls. Implementuje szukanie w PATH.

# Faza 3: Integracja Logiki (Praca równoległa - 5-7 dni)
[ ] Osoba A: Implementuje obsługę $? i zmiennych środowiskowych ($HOME itp.). 
[v] Dodaje logikę export i unset.
[ ] Osoba B: Implementuje przekierowania proste (<, >). 
[v] Implementuje cd (zmienia katalog roboczy procesu) i pwd.

# Faza 4: "The Heavy Lifting" (Najtrudniejszy etap - 5-7 dni)
[ ] Osoba A: Dopracowuje parser pod kątem dziwnych przypadków (np. echo "sdfsdf"'$USER' > plik). Przygotowuje listę komend dla potoków (linked list of commands).
[ ] Osoba B: Implementuje Pipes (|). Implementuje heredoc (<<).

# Faza 5: Czyszczenie i Edge Cases (Wspólnie - 3-4 dni)
[ ] Memory Leaks: valgrind --leak-check=full. Pamiętajcie, że readline może cieknąć (jest to dozwolone), ale wasz kod nie może.
[v] Sygnały w procesach potomnych: Ctrl-C wewnątrz cat (blocking command) działa inaczej niż w prompcie. Tutaj przyda się ta jedna zmienna globalna.
[ ] Testy: Porównujcie swoje wyniki z bash (nie zsh!). Sprawdźcie dziwne komendy, np. cat | cat | ls.

# English Details
- [v] Display a prompt when waiting for a new command.
- [v] Have a working history.
- [v] Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
- [v] Use at most one global variable to indicate a received signal. Consider the
implications: this approach ensures that your signal handler will not access your
main data structures.

- [ ] Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
- [ ] Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
- [ ] Implement the following redirections:
◦ < should redirect input.
◦ > should redirect output.
◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
◦ >> should redirect output in append mode.
- [ ] Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
- [ ] Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
- [ ] Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
- [v] Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash. In interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
- [v] Your shell must implement the following built-in commands:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
