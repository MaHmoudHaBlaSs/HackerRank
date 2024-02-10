#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
//#define DEBUG_MODE
struct word {
    char* data;
};

struct sentence {
    struct word* data; // array of characters
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data; // array of words
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data; // array of sentences
    int paragraph_count;//denotes number of paragraphs in a document
};
// Code Space
struct paragraph kth_paragraph(struct document Doc, int k);
struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m);
struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n);
void print_word(struct word w);
void print_sentence(struct sentence sen);
void print_paragraph(struct paragraph para);

struct document get_document(char* text) 
{
    struct document _document = {0};
    _document.paragraph_count = 1;// we should do the same with sentences count and words count but i fixed it in the code latter.
    unsigned short counter = 0, prgrfs = 0, sents = 0, words = 0, chars = 0;
    // Allocating space.
    
    _document.data = calloc(sizeof(struct paragraph),5);
    for(unsigned int i = 0; i < 5; i++)
    {
        _document.data[i].data = calloc(sizeof(struct sentence),30);
        for(unsigned int j = 0; j < 30; j++)
        {
            _document.data[i].data[j].data = calloc(sizeof(struct word),30);
            for(unsigned int k = 0; k < 30; k++)
            {
                _document.data[i].data[j].data[k].data = (char*)calloc(sizeof(char),50);
            }
        }
    }
    // Assigning values.
    while(counter <= strlen(text))
    {
        if((text[counter] != '\n') && (counter < strlen(text))) // Paragraphs
        {
#ifdef DEBUG_MODE
    printf("First condition '\\n' passed.\n");
#endif
            if(text[counter] != '.') // Sentences
            {
#ifdef DEBUG_MODE
    printf("Second condition '.' passed.\n");
#endif
                if(text[counter] != ' ') // Words
                {
#ifdef DEBUG_MODE
    printf("Third condition ' ' passed.\n");
#endif
                    //array of:    prgrfs  -    sents   -   words   -   chars
                    _document.data[prgrfs].data[sents].data[words].data[chars] = text[counter];
                    counter++;
                    chars++;
#ifdef DEBUG_MODE
    printf("_document.data[%d].data[%d].data[%d].data[%d] = %c\n", prgrfs, sents, words, chars-1, text[counter-1]);
#endif
                }
                else
                {
                    counter++;
                    words++;
                    chars = 0;
                }
            }
            else
            {
                counter++;
                words++;
                _document.data[prgrfs].data[sents].word_count = words;
                sents++;
                words = 0;
                chars = 0;
            }
        }
        else
        {
#ifdef DEBUG_MODE
printf("First condition '\\n' Else route.\n");
#endif
            counter++;
            _document.data[prgrfs].sentence_count = sents;
            prgrfs++;
            _document.paragraph_count = prgrfs;
            sents = 0;
            words = 0;
            chars = 0;
        }
    }
    /*--------------------------------Testing-------------------------------*/
    struct word Testword = {0};
    struct sentence TestSent = {0};
    struct paragraph TestPara = {0};
    //print_word(_document.data[1].data[0].data[0]); //-> works
    //Testword = kth_word_in_mth_sentence_of_nth_paragraph(_document, 1, 2, 2);print_word(Testword); //-> works
    //print_sentence(_document.data[1].data[1]); //-> works
    //TestSent = kth_sentence_in_mth_paragraph(_document, 1, 2);print_sentence(TestSent); //-> works
    //print_paragraph(_document.data[1]); //-> works
    //TestPara = kth_paragraph(_document, 2);print_paragraph(TestPara); //-> works
    


    return _document;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) 
{
    return Doc.data[n-1].data[m-1].data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) 
{ 
    return (Doc.data[m-1].data[k-1]);
}

struct paragraph kth_paragraph(struct document Doc, int k) 
{
    return (Doc.data[k-1]);
}

/*
Notes :
- We firstly must allocate space for these struct pointers before assigning them to any value.
- We can use memcpy() with any level of pointers but both of them must be of the same level 
Ex : memcpy(***ptr1, ***ptr2, 88) -> valid / memcpy(**ptr1, ***ptr2, 88) -> not valid
*/

//End of Code Space
void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar(); // clear buuffer.
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

   /*--------------------------Application----------------------*/
    
    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3) // Print word.
        {
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) // Print sentence .
        {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else // Print Paragraph
        {
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }
       
}
