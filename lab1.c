#include <stdio.h>
#include <stdlib.h>

int max(int arr[100],int j)
{
	int abs_max=0;
	for (int i=0;i<j;i++)
	{
		if(abs(arr[i])>abs(abs_max)) abs_max=arr[i];
	}
	return abs_max;
};

int min(int arr[100],int j)
{
	int abs_min=arr[0];
	for (int i=0;i<j;i++)
	{
		if(abs(arr[i])<abs(abs_min)) abs_min=arr[i];
	}
	return abs_min;	
};

long diff(int arr[100],int j)
{
	long diff = max(arr,j)- min(arr,j);
	return diff; 
};

long sum(int arr[100],int j){
	long sum = 0,a = max(arr,j),z=0;
	for (int i=0;i<j;i++)
	{
		if(arr[i]==a) z=1;
        if(z == 1)sum+=arr[i]; 
    }
	return sum;
};


int main() {
	int i=0,arr[100],choice;
	scanf("%d",&choice);
		
	while(scanf("%d",&arr[i])>0){
        i++;
	}

	switch(choice) {
		case 0:
			printf("%d\n",max(arr,i));
			break;
		case 1:
			printf("%d\n",min(arr,i));
			break;
		case 2:
			printf("%ld\n",diff(arr,i));
			break;
		case 3:
			printf("%ld\n",sum(arr,i));
			break;
		default:
			printf("Данные некорректны\n");
			break;
		}
		return 0;
   }
