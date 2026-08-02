#include<stdio.h>
int ans[2];
void linearsearch(int arr[3][3],int key){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(arr[i][j]==key){
                ans[0]=i;
                ans[1]=j;
            }
        }
    }
}

int main(){
    int arr[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            printf("Enter the element in %d %d\n ",i,j);
            scanf("%d",&arr[i][j]);
        }
    }
    int key;
    printf("Enter the element u want ot search\n");
    scanf("%d",&key);
    linearsearch(arr,key);
    printf("The element found at index %d %d index\n",ans[0],ans[1]);
    return 0;
}