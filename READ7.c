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

	data = fopen("inventory.dat", "rb+");
	if(data == NULL)
		data = fopen("inventory.dat", "wb+");

	printf("Enter an item number: ");
	scanf("%d", &itemNum);

	fseek(data, itemNum * sizeof(Item), SEEK_SET);
	n = fread(&temp, sizeof(Item), 1L, data);
	if(n != 1 || temp.maxQuantity == 0)
		printf("ERROR: item not found\n");
	else {
		printf("Item name: %s\nSimple name: %s\nItem Number: %d\nQty: %d/%d\nDescription: %s\n", 
			temp.itemName,
			temp.simpleName,
			itemNum,
			temp.currQuantity,
			temp.maxQuantity,
			temp.body);	
	}


	return 0;
}