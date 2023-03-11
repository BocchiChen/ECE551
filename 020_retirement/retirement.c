#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double balance;
int age;

double cal_monthly_balance(double money, double monthly_rate, double contribution){
  return money+(money*monthly_rate)+contribution;
}

void output(retire_info status){
    while(status.months>0){
        printf("Age %3d month %2d you have $%.2f\n",age/12,age%12,balance);
        balance = cal_monthly_balance(balance,status.rate_of_return/12,status.contribution);
        age++;
        status.months--;
    }
}

void retirement(int startAge,double initial,retire_info working,retire_info retired){
    balance = initial;
    age = startAge;
    output(working);
    output(retired);
}

int main(){
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;
  retirement(327,21345,working,retired);
  return EXIT_SUCCESS;
}