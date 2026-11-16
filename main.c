#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_BUFFER_SIZE 256

int find_in_path(char *command, char *args[], char *envp[]);

int main(int argc, char *argv[], char *envp[]) {
  char *token;
  char *command = malloc(MAX_BUFFER_SIZE);
  char *command_pointer;
  char *command_args[60];

  printf("\nCAVE SHELL\n");
  while (1) {
    printf("$ ");
    fgets(command, MAX_BUFFER_SIZE, stdin);
    if ((strlen(command) > 0) && (command[strlen(command) - 1] == '\n')) {
      command[strlen(command) - 1] = '\0';
    }

    // Tokenize the input
    token = strtok(command, " ");
    command_pointer = &token[0];
    int count = 0;
    while (token != NULL) {
      command_args[count] = token;
      count++;

      token = strtok(NULL, " ");
    }
    command_args[count] = NULL;
    find_in_path(command_pointer, command_args, envp);
  }
  free(command);
  return 0;
}

int find_in_path(char *command, char *args[], char *envp[]) {
  char *_path;
  char *directory;
  int not_found = 1;
  _path = getenv("PATH");

  if (strlen(_path) == 0) {
    perror("cave shell path error");
    return 1;
  } else {
    char *temp_path;
    memcpy(temp_path, _path, strlen(_path));
    directory = strtok(temp_path, ":");
    char temp_directory[PATH_MAX];

    while (directory != NULL) {

      snprintf(temp_directory, sizeof(temp_directory), "%s/%s", directory,
               command);

      if (access(temp_directory, X_OK) == 0) {
        // Run the process
        not_found = 0;
        int pid = fork();
        if (pid == 0) {
          // child process
          execv(temp_directory, args);

          perror("cave shell progam execute error");
          exit(1);

          // return 0;
        }
        if (pid > 1) {
          // parent process
          waitpid(pid, NULL, 0);
        }
        return 0;
      }

      directory = strtok(NULL, ":");
    }
    if (not_found == 1) {
      perror("cave");
    }
    return 0;
  }
}
