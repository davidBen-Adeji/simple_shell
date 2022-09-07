#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

char *create_buff(void);
void _execute(char **arg, char **env);
char *_strcpy(char *dest, char *src);
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
	int n = 0, k;
	char *buff = NULL, *dup;
	char *arg[25];
	char str[50];

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
			buff = create_buff();
			dup = _strcpy(str, buff);
			free(buff);
			arg[n] = strtok(dup, " ");

			while (arg[n] != NULL)
				arg[++n] = strtok(NULL, " ");

			n--;
			arg[n] = strtok(arg[n], "\n");

			_execute(arg, envp);
		}
		else
			wait(&k);
	}

	return (0);
}

/**
* create_buff - function to get user input
* Return: allocated memory
*/

char *create_buff(void)
{
	size_t m = 10;
	char *buff = NULL;

	getline(&buff, &m, stdin);

	if (buff == NULL)
	{
		perror("Error:");
		exit(EXIT_FAILURE);
	}

	return (buff);
}

/**
* _strcpy - function to copy a string
* @dest: data type to be copied into
* @src: string to be copied
* Return: the copied string
*/

char *_strcpy(char *dest, char *src)
{
	char *temp = dest;

	while (*src)
		*dest++ = *src++;

	return (temp);
}

/**
* _execute - function that executes a file
* @arg: argument
* @env: environment
* Return:nothing
*/

void _execute(char **arg, char **env)
{
	if (execve(arg[0], arg, env) == -1)
		perror("Error");
}
