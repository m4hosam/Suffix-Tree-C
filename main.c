#include <stdio.h>
#include <stdlib.h>
#define MAX 7

struct TreeNodes
{
    char *data;
    struct TreeNodes *branches[MAX];
};

struct TreeNodes *createNode(char *text)
{
    struct TreeNodes *node = (struct TreeNodes *)malloc(sizeof(struct TreeNodes));
    node->data = text;
    for (int i = 0; i < MAX; i++)
        node->branches[i] = NULL;

    return (node);
}

void printTree(struct TreeNodes *node)
{
    if (node == NULL)
    {
        printf("--empty--\n");
        return;
    }
    printf("Data: %s\n", node->data);
    for (int i = 0; i < MAX; i++)
    {
        printf("pointers %d: %p\n", i + 1, node->branches[i]);
    }
}
void BuildSuffixTree(char *text)
{
    int length = strlen(text);
    struct TreeNodes *root = (struct TreeNodes *)malloc(sizeof(struct TreeNodes));
    for (int i = 0; i < length; i++)
        root->branches[i] = NULL;

    for (int k = 0; k < length; k++)
    {
        int flag = 0;
        for (int i = 0; i < length; i++)
        {
            if (root->branches[i] != NULL)
            {

                if (root->branches[i]->data[0] == text[k])
                {
                    printf("222 , k: %d, i: %d, %s\n", k, i, &(root->branches[i]->data[1]));
                    flag = 1;
                    char *tmp = root->branches[i]->data;
                    char *subString = tmp;
                    subString[1] = '\0';
                    //printf("tmp: %s\n", subString);
                    root->branches[i]->data = subString;
                    struct TreeNodes *n2 = createNode(text + k + 1);
                    root->branches[i]->branches[0] = n2;
                    struct TreeNodes *n3 = createNode(tmp + 1);
                    root->branches[i]->branches[1] = n3;

                    break;
                }
            }
            else
            {
                struct TreeNodes *n1 = createNode(text + k);
                root->branches[k] = n1;
                printf("111 , k: %d, i: %d, %p\n", k, i, root->branches[k]);
                break;
            }
        }
    }
    for (int i = 0; i < length; i++)
    {
        struct TreeNodes *n1 = root->branches[i];
        printTree(n1);
    }
}

int main()
{
    char text[10] = "xabxa$";
    //text[2] = '\0';
    //printf("%s\n",text);

    BuildSuffixTree(text);

    return 0;
}
