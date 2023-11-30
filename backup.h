/**#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define MAX_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

void mask(void);
char *readprompt(void);
char **parseline(char *line);
int _cd(char **args);
int _help(char **args);
int r_exit(char **args);
int ar_execpath(const char *op, char *const av[], char *const env[]);
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};


int (*builtin_func[]) (char **) = {
  &_cd,
  &_help,
  &r_exit
};

int _num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}
int _cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "error: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("chdir");
    }
  }
  return 1;
}
int _help(char **args)
{
  int i;
  printf("The following are built in:\n");

  for (i = 0; i < _num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("_help function executed.\n");

  return 1;
}
int r_exit(char **args)
{
  return 0;
}


int _launch(char **args)
{
  pid_t pid;
  int status;
  char *path = "/bin/ls";

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execve(path, args, NULL) == -1) {
      perror("Execve failed");

       exit(EXIT_FAILURE);
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
    exit(EXIT_FAILURE);
  } else {

    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
/*free(path);*/
  return 1;
}

int _exec(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < _num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  return _launch(args);
  }
void mask(void)
{
  char *prompt;
  char **args;
int status = 1;
while(status)
  {
    putchar('$');
    prompt = readprompt();
    args = parseline(prompt);
    status = _exec(args);
    free(prompt);
    for (int i = 0; args[i] != NULL; i++)
    {
free(args[i]);
    }
    free(args);
  }
}
char *readprompt(void)
{
char *command = NULL;
size_t buff = 0;
if (getline(&command, &buff, stdin)
  == -1)
{
if(feof(stdin))
{
exit(EXIT_SUCCESS);
}
else
{
perror("readline");
exit(EXIT_FAILURE);
}
}
return (command);
}

char **parseline(char *line) {
    int buff = TOK_BUFSIZE;
    char **args = (char **)malloc(buff * sizeof(char *));
    int i = 0;

    if (!args) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line, TOK_DELIM);

    while (token != NULL) {
        args[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));

        if (args[i] == NULL) {
            perror("Allocation error");
            exit(EXIT_FAILURE);
        }

        strcpy(args[i], token);
        i++;

        token = strtok(NULL, TOK_DELIM);
    }

    args[i] = NULL;

    return args;
}


int main (int argc, char **argv)
{
  mask();
  return (EXIT_SUCCESS);
}
