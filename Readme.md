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
- Signal Actions
- Built-ins

# Faza 1: Szkielet (Wspólnie - 1-2 dni)
[v] Stworzenie repozytorium, Makefile i włączenie Libft.
[v] Prosta pętla while(1) z readline.
[v] Zdefiniowanie struktur danych w .h.
[v] Obsługa sygnałów w pętli głównej (pusta obsługa, byle nie crashowało).

# Faza 2: Podstawy (Praca równoległa - 3-5 dni)
[ ] Osoba A: Pisze tokenizer, który dzieli input po spacjach, ale ignoruje spacje w cudzysłowach.
[v] Osoba B: Pisze prosty executor, który potrafi uruchomić jedną komendę (bez pipe'ów), np. /bin/ls. Implementuje szukanie w PATH.

# Faza 3: Integracja Logiki (Praca równoległa - 5-7 dni)
[ ] Osoba A: Implementuje obsługę $? i zmiennych środowiskowych ($HOME itp.). Dodaje logikę export i unset.
[ ] Osoba B: Implementuje przekierowania proste (<, >). Implementuje cd (zmienia katalog roboczy procesu) i pwd.

# Faza 4: "The Heavy Lifting" (Najtrudniejszy etap - 5-7 dni)
[ ] Osoba A: Dopracowuje parser pod kątem dziwnych przypadków (np. echo "sdfsdf"'$USER' > plik). Przygotowuje listę komend dla potoków (linked list of commands).
[ ] Osoba B: Implementuje Pipes (|). To wymaga pętli forkowania, gdzie wyjście jednego dziecka staje się wejściem drugiego. Musisz pilnować zamykania FD, żeby nie zawiesić programu (deadlock). Implementuje heredoc (<<).

# Faza 5: Czyszczenie i Edge Cases (Wspólnie - 3-4 dni)
[ ] Memory Leaks: valgrind --leak-check=full. Pamiętajcie, że readline może cieknąć (jest to dozwolone), ale wasz kod nie może.
[ ] Sygnały w procesach potomnych: Ctrl-C wewnątrz cat (blocking command) działa inaczej niż w prompcie. Tutaj przyda się ta jedna zmienna globalna.
[ ] Testy: Porównujcie swoje wyniki z bash (nie zsh!). Sprawdźcie dziwne komendy, np. cat | cat | ls.

