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
	char c;
	Item temp, NullCheck;
	int n, itemNum, i;
	int iName, sName, cQ, mQ, b;

	data = fopen("inventory.dat", "rb+");
	if(data == NULL)
		data = fopen("inventory.dat", "wb+");

	printf("Enter an item number: ");
	fgets(buf, 256, stdin);
	sscanf(buf, "%d", &itemNum);

	printf("Enter a simple name: ");
	fgets(buf, 256, stdin);
	sName = sscanf(buf, "%s", temp.simpleName);
	if(sName == EOF)
		printf("SIMPLE NAME %s IS WORKING\n", temp.simpleName);

	printf("Enter an item name: ");
	fgets(buf, 256, stdin);
	iName = sscanf(buf, "%[^\n]", temp.itemName);
	if(iName == EOF || iName == 0)
		printf("ITEM NAME %s IS WORKING\n", temp.itemName);

	printf("Enter the current quantity: ");
	fgets(buf, 256, stdin);
	cQ = sscanf(buf, "%d", &temp.currQuantity);
	if(cQ == EOF)
		printf("CURR Q %d IS WORKING\n", temp.currQuantity);

	printf("Enter the max quantity: ");
	fgets(buf, 256, stdin);
	mQ = sscanf(buf, "%d%c", &temp.maxQuantity, &c);
	if(mQ == EOF)
		printf("MAX Q %d IS WORKING\n", temp.maxQuantity);

	printf("Enter the description: ");
	fgets(buf, 256, stdin);
	b = sscanf(buf, "%[^\n]", temp.body);
	if(b == EOF || b == 0)
		printf("BODY %s IS WORKING\n", temp.body);

	fseek(data, itemNum * sizeof(Item), SEEK_SET);
	n = fread(&NullCheck, sizeof(Item), 1L, data);

	if(n != 1 || temp.maxQuantity == 0)
		printf("ERROR: item not found\n");
	else {
		fseek(data, itemNum * sizeof(Item), SEEK_SET);
		if(sName != EOF)
			sscanf(temp.simpleName, "%s", NullCheck.simpleName);
		if(iName != EOF || iName != 0)
			sscanf(temp.itemName, "%[^\n]", NullCheck.itemName);
		if(cQ != EOF)
			NullCheck.currQuantity = temp.currQuantity;
		if(mQ != EOF)
			NullCheck.maxQuantity = temp.maxQuantity;
		if(b != EOF || b != 0)
			sscanf(temp.body, "%[^\n]", NullCheck.body);
		fwrite(&NullCheck, sizeof(Item), 1L, data);
	}
	fclose(data);
	return 0;
}