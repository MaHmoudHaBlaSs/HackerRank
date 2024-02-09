#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_ELEMENT 1
#define MAX_ELEMENT 1000000
/*
We use variadic function when we don't know how many arguments should be passed to our function ,and there are
many standard variadic functions in C such as printf (when we add a specifier % it allows us to add an extra argument).
note : we should have one argument specified in the function, we can't make it without any arguments like fun(...)-> false.
we can acheive such function using <stdarg.h> library ,and mainly there are 2 ways of making it :
1. considering the first passed argument as counter which specify the number of next arguments to be passed.
2. considering the first argument as a normal pass argument and keep taking arguments till a certain condition is found. 
the folllowing functions are from the first type.
*/

int sum (int count,...) 
{
// va_list is a defined data type inside the library, args is a pointer.
    va_list args; 
//va_start puts args pointer to point to the first argument after count.
    va_start(args, count);
    int sum = 0;
    int num = 0;
    for(unsigned int i = 0; i < count; i++)
    {
//This one accesses the next variadic function argument, expects (double, float, int etc.).
        num = va_arg(args, int);
        sum += num;
    }
//This ends the traversal of the variadic function arguments.
    va_end(args);
    return sum;
}

int min(int count,...) 
{
    va_list args;
    va_start(args, count);
    int num = va_arg(args, int);
    int min = num;
    for(unsigned int i = 0; i < count-1; i++)
    {
        num = va_arg(args, int);
        if(num < min)
        {
            min = num;
        }
    }
    va_end(args);
    return min;
}

int max(int count,...) 
{
    va_list args;
    va_start(args, count);
    int num = va_arg(args, int);
    int max = num;
    for(unsigned int i = 0; i < count-1; i++)
    {
        num = va_arg(args, int);
        if(num > max)
        {
            max = num;
        }
    }
    va_end(args);
    return max;
}
//https://www.youtube.com/watch?v=oDC208zvsdg&ab_channel=CodeVault -> youtube video explains the main idea of variadic funs.


int test_implementations_by_sending_ten_elements() {
    srand(time(NULL));
    
    int elements[10];
    
    elements[0] = rand() % (MAX_ELEMENT - MIN_ELEMENT + 1) + MIN_ELEMENT;
    elements[1] = rand() % (MAX_ELEMENT - MIN_ELEMENT + 1) + MIN_ELEMENT;
    elements[2] = rand() % (MAX_ELEMENT - MIN_ELEMENT + 1) + MIN_ELEMENT;
    elements[3] = rand() % (MAX_ELEMENT - MIN_ELEMENT + 1) + MIN_ELEMENT;
    elements[4] = rand() % (MAX_ELEMENT - MIN_ELEMENT + 1) + MIN_ELEMENT;
    elements[5] = rand() % (MAX_ELEMENT - MIN_ELEMENT + 1) + MIN_ELEMENT;
    elements[6] = rand() % (MAX_ELEMENT - MIN_ELEMENT + 1) + MIN_ELEMENT;
    elements[7] = rand() % (MAX_ELEMENT - MIN_ELEMENT + 1) + MIN_ELEMENT;
    elements[8] = rand() % (MAX_ELEMENT - MIN_ELEMENT + 1) + MIN_ELEMENT;
    elements[9] = rand() % (MAX_ELEMENT - MIN_ELEMENT + 1) + MIN_ELEMENT;
    
    fprintf(stderr, "Sending following ten elements:\n");
    for (int i = 0; i < 10; i++) {
        fprintf(stderr, "%d\n", elements[i]);
    }
    
    int elements_sum = sum(10, elements[0], elements[1], elements[2], elements[3], elements[4],
                           elements[5], elements[6], elements[7], elements[8], elements[9]);
    int minimum_element = min(10, elements[0], elements[1], elements[2], elements[3], elements[4],
                           elements[5], elements[6], elements[7], elements[8], elements[9]);
    int maximum_element = max(10, elements[0], elements[1], elements[2], elements[3], elements[4],
                           elements[5], elements[6], elements[7], elements[8], elements[9]);
    
    fprintf(stderr, "Your output is:\n");
    fprintf(stderr, "Elements sum is %d\n", elements_sum);
    fprintf(stderr, "Minimum element is %d\n", minimum_element);
    fprintf(stderr, "Maximum element is %d\n\n", maximum_element);
    
    int expected_elements_sum = 0;
    for (int i = 0; i < 10; i++) {
        if (elements[i] < minimum_element) {
            return 0;
        }
        
        if (elements[i] > maximum_element) {
            return 0;
        }
        
        expected_elements_sum += elements[i];
    }
    
    return elements_sum == expected_elements_sum;
}

int main ()
{
    int number_of_test_cases;
    scanf("%d", &number_of_test_cases);
    
    while (number_of_test_cases--) {
        if (test_implementations_by_sending_three_elements()) {
            printf("Correct Answer\n");
        } else {
            printf("Wrong Answer\n");
        }
        
        if (test_implementations_by_sending_five_elements()) {
            printf("Correct Answer\n");
        } else {
            printf("Wrong Answer\n");
        }
        
        if (test_implementations_by_sending_ten_elements()) {
            printf("Correct Answer\n");
        } else {
            printf("Wrong Answer\n");
        }
    }
    
    return 0;
}