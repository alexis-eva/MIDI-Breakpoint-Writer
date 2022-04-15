/* hw 3_1 alexis eve - user-input breakpoint file */

#include <stdio.h>
#include <stdlib.h>
#define CLRBUF while(getchar() !='\n') {}

int main(int argc, char * argv[]) { // a breakpoints.txt
    
    // command line arguments validation
    if (argc !=2) { // if not correct arguments
        printf("Usage: %s textfilename", argv[0]);
        return 1;
    }

    FILE * fp; // create new file
    fp = fopen(argv[1], "w"); // create new file to be written
    float btime; // breakpoint time
    int bval; // breakpoint value
    int points = 0; // number of points

    puts("Rules:"); // print starting info
    puts("1. The first number gives the time for the breakpoint, the second number gives the MIDI value at that time.");
    puts("2. The time of the first point must be 0.");
    puts("3. The times must be increasing. Two breakpoints cannot have the same time.");
    puts("4. MIDI values must be between 21 and 108\n5. A breakpoint file must contain at least two points.");

    float * btimes = (float *)malloc(2 * sizeof(float)); // dynamically allocateable array for btimes
    int * bvals = (int *)malloc(2 * sizeof(int)); // array for bvals

    // point 1 - time start must be zero, cannot 0 0 out
    printf("Enter breakpoint #%d (time must be 0) (e.g. 0 72): ", (points + 1));
    while((scanf("%f%d", &btime, &bval) != 2) || btime != 0 || bval < 21 || bval > 108) { // input validation for first point
        printf("%f|%dWrong input. Enter breakpoint #1 again: ", btime, bval);
        CLRBUF
    }

    btimes[points] = btime;
    bvals[points] = bval;
    points++;

    // point 2 - cannot 0 0 out
    printf("Enter breakpoint #%d: ", (points + 1));
    while(scanf("%f %d", &btime, &bval) != 2 || btime <= btimes[points - 1] || bval < 21 || bval > 108) { // input validation
        printf("Wrong input. Enter again: ");
        CLRBUF
    }

    btimes[points] = btime;
    bvals[points] = bval;
    points++;

    //now loop until the user is done
    while(btime != 0 && bval != 0) {
        printf("Enter breakpoint #%d: ", (points + 1));
        CLRBUF
        while(scanf("%f %d", &btime, &bval) != 2 || btime <= btimes[points - 1] ||bval < 21 || bval > 108) {
            if(btime == 0 && bval == 0) {break;} // jump to ending
            printf("Wrong input. Enter again: ");
            CLRBUF
        }
        if(btime == 0 && bval == 0) {break;} // jump to ending
        btimes = (float *)realloc(btimes, (points  + 1) * sizeof(float)); // reallocate new, larger array space for btimes
        bvals = (int *)realloc(bvals, (points + 1) * sizeof(int)); // reallocate for bvals
        btimes[points] = btime;
        bvals[points] = bval;
        points++;
    }

    printf("You entered %d breakpoints in total.", points + 1);
    for (int i = 0; i < points; i++) { // for loop to print to file
        fprintf(fp, "%0.6f\t%d\n", btimes[i], bvals[i]);
    }
    
    // free memory, close files, return 0
    free(btimes);
    free(bvals);
    fclose(fp);
    return 0;
}