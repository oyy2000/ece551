#include <stdio.h>
#include <stdlib.h>

typedef struct _retire_info
{
    int months;
    double contribution;
    double rate_of_return;
} retire_info;

double computeBalance(int startAge, double balance, retire_info info);

double computeBalance(int startAge, double balance, retire_info info)
{
    int year, month;

    year = startAge / 12;
    month = startAge % 12;

    while (info.months--)
    {
        printf("Age %3d month %2d you have $%.2lf\n", year, month, balance);
        balance = (1.0 + info.rate_of_return) * balance + info.contribution;
        month++;
        if (month == 12)
        {
            year++;
            month = 0;
        }
    }
    return balance;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired)
{
    double afterWork = computeBalance(startAge, initial, working);
    computeBalance(startAge + working.months, afterWork, retired);
}

int main()
{
    retire_info working = {489, 1000, 0.045 / 12};
    retire_info retired = {384, -4000, 0.01 / 12};
    retirement(327, 21345, working, retired);

    return 0;
}