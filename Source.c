#include "header.h"

int main()
{
	char fileName[12] = { "student.csv" };
	char* strArr[4] = { "select","set","quit","print" };
	struct List list = createNewList();
	struct List* Plist = &list;
	char* str = NULL, * token;
	copyFileToStruct(Plist, fileName);
	struct student* s = list.head;
	printTitle();
	for (size_t i = 0; i < list.size; i++)
	{
		printStruct(s);
		s = s->next;
	}
	s = list.head;
	while (1)
	{
		s = list.head;
		printf("\nEnter a query -->  ");
		str = takeLineFromUser();
		while (str == NULL)
		{
			printf("\nEnter a query -->  ");
			str = takeLineFromUser();
		}
		changStrinToLower(str);
		str = deleteSpace(str);
		while (*str == ' ')str++;
		token = strtok(str, " ");
		bool check = false;
		if (strcmp(token, strArr[3]) == 0)
		{
			printTitle();
			for (size_t i = 0; i < list.size; i++)
			{
				printStruct(s);
				s = s->next;
			}
			check = true;
		}
		else if (!strcmp(token, strArr[2]))
		{
			printf("Program end. good bye");
			break;
		}
		else if (!check)
		{
			for (size_t i = 0; i < 2; i++)
			{

				if (!strcmp(token, strArr[1]))
				{
					check = true;
					mainSetFunck(str, Plist);
					break;
				}
				if (!strcmp(token, strArr[0]))
				{
					check = true;
					if (!mainSelectFunck(str, list))
						printf("You entered incorrect data, please try again\n");
					break;
				}
			}
		}
		if (!check)
			printf("You entered incorrect data, please try again\n");
	}
	free(str);
	freeList(list);
	return 0;
}








