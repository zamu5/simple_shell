#include "holberton.h"
/**
 * main - execute a simple shell
 * Return: nothing
 */
int main(void)
{
	char *buffer = NULL, **buff = NULL, *path, *cpath;
	ssize_t d = 0;
	size_t bufsize = 1024;
	int status, s = 5, cont = 0, e;

	while (1)
	{
		s = 5, cont++, path = get_env("PATH="), cpath = cpstring(path);
		signal(SIGINT, sigintHandler), prompt();
		buffer = malloc(bufsize * sizeof(char));
		if (buffer == NULL)
			free(buffer), ret();
		d = getline1(&buffer, &bufsize, stdin);
		if (d == -1 || d == EOF)
			exit(0);
		spaces(buffer), buffer = compare_path(buffer, cpath);
		if (buffer[0] != '\n' && buffer[0] != '\0')
		{
			buff = getargs(buffer);
			if (buff == NULL)
				free(buffer), freeAll(buff), ret();
			if (buff[0] != NULL)
				s = coincidence(buff, buffer);
		}
		if (s == -1 && buff[0] != NULL && fork() == 0)
		{
			status = execve(buff[0], buff, environ);
			if (status == -1 && buff[0] != NULL)
				writeexe(buff, cont);
			freeAll(buff), free(buffer), ret();
		}
		else
			wait(&e), extstatus(&e);
		check(s, buff, buffer);
	}
	return (0);
}
/**
 * ret - return function
 *return: nothing
 */
void ret(void)
{
	exit(0);
}
/**
 * extstatus - function
 * @p: status error
 * Return: status
 */
int extstatus(int *p)
{
	static int status;

	if (p != NULL)
		status = *p;
	return (status);
}
/**
 * writeexe - function
 * @buff: buffer
 * @cont: cont
 *return: nothing
 */
void writeexe(char **buff, int cont)
{
	_puts2("hsh: ");
	_puts2(unatoi(cont));
	_puts2(" ");
	_puts2(buff[0]);
	_puts2(": not found");
	_puts2("\n");
}
/**
 * writes0 - function
 * @buff: buffer
 *return: nothing
 */
void writes0(char **buff)
{
	_puts2("hsh: cd: ");
	_puts2(buff[1]);
	_puts2(": No such file or directory");
	_puts2("\n");
}
