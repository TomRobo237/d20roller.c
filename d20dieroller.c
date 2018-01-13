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
int multidieroller(int dice, int sides);
int highroll(int dice, int sides);
int numbercheck(char * check);
void helpmenu();

int main(int argc, char **argv) {
	int sides = 20, dice = 1, roll, c, option_index = 0; 
	int high_flag = 0, plus = 0, add_total = 0;
	/* Default assumptions: 1 die, 20 sided, plus 0.
	 * Roll is to store value returned from roll functions.
	 * c is used to process getopt_long	 */
	while  (1){ //processing arguments
		static struct option long_options[] =
			{
				{"side", required_argument, 0, 's'},
				{"plus", required_argument, 0, 'p'},
				{"dice", required_argument, 0, 'd'},
				{"high", no_argument, 0, 'h'},
				{"help", no_argument,0, '?'},
				{0,0,0,0}
			};
		c = getopt_long( argc, argv, "s:d:p:h?", long_options, &option_index);
		if ( c == -1 )
			break;
		switch (c)
			{
				case 's':
					if (numbercheck(optarg) == 1)
						{
							fprintf( stderr , "%s is not a number we can roll!\n", optarg);
							exit(EXIT_FAILURE);
						}
					else
						{
							sides = atoi(optarg);
							break;
						};
				case 'd':
					if (numbercheck(optarg) == 1)
						{
							fprintf( stderr , "%s is not a number of dice we can roll!\n", optarg);
							exit(EXIT_FAILURE);
						}
					else
						{
							dice = atoi(optarg);
							break;
						}
				case 'p':
					if (numbercheck(optarg) == 1)
						{
							fprintf(stderr , "%s is not a number we can add!", optarg);
							exit(EXIT_FAILURE);
						}
					else
						{
							plus = atoi(optarg);
							break;
						}
				case 'h':
						high_flag = 1;
						break;
				case '?':
						helpmenu();
						break;
					}
		}				
	srand(time(NULL));
	if ( dice > 1 && high_flag == 1 )
		{
			roll = highroll( dice, sides );
		}
	else if ( dice > 1 )
		{
			roll = multidieroller( dice, sides );
		}
	else
		{
			roll = (dieroller(sides));
			printf("Rolled d%d: %d\n", sides, roll);
		};
	if ( plus > 0 ) {
		add_total = roll + plus;
		printf("Rolled a %dd%d+%d:%d.\nTotal: %d\n", dice, sides, plus, roll, add_total);
	} 
	return 0;
}

int dieroller(int sides) {
	int rolled = ((rand() % sides) + 1 );
	return rolled;
}

int multidieroller(int dice, int sides) {
	int rolled, totalrolled = 0, i;
	printf("Rolling %dd%d:\n", dice, sides);
	for ( i = 1 ; i <= dice ; i++)
		{
			printf("Rolling die %d:%d\n", i , 
			rolled = ((rand() % sides) + 1 ));
			totalrolled = rolled + totalrolled; 
		}
		printf("Total roll:%d\n", totalrolled);
		return totalrolled;
}

int highroll( int dice, int sides){
	int rolled, highestroll = 0, i;
	printf("Rolling %dd%d and giving higest roll:\n", dice, sides);
	for ( i = 1 ; i <= dice ; i++)
		{
			printf("Rolling die %d:%d\n", i , 
			rolled = ((rand() % sides) + 1 ));
			if ( rolled > highestroll ) 
				{
					highestroll = rolled; 
				}
		}
		printf("Highest Roll: %d\n", highestroll);
		return highestroll;
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

void helpmenu() {
	printf("\
USAGE: d20dieroller [OPTIONS]...\n\n\
Possible options:\n\t\
--side or -s: number of sides of the dice\n\t\
--dice or -d: number of dice to roll\n\t\
--high or -h: takes the highest die rolled\n\t\
--plus or -p: adds number at end of roll\n\t\
--help or -?: prints this help menu\n");
	exit(EXIT_SUCCESS);
}
