/* 2026FA-ENGR-2304-00003-GETE-HENOCK-P04 */

#include <stdio.h>
#include <math.h>

double determinant2(double a, double b, double c, double d)
{
    return a * d - b * c;
}

/* Uses cofactor expansion across the first row. */
double determinant3(double m[3][3])
{
    double cofactor1 =  determinant2(m[1][1], m[1][2], m[2][1], m[2][2]);
    double cofactor2 = -determinant2(m[1][0], m[1][2], m[2][0], m[2][2]);
    double cofactor3 =  determinant2(m[1][0], m[1][1], m[2][0], m[2][1]);

    return m[0][0] * cofactor1
         + m[0][1] * cofactor2
         + m[0][2] * cofactor3;
}

void solve2Equations(void)
{
    double a1, b1, c1, a2, b2, c2;
    double d, dx, dy;

    printf("Enter a1 b1 c1 for a1x + b1y = c1: ");
    scanf("%lf %lf %lf", &a1, &b1, &c1);
    printf("Enter a2 b2 c2 for a2x + b2y = c2: ");
    scanf("%lf %lf %lf", &a2, &b2, &c2);

    d  = determinant2(a1, b1, a2, b2);
    dx = determinant2(c1, b1, c2, b2);
    dy = determinant2(a1, c1, a2, c2);

    if (fabs(d) < 0.000001) {
        printf("The system does not have one unique solution.\n");
    } else {
        printf("D = %.2f, Dx = %.2f, Dy = %.2f\n", d, dx, dy);
        printf("x = %.2f\ny = %.2f\n", dx / d, dy / d);
    }
}

void solve3Equations(void)
{
    double a[3][3], answers[3];
    double mx[3][3], my[3][3], mz[3][3];
    double d, dx, dy, dz;
    int row, column;

    printf("Enter each equation as: x coefficient, y coefficient, "
           "z coefficient, answer.\n");

    for (row = 0; row < 3; row++) {
        printf("Equation %d: ", row + 1);
        scanf("%lf %lf %lf %lf", &a[row][0], &a[row][1],
                                  &a[row][2], &answers[row]);
    }

    for (row = 0; row < 3; row++) {
        for (column = 0; column < 3; column++) {
            mx[row][column] = a[row][column];
            my[row][column] = a[row][column];
            mz[row][column] = a[row][column];
        }
        mx[row][0] = answers[row];
        my[row][1] = answers[row];
        mz[row][2] = answers[row];
    }

    d  = determinant3(a);
    dx = determinant3(mx);
    dy = determinant3(my);
    dz = determinant3(mz);

    if (fabs(d) < 0.000001) {
        printf("The system does not have one unique solution.\n");
    } else {
        printf("D = %.2f, Dx = %.2f, Dy = %.2f, Dz = %.2f\n",
               d, dx, dy, dz);
        printf("x = %.2f\ny = %.2f\nz = %.2f\n",
               dx / d, dy / d, dz / d);
    }
}

int main(void)
{
    int choice;

    printf("Cramer's Rule Solver\n");
    printf("1. Solve two equations\n");
    printf("2. Solve three equations\n");
    printf("Choose 1 or 2: ");
    scanf("%d", &choice);

    if (choice == 1) {
        solve2Equations();
    } else if (choice == 2) {
        solve3Equations();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
