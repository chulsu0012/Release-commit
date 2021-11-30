#include <stdio.h>
#include <stdlib.h>

int FeeCalculate(int day, int hour, int minute);
void Switch(int* a, int* b);

int main(void) {
    FILE* ifp; FILE* ofp; //File pointer variable

    //An index with a value of { 0 } is considered empty.
    int res; //fscanf return value
    int Parking[50][4] = { 0 }; //first index:number plate / others:time stamp(day/hour/minute)
    int Money[50][2]; //first index:number plate / second index:total amount of fee

    //file open
    ifp = fopen("a.txt", "r");
    if (ifp == NULL)
        return 1;

    ofp = fopen("b.txt", "w");
    if (ifp == NULL)
        return 1;

    int NumberPlate, day, hour, minute;
    int NumberofCar = 0; //The number of cars used the parking lot.(Count when it left).
    while (1) {
        //Receive the car's number plate and time stamp in one line.
        res = fscanf(ifp, "%d %d:%d:%d", &NumberPlate, &day, &hour, &minute);
        if (res == EOF) break;

        int CarOut = 0; //Whether there is a matching number plate in Parking[][0].(Whether the car is going in to the parking lot or going out.) > 1==true / 0==false

        //Find out if Parking[][0] has a number plate that matches the value of the numberplate variable you just received.
        for (int i = 0; i < 50; i++) {
            //If a matching Number plate exists(The car is leaving the parking lot),
            //Calculate the time the car was in the parking lot and the amount fee it had to pay.
            //Empty the values of all the indexes related to the car by making them { 0 }.
            if (Parking[i][0] == NumberPlate) {
                CarOut = 1;//The car is leaving the parking lot.

                //Calculate the time the car stayed in the parking lot.
                day -= Parking[i][1];
                hour -= Parking[i][2];
                minute -= Parking[i][3];

                if (minute < 0) {
                    hour -= 1;
                    minute += 60;
                }
                if (hour < 0) {
                    day -= 1;
                    hour += 24;
                }

                Money[NumberofCar][0] = NumberPlate; //Specify the car it has to pay for.
                Money[NumberofCar][1] = FeeCalculate(day, hour, minute); //Calculate the amount of fee the car has to pay.

                //Since the car has left,
                //Add the number of cars using the Parking Lot and Empty indexes where the car was.
                NumberofCar += 1;
                for (int j = 0; j < 4; j++) {
                    Parking[i][j] = 0;
                }
                break;
            }
        }

        //If there is no matching number plate in Parking index(The car is entering the parking lot),
        //Find the empty index of the 'Parking' array and enter the number plate of the car and the time the car entered the parking lot.
        if (CarOut == 0) {
            int FindEmpty = 0; //A variable that allows to find an empty index in the 'Parking' array in a linear way.
            while (1) {
                //From 0 to max, find whether Parking[x][0] is empty.
                //If it is, end the loop and place the values of the variables in the array.
                if (Parking[FindEmpty][0] == 0) {
                    break;
                }
                else FindEmpty++;
            }
            Parking[FindEmpty][0] = NumberPlate;
            Parking[FindEmpty][1] = day;
            Parking[FindEmpty][2] = hour;
            Parking[FindEmpty][3] = minute;
        }
    }

    //Arrange 'Money' array in descending order according to the value of the fee.
    for (int i = 0; i < NumberofCar; i++) {
        for (int j = 0; j < NumberofCar - 1; j++) {
            if (Money[j][1] < Money[j + 1][1]) {
                Switch(&Money[j][0], &Money[j + 1][0]);
                Switch(&Money[j][1], &Money[j + 1][1]);
            }
        }
    }

    //Store the number plate and total amount of fee in descending order in the output file b.txt.
    for (int i = 0; i < NumberofCar; i++) {
        fprintf(ofp, "%d	%d	won\n", Money[i][0], Money[i][1]);
    }

    //file close
    fclose(ifp);
    fclose(ofp);

    return 0;
}

int FeeCalculate(int day, int hour, int minute) {
    //Calculate the amount of fee the car has to pay.
    int result = (day * 24 + hour) * 1000;
    if (day >= 3 && (hour != 0 || minute != 0))
        result += 15000;
    return result;
}


void Switch(int* a, int* b) {
    //Exhange the values of a and b.
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}
