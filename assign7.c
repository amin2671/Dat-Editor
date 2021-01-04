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
	char buf[255];
	char c, choice;
	Item temp, NullCheck;
	int n, itemNum, i;
	int iName, sName, cQ, mQ, b;

	data = fopen("inventory.dat", "rb+");
	if(data == NULL)
		data = fopen("inventory.dat", "wb+");

	while(1) {
		temp.maxQuantity = 0;
		printf("Enter one of the following actions or press CTRL-D to exit.\nC - create a new item\nR - read an existing item\nU - update an existing item\nD - delete an existing item\n");

		i = scanf("%c", &choice);
		if(i == EOF)
			break;
		choice = toupper(choice);
		/*if(choice != 'C' || choice != 'R' || choice != 'U' || choice != 'D') {
			printf("ERROR: invalid option\n");
			continue;
		}*/
		if(choice == 'C') {
			printf("Enter an item number: ");
			scanf("%d", &itemNum);
			getchar();

			fseek(data, itemNum * sizeof(Item), SEEK_SET);
			n = fread(&NullCheck, sizeof(Item), 1L, data);
			if(n == 1 && NullCheck.maxQuantity != 0) {
				printf("ERROR: item already exists\n");
				continue;
			}

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
			getchar();

			fseek(data, itemNum * sizeof(Item), SEEK_SET);
			fwrite(&temp, sizeof(Item), 1L, data);
		} else if(choice == 'R') {
			printf("Enter an item number: ");
			scanf("%d", &itemNum);
			getchar();

			fseek(data, itemNum * sizeof(Item), SEEK_SET);
			n = fread(&temp, sizeof(Item), 1L, data);
			if(n != 1 || temp.maxQuantity == 0)
				printf("ERROR: item not found\n");
			else
				printf("Item name: %s\nSimple name: %s\nItem Number: %d\nQty: %d/%d\nDescription: %s\n", 
					temp.itemName,
					temp.simpleName,
					itemNum,
					temp.currQuantity,
					temp.maxQuantity,
					temp.body);
		} else if(choice == 'U') {
			printf("Enter an item number: ");
			//fgets(buf, 256, stdin);
			scanf("%d", &itemNum);
			getchar();
			
			fseek(data, itemNum * sizeof(Item), SEEK_SET);
			n = fread(&NullCheck, sizeof(Item), 1L, data);
			if(n != 1 || NullCheck.maxQuantity == 0) {
				printf("ERROR: item not found\n");
				continue;
			}
			printf("Enter a simple name: ");
			fgets(buf, 256, stdin);
			sName = sscanf(buf, "%s", temp.simpleName);

			printf("Enter an item name: ");
			fgets(buf, 256, stdin);
			iName = sscanf(buf, "%[^\n]", temp.itemName);

			printf("Enter the current quantity: ");
			fgets(buf, 256, stdin);
			cQ = sscanf(buf, "%d", &temp.currQuantity);

			printf("Enter the max quantity: ");
			fgets(buf, 256, stdin);
			mQ = sscanf(buf, "%d%c", &temp.maxQuantity, &c);

			printf("Enter the description: ");
			fgets(buf, 256, stdin);
			b = sscanf(buf, "%[^\n]", temp.body);

			fseek(data, itemNum * sizeof(Item), SEEK_SET);
			n = fread(&NullCheck, sizeof(Item), 1L, data);

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
		} else if(choice == 'D') {
			printf("Enter an item number: ");
			scanf("%d", &itemNum);
			getchar();

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
		} else if(choice != 'C' && choice != 'R' && choice != 'U' && choice != 'D') {
			printf("ERROR: invalid option\n");
			continue;
		}

	}

	fclose(data);
	return 0;
}