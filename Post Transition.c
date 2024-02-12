#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 6
// #define DEBUG_MODE
struct package
{
    char *id;   // Package name [Lower Case letter (a->z)]
    int weight; // weight of the package
};

typedef struct package package;

struct post_office
{
    int min_weight;     // min weight allowed
    int max_weight;     // max weight allowed
    package *packages;  // package info
    int packages_count; // Packages count
};

typedef struct post_office post_office;

struct town
{
    char *name;           // Town name [Upper Case letter (A->Z)]
    post_office *offices; // office info
    int offices_count;    // officies in the town
};

typedef struct town town;
// Code Space

// print all packages in this town.
void print_all_packages(town t)
{

    printf("%s:\n", t.name);
    for (unsigned int i = 0; i < t.offices_count; i++)
    {
#ifdef DEBUG_MODE
        printf("t.offices[%d].packages_count = %d\n", i, t.offices[i].packages_count);
#endif
        printf("\t%i:\n", i);
        for (unsigned int j = 0; j < t.offices[i].packages_count; j++)
        {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

void send_all_acceptable_packages(town *source, int source_office_index, town *target, int target_office_index)
{
    unsigned short indlen = 0, acceptedind = 0, rejectedind = 0;
    for (unsigned short i = 0; i < source->offices[source_office_index].packages_count; i++)
    {
        // if passed from this condition that means the packages[i] is an accepted package.
        if ((source->offices[source_office_index].packages[i].weight <= target->offices[target_office_index].max_weight) && (source->offices[source_office_index].packages[i].weight >= target->offices[target_office_index].min_weight))
        {
            indlen++; // accepted packs number
        }
    }
    struct package *acceptedpack = calloc(sizeof(struct package), indlen);
    struct package *rejectedpack = calloc(sizeof(struct package), (source->offices[source_office_index].packages_count - indlen));

    if (acceptedpack && rejectedpack)
    {
        for (unsigned short i = 0; i < source->offices[source_office_index].packages_count; i++)
        {
            // if passed from this condition that means the packages[i] is an accepted package.
            if ((source->offices[source_office_index].packages[i].weight <= target->offices[target_office_index].max_weight) && (source->offices[source_office_index].packages[i].weight >= target->offices[target_office_index].min_weight))
            {
                acceptedpack[acceptedind++] = source->offices[source_office_index].packages[i];
            }
            else
            {
                rejectedpack[rejectedind++] = source->offices[source_office_index].packages[i];
            }
        }
        acceptedind = 0;
        target->offices[target_office_index].packages = realloc(target->offices[target_office_index].packages,
                                                                (target->offices[target_office_index].packages_count + indlen) * sizeof(struct package));
        for (unsigned short i = target->offices[target_office_index].packages_count; i < (target->offices[target_office_index].packages_count + indlen); i++)
        {
            target->offices[target_office_index].packages[i] = acceptedpack[acceptedind++];
#ifdef DEBUG_MODE
            printf("target->offices[%d].packages[%d].id = %s\n", target_office_index, i, target->offices[target_office_index].packages[i].id);
#endif
        }
        target->offices[target_office_index].packages_count += indlen;
#ifdef DEBUG_MODE
        printf("target->offices[%d].packages_count = %d\n", target_office_index, target->offices[target_office_index].packages_count);
#endif
        free(acceptedpack);
        acceptedpack = NULL;
    }
    else
    {
#ifdef DEBUG_MODE
        printf("Couldnit allocate space for acceptedpack or rejectedpack..\n");
#endif
        exit(EXIT_FAILURE);
    }

    source->offices[source_office_index].packages_count = rejectedind;
    rejectedind = 0;
    for (unsigned short i = 0; i < source->offices[source_office_index].packages_count; i++)
    {
        source->offices[source_office_index].packages[i] = rejectedpack[rejectedind++];
    }
    source->offices[source_office_index].packages = realloc(source->offices[source_office_index].packages, source->offices[source_office_index].packages_count * sizeof(struct package));
    free(rejectedpack);
    rejectedpack = NULL;
}

town town_with_most_packages(town *towns, int towns_count)
{
    town maxtown = {0};
    int totalpacks = 0, formermax = 0;

    for (unsigned short i = 0; i < towns_count; i++)
    {
        for (unsigned short j = 0; j < towns[i].offices_count; j++)
        {
            totalpacks += towns[i].offices[j].packages_count;
        }
        if (totalpacks > formermax)
        {
            maxtown = towns[i];
            formermax = totalpacks;
        }
        totalpacks = 0;
    }
    return maxtown;
}

town *find_town(town *towns, int towns_count, char *name)
{
    // town *unknown_town = NULL; -> we can't use such variable to return the address because there is inside it many another
    //                               objects which need to be allocated in memory [Dynamically]
    unsigned short ind = 0;
    for (unsigned short i = 0; i < towns_count; i++)
    {

        if (strcmp(name, towns[i].name) == 0)
        {
            ind = i;
            break;
        }
    }

    return (&towns[ind]);
}
/*
Notes : In C, you shouldn't use the == operator to compare strings because it compares the addresses of the strings,
not their actual content.Instead, you should use functions like strcmp() to compare the content of strings.
*/
// End of Code Space
int main()
{
    /*--------------------------------------------Initialize Towns--------------------------------------------*/
    int towns_count;
    scanf("%d", &towns_count);
    town *towns = malloc(sizeof(town) * towns_count);
    for (int i = 0; i < towns_count; i++)
    {
        towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);
        towns[i].offices = malloc(sizeof(post_office) * towns[i].offices_count);
        for (int j = 0; j < towns[i].offices_count; j++)
        {
            scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
            towns[i].offices[j].packages = malloc(sizeof(package) * towns[i].offices[j].packages_count);
            for (int k = 0; k < towns[i].offices[j].packages_count; k++)
            {
                towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weight);
            }
        }
    }

    /*-----------------------------------------------Testing---------------------------------------------------*/
    /*
    printf("Towns Initialized..\n");
    town Test = {0};
    town *PTest = NULL;
    char *name = "B";
    //print_all_packages(towns[1]); //-> works
    //send_all_acceptable_packages(&towns[1], 0, &towns[0], 1);print_all_packages(towns[0]);print_all_packages(towns[1]); //-> works
    // = town_with_most_packages(towns, towns_count);print_all_packages(Test); //-> works
    //PTest = find_town(towns, towns_count, name);print_all_packages(*PTest);
    */
    /*---------------------------------------------Application--------------------------------------------*/

    int queries;
    scanf("%d", &queries);
    char town_name[MAX_STRING_LENGTH];
    while (queries--)
    {
        int type;
        scanf("%d", &type);
        switch (type)
        {
        case 1:
            scanf("%s", town_name);
            town *t = find_town(towns, towns_count, town_name);
            print_all_packages(*t);
            break;
        case 2:
            scanf("%s", town_name);
            town *source = find_town(towns, towns_count, town_name);
            int source_index;
            scanf("%d", &source_index);
            scanf("%s", town_name);
            town *target = find_town(towns, towns_count, town_name);
            int target_index;
            scanf("%d", &target_index);
            send_all_acceptable_packages(source, source_index, target, target_index);
            break;
        case 3:
            printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
            break;
        }
    }

    for (unsigned short i = 0; i < towns_count; i++)
    {
        for (unsigned short j = 0; j < towns[i].offices_count; j++)
        {
            for (unsigned short k = 0; k < towns[i].offices[j].packages_count; k++)
            {
                free(towns[i].offices[j].packages[k].id);
            }
            free(towns[i].offices[j].packages);
        }
        free(towns[i].offices);
        free(towns[i].name);
    }
    free(towns);

    return 0;
}