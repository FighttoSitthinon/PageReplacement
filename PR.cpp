#include <stdio.h>
#include <stdbool.h>
struct Frame
{
    int page;
    int count;     //เอาไว้ใช้กับ FIFO
    int nextIndex; //เอาไว้ใช้กับ OPT
    int pastIndex; //เอาไว้ใช้กับ LRU
};
int page[20];
bool isvalueinarray(int val, Frame frame[], int size);
int max(Frame frame[], int size, int key);
int min(Frame frame[], int size, int key);
int searchNextIndex(int Nframe, int nowIndex);
int searchPastIndex(int Nframe, int nowIndex);
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
    while (key != 4)
    {
        printf("\nPlease select menu...\n");
        printf("1. FIFO\n2. OPT\n3. LRU\n4. Exit Program\n");
        printf("Please input key to continue...\n>>>");
        scanf("%d", &key);
        printf("%d", key);
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
    int pf = 0;
    printf("\n\nPlease input number of frame...\n>>>");
    scanf("%d", &n);
    struct Frame frame[n];
    for (int e = 0; e < n; e++)
    {
        frame[e].page = -1;
        frame[e].count = 0;
    }
    for (int i = 0; i < 20; i++)
    {
        if (isvalueinarray(page[i], frame, n) != 1) // 0 == false, 1 == true เช็คว่าค่าซ้ำไหม? ถ้าซ้ำจะไม่ทำ
        {
            if (isvalueinarray(-1, frame, n) == 1) //check -1 in frame page เช็คว่าใน frame มีค่าว่างแรกเริ่มไหม?
            {
                for (int e = 0; e < n; e++)
                {
                    if (frame[e].page == -1)
                    {
                        frame[e].page = page[i];
                        frame[e].count++;
                        pf++;
                        break;
                    }
                    else
                    {
                        frame[e].count++;
                    }
                }
            }
            else
            {
                for (int e = 0; e < n; e++)
                {
                    if (max(frame, n, 1) != e)
                    { //เพิ่มการนับหน้าที่ไม่ถูกเรียก
                        frame[e].count++;
                    }
                }
                frame[max(frame, n, 1)].page = page[i];
                frame[max(frame, n, 1)].count = 1;
                pf++;
            }
        }
        else
        { // กรณีที่เรียกหน้าซ้ำ เพิ่มการนับเวลาทุก frame
            for (int e = 0; e < n; e++)
            {
                frame[e].count++;
            }
        }
        printf("\nInput page : %d\n", page[i]);
        for (int e = 0; e < n; e++)
        {
            if (frame[e].page == -1)
            {
                printf("\nAddress : [%p] | Value : [ ] | Time : [%d]\n", &frame[e].page, frame[e].count);
            }
            else
            {
                printf("\nAddress : [%p] | Value : [%d] | Time : [%d]\n", &frame[e].page, frame[e].page, frame[e].count);
            }
        }
        printf("\n=========================================\n");
        printf("\n Page fault (FIFO) : %d\n", pf);
        printf("\n=========================================\n");
    }
    return 0;
}
int OPT()
{
    int n = 0;
    int pf = 0;
    printf("\n\nPlease input number of frame...\n>>>");
    scanf("%d", &n);
    struct Frame frame[n];
    for (int e = 0; e < n; e++)
    {
        frame[e].page = -1;
        frame[e].nextIndex = 0;
    }
    for (int i = 0; i < 20; i++)
    {
        if (isvalueinarray(page[i], frame, n) != 1) // 0 == false, 1 == true เช็คว่าค่าซ้ำไหม? ถ้าซ้ำจะไม่ทำ
        {
            if (isvalueinarray(-1, frame, n) == 1) //check -1 in frame page เช็คว่าใน frame มีค่าว่างแรกเริ่มไหม?
            {
                for (int e = 0; e < n; e++)
                {
                    if (frame[e].page == -1)
                    {
                        frame[e].page = page[i];
                        frame[e].nextIndex = searchNextIndex(frame[e].page, i);
                        pf++;
                        break;
                    }
                    else
                    {
                        frame[e].nextIndex = searchNextIndex(frame[e].page, i);
                    }
                }
            }
            else
            {
                if (frame[min(frame, n, 1)].nextIndex == 0)
                {
                    frame[min(frame, n, 1)].page = page[i];
                    frame[min(frame, n, 1)].nextIndex = searchNextIndex(frame[min(frame, n, 1)].page, i);
                }
                else
                {
                    frame[max(frame, n, 2)].page = page[i];
                    frame[max(frame, n, 2)].nextIndex = searchNextIndex(frame[max(frame, n, 2)].page, i);
                }
                pf++;
            }
        }
        else
        {
            for (int e = 0; e < n; e++)
            {
                frame[e].nextIndex = searchNextIndex(frame[e].page, i);
            }
        }
        printf("\nInput page : %d\n", page[i]);
        for (int e = 0; e < n; e++)
        {
            if (frame[e].page == -1)
            {
                printf("\nAddress : [%p] | Value : [ ] | Next index : [ ]\n", &frame[e].page);
            }
            else
            {
                printf("\nAddress : [%p] | Value : [%d] | Next index : [%d]\n", &frame[e].page, frame[e].page, frame[e].nextIndex);
            }
        }
        printf("\n=========================================\n");
        printf("\n Page fault (OPT) : %d\n", pf);
        printf("\n=========================================\n");
    }
    return 0;
}
int LRU()
{
    int n = 0;
    int pf = 0;
    printf("\n\nPlease input number of frame...\n>>>");
    scanf("%d", &n);
    struct Frame frame[n];
    for (int e = 0; e < n; e++)
    {
        frame[e].page = -1;
        frame[e].pastIndex = 0;
    }
    for (int i = 0; i < 20; i++)
    {
        if (isvalueinarray(page[i], frame, n) != 1) // 0 == false, 1 == true เช็คว่าค่าซ้ำไหม? ถ้าซ้ำจะไม่ทำ
        {
            if (isvalueinarray(-1, frame, n) == 1) //check -1 in frame page เช็คว่าใน frame มีค่าว่างแรกเริ่มไหม?
            {
                for (int e = 0; e < n; e++)
                {
                    if (frame[e].page == -1)
                    {
                        frame[e].page = page[i];
                        frame[e].pastIndex = i;
                        pf++;
                        break;
                    }
                    else
                    {
                        frame[e].pastIndex = searchPastIndex(frame[e].page, i);
                    }
                }
            }
            else
            {
                frame[min(frame, n, 2)].page = page[i];
                frame[min(frame, n, 2)].pastIndex = searchPastIndex(frame[min(frame, n, 2)].page, i);
                pf++;
            }
        }
        else
        {
            for (int e = 0; e < n; e++)
            {
                frame[e].pastIndex = searchPastIndex(frame[e].page, i);
            }
        }
        printf("\nInput page : %d\n", page[i]);
        for (int e = 0; e < n; e++)
        {
            if (frame[e].page == -1)
            {
                printf("\nAddress : [%p] | Value : [ ] | Nearest past index : [ ]\n", &frame[e].page);
            }
            else
            {
                printf("\nAddress : [%p] | Value : [%d] | Nearest past index : [%d]\n", &frame[e].page, frame[e].page, frame[e].pastIndex);
            }
        }
        printf("\n=========================================\n");
        printf("\n Page fault (LRU) : %d\n", pf);
        printf("\n=========================================\n");
    }
    return 0;
}
bool isvalueinarray(int val, Frame frame[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (frame[i].page == val)
            return true;
    }
    return false;
}
int max(Frame frame[], int size, int key)
{
    int index = 0;
    if (key == 1) //เรียกใช้ FIFO
    {
        int max = frame[index].count;
        for (int i = 0; i < size; i++)
        {
            if (frame[i].count > max)
            {
                max = frame[i].count;
                index = i;
            }
        }
    }
    else if (key == 2) //เรียกใช้ OPT
    {
        int max = frame[index].nextIndex;
        for (int i = 0; i < size; i++)
        {
            if (frame[i].nextIndex > max)
            {
                max = frame[i].nextIndex;
                index = i;
            }
        }
    }
    return index;
}
int min(Frame frame[], int size, int key)
{
    int index = 0;
    if (key == 1) //ใช้กับ OPT
    {
        int min = frame[index].nextIndex;
        for (int i = 0; i < size; i++)
        {
            if (frame[i].nextIndex < min)
            {
                min = frame[i].nextIndex;
                index = i;
            }
        }
    }
    else if (key == 2) // ใช้กับ LRU
    {
        int min = frame[index].pastIndex;
        for (int i = 0; i < size; i++)
        {
            if (frame[i].pastIndex < min)
            {
                min = frame[i].pastIndex;
                index = i;
            }
        }
    }

    return index;
}
int searchNextIndex(int Nframe, int nowIndex)
{
    int index = 0;
    for (int i = nowIndex + 1; i < 20; i++)
    {
        if (Nframe == page[i])
        {
            index = i; //ถ้ามีการเรียกใช้ในอนาคต
            break;
        }
    }
    return index;
}
int searchPastIndex(int Nframe, int nowIndex)
{
    int index = 0;
    for (int i = nowIndex; i > 0; i--)
    {
        if (Nframe == page[i])
        {
            index = i; //หาตัวที่เรียกใช้ก่อนชาวบ้านใน frame และเป็นตัวที่ใกล้ที่สุด
            break;
        }
    }
    return index;
}
//compile gcc -o PR PR.cpp
//run PR
//Input  2 7 4 0 5 5 3 6 6 5 3 1 5 2 3 0 7 0 1 2