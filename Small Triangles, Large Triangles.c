#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
    int a;
    int b;
    int c;
};

typedef struct triangle triangle;
/*
 * @brief rearrange the array from the smallest triangle area to the largest.
 * @param tr is a 1D array which considered to be rearranged.
 * @param n  the numbers of triangle (array size).
 */
void sort_by_area(triangle *tr, const int n)
{

    double p = 0, s = 0, temp_a;
    double area[n];
    triangle temp_t;
    // We have created an area array for calculating area of each triangle.
    for (unsigned int i = 0; i < n; i++)
    {
        p = (tr[i].a + tr[i].b + tr[i].c) / 2.0; //we have to use 2.0 not 2 to make this expression return float value
        s = sqrt(p * (p - tr[i].a) * (p - tr[i].b) * (p - tr[i].c));
        area[i] = s;
        //printf("arr[%d] = %lf\n", i, area[i]); -> you can uncomment this for checking how things work.
    }

    // here we are compairing area array elements and arranging them in ascending order also applying these actions on
    // triangles array.
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = i + 1; j < n; j++)
        {

            if (area[j] < area[i])
            {
                temp_t = tr[i];
                //temp_a = area[i];
                tr[i] = tr[j];
                //area[i] = area[j];     you can uncomment these lines to look at how area array will also
                //                       be arranged using these commands. 
                tr[j] = temp_t;
                //area[j] = temp_a;
            }
        }
    }
    // you can use this loop to check for the arrangment of the area array.
    /*
    for (unsigned int i = 0; i < n; i++)
    {
        printf("Area[%d] = %lf\n", i, area[i]);
    }
    */
}

int main()
{
    int n;
    scanf("%d", &n);
    triangle *tr = malloc(n * sizeof(triangle));
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
    }
    sort_by_area(tr, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
    }
    return 0;
}