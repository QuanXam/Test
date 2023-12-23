#include <stdio.h> 
#include <unistd.h> 
#include <signal.h> 

void catch_int( int sig_num )
{
	signal( SIGINT, catch_int );
	printf( "Do not press Ctrl+C\n" );
}
int main()
{
	int count = 0;
	signal( SIGINT, catch_int ); 
	while ( 1 )
	{
		printf( "Counting ... %d\n", count++ );
		sleep( 1 );
	}
}
