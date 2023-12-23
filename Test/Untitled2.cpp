// vi pipe.c
#include <stdio.h>
#include <unistd.h>

void do_child( int data_pipes[] )
{
	int c; 
	int rc; 
	close( data_pipes[1] );
	while ( ( rc = read( data_pipes[0], &c, 1 ) ) > 0 )
	{
		putchar( c );
	}
	exit(0);
}

void do_parent(int data_pipes[])
{
	int c; 
	int rc; 
	close( data_pipes[0] );
	while ( ( c = getchar() ) > 0 )
	{
		rc = write( data_pipes[1], &c, 1 );
		if ( rc == -1 )
		{
			perror( "Parent: pipe write error" );
			close( data_pipes[1] );
			exit( 1 );
		}
	}

	close(data_pipe[1]);
	exit(0);
}
int main()
{
	int data_pipe[2];
	int pid;
	int rc; 
	rc = pipe( data_pipes ); 
	if ( rc == -1 )
	{
		perror( "Error: pipe not created" );
		exit( 1 );
	}

	pid = fork();
	switch ( pid )
	{
		case -1: 
			perror( "Child process not create" );
			exit( 1 );
		case 0: 
			do_child( data_pipes );
		default: 
			do_parent( data_pipes );
	}
	
	return 0;
}
