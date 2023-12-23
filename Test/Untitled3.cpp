// pipe_pipe.c
#include <stdio.h>
#include <unistd.h>
#include <ctype.h> 

void user_handler(int input_pipe[], int output_pipe[])
{
	char c;
	int rc; 
	close(input_pipe[1]); 
	close(output_pipe[0]);

	while((c = getchar())>0)
	{
		rc = write(output_pipe[1], &c, 1);
		if(rc == -1) 
		{
			perror("user_handler: pipe write error");
			close(input_pipe[0]);
			close(output_pipe[1]);
			exit(1);
		}
		rc=read(input_pipe[0], &c, 1);
		if(rc <= 0)
		{
			perror("user_handler: read error");
			close(input_pipe[0]);
			close(output_pipe[1]);
			exit(1);
		}
		putchar(c);
	}
	
	close(input_pipe[0]);
	close(output_pipe[1]);
	exit(0);
}
void translator( int input_pipe[], int output_pipe[])
{
	char c;
	int rc; 
	close(input_pipe[1]);
	close(output_pipe[0]);
	while(read(input_pipe[0], &c, 1)>0)
	{
		if( isascii(c) && islower(c))
			c = toupper(c);
		rc = write(output_pipe[1], &c, 1);
		if(rc == -1) 
		{
			perror("Translator: write");
			close(input_pipe[0]);
			close(output_pipe[1]);
			exit(1);
		}
	}
	
	close(input_pipe[0]);
	close(output_pipe[1]);
	exit(0);
}

int main()
{
	int user_to_translator[2];
	int translator_to_user[2];
	int pid; 
	int rc; 

	rc = pipe(user_to_translator);
	if(rc == -1)
	{
		perror("main: pipe user_to_translator error");
		exit(1);
	}

	rc=pipe(translator_to_user);
	if(rc == -1)
	{
		perror("main: pipe translator_to_user error");
		exit(1);
	}
	pid = fork();
	switch(pid)
	{
		case -1: 
			perror("main: fork error");
			exit(1);
		case 0: 
			translator(user_to_translator,translator_to_user);
		default:
			user_handler(translator_to_user,user_to_translator);
	}

	return 0;
}
