#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 8

typedef struct TreeNodes
{
    char *data;
    struct TreeNodes *branches[MAX];
    int children;
    int index;
} TreeNodes;

struct Student
{
    char *name;
};

struct TreeNodes *createNode(char *text, int children, int index)
{
    struct TreeNodes *node = (struct TreeNodes *)malloc(sizeof(struct TreeNodes));
    // node->data = malloc(20 * sizeof(char));
    node->data = text;
    node->children = children;
    node->index = index;
    for (int i = 0; i < MAX; i++)
        node->branches[i] = NULL;

    return (node);
}

struct TreeNodes *modifyNode(struct TreeNodes *node, char *text, int children, int index)
{
    node->data = text;
    node->children = children;
    node->index = index;
    return (node);
}

void subString(char *src, char sub1[20], char sub2[20], int index)
{
    int length = strlen(src);
    for (int i = 0; i < length; i++)
    {
        if (i < index)
            sub1[i] = src[i];
        else
            sub2[i - index] = src[i];
    }
    sub1[index] = '\0';
    sub2[(length - index)] = '\0';
}

void printNode(struct TreeNodes *node)
{
    if (node == NULL)
    {
        printf("--empty--\n");
        return;
    }
    printf("Data: %s\n", node->data);
    printf("Children: %d\n", node->children);
    printf("Index: %d\n", node->index);
    for (int i = 0; i < MAX; i++)
    {
        printf("pointers %d: %p\n", i + 1, node->branches[i]);
    }
}
void printTree(struct TreeNodes *root)
{
    if (root == NULL)
    {
        printf("--Tree is Empty--\n");
        return;
    }
    for (int i = 0; i < MAX; i++)
    {
        struct TreeNodes *n = root->branches[i];
        if (root->branches[i] == NULL)
        {
            return;
        }
        printNode(n);
        if (root->branches[i]->children > 0)
        {
            for (int j = 0; j < MAX; j++)
            {
                printf("\tBranch %d\n", j);
                struct TreeNodes *b1 = root->branches[i]->branches[j];
                printNode(b1);
            }
        }
        printf("---------------------\n\n");
    }
}
int StringCmp(char *data, char *text)
{
    int size = strlen(data);
    for (int i = 0; i < size; i++)
    {
        if (data[i] != text[i])
            return i;
    }
}
struct TreeNodes *searchTree(struct TreeNodes *node, char *text, int *idx)
{
    if (node == NULL)
    {
        return node;
    }
    else
    {
        for (int i = 0; i < MAX; i++)
        {
            if (node->branches[i] == NULL)
            {
                return node;
            }
            int index = StringCmp(node->branches[i]->data, text);
            int lenData = strlen(node->branches[i]->data);
            if (index > 0)
            {
                if (index == lenData)
                {
                    (*idx)++;
                    return searchTree(node->branches[i], (text + index), idx);
                }
                else
                {
                    (*idx)++;
                    return node->branches[i];
                }
            }
            // printf("index %d: %d lenData: %d\n", i, index, lenData);
        }
    }
    return node;
}

void customTree()
{
    struct TreeNodes *root = (struct TreeNodes *)malloc(sizeof(struct TreeNodes));
    root->data = "root";
    root->children = 5;
    root->index = -1;
    for (int i = 0; i < MAX; i++)
        root->branches[i] = NULL;

    struct TreeNodes *n1 = createNode("bxa$", 0, -1);
    root->branches[0] = n1;

    struct TreeNodes *n2 = createNode("$", 0, -1);
    root->branches[1] = n2;

    struct TreeNodes *n3 = createNode("abxa$", 2, -1);
    root->branches[2] = n3;
    // struct TreeNodes *n31 = createNode("$", 0, -1);
    // root->branches[2]->branches[0] = n31;
    // struct TreeNodes *n32 = createNode("bxa$", 0, -1);
    // root->branches[2]->branches[1] = n32;

    struct TreeNodes *n4 = createNode("xa", 2, -1);
    root->branches[3] = n4;
    struct TreeNodes *n41 = createNode("$", 0, -1);
    root->branches[3]->branches[0] = n41;
    struct TreeNodes *n42 = createNode("bxa$", 0, -1);
    root->branches[3]->branches[1] = n42;
    int idx = 0;
    struct TreeNodes *searchedNode = searchTree(root, "a$", &idx);
    printf("---------Searching-----------\n");
    printNode(searchedNode);
    searchedNode->branches[3] = createNode("new", 0, -1);
    printf("ROot Index: %d\n", idx);
    printf("---------Printing-----------\n");

    printTree(root);
}

void BuildSuffixTree(char *text)
{
    int length = strlen(text);
    struct TreeNodes *root = createNode("$root$", 0, -1);
    int idx, index;

    root->branches[0] = createNode(text, 0, 0);
    root->children = (root->children) + 1;

    for (int i = 1; i < length; i++)
    {
        idx = 0;
        struct TreeNodes *searchedNode = searchTree(root, text + i, &idx);

        if (idx == 0) // Returned root append directly
        {

            root->branches[root->children] = createNode(text + i, 0, i);
            (root->children)++;
        }
        else
        {
            if (searchedNode->children == 0)
            {
                // printf("modified i(%d) idx(%d): %s\n", i, idx, searchedNode->data);

                index = StringCmp(searchedNode->data, text + i);
                // printf("index:%d\n", index);

                char subString1[MAX][20], subString2[MAX][20];
                // printf("text: %s\n", text + index);

                subString((searchedNode->data), subString1[i], subString2[i], index);

                // printf("i: %d text + index: %s\n", i, text + i + index);
                // printf("xa11 i(%d) idx(%d): %s\n", i, idx, root->branches[0]->data);
                searchedNode->branches[0] = createNode(text + i + index, 0, i);

                searchedNode->branches[1] = createNode(subString2[i], 0, searchedNode->index);

                // printf("xa11 i(%d) idx(%d): %s\n", i, idx, root->branches[0]->data);
                // printf("--------\ni(%d)subString: 1.%s    2.%s\n---------\n", i, subString1[i], subString2[i]);
                searchedNode = modifyNode(searchedNode, &subString1[i], 2, -1);
                // printf("data: %s\n", searchedNode->data);
                // printf("--------\n22subString: 1.%s    2.%s\n---------\n", subString1[i], subString2[i]);
                // searchedNode->index = -1;
                // searchedNode->children = 2;

                // (*searchedNode).data[index] = '\0';
                // printf("xa22 i(%d) idx(%d): %s\n", i, idx, root->branches[0]->data);
            }
            else
            {
                index = StringCmp(searchedNode->data, text + i);
                printf("--happened--\n");
                searchedNode->branches[(searchedNode->children)] = createNode(text + i + index, 0, i);
                (searchedNode->children)++;
            }
        }
    }
    printTree(root);
}
// void StringCpy(char *data, char *cpy)
// {
//     int length = strlen(cpy);
//     for (int i = 0; i < length; i++)
//     {
//         data[i] = cpy[i];
//     }
//     data[length] = '\0';
// }

int main()
{
    // char *tmp = "ssssss";
    char *text = "xaxaxaxa$";
    // char *data = "ss";
    // strcpy(&data, &text);
    // printf("data: %s\n", data);
    // printf("text: %s\n", text);
    // strcpy(&text, &tmp);
    // printf("data: %s\n", data);
    // printf("text: %s\n", text);
    // char subString1[20], subString2[20];
    // subString(text, subString1, subString2, 2);
    // printf("1.%s 2.%s", subString1,subString2);
    // customTree();
    // struct Student *s = (struct Student *)malloc(sizeof(struct Student));
    // s->name = malloc(sizeof(char) * 20);
    // s->name = text;
    // (*s).name = 'q';
    // printf("%s", s->name);

    BuildSuffixTree(text);

    return 0;
}
