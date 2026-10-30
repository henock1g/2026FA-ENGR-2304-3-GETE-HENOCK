/* 2026FA-ENGR-2304-00003-GETE-HENOCK-P04
   Circuit problem generator. Replace 00003 if your course uses a different
   five-digit section number. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Truncate toward zero to three digits after the decimal point. */
double three(double value) {
    return floor(value * 1000.0 + 1e-9) / 1000.0;
}

int main(void) {
    int Vs, R1, R2, R3, choice, k;
    double denominator, i1, i2, v1, v2, v3;
    double expected[5], answer[5];
    const char *names[5] = {"i1 (A)", "i2 (A)", "V1 (V)", "V2 (V)", "V3 (V)"};

    srand((unsigned)time(NULL));
    do {
        Vs = 1 + rand() % 9;     /* 1 through 9 V */
        R1 = 1 + rand() % 19;   /* 1 through 19 ohms */
        R2 = 1 + rand() % 19;
        R3 = 1 + rand() % 19;

        /* [(R1+R2) -R2; -R2 (R2+R3)] [i1;i2] = [Vs;0] */
        denominator = (double)R1 * R2 + (double)R1 * R3 + (double)R2 * R3;
        i1 = Vs * (R2 + R3) / denominator;
        i2 = (double)Vs * R2 / denominator;
        v1 = R1 * i1;
        v2 = (double)Vs * R2 * R3 / denominator; /* R2*(i1-i2) */
        v3 = v2; /* the parallel resistors have equal voltage */
        expected[0] = three(i1);
        expected[1] = three(i2);
        expected[2] = three(v1);
        expected[3] = three(v2);
        expected[4] = three(v3);

        printf("\nVs = %d V, R1 = %d ohms, R2 = %d ohms, R3 = %d ohms\n", Vs, R1, R2, R3);
        puts("Enter i1, i2, V1, V2 and V3 truncated to three decimal places.");
        for (k = 0; k < 5; k++) {
            printf("%s: ", names[k]);
            if (scanf("%lf", &answer[k]) != 1) {
                puts("Invalid input. Exiting.");
                return 1;
            }
        }
        for (k = 0; k < 5; k++) {
            if (fabs(answer[k] - expected[k]) < 0.0005)
                printf("%s: success\n", names[k]);
            else
                printf("%s: failure (correct: %.3f)\n", names[k], expected[k]);
        }
        printf("Enter 0 to exit or 1 for another circuit: ");
        if (scanf("%d", &choice) != 1) {
            puts("Invalid input. Exiting.");
            return 1;
        }
    } while (choice != 0);
    return 0;
}
