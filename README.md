# Minishell Research and Planning

## Repositories
* [Nice explanation of the project](https://github.com/maiadegraaf/minishell)
* [Evaluation Sheet](https://42evals.com/Cursus/minishellhttps://42evals.com/Cursus/minishell)
* [Walkthrough of the project + cool image at the end](https://github.com/migmanu/minishell?tab=readme-ov-file)

## Articles
* [Building mini bash (guy went for AST)](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
* [Very noice article with references - High level explanation](https://haglobah.github.io/Mastering-42/holy_graph/minishell.html)
* [Interesting collection of references](https://minishell.simple.ink/)
* [Nicee explanation of each of the allowed functions - use google translator](https://velog.io/@chez_bono/Minishell)
* [Bigger Picture](https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J)
* [Suspectedoceano collection of resources](https://suspectedoceano.notion.site/Cursus-97a5ef0ea22b47779a24de1299e53e9b)

## Important
* [List of edge cases](https://docs.google.com/spreadsheets/d/1TDwyd-S0WBAXehgkrKQtBJ6zquQ4p6k7JfE5g3jICNA/edit#gid=0)
* [List of more edge cases, but not to worry too much](https://docs.google.com/spreadsheets/u/0/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/htmlview?lsrp=1#gid=0)

## About git for who wants to learn more
[Git for beginners](https://learngitbranching.js.org/)

## Some random intereseting links
* [Noice simple version of shell](https://brennan.io/2015/01/16/write-a-shell-in-c/)
* [Another simple version of shell](https://www.geeksforgeeks.org/making-linux-shell-c/)
* [The pdf in 42docs](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

## Some practice Studies
* [AST in typescript](./ast-example-js/)
* [AST in C](./ast-example-c/)

## PLANNING AND DIVISION OF TASKS

### Requirements
* [x] Mandatory part
* [ ] Bonus part (will do?)

### 4 Tasks
* [ ] Lexer
* [ ] Parser
* [ ] Executor
* [ ] Builtins commands

### Interfaces 
Lexer will return a list of tokens
the lexer return will look like this:
```c
typedef enum e_token_type
{
    WORD,
    PIPE,
    SEMICOLON,
    GREAT,
    DGREAT,
    LESS,
    DLESS,
    NEWLINE,
    AND,
    OR,
    EOF
} t_token_type;

typedef struct s_token
{
    // first two are for debugging porpuses
    int         input_start_idx;
    int         current_idx;
    char        *value;
    t_token_type type;
} t_token;

typedef struct s_lexer
{
    t_list *tokens;
    int     size;
} t_lexer;

/** 
  * input will be the entry string from the prompt
  * return will have a list of tokens that represent the input
  */
t_lexer *lexer(char *input);
```

Parser will return a list of commands
the parser return will look like this:
```c
typedef struct s_command
{
    char    *command;
    char    **args;
    char    *heredoc_file_name;
    t_token *fd;
} t_command;

typedef struct s_commands
{
    t_list *commands;
} t_commands;
```

Executor will execute the commands

<br>

Builtins will be the commands that are built in the shell
