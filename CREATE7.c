#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char itemName[64];
    char simpleName[16];
    int currQuantity;
    int maxQuantity;
    char body[128];
} Item;

int main() {
	FILE *data;
	char buf[256];
	Item temp, NullCheck;
	int n, itemNum, i;
	temp.maxQuantity = 0;

	data = fopen("inventory.dat", "rb+");
	if(data == NULL)
		data = fopen("inventory.dat", "wb+");

	printf("Enter an item number: ");
	scanf("%d", &itemNum);

	printf("Enter a simple name: ");
	scanf("%s", temp.simpleName);

	printf("Enter an item name: ");
	scanf("\n%[^\n]", temp.itemName);

	printf("Enter the current quantity: ");
	scanf("%d", &temp.currQuantity);

	printf("Enter the max quantity: ");
	scanf("%d", &temp.maxQuantity);

	printf("Enter the description: ");
	scanf("\n%[^\n]", temp.body);

	fseek(data, itemNum * sizeof(Item), SEEK_SET);
	n = fread(&NullCheck, sizeof(Item), 1L, data);
	if(n == 1 && temp.maxQuantity != 0)
		printf("ERROR: item already exists\n");
	else {
		fwrite(&temp, sizeof(Item), 1L, data);
	}

	fclose(data);
	return 0;
}