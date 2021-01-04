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
		fseek(data, itemNum * sizeof(Item), SEEK_SET);
		printf("%s was successfully deleted.\n", temp.simpleName);
		temp.itemName[0] = '\0';
		temp.simpleName[0] = '\0';
		temp.currQuantity = 0;
		temp.maxQuantity = 0;
		temp.body[0] = '\0';
		fwrite(&temp, sizeof(Item), 1L, data);
	}

	fclose(data);
	return 0;
}