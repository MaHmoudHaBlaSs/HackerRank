#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// to sort the strings in lexicographically increasing order. [a -> z] comapres only 2 strings returns [0 for a , 1 for b and -1 for equallity]
// no repeated first character
int lexicographic_sort(const char *a, const char *b)
{
    int Ret = -1;
    if (strlen(b) <= strlen(a))
    {
        for (unsigned int i = 0; i < strlen(b); i++)
        {
            if (a[i] < b[i])
            {
                Ret = 0;
                break;
            }
            else if (b[i] < a[i])
            {
                Ret = 1;
                break;
            }
            else // b[i] == a[i]
            {
                Ret = 1;
                continue;
            }
        }
    }
    else if (strlen(a) < strlen(b))
    {
        for (unsigned int i = 0; i < strlen(b); i++)
        {
            if (a[i] < b[i])
            {
                Ret = 0;
                break;
            }
            else if (b[i] < a[i])
            {
                Ret = 1;
                break;
            }
            else // b[i] == a[i]
            {
                continue;
            }
        }
    }
    return (Ret);
}

// to sort the strings in lexicographically decreasing order. [z -> a] comapres only 2 strings returns [0 for a , 1 for b and -1 for equallity]
int lexicographic_sort_reverse(const char *a, const char *b)
{
    int Ret = -1;
    if (strlen(b) <= strlen(a))
    {
        for (unsigned int i = 0; i < strlen(b); i++)
        {
            if (a[i] < b[i])
            {
                Ret = 1;
                break;
            }
            else if (b[i] < a[i])
            {
                Ret = 0;
                break;
            }
            else // b[i] == a[i]
            {
                continue;
            }
        }
    }
    else if (strlen(a) < strlen(b))
    {
        for (unsigned int i = 0; i < strlen(b); i++)
        {
            if (a[i] < b[i])
            {
                Ret = 1;
                break;
            }
            else if (b[i] < a[i])
            {
                Ret = 0;
                break;
            }
            else // b[i] == a[i]
            {
                continue;
            }
        }
    }
    return (Ret);
}

//  to sort the strings in increasing order of the number of distinct characters (or non-repeating characters) present in them. comapres only 2 strings
//  If two strings have the same number of distinct characters present in them, then the lexicographically smaller string should appear first. [0 for a , 1 for b]
int sort_by_number_of_distinct_characters(const char *a, const char *b)
{
    int distinct_a = 0, distinct_b = 0, temp = 0;
    int lena = strlen(a)+1, lenb = strlen(b)+1;
    char stra[lena], strb[lenb];
    strcpy(stra , a);
    strcpy(strb , b);
    for (unsigned int i = 0; i < strlen(a); i++)
    {
        for (unsigned int j = i+1; j < strlen(a); j++)
        {
            if (stra[i] == '\0')
            {
                continue;
            }
            else if (stra[i] == stra[j])
            {
                stra[j] = '\0';
            }
        }
    }
    for(unsigned int i = 0; i < strlen(a); i++)
    {
        if(stra[i] != '\0')
            distinct_a++;
    }
    for (unsigned int i = 0; i < strlen(b); i++)
    {
        for (unsigned int j = i+1; j < strlen(b); j++)
        {
            if (strb[i] == '\0')
            {
                continue;
            }
            else if (strb[i] == strb[j])
            {
                strb[j] = '\0';
            }
        }
    }
    for(unsigned int i = 0; i < strlen(b); i++)
    {
        if(strb[i] != '\0')
            distinct_b++;
    }
    if (distinct_a < distinct_b)
    {
        return 0;
    }
    else if (distinct_b < distinct_a)
    {
        return 1;
    }
    else
    {
        return (lexicographic_sort(a, b));
    }
}

// to sort the strings in increasing order of their lengths. If two strings have the same length,
// then the lexicographically smaller string should appear first. comapres only 2 strings
int sort_by_length(const char *a, const char *b)
{
    if (strlen(a) < strlen(b))
    {
        return 0;
    }
    else if (strlen(b) < strlen(a))
    {
        return 1;
    }
    else
    {
        return (lexicographic_sort(a,b));
    }
}
//              array of strings - number of strings - function pointer
void string_sort(char **arr, const int len, int (*cmp_func)(const char *a, const char *b))
{
    if (cmp_func == lexicographic_sort)
    {
        // lexicographic_sort
        char temp[1024];
        for (unsigned int i = 0; i < len - 1; i++)
        {
            for (unsigned int j = i + 1; j < len; j++)
            {
                if (lexicographic_sort(arr[i], arr[j]) == 1) // arr[j] comes first
                {
                    strcpy(temp, arr[i]);
                    strcpy(arr[i], arr[j]);
                    strcpy(arr[j], temp);
                }
            }
        }
    }
    else if (cmp_func == lexicographic_sort_reverse)
    {
        // lexicographic_sort_reverse
        char temp[1024];
        for (unsigned int i = 0; i < len - 1; i++)
        {
            for (unsigned int j = i + 1; j < len; j++)
            {
                if (lexicographic_sort_reverse(arr[i], arr[j]) == 1) // arr[j] sould come first
                {
                    strcpy(temp, arr[i]);
                    strcpy(arr[i], arr[j]);
                    strcpy(arr[j], temp);
                }
            }
        }
    }
    else if (cmp_func == sort_by_number_of_distinct_characters)
    {
        // sort_by_number_of_distinct_characters
        char temp[1024];
        for (unsigned int i = 0; i < len - 1; i++)
        {
            for (unsigned int j = i + 1; j < len; j++)
            {
                if (sort_by_number_of_distinct_characters(arr[i] , arr[j]) == 1)
                {
                    strcpy(temp, arr[i]);
                    strcpy(arr[i], arr[j]);
                    strcpy(arr[j], temp);
                }
            }
        }
    }
    else if (cmp_func == sort_by_length)
    {
        // sort_by_length
        char temp[1024];
        for (unsigned int i = 0; i < len - 1; i++)
        {
            for (unsigned int j = i + 1; j < len; j++)
            {
                if (sort_by_length(arr[i] , arr[j]) == 1)
                {
                    strcpy(temp, arr[i]);
                    strcpy(arr[i], arr[j]);
                    strcpy(arr[j], temp);
                }
            }
        }
    }

}

int main()
{
    int n;
    scanf("%d", &n); // n >= 1 && n <= 50

    char **arr;
    arr = (char **)malloc(n * sizeof(char *)); // 2D array[n(number of strings)][1024(string width)]

    for (int i = 0; i < n; i++)
    {
        arr[i] = malloc(1024 * sizeof(char));
        scanf("%s", arr[i]);
        arr[i] = realloc(arr[i], strlen(arr[i]) + 1);
    }

    /*-----------------------------------------------------------------------------------------------*/
    
    string_sort(arr, n, lexicographic_sort);
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");
     
    string_sort(arr, n, sort_by_length);
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");
    
    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for (int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");
    
}

/*
Notes :
in lexicographic_sort why when I used :                                  And when used :
char *temp;                                                              char temp[1024];
strcpy(temp, arr[i]);                                                    strcpy(temp, arr[i]);
strcpy(arr[i], arr[j]);                                                  strcpy(arr[i], arr[j]);
strcpy(arr[j], temp);                                                    strcpy(arr[j], temp);
it didn't work and                                                       It worked well !
*/