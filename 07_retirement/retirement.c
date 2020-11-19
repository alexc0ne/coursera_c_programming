#include <stdio.h>
#include <stdlib.h>




struct _retire_info
{
    int months;
    double contribution;
    double rate_of_return;   
};
typedef struct _retire_info retire_info;


void print_information(int * startAge, double * total, retire_info ri)
{
    ++*startAge;
    int age_in_years = *startAge / 12;
    int rest_in_months = *startAge % 12;
        
    *total += ri.contribution + *total * ri.rate_of_return;

    printf("Age %3d month %2d you have $%.2lf\n", age_in_years, rest_in_months, *total);
}


void retirement (int startAge,   //in months
                 double initial, //initial savings in dollars
                 retire_info working, //info about working
                 retire_info retired) //info about being retired
{
    
    int age_in_years = startAge / 12;
    int rest_in_months = startAge % 12;
    double total = initial;
    printf("Age %3d month %2d you have $%.2lf\n", age_in_years, rest_in_months, total);
    for (int i = 0; i < working.months; ++i)
        print_information(&startAge, &total, working);

    for (int i = 0; i + 1 < retired.months; ++i)
        print_information(&startAge, &total, retired);
}




int main()
{
    int startAge = 327;
    double initial = 21345;

    retire_info working;
    working.months = 489;
    working.contribution = 1000;
    working.rate_of_return = 0.045/12;

    retire_info retired;
    retired.months = 384;
    retired.contribution = -4000;
    retired.rate_of_return = 0.01/12;
    retirement(startAge, initial, working, retired);

    return EXIT_SUCCESS;
}

/*

2. We're going to model both savings (while working) and expenditure
    (while retired).  It turns out that both of these require the
    same basic information, so we will make a struct to represent that.
    Declare a struct _retire_info which has three fields: 
       (1) an int called "months" for the number of months it is applicable to, 
       (2) a double called "contribution" for how many dollars
           are contributed (or spent if negative) from the account per month 
       (3) a double called "rate_of_return" for the rate of returns 
           (which we will assume to be "after inflation").  

3. Write the function 
      void retirement (int startAge,   //in months
                       double initial, //initial savings in dollars
                       retire_info working, //info about working
                       retire_info retired) //info about being retired

   This function should perform two tasks (which are similar---look
   for a chance to abstract something out into a function!).
  
   First, it should compute your retirement account balance each 
   month while you are working.  To do this, you need to calculate
   the account balance increase from returns (balance * rate of return),
   and add that to the current balance.  You then need to add the
   monthly contribution to the balance.
   For example, if you have $1,000 in the account, earn a 0.5% rate of
   return per month, and contribute $100 per month, you would
   cmopute 1000 * 0.005 = $5 in interest earned.  You would then
   add this plus the monthly contribution to the balance to end up
   with $1105 in the account at the end of the month.

   At the start of each month (before the balance changes), you should
   print out the current balance with the following format:
    "Age %3d month %2d you have $%.2lf\n"
   The first two format conversions are the savers age in years and months.
   The third format conversion is the account balance
   This calculation goes on for the number of months specified 
   in the "working" retire_info structure.  

 
   Second, you should perform a very similar calculation for each
   month of retirment.  The difference here is that you will use the
   information in the "retired" retire_info structure instead
   of the information in the "working" structure.  As with
   working, you should print out the same information as before.

   [Hint: since you are performing a very similar computation,
    think about how you can abstract that part out into a function,
    and re-use it, rather than re-writing it]  


 4. Write a main function which computes the retirement assuming
     Working:
     --------
      Months: 489
      Per Month Savings: $1000
      Rate of Return:  4.5% per year ( 0.045/12 per month) 
                       [above inflation]
    Retired:
    --------
      Months: 384
      Per Month Spending: -4000
      Rate of Return: 1% per year ( 0.01/12 per month) 
                      [above inflation]
    Starting conditions:
    -------------------
       Age: 327 months (27 years, 3 months)
       Savings: $21,345
  5. Compile your code (we provided a Makefile) and test
     it (we provided the output: retirement_ans.txt).

  6. Submit retirement.c


*/
