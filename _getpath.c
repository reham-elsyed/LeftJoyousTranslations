#include "main.h"

char *_strdup(const char *str)
{
  size_t i = 0;
  size_t len = 0;
  char *_str = NULL;

  while (str[i++])
    ;
  len += i;
  _str = malloc(sizeof(*_str) * (len + 1));
  i = 0;
  while (i <= len)
    {
      _str[i] = str[i];
      i++;
    }
  printf("strdup worked\n");
  return (_str);
}

int file_exist(const char *path)
{
  struct stat buffer;
  if (stat(path, &buffer) == 0)
    return (1);
  printf("file exist worked\n");
  return (0);
}

char *join_path(const char sep, const char *path1, const char *path2)
{
  size_t i = 0;
  size_t len = strlen(path1) + strlen(path2) + 1;
  char *joined = NULL;
  
  /*while (path1[i++] != '\0')
    ;
  len += i;
  i = 0;
  while (path2[i++] != '\0')
    ;
  len += i;
  len += 1;*/
  if (len > 0)
  {joined = malloc(sizeof(*joined) * (len + 1));/*free this malloc*/
   if (joined == NULL)
   {
     perror("malloc joined failed\n");
     exit(EXIT_FAILURE);
   }
 /**  joined = strcpy(joined, path1);
   joined = strcat(joined, sep);
   joined = strcat(joined, path2);*/
   strcpy(joined, path1); 
   joined[strlen(path1)] = sep;      
   strcpy(joined + strlen(path1) + 1, path2); 
}
  printf("joined worked\n");
  return (joined);
}
char *locate(const char *filename)
{
  char *path = _getenv("PATH");
  char *dir_path = NULL;
  char *file_path = NULL;

  if (path == NULL)
    return (NULL);
  
  if (file_exist(filename))
    printf("filename exist in licate first if statement\n");
    return (_strdup(filename));
  
  strtok(path, "=");
  dir_path = strtok(NULL, ":");
  while (dir_path != NULL)
    {
      file_path = join_path('/', dir_path, filename);

      if (file_exist(file_path))
      {
        free(path);
        printf("file path after using joined path\n");
        return (file_path);
      }
      free(file_path);
      file_path = NULL;
      dir_path = strtok(NULL,":");
    }
  free(path);
  return (NULL);
  
}


char *_getenv(const char *name)
{
  size_t i = 0, k;
  const char *env = NULL;
  while (environ[i] != NULL)
    {
      env = environ[i];
  k =0;
      while (env[k] == name[k] && env[k] != '=' && env[k] != '\0' &&  name[k] != '\0')
  k++;
    // Add the statements for the loop body here
  if (name[k] == '\0')
    printf("_getenve worke\n");
    return(_strdup(env));
  i++;
    }
      return NULL;
}
/**char *print(){
  size_t n_need = 0;
  char *cmd = NULL;
  size_t buff_size = 0;


  printf("Enter command");
   n_need = getline(&cmd, &buff_size, stdin);
   cmd[n_need -1] = '\0';
  return cmd;
}
int main (){
  char *cmd = NULL;
  char *args[] = {NULL,NULL};
 // size_t buff_size = 0;
//  size_t n_need = 0;
  char *cmd_path = NULL;
   cmd = print();
  while (1)
    {
      //printf("Enter command");
     // n_need = getline(&cmd, &buff_size, stdin);
     // cmd[n_need -1] = '\0';
     //cmd = print();
      if (strcmp(cmd, "exit"));
      break;
      cmd_path = locate(cmd);
      if (cmd_path)
      {
       
      args[0] = cmd_path;
     if (fork() ==0)
      
        execve(*args, args, NULL);
      
        else  wait(NULL);
    
    
    }
    else{
      dprintf(STDERR_FILENO, "%s : command not found\n", cmd);
    }}
  return (0);
}    */