#include <stdio.h>
#include <math.h>

void createCSV(char filename[], int type)
{
    FILE *fp = fopen(filename, "w");

    if(fp == NULL)
    {
        printf("Error creating file %s\n", filename);
        return;
    }

    fprintf(fp,"n,Search,Insert,Delete,Maximum,Minimum,Predecessor,Successor\n");

    for(int n=100;n<=1000;n+=100)
    {
        double search, insert, del, max, min, pre, suc;

        switch(type)
        {
        //==========================
        // 1. Unsorted Array
        //==========================
        case 1:
            search = 10*n;        // O(n)
            insert = 1;           // O(1)
            del = 20*n;           // O(n)
            max = 30*n;           // O(n)
            min = 40*n;           // O(n)
            pre = 50*n;           // O(n)
            suc = 60*n;           // O(n)
            break;

        //==========================
        // 2. Sorted Array
        //==========================
        case 2:
            search = 10*log2(n);  // O(log n)
            insert = 20*n;        // O(n)
            del = 30*n;           // O(n)
            max = 1;              // O(1)
            min = 2;              // O(1)
            pre = 3;              // O(1)
            suc = 4;              // O(1)
            break;

        //==========================
        // 3. Singly Unsorted List
        //==========================
        case 3:
            search = 10*n;
            insert = 2;
            del = 20*n;
            max = 30*n;
            min = 40*n;
            pre = 50*n;
            suc = 60*n;
            break;

        //==========================
        // 4. Singly Sorted List
        //==========================
        case 4:
            search = 10*n;
            insert = 20*n;
            del = 30*n;
            max = 40*n;
            min = 1;
            pre = 50*n;
            suc = 60*n;
            break;

        //==========================
        // 5. Doubly Unsorted List
        //==========================
        case 5:
            search = 10*n;
            insert = 3;
            del = 20*n;
            max = 30*n;
            min = 40*n;
            pre = 50*n;
            suc = 60*n;
            break;

        //==========================
        // 6. Doubly Sorted List
        //==========================
        case 6:
            search = 10*n;
            insert = 20*n;
            del = 30*n;
            max = 1;
            min = 2;
            pre = 3;
            suc = 4;
            break;
        }

        fprintf(fp,"%d,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf,%.2lf\n",
                n,search,insert,del,max,min,pre,suc);
    }

    fclose(fp);
}

int main()
{
    createCSV("unsorted_array.csv",1);
    createCSV("sorted_array.csv",2);
    createCSV("singly_unsorted.csv",3);
    createCSV("singly_sorted.csv",4);
    createCSV("doubly_unsorted.csv",5);
    createCSV("doubly_sorted.csv",6);

    printf("All CSV files generated successfully.\n");

    return 0;
}