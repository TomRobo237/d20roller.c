/* Thomas Miller
 * A C program to roll a d20
 * May add other dies / formulas
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int dieroller(int sides);
// int ac_calc(int armor, int sheild, int dex, int size_diff); May work on later
int numbercheck(char * check);

int main(int argc, char **argv) {
	int sides = 20, roll, c, option_index = 0; 
	/*default sides to 20 unless specified through -s or --sides flag
	 * c is used to process getopt_long, n is used to convert getopt arguments
	 * into int variables.
	 */
	while  (1){
		static struct option long_options[] =
			{
				{"sides", required_argument, 0, 's'},
				{0,0,0,0}
			};
		c = getopt_long( argc, argv, "s:", long_options, &option_index);
		if ( c == -1 )
			break;
		switch (c)
			{
				case 's':
					if (numbercheck(optarg) == 1)
						{
							fprintf ( stderr , "%s is not a number!\n", optarg);
							exit(EXIT_FAILURE);
						}
					else
						{
							sides = atoi(optarg);
							printf("DEBUG: Setting sides to %d\n", sides);
							break;
						};
			}
		}				
	srand( time(NULL));
	roll = (dieroller(sides));
	printf("Rolled d%d: %d\n", sides, roll);
	return 0;
}

int dieroller(int sides) {
	int rolled = ((rand() % sides) + 1 );
	return rolled;
}

int numbercheck(char * check) {
	int x = 0;
	int len = strlen(check);
	
	while (x < len) {
		if (!isdigit(*(check + x)))
		return 1;
		++x;
	}
	return 0;
}
