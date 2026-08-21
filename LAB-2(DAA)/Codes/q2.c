#include <stdio.h>
#include <math.h>

int main()
{
    FILE *fp;

    fp = fopen("merge_growth.csv","w");

    if(fp==NULL)
    {
        printf("Error creating file.\n");
        return 1;
    }

    fprintf(fp,"n,MergeSort,ModifiedMergeSort\n");

    for(int n=100;n<=1000;n+=100)
    {
        double mergeSort;
        double modifiedMergeSort;

        /* Merge Sort : n log2 n */
        mergeSort = n * log2(n);

        /* Modified Merge Sort :
           same complexity but multiplied by 1.3
           only to separate the curves */
        modifiedMergeSort = 1.3 * n * log3(n);

        fprintf(fp,"%d,%.2lf,%.2lf\n",
                n,
                mergeSort,
                modifiedMergeSort);
    }

    fclose(fp);

    printf("merge_growth.csv created successfully.\n");

    return 0;
}