#include<stdio.h>

int linearsearch(int arr[],int n,int key){
    for(int i=0;i<n;i++){
        if(arr[i]==key){
            return i;
        }
    }
    return -1;
}

int main(){
    int arr[6];
    for(int i=0;i<6;i++){
        printf("Enter %d th index:\n",i);
        scanf("%d",&arr[i]);
    }
    int a;
    printf("Enter the no u want to search in array:\n");
    scanf("%d",&a);
    int ans;
    ans=linearsearch(arr,6,a);
    printf("The index is %d\n",ans);
    return 0;
}