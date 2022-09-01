#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
* main - simple shell
* @argc: argument count
* @argv: argument vector
* @envp: environment variable
* Return: 0 on success, 1 on failure
*/

int main(int argc, char *argv[], char *envp[])
{
	pid_t pid;
	int n = 0;
	size_t m = 1;
	char *buff = NULL;
	char *arg[25];

	while (argc != 0 && argv != NULL)
	{
		pid = fork();

		if (pid == -1)
		{
			perror("Error");
			return (1);
		}
		else if (pid == 0)
		{
			printf("Shell ~ ");
			getline(&buff, &m, stdin);
			arg[n] = strtok(buff, " ");

			while (arg[n] != NULL)
				arg[++n] = strtok(NULL, " ");

			n--;
			arg[n] = strtok(arg[n], "\n");

			if (execve(arg[0], arg, envp) == -1)
				perror("Error");
		}
		else
			wait(NULL);
	}

	return (0);
}
