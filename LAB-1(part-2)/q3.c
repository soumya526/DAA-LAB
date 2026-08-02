#include<stdio.h>

void merge(int arr1[],int arr2[],int n1,int n2){
    int st1=0;
    int end1=n1;
    int st2=0;
    int end2=n2;
    int n=n1+n2-1;
    int arr3[n];
    int k=0;
    while(st1<end1 && st2<end2){
        if(arr1[st1]>arr2[st2]){
            arr3[k]=arr2[st2];
            st2++;
            k++;
        }
        else{
            arr3[k]=arr1[st1];
            st1++;
            k++;
        }
    }
    while(st1<end1){
        arr3[k]=arr1[st1];
        st1++;
        k++;
    }
    while(st2<end2){
        arr3[k]=arr2[st2];
        st2++;
        k++;
    }
    for(int i=0;i<k;i++){
        printf("%d\n",arr3[i]);
    }
}
int main(){
    int arr1[4];
    int arr2[4];
    for(int i=0;i<4;i++){
        printf("Enter %d th index for arr1:\n",i);
        scanf("%d",&arr1[i]);
    }
    for(int i=0;i<4;i++){
        printf("Enter %d th index for arr2:\n",i);
        scanf("%d",&arr2[i]);
    }
    merge(arr1,arr2,4,4);
    return 0;
}