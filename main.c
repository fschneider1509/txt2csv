/*includes*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void print_usage( void )
{
	fprintf( stdout, "Usage: \n" );
	fprintf( stdout, "\ttxt2csv </path/to/txt/file>\n" );
}

void print_msg( char *pmsg, char *padd, int ptype )
{
	switch( ptype )
	{
	case 1:
		fprintf( stdout, "Info: %s %s\n", pmsg, padd );
		break;
	case 2:
		fprintf( stderr, "Error: %s %s\n", pmsg, padd );
		break;
	default:
		fprintf( stdout, "Message: %s %s\n", pmsg, padd );
		break;
	}
}

char *get_csv_file_name( char *psrc )
{
	/*variables*/
	char *dot;
	char *filename;
	char *save;
	size_t srclen;

	/*get length of filename*/
	srclen = strlen( psrc );

	/*allocate memory for the filename*/
	filename = malloc( sizeof( char ) * srclen + 1 );

	if( filename != NULL )
	{
		/*get last dot position*/
		dot = strrchr( psrc, '.' );

		/*save first address of new filename*/
		save = filename;

		/*copy string to filetype*/
		while( psrc != dot )
		{
			*filename++ = *psrc++;

		}

		/*append .csv*/
		*filename++ = '.';
		*filename++ = 'c';
		*filename++ = 's';
		*filename++ = 'v';
		*filename++ = '\0';

		return save;
	}
	else
		return NULL;

}

int write_csv( FILE *input, FILE *output )
{
	/*variables*/
	int c = 0;

	c = fgetc( input );

	while( c != EOF )
	{
		fputc( (int)c, output );
		c = fgetc( input );

		/*replace space by semicolon*/
		if( c == ' ' )
			c = ';';
	};

	return 0;
}

int main( int argc, char *argv[] )
{
	/*variables*/
	FILE *input;
	FILE *output;
	char *strout;

	if( argc != 2 )
	{
		print_usage();
		return -1;
	}

	/*create new filename*/
	strout = get_csv_file_name( argv[1] );

	/*open/create files*/
	input = fopen( argv[1], "r" );
	output = fopen( strout, "w+" );

	if( input != NULL && output != NULL )
	{
		write_csv( input, output );

		print_msg( "csv file was written successfully:", strout, 1 );

		/*free new path*/
		free( strout );
	}
	else
	{
		print_msg( "File could not be opened:", argv[1], 2 );
		print_msg( "File could not be created:", strout, 2 );

		/*free new filename*/
		free( strout );

		return -1;
	}

	return 0;
}
