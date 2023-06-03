#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node
{
    int userID;
    int itemID;
    float ratingValue;  // 1 to 5
    struct Node* next;
} Node;

Node* head = NULL;

void insert (int userID, int itemID, float ratingValue)
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode-> userID = userID;
    newNode-> itemID = itemID;
    newNode-> ratingValue = ratingValue;
    newNode-> next = head;

    Node* curr = head;
    while (curr)
    {
        if (curr->userID == userID && curr->itemID == itemID)
        {
            curr->ratingValue = ratingValue;
            printf("Customer rating (%d, %d) is updated\n", userID, itemID);
            return;
        }
        curr = curr->next;
    }

    newNode->next = head;
    head = newNode;
    printf("Customer rating (%d, %d) is added successful\n", userID, itemID);

}

void removeRating(int userID, int itemID)
{
    Node* curr = head;
    Node* prev = NULL;
    while (curr)
    {
        if (curr->userID == userID && curr->itemID == itemID)
        {
            if (prev)
            {
                prev->next = curr->next;
            }
            else
            {
                head = curr->next;
            }
            free(curr);
            printf("Customer rating (%d, %d) is removed successful\n", userID, itemID);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Customer rating (%d, %d) does not exist\n", userID, itemID);
}

void rating(int userID, int itemID)
{
    Node* curr = head;
    while (curr)
    {
        if (curr->userID == userID && curr->itemID == itemID)
        {
            printf("Customer rating (%d, %d) is: %.1f\n", userID, itemID, curr->ratingValue);
            return;
        }
        curr = curr->next;
    }
    printf("Customer rating (%d, %d) is: 0.0\n", userID, itemID);
}

void average(int itemID)
{
    Node* curr = head;
    float sum = 0.0;
    int count = 0;
    while (curr)
    {
        if (curr->itemID == itemID)
        {
            sum += curr->ratingValue;
            count++;
        }
        curr = curr->next;
    }
    if (count > 0)
    {
        printf("Average rating (%d) is: %.1f\n", itemID, sum / count);
    }
    else
    {
        printf("Average rating (%d) is: 0.0\n", itemID);
    }
}

int main(int argc, char const *argv[])
{
    char operation[10];
    int userID, itemID;
    float ratingValue;

    while (scanf("%s", operation) == 1) {
        if (strcmp(operation, "INSERT") == 0) {
            scanf("%d%d%f", &userID, &itemID, &ratingValue);
            insert(userID, itemID, ratingValue);
        } else if (strcmp(operation, "REMOVE") == 0) {
            scanf("%d%d", &userID, &itemID);
            removeRating(userID, itemID);
        } else if (strcmp(operation, "RATING") == 0) {
            scanf("%d%d", &userID, &itemID);
            rating(userID, itemID);
        }else if(strcmp(operation, "AVERAGE")== 0){
            scanf("%d", &itemID);
            average(itemID);
        }
    }
    return 0;
}
