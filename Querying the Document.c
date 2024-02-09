#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// #define DEBUG_MODE

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

// Code space

/*
 *@brief Taking documeny and return certain word from it.
 */
char *kth_word_in_mth_sentence_of_nth_paragraph(char ****document, int k, int m, int n)
{
    return document[n - 1][m - 1][k - 1];
}

/*
 *@brief Taking documeny and return certain sentence from it.
 */
char **kth_sentence_in_mth_paragraph(char ****document, int k, int m)
{
    return document[m - 1][k - 1];
}

/*
 *@brief Taking documeny and return certain paragraph from it.
 */
char ***kth_paragraph(char ****document, int k)
{
    return document[k - 1];
}

/*
 *@brief Taking normal string and return it as detailed one [paragraphs -> sentences -> word]
 */
char ****get_document(char *text)
{
    char ****document; //we have to allocate a space for this pointer before using it. whether dynamically or statically

    unsigned short chars = 0, prgrfs = 0, sents = 0, words = 0, counter = 0;

    // Allocate memory for top level pointers [Paragraphs]
    document = (char ****)calloc(5, sizeof(char ***));

    for (int i = 0; i < 5; i++)
    {

        // Allocate memory for each first level pointer [Sentences]
        document[i] = (char ***)calloc(50, sizeof(char **));

        for (int j = 0; j < 50; j++)
        {

            // Allocate memory for each second level pointer [Words]
            document[i][j] = (char **)calloc(50, sizeof(char *));

            for (int k = 0; k < 50; k++)
            {

                // Allocate memory for each third level pointer [Characters]
                document[i][j][k] = (char *)calloc(50, sizeof(char));
            }
        }
    }

    while (counter < strlen(text))
    {
#ifdef DEBUG_MODE
        printf("loop entered.\n");
#endif
        if (text[counter] != '\n')
        {
#ifdef DEBUG_MODE
            printf("First Condition passed.\n");
#endif
            if (text[counter] != '.')
            {
#ifdef DEBUG_MODE
                printf("Second Condition passed.\n");
#endif
                if (text[counter] != ' ')
                {
#ifdef DEBUG_MODE
                    printf("Third Condition passed.\n");
                    printf("text[%d] = %c\n", counter, text[counter]);
#endif
                    document[prgrfs][sents][words][chars] = text[counter];
                    chars++;
                    counter++;
#ifdef DEBUG_MODE
                    printf("text[%d] = %c\n", counter, text[counter]);
#endif
                }
                else // text[counter] == ' '
                {
                    counter++;
                    words++;
                    chars = 0;
                }
            }
            else
            {
                counter++;
                sents++;
                words = 0;
                chars = 0;
            }
        }
        else // text[counter] == '\n'
        {
            prgrfs++;
            counter++;
            sents = 0;
            words = 0;
            chars = 0;
        }
    }
    // return the address of the previously dynamically allocated memory.
    return document;
}
/*
Notes : Paragraph ends with '\n' [except last paragraph] - Sentence ends with '.'
Word ends with ' ' [except last word].
- when we dynamically allocates memory using calloc , malloc or any of these funs we hold the return address in a
higher level pointer Ex: (char****)malloc(sizeof(char***)).
*/

// End of code space
char *get_input_text()
{
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++)
    {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char *returnDoc = (char *)malloc((strlen(doc) + 1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char *word)
{
    printf("%s", word);
}

void print_sentence(char **sentence)
{
    int word_count;
    scanf("%d", &word_count); // how many words in the sentence

    for (int i = 0; i < word_count; i++)
    {
#ifdef DEBUG_MODE
        printf("Print_sentence loop entered_%d\n", i);
#endif
        printf("%s", sentence[i]);
        if (i != word_count - 1)
            printf(" ");
    }
}

void print_paragraph(char ***paragraph)
{
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++)
    {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main()
{
    char *text = get_input_text();
    char ****document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--)
    {
        int type;
        scanf("%d", &type);

        if (type == 3) // to print single word.
        {
            // k -> Paragraph, m -> Sentence, n -> Word
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char *word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2) // to print sentences.
        {
            // k -> Paragraph, m -> Sentence
            int k, m;
            scanf("%d %d", &k, &m);
            char **sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else
        {
            // k -> Paragraph
            int k;
            scanf("%d", &k);
            char ***paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }
}