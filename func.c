#include "header.h"


char* takeLineFromUser()
{
	char* input = NULL, * realTemp;
	char bufer[CHANK];
	int length = 0, tmp = 0;
	do
	{
		fgets(bufer, CHANK, stdin);
		tmp = strlen(bufer);
		realTemp = realloc(input, tmp + length + 1);
		input = realTemp;
		if (input == NULL)
		{
			printf("Allocation faild\n Try again\n");
			return input;
		}
		strcpy(input + length, bufer);
		length += tmp;

	} while (tmp == CHANK - 1 && bufer[CHANK - 2] != '\n');
	return input;
}
void changStrinToLower(char* str)
{
	char* ptr = str;
	while (*ptr)
	{
		if (*ptr >= 'A' && *ptr <= 'Z')
			*ptr = tolower(*ptr);
		ptr++;
	}
}
void fixNameString(char* str)
{
	char* startStr = str;
	*str = toupper(*str);
	str++;
	while (*str)
	{
		if (*str == ' ')
		{
			str++;
			*str = toupper(*str);
			str++;
		}
		*str = tolower(*str);
		str++;
	}
}
char* fixCourseName(char* course)
{
	int i = 0;
	char* courseArr[3] = { "c language", "computer networks", "cs fundamentals" };
	char* validCourseName[3] = { "C Language", "Computer Networks", "CS Fundamentals" };
	int j = strcmp(course, courseArr[i]);
	while (i <= 2 && strcmp(course, courseArr[i]))
		i++;
	if (i > 2)
	{
		return NULL;
	}
	strcpy(course, validCourseName[i]);
	return course;
}
void mainSetFunck(char* str, struct List* list)
{
	char* str1 = NULL, * realTmp = NULL;
	int tmp = 0, len = 0, i = 0;
	char* strArr[6] = { "first name", "second name", "id",
		"c language", "computer networks", "cs fundamentals" };
	char sign[2] = { "," };
	int lenOfStrArr = 6, cnt, length = 0;
	struct student* tmpStudent = (struct student*)calloc(sizeof(struct student), 1);
	if (tmpStudent == NULL)return 0;
	for (size_t i = 0; i < GRADES; i++)
	{
		tmpStudent->courseName[i] = NULL;
		tmpStudent->grades[i] = -1;
	}
	char* token = strtok(NULL, "\0");
	cnt = isCharExist(token, '=');
	if (cnt == 0)
	{
		printf("You did not enter a mark the required number of times");
		freeStruct(tmpStudent);
		return;
	}
	changStrinToLower(token);
	token = strtok(token, "=");
	token = deleteSpace(token);

	for (size_t i = 0; i < cnt; i++)
	{
		if (!token)
		{
			freeStruct(tmpStudent);
			//free(str1);
			printf("Wrong details\n");
			return;
		}
		if (strcmp(strArr[i], token) && i < 3) {
			printf("Wrong details\n");
			freeStruct(tmpStudent);
			//free(str1);
			return;
		}
		if (i == 3)
		{
			int j = i;
			while (j < lenOfStrArr)
			{
				if (!strcmp(strArr[j], token))
					break;
				j++;
			}
			if (j == lenOfStrArr)
			{
				printf("Wrong details\n");
				freeStruct(tmpStudent);
				//free(str1);
				return;
			}
		}
		if (i == 3)
		{
			tmp = strlen(token);
			realTmp = realloc(str1, tmp + len + 1);
			if (realTmp == NULL)
			{
				printf("Allocation faild\n Try again\n");
				freeStruct(tmpStudent);
				//free(str1);
				return;
			}
			str1 = realTmp;
			strcpy(str1 + len, token);
			str1 = deleteSpace(str1);
			len += tmp;
			strcpy(str1 + len, ",");
			len++;
		}

		token = strtok(NULL, ",");
		token = deleteSpace(token);
		tmp = strlen(token);
		realTmp = realloc(str1, tmp + len + 2);
		if (realTmp == NULL)
		{
			printf("Allocation faild\n Try again\n");
			freeStruct(tmpStudent);
			return;
		}
		str1 = realTmp;
		strcpy(str1 + len, token);
		len += tmp;
		strcpy(str1 + len, ",");
		len++;
		token = strtok(NULL, "=");
		if (token)
			token = deleteSpace(token);
	}
	str1[len - 1] = '\0';
	buildStruct(tmpStudent, str1, sign);
	int index = ifStructExist(list, tmpStudent->id);
	if (index == -1 && tmpStudent->isId == false)
	{
		printf("Invalid ID number\n");
		freeStruct(tmpStudent);
		return;
	}
	if (index == -1)
	{
		sortList(list, tmpStudent);
		list->size++;
		copyListToFile(list);
		printf("A new student has been successfully created\n");
		return;
	}
	struct student* s = returnPtrStruct(list, index);
	if (!isStructlegal(s, tmpStudent) && s->isName == true)
	{
		printf("Uncorrect detaild!\n");
		freeStruct(tmpStudent);
		return;
	}
	if (!s->isName && tmpStudent->isName)
	{
		strcpy(s->firstName, tmpStudent->firstName);
		s->isName = true;
		copyListToFile(list);
		printf("The name has been successfully corrected\n");
	}

	if (changeSecondName(s, tmpStudent))
	{
		freeStructFromList(s->id, list);
		sortList(list, s);
		printf("%s's last name has been successfully changed\n", s->firstName);
	}
	if (!tmpStudent->courseName[0])
	{
		copyListToFile(list);
		return;
	}
	updateGrade(s, tmpStudent);
	copyListToFile(list);
}

bool isStructValid(struct student* s)
{
	bool flag = false;
	char* ptr1 = s->firstName;
	char* ptr2 = s->lastName;
	while (*ptr1)
	{
		if ((*ptr1 < 'a' || *ptr1 > 'z') && (*ptr1 < 'A' || *ptr1 > 'Z') && *ptr1 != ' ')
			return flag;
		if (*ptr1 == ' ' && *(++ptr1) == ' ')
			return flag;
		ptr1++;
	}
	while (*ptr2)
	{
		if ((*ptr2 < 'a' || *ptr2 > 'z') && (*ptr2 < 'A' || *ptr2 > 'Z') && *ptr2 != ' ')
			return flag;
		if (*ptr2 == ' ' && *(++ptr2) == ' ')
			return flag;
		ptr2++;
	}
	return flag = true;
}

void updateGrade(struct student* s, struct student* tmp)
{
	for (size_t i = 0; i < GRADES; i++)
	{
		if (s->courseName[i] == NULL) {
			s->courseName[i] = malloc(strlen(tmp->courseName[0]) + 1);
			if (s->courseName[i] == NULL)
			{
				printf("Alocation faild\n");
				return;
			}
			strcpy(s->courseName[i], tmp->courseName[0]);
			s->grades[i] = tmp->grades[0];
			printf("%s's score has been updated\n", s->firstName);
			return;
		}
		if ((!strcmp(s->courseName[i], tmp->courseName[0])) &&
			(s->grades[i] != tmp->grades[i]))
		{
			s->grades[i] = tmp->grades[0];
			printf("%s's score has been updated\n", s->firstName);

			return;
		}
	}
	printf("No new score has been updated\n");
	return;
}
void freeStr(char* str, char* sArr[], int length)
{
	for (size_t i = 0; i < length; i++)
		free(sArr[i]);

	if (str)
		free(str);
}
struct student* returnPtrStruct(struct List* list, int index)
{
	struct student* s = list->head;
	for (size_t i = 0; i < index; i++)
	{
		s = s->next;
	}
	return s;
}
int isStructlegal(struct student* s, struct student* tmp)
{
	if (strcmp(tmp->firstName, s->firstName))
	{
		printf("You enterd a Wrong name\n");
		return 0;
	}
	return 1;
}
int changeSecondName(struct student* s, struct student* tmp)
{
	if (strcmp(tmp->lastName, s->lastName))
	{
		strcpy(s->lastName, tmp->lastName);
		return 1;
	}
	return 0;
}
void freeStructFromList(char* str, struct List* list)
{
	struct student* ptr = list->head;
	struct student* prev = list->head;
	ptr = ptr->next;
	if (strcmp(prev->id, str) == 0)
	{
		list->head = ptr;
		return;
	}
	while (strcmp(ptr->id, str))
	{
		ptr = ptr->next;
		prev = prev->next;
	}
	if (ptr->next)
		prev->next = ptr->next;
	else
	{
		prev->next = NULL;
		list->tail = prev;
	}
}

void copyListToFile(struct List* list)
{
	struct student* s = list->head;
	char c = '\n';
	FILE* fp = fopen("student.csv", "wt");
	if (fp == NULL)
	{
		printf("Alocation faild");
		exit(1);
	}
	for (size_t i = 0; i < list->size; i++)
	{
		bool flag = true;
		int j = 0;
		while (s->courseName[j] && j < GRADES)
		{
			flag = false;
			fprintf(fp, "%s,%s,%s,%s,%d\n", s->firstName, s->lastName, s->id, s->courseName[j], s->grades[j]);
			j++;
		}
		if (flag)
			fprintf(fp, "%s,%s,%s\n", s->firstName, s->lastName, s->id);
		s = s->next;
	}
	fclose(fp);
}
char* deleteSpace(char* str)
{
	while (*str == ' ')
		str++;
	char* p = str;
	while (*p) p++;
	p--;
	while (*p == ' ' || *p == '\n')
	{
		*p = '\0';
		p--;
	}

	return str;
}

bool isIdCorect(char* str)
{
	int cnt = 0, leangthId = 9;
	bool flag = true;
	char* ptr = str;
	while (ptr == ' ') ptr++;
	while (*ptr)
	{
		if (*ptr < '0' || *ptr > '9')
			return flag = false;
		ptr++;
		cnt++;
		if (cnt == leangthId && *ptr == ' ' || *ptr == '\n')
			*ptr = '\0';
	}
	if (cnt != leangthId)
		flag = false;
	return flag;

}
int isCharExist(char* s, char c)
{
	int cnt = 0;
	char* p = s;
	while (*p)
	{
		if (*p == c)
			cnt++;
		p++;
	}
	if (cnt != 3 && cnt != 4)
		return 0;
	return cnt;
}
char* returnStrAfterZero(char* str)
{
	while (*str)
		str++;
	str++;
	return str;
}
int mainSelectFunck(char* str, struct List list)
{
	char* strArr[5] = { "first name", "second name", "id",
	"c language computer networks cs fundamentals", "average" };
	char* token, * st;
	char signArr[] = "!<>=";
	int len = 4, lenOfStrArr = 5;
	str = returnStrAfterZero(str);
	char sign = findchar(str, signArr, len);
	if (sign == NULL)return 0;
	st = _strdup(strtok(NULL, signArr));
	if (st == NULL) {
		return 0;
	}
	st = deleteSpace(st);
	int index = selectCmp(st, strArr, lenOfStrArr);
	token = strtok(NULL, "\0");
	if (sign == '!')
		token++;
	token = deleteSpace(token);
	void(*fun_ptr_arr[])(struct List, char*, char*, char) = {
		serchAndPrintStructByFirstName, serchAndPrintStructBySecondName,
		serchAndPrintStructById,serchAndPrintStructByGread,
		serchAndPrintStructByAverage
	};
	if (index > -1)
	{
		(*fun_ptr_arr[index])(list, token, st, sign);
		return 1;
	}

	return 0;
}
int selectCmp(char* s1, char* s2[], int length)
{
	char* course[3] = { "c language","computer networks", "cs fundamentals" };
	for (size_t i = 0; i < length; i++)
	{
		if (!strcmp(s2[i], s1))
			return i;
		if (i == 3)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (!strcmp(course[j], s1))
					return i;
			}
		}
	}
	return -1;
}
void printTitle()
{
	printf("\n\n   |first name   |  second name   |     id     |C Language|CS Fundamentals|Computer Networks|Average|      comments    | \n");
	for (size_t i = 0; i < 140; i++)
	{
		printf("-");
	}
	printf("\n");
}
void printStruct(struct student* s)
{

	bool flag = false;
	char noGrade[3] = { "//" };
	char* course[3] = { "C Language","CS Fundamentals","Computer Networks" };
	int i = 0, j = 0, sum = 0, numOfCours = 0;
	printf("      %-13s %-16s %-15s", s->firstName, s->lastName, s->id);

	while (i < GRADES)
	{
		j = 0;
		while (j < GRADES)
		{
			if (!s->courseName[j])
			{
				printf("%-9s     ", noGrade);
				break;
			}
			else
			{
				if (!strcmp(course[i], s->courseName[j]))
				{
					printf("%-10d    ", s->grades[j]);
					sum += s->grades[j];
					flag = true;
					numOfCours++;
					break;
				}

			}
			j++;
		}
		i++;
	}
	if (flag)
	{
		s->avg = (float)sum / numOfCours;
		printf("%.1f", s->avg);
	}
	else
		printf("      ");
	if (s->isId == false)
	{
		printf("    Your ID is Invalid!!");
	}
	if (s->isName == false)
	{
		if (s->isId == false)
		{
			printf("\n");
			for (size_t i = 0; i < 98; i++)
			{
				printf(" ");
			}
		}
		printf("    Invalid first or last name");
	}
	printf("\n");
	for (size_t i = 0; i < 140; i++)
	{
		printf("-");
	}
	printf("\n\n");
}
void serchAndPrintStructByAverage(struct List list, char* str1, char* str2, char c)
{
	if (!isGradeValid(str1))
	{
		printf("Invalid grade");
		return;
	}
	float grade = atof(str1);
	bool flag = false, gate = true;
	struct student* s = list.head;
	for (size_t i = 0; i < list.size; i++) {

		if (c == '>' && s->avg > grade && s->courseName[0])
		{
			if (gate)
			{
				printTitle();
				gate = false;
			}
			printStruct(s);
			flag = true;
		}
		else if (c == '<' && s->avg < grade && s->courseName[0])
		{
			if (gate)
			{
				printTitle();
				gate = false;
			}
			printStruct(s);
			flag = true;
		}
		else if (c == '=' && s->avg == grade && s->courseName[0])
		{
			if (gate)
			{
				printTitle();
				gate = false;
			}
			printStruct(s);
			flag = true;
		}
		else if (c == '!' && s->avg != grade && s->courseName[0])
		{
			if (gate)
			{
				printTitle();
				gate = false;
			}
			printStruct(s);
			flag = true;
		}
		s = s->next;
	}
	if (!flag)
		printf("We dont heve a student with average %c %.1f\n", c, grade);
}

void serchAndPrintStructByGread(struct List list, char* str1, char* courseName, char c)
{
	courseName = fixCourseName(courseName);
	if (courseName == NULL) return;
	if (!isGradeValid(str1))
	{
		printf("Invalid grade");
		return;
	}
	int grade = atoi(str1);
	bool flag = false, check = true;
	struct student* s = list.head;
	for (size_t i = 0; i < list.size; i++)
	{
		bool gate = false;
		int j = 0;
		while (j < GRADES && s->courseName[j])
		{
			if (strcmp(s->courseName[j], courseName) == 0) {
				gate = true;
				if (c == '>' && s->grades[j] > grade)
				{
					if (check)
					{
						printTitle();
						check = false;
					}
					printStruct(s);
					flag = true;
					break;
				}
				else if (c == '<' && s->grades[j] < grade)
				{
					if (check)
					{
						printTitle();
						check = false;
					}
					printStruct(s);
					flag = true;
					break;
				}
				else if (c == '=' && s->grades[j] == grade)
				{
					if (check)
					{
						printTitle();
						check = false;
					}
					printStruct(s);
					flag = true;
					break;
				}
				else if (c == '!' && s->grades[j] != grade)
				{
					if (check)
					{
						printTitle();
						check = false;
					}
					printStruct(s);
					flag = true;
					break;
				}
			}
			if (gate) break;
			j++;
		}
		s = s->next;
	}
	if (!flag)
		printf("We dont heve a student with a grade in %s %c %d\n", courseName, c, grade);
}
void serchAndPrintStructById(struct List list, char* str1, char* str2, char c)
{
	bool flag = false, gate = true;
	struct student* s = list.head;
	for (int i = 0; i < list.size; i++)
	{
		if (c == '=')
		{
			if (!strcmp(s->id, str1))
			{
				if (gate)
				{
					printTitle();
					gate = false;
				}
				flag = true;
				printStruct(s);
			}
		}
		else if (c == '<')
		{
			if (strcmp(s->id, str1) < 0)
			{
				if (gate)
				{
					printTitle();
					gate = false;
				}
				flag = true;
				printStruct(s);
			}
		}
		else if (c == '>') {
			if (strcmp(s->id, str1) > 0)
			{
				if (gate)
				{
					printTitle();
					gate = false;
				}
				flag = true;
				printStruct(s);
			}
			else if (c == '!')
			{
				if (strcmp(s->id, str1))
				{
					if (gate)
					{
						printTitle();
						gate = false;
					}
					flag = true;
					printStruct(s);
				}
			}
		}
		s = s->next;
	}
	if (flag == false)
		printf("We dont heve a student with the current id\n");
}
void serchAndPrintStructBySecondName(struct List list, char* str1, char* str2, char c)
{
	fixNameString(str1);
	bool flag = false, gate = true;
	struct student* s = list.head;
	for (int i = 0; i < list.size; i++)
	{
		if (c == '=')
		{
			if (!strcmp(s->lastName, str1))
			{
				if (gate)
				{
					printTitle();
					gate = false;
				}
				flag = true;
				printStruct(s);
			}
		}
		else if (c == '<')
		{
			if (strcmp(s->lastName, str1) < 0)
			{
				if (gate)
				{
					printTitle();
					gate = false;
				}
				flag = true;
				printStruct(s);
			}
		}
		else if (c == '>') {
			if (strcmp(s->lastName, str1) > 0)
			{
				if (gate)
				{
					printTitle();
					gate = false;
				}
				flag = true;
				printStruct(s);
			}
			else if (c == '!')
			{
				if (strcmp(s->lastName, str1))
				{
					if (gate)
					{
						printTitle();
						gate = false;
					}
					flag = true;
					printStruct(s);
				}
			}
		}
		s = s->next;
	}
	if (flag == false)
		printf("We dont heve a student names %s\n", str1);
}
void serchAndPrintStructByFirstName(struct List list, char* str1, char* str2, char c)
{
	fixNameString(str1);
	bool flag = false;
	bool gate = true;
	struct student* s = list.head;
	for (int i = 0; i < list.size; i++)
	{
		if (c == '=')
		{
			if (strcmp(s->firstName, str1) == 0)
			{
				if (gate)
				{
					printTitle();
					gate = false;
				}
				flag = true;
				printStruct(s);
			}
		}
		else if (c == '<')
		{
			if (strcmp(s->firstName, str1) < 0)
			{
				if (gate)
				{
					printTitle();
					gate = false;
				}
				flag = true;
				printStruct(s);
			}
		}
		else if (c == '>') {
			if (strcmp(s->firstName, str1) > 0)
			{
				if (gate)
				{
					printTitle();
					gate = false;
				}
				flag = true;
				printStruct(s);
			}
			else if (c == '!')
			{
				if (strcmp(s->firstName, str1))
				{
					if (gate)
					{
						printTitle();
						gate = false;
					}
					flag = true;
					printStruct(s);
				}
			}
		}
		s = s->next;
	}
	if (flag == false)
		printf("We dont heve a student names %s\n", str1);
}
char findchar(char* str, char st[], int len)
{
	char c = NULL;
	char* ptr = str;
	while (*ptr)
	{
		for (int i = 0; i < len; i++)
		{
			if (*ptr == st[i])
			{
				c = st[i];
				if (c == '!' && ptr[1] != '=')
					c = NULL;
				return c;
			}
		}
		ptr++;
	}
	return c;
}

struct List createNewList()
{
	struct List list = { NULL,NULL, 0 };
	return list;
}

void sortList(struct List* list, struct student* s)
{
	int index = 0;
	struct student* ptr = list->head;
	while (strcmp(ptr->lastName, s->lastName) <= 0)
	{
		index++;
		ptr = ptr->next;
		if (ptr == NULL)
		{
			addToTail(list, s);
			return;
		}
	}
	if (index == 0)
	{
		addToHead(list, s);
		return;
	}
	else
	{
		addByIndex(list, s, index);
		return;
	}
}
void addToTail(struct List* list, struct student* s)
{
	list->tail->next = s;
	list->tail = s;
	return;
}
void addToHead(struct List* list, struct student* s)
{
	s->next = list->head;
	list->head = s;
	return;
}
void addByIndex(struct List* list, struct student* s, int index)
{
	struct student* ptr = list->head->next;
	struct student* prev = list->head;
	for (int i = 1; i < index; i++)
	{
		ptr = ptr->next;
		prev = prev->next;
	}
	s->next = ptr;
	prev->next = s;
}
//The function take oun line from the file in a dinamic way and return the line
char* takeLineFromFile(FILE* pf)
{
	char* input = NULL, * realTemp = NULL;
	char bufer[CHANK];
	int length = 0, tmp = 0;
	//The while loop run to the end of the line in the file
	//evry run the pountr files advanced "CHANK" steps and lucrative the characters in to string
	do
	{
		fgets(bufer, CHANK, pf);
		tmp = strlen(bufer);
		realTemp = realloc(input, tmp + length + 1);
		input = realTemp;
		strcpy(input + length, bufer);
		length += tmp;

	} while (tmp == CHANK - 1 && bufer[CHANK - 2] != '\n');
	return input;
}
int buildStruct(struct student* s, char* line, const char c[])
{
	char* token;
	token = strtok(line, c);
	token = deleteSpace(token);
	fixNameString(token);
	s->firstName = _strdup(token);
	token = strtok(NULL, c);
	token = deleteSpace(token);
	fixNameString(token);
	s->lastName = _strdup(token);
	token = strtok(NULL, c);
	token = deleteSpace(token);
	s->id = _strdup(token);
	token = strtok(NULL, c);
	if (token != "\n" && token != NULL)
	{
		token = deleteSpace(token);
		token = fixCourseName(token);
		s->courseName[0] = _strdup(token);
		token = strtok(NULL, c);
		token = deleteSpace(token);
		if (!isGradeValid(token))
		{
			s->courseName[0] = NULL;
			s->next = NULL;
			s->isId = isIdCorect(s->id);
			s->isName = isStructValid(s);
			return 1;
		}
		s->grades[0] = atoi(token);
		if (s->grades[0] > 120 || s->grades[0] < -10)
			s->courseName[0] = NULL;
	}
	s->next = NULL;
	s->isId = isIdCorect(s->id);
	s->isName = isStructValid(s);
	return 1;
}
void copyFileToStruct(struct List* list, const char fileName[])
{
	int userChoice;
	char* ch1, * userFileName;
	char* arr[7] = { NULL };
	FILE* in = fopen(fileName, "r");
	while (in == NULL)
	{
		printf("\n\n\n                                The current file is not available if you have");
		printf(" a file name press 1 otherwise press 0 and the system will open a new file");
		ch1 = scanf("%d", &userChoice);
		while (userChoice < 0 && userChoice > 1)
		{
			printf("Enter 1 or 0 only!\n");
			ch1 = scanf("%d", &userChoice);
		}
		if (userChoice)
		{
			userFileName = takeLineFromUser();
			in = fopen(userFileName, "r");
		}
		else
		{
			in = fopen(fileName, "w");
			if (in == NULL)
			{
				printf("Failed to open the file, the program is ending");
				exit(1);
			}
		}

	}
	char* token, * line = NULL;
	char ch;
	const char c[2] = ",";
	// The while loop reed aline from the file and fills in the structure fields
	while ((ch = fgetc(in)) != -1)
	{
		fseek(in, -1, SEEK_CUR);
		line = takeLineFromFile(in);
		changStrinToLower(line);
		struct student* tmp = (struct student*)malloc(sizeof(struct student));
		if (tmp == NULL)
		{
			printf("Alocation faild");
			exit(1);
		}
		for (size_t i = 0; i < GRADES; i++)
		{
			tmp->courseName[i] = NULL;
			tmp->grades[i] = -1;
		}

		if (buildStruct(tmp, line, c))
		{
			if (tmp)
			{
				if (list->size == 0)
				{
					list->head = tmp;
					list->tail = tmp;
					list->size++;
				}
				else
				{
					int index = ifStructExist(list, tmp->id);
					if (index > -1)
						addGredAndCours(list, tmp, index);
					else
					{
						sortList(list, tmp);
						list->size++;
					}
				}
			}
			else
				free(tmp);
		}

	}
	fclose(in);
	free(line);
}
int isGradeValid(char* str)
{
	char* ptr = str;
	int pointCnt = 0, i = 0, grade, maxGrade = 110, nimGrade = -10;
	if(ptr[i] < '0' || ptr[i] > '9' && ptr[i] != '-')
	return 0;
	i++;
	while (ptr[i])
	{
		if (ptr[i] == '.')
			pointCnt++;
		if (ptr[i] < '0' && ptr[i] > '9' || ptr[i] != '.' && pointCnt > 1)
			return 0;
		i++;
	}
	grade = atoi(str);
	if (grade < nimGrade || grade > maxGrade)
		return 0;
	return 1;
}
void addGredAndCours(struct List* list, struct student* s, int index)
{
	int i = 0;
	struct student* ptr = list->head;
	while (i < index)
	{
		ptr = ptr->next;
		i++;
	}
	i = 0;
	while (ptr->courseName[i] && i < GRADES)
		i++;
	if (i < GRADES) {
		ptr->grades[i] = s->grades[0];
		ptr->courseName[i] = s->courseName[0];
	}
}
void erorMeseg(char* str)
{
	if (str == NULL)
	{
		printf("Alocation faild");
		exit(1);
	}
}

int ifStructExist(struct List* list, char* id)
{
	struct student* s = list->head;
	for (int i = 0; i < list->size; i++)
	{
		if (strcmp(s->id, id) == 0)
			return i;
		s = s->next;
	}
	return -1;
}
void freeList(struct List list)
{
	struct student* prev = list.head;
	struct student* ptr = prev->next;
	while (ptr)
	{
		freeStruct(prev);
		prev = ptr;
		ptr = ptr->next;
	}
	freeStruct(prev);
}
void freeStruct(struct student* s)
{
	int i = 0;
	while (i < GRADES)
	{
		free(s->courseName[i++]);
	}
	free(s->firstName);
	free(s->lastName);
	free(s->id);
	free(s);
}

