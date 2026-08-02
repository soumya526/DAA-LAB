#include<stdio.h>

int binarysearch(int arr[],int key,int n){
    int st=0;
    int end=n-1;
    while(st<end){
        int mid=st+(end-st)/2;
        if(arr[mid]==key) return 1;
        if(arr[mid]>key){
            end=mid-1;
        }
        if(arr[mid]<key){
            st=mid+1;
        }
    }
    return 0;
}

int main(){
    int arr[6];
    for(int i=0;i<6;i++){
        printf("Enter %d th index:\n",i);
        scanf("%d",&arr[i]);
    }
    int key;
    printf("Enter key u want to find:\n");
    scanf("%d",&key);
    if(binarysearch(arr,key,6)==0){
        printf("Element not found\n");
    }
    else{
        printf("Element Found\n");
    }
    return 0;
}