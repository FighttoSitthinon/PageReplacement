#include <stdio.h>
struct Frame
{
    int page;
    int count;
};
int page[20];
int FIFO();
int OPT();
int LRU();
int main()
{
    int key;
    printf("\n\nWelcome to page replacement program...\n");
    printf("Please input number 20 page...\n");
    for (int i = 0; i < 20; i++)
    {
        scanf("%d", &page[i]);
    }
    printf("\nYou input : ");
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", page[i]);
    }
    printf("\nPlease select menu...\n");
    printf("1. FIFO\n2. OPT\n3. LRU\n4. Exit Program\n");
    printf("Please input key to continue...\n>>>");
    scanf("%d", &key);
    printf("%d", key);
    while (key != 4)
    {
        switch (key)
        {
        case 1:
            FIFO();
            break;
        case 2:
            OPT();
            break;
        case 3:
            LRU();
            break;
        }
    }
    return 0;
}
int FIFO()
{
    int n = 0;
    printf("\n\nPlease input number of frame...\n>>>");
    scanf("%d", &n);
    struct Frame frame[n];

    return 0;
}
int OPT(){

}
int LRU(){
    
}