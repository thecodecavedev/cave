#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 256

int find_in_path(char *command, char *envp[]);

int main(int argc, char *argv[], char *envp[]) {
  char *token;
  char *command = malloc(MAX_BUFFER_SIZE);
  char *command_pointer;

  printf("\nCAVE SHELL\n");
  while (1) {
    printf("enter command$ ");
    fgets(command, MAX_BUFFER_SIZE, stdin);
    if ((strlen(command) > 0) && (command[strlen(command) - 1] == '\n')) {
      command[strlen(command) - 1] = '\0';
    }

    // Tokenize the input
    // printf("%i", *command_pointer);
    token = strtok(command, " ");
    command_pointer = &token[0];
    printf("\n%s\n", command_pointer);
    find_in_path(command_pointer, envp);
    while (token != NULL) {
      printf("token: %s\n", token);
      token = strtok(NULL, " ");
    }
    // printf("run command\n");
  }
  free(command);
  return 0;
}

int find_in_path(char *command, char *envp[]) {
  char *_path;
  for (int i = 0; envp[i] != NULL; i++) {
    if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' &&
        envp[i][3] == 'H') {
      _path = envp[i];
    }
  }
  if (strlen(_path) == 0) {
    perror("cave shell path error");
    return 1;
  } else {
    printf("\n%s", _path);
    return 0;
  }

  // TODO: look for the command
}
