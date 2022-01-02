#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _schedule{
	int year;
	int month;
	int day;
	char name[9];
}SCHEDULE;

int leapyear(int year);
int PastCount(int year, int month, int yearday[]);
void INPUT(int* year, int* month, int* day, char* name);
void ResetArray(SCHEDULE* SDL);

//Month: Array that saves the name of month.
char Month[12][10]={"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", " November", "December"};

int main(void){
	printf("\n\n\n   ============= Second Project =============\n\n");
	printf("\t\t0. Print calendar\n\n\t\t1. Search schedule(name)\n\n");
	printf("\t\t2. Add schedule\n\n\t\t3.Edit schedule(year, month, day, name)\n\n");
	printf("\t\t4. Delete schedule(year, month, day, name)\n\n\t\t5. Exit");

	//@param	
	//N: The number to choose from the first page.
	//year: The year of the schedule you received.
	//month: The month of the schedule you received.
	//day: The day of the schedule you received.
	//week: To find the day of the week when the day begins.
	//sdl_n: Number of empty structure arrangements to store the received schedule.
	//name: The name of the schedule you received.
	//line: Save "===Second Project===".
	//SDL: Structure to receive and store schedules (10 array).
	//yearday[12]: Array that stores the maximum number of days of each month.
	//i: To repeat for for loop.
	//j: To repeat for loop in for loop.
	int N, year, month, day, week, sdl_n;
	char name[9], line[50];
	SCHEDULE *SDL;
	SDL=(SCHEDULE*)malloc(sizeof(SCHEDULE)*10);
	
	//The int member of the structure is initialized to 0 and the char member to "".
	for(int i=0;i<10;i++){
		ResetArray(SDL+i);
	}

	sprintf(line, "\n\n\n\n   ============= Second Project =============\n\n");

	//Repeat the entire iteration until you select 5.		
	while(1){
		printf("\n\n\n\nEnter your coice : ");
		scanf("%d", &N);

		//In choice 5, SDL dynamic allocation is released and the repetition statement is terminated.
		if(N==5){
			free(SDL);
			printf("exit\n");
			return 0;
		}

		//In choice 0, enter year and month, output the calendar of the corresponding date, and return to the first page.
		else if(N==0){
			printf("%s", line);
			printf("\t\t0. Print calendar\n\n");

			printf("\t\tinput year : ");
			scanf("%d", &year);

			//If the value of year is between 1000 and 3000, month is input and a calendar of the corresponding date is output.
			//If the value of year goes against the condition, output an error message.
			if(1000<=year && year<3000){
				printf("\t\tinput month : ");
				scanf("%d", &month);
			
				printf("\n\n\n\n   =========================== %d %s ===========================\n\n", year, Month[month - 1]);
	
				int yearday[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
				//If the year received is a leap year, add 1 to the maximum number of days of yearday [1] corresponding to February.
				if(leapyear(year)==1)
					yearday[1]++;

				week = PastCount(year, month, yearday) % 7;
	
				printf("       Sun       Mon       Tue       Wed      Thur       Fri       Sat\n");
				
				//Fill the blanks on the calendar with 0 before the day 1 begins.
				for(int i=0;i<week;i++)
					printf("%10d", 0);
				
				//Fill in the column of the calendar by outputting numbers sequentially up to the maximum number of days of the month.
				//If there is a schedule on the corresponding date, print the name of the schedule instead of the number.
				for(int i=1;i<=yearday[month-1];i++){
					//Check all arrangements to see if a schedule in which year, month, and day all match for each date is stored in the structure SDL[10].
					for(int j=0;j<10;j++){
						if((SDL+j)->year==year && (SDL+j)->month==month && (SDL+j)->day==i){
							printf("%10s", SDL[j].name);
							break;
						}
						else if(j==9)
							printf("%10d", i);
					}
					//If the date reaches saturday, then the date is output from Sunday in the next row.
					//The first column of each line is Sunday with week=0, and the last column is Saturday with week=6.
					if(week == 6){
						week = -1;
						printf("\n\n\n\n");
					}
					week++;
				}
			}
			else
				printf("\n\n\t\tError: Enter year between 1000 and 2999.\n");
		}

		//The name of the schedule to be found in choice 1 is input.
		else if(N==1){
                        printf("%s", line);
			printf("\t\t1. Search schedule\n\n");

			printf("\t\tSearch by name : ");
			scanf("%s", name);

			//All arrangements of the structure SDL [10] are checked, and when the received name matches the stored name, the corresponding date is output.
			//If you have checked up to the ninth array and there is no matching schedule name, output a message that there is no matching schedule name.
			//When the output is finished, the repeat statement is terminated.
			for(int i=0;i<10;i++){
				if(strcmp(name, SDL[i].name) == 0){
					printf("\n\n\n\t\tyear : %d\n", (SDL+i)->year);
					printf("\t\tmonth : %d\n", (SDL+i)->month);
					printf("\t\tday : %d\n", (SDL+i)->day);
					break;
				}
				else if(i==9 && strcmp(name, SDL[i].name) != 0){
					printf("\n\t\t'%s' does not exist\n", name);
					break;
				}
			}
		}

		//In choice 2, an input of a schedule date to be added and stored is received.
		else if(N==2){
                        printf("%s", line);
			printf("\t\t2. Add schedule\n\n");
			
			//Repeated statement to find the number of empty arrays to save the entered schedule.
			//When the empty index is found, the number of the index is stored in the variable sdl_n and the repetition statement is terminated.
			for(int i=0;i<10;i++){
				if((SDL+i)->year == 0){
					sdl_n = i;
					break;
				}
			}

			INPUT(&(SDL+sdl_n)->year, &(SDL+sdl_n)->month, &(SDL+sdl_n)->day, SDL[sdl_n].name);
			//If the input meets the conditions and succeeds in saving the schedule, output a success message.
			if((SDL+sdl_n)->year != 0){
				printf("\n\n\n\n\t\t%d-%d-%d\n", (SDL+sdl_n)->year, (SDL+sdl_n)->month, (SDL+sdl_n)->day);
				printf("\t\t%-10s successfully added\n", SDL[sdl_n].name);
			}
		}
			
		//Select a schedule saved in choice 3 and save it again with a new date and name.
		else if(N==3){
                        printf("%s", line);
			printf("\t\t3. Edit schedule\n\n");
			INPUT(&year, &month, &day, name);
			
			//If the received schedule is suitable for the condition(1000<=year<3000 / stren(char)<=9), the following is performed.
			if(year!=0){
				//If a schedule matching the input date and name is stored in one of the arrangements of the structure SDL,
				//If the conditions are not met, an error message is output according to the INPUT function.
				//If the received schedule meets the conditions, the received schedule is stored in the structure of the same array.
				//When editing is finished, the repetition statement is terminated.
				for(int i=0;i<10;i++){
					if((SDL+i)->year==year && (SDL+i)->month==month && (SDL+i)->day==day && strcmp(SDL[i].name, name) == 0){
						printf("%s", line);
						printf("\t\t3. Edit schedule\n\n");
						INPUT(&year, &month, &day, name);
						if(year!=0){
							(SDL+i)->year = year;
							(SDL+i)->month = month;
							(SDL+i)->day = day;
							strcpy(SDL[i].name, name);
						}	
						break;
					}
				}
			}
		}

		//Choice 4 receives a date and name that meets the conditions.
		//The arrangement of the structure SDL in which the corresponding schedule is stored is initialized to {0, 0, 0, ""}.
		else if(N==4){
                        printf("%s", line);
			printf("\t\t4. Delete schedule\n\n");

			INPUT(&year, &month, &day, name);
			
			//Check the existence of a schedule of the date and name input from the 0th array to the 9th array.
			//If the schedule exists, the structure of the array in which the schedule exists is initialized to {0, 0, 0, ""}.
			//When initialization is over, the repetition statement is terminated.
			if(year!=0){
				for(int i=0;i<10;i++){
					if((SDL+i)->year==year && (SDL+i)->month==month && (SDL+i)->day==day && strcmp(SDL[i].name, name) == 0){
						ResetArray(SDL+i);
						break;
					}
				}
			}
		}
	}
}

int leapyear(int year){
//This function determines whether a particular year is a leap year or not.
//@param
//year: A specific year to check if it's leap year
//@return
//If year is leap year, return 1 and if not, return 0.

	if(year%4==0 && year%100!=0 || year%400==0)
		return 1;
	else
		return 0;
}

int PastCount(int year, int month, int yearday[]){
//Sums all the dates before a specific year and month.
//@param
//year: A specific year that's the standard.
//month: A specific month that's the standard.
//yearday[]: Array to find the maximum dates of each month.
//@return
//This function returns the result of summing all dates before a specific year and month.

	int past = 365;
	for(int i=1;i<year;i++){
		if(leapyear(i)==1)
			past+=366;
		else
			past+=365;
	}

	for(int i=0;i<month-1;i++)
		past += yearday[i];
	return past;
}

void INPUT(int* year, int* month, int* day, char* name){
//This function receives parameters according to the conditions.
//If the input value does not meet the conditions, output an error message, initialize all parameters, and stop.
//@param
//*year: Pointer of year parameter to be input.
//*month: Pointer of month parameter to be input.
//*day: Pointer of day parameter to be input.
//*name: Pointer of name parameter to be input.
//yearday[12]: Array that stores the maximum number of days of each month.
//@return
//void.

	printf("\t\tinput year : ");
	scanf("%d", &(*year));
	if(*year<1000 || *year>=3000){
		printf("\n\n\t\tError: Enter year between 1000 and 2999.\n");
		*year = 0;
		return;
	}
	
	printf("\t\tinput month : ");
	scanf("%d", &(*month));
	if(*month<1 || *month>12){
		printf("\n\n\t\tError: Enter month between 1 and 12.\n");
		*year = 0;
		*month = 0;
		return;
	}

	int yearday[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	//If the year received is a leap year, add 1 to the maximum number of days of yearday [1] corresponding to February.
	if(*year%4==0 && *year%100!=0 || *year%400==0)
		yearday[1]++;

	printf("\t\tinput day : ");
	scanf("%d", &(*day));
	if(*day<1 || *day>yearday[*month - 1]){
		printf("\n\n\t\tError: %s %d exists until %dnd.\n", Month[*month - 1], *year, yearday[*month - 1]);
		*year = 0;
		*month = 0;
		*day = 0;
		return;
	}

	printf("\t\tname : ");
	scanf("%s", name);
	if(strlen(name)>9){
		printf("\n\n\t\tError: Name can be entered up to 9 characters.\n");
		*year = 0;
		*month = 0;
		*day = 0;
		name = "";
	}
	return;
}

void ResetArray(SCHEDULE* SDL){
//This function initializes the int member of the structure to 0 and the char member to "".
//@param
//*SDL: The structure to be reset.
//@return
//void.

	SDL->year = 0;
	SDL->month = 0;
	SDL->day = 0;
	strcpy(SDL->name, "");
	return;
}
