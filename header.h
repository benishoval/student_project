#pragma once
#ifndef header
#define header

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#define GRADES 3
#define CHANK 10

typedef enum {
	false = 0,
	true = 1
} bool;
struct student {
	bool isId;
	bool isName;
	char* firstName;
	char* lastName;
	char* id;
	char* courseName[3];
	int grades[3];
	float avg;
	struct student* next;
};
struct List {
	struct student* head;
	struct student* tail;
	int size;
};
//The createNewList function creates a manager structure for a linked list and initializes it to NULL
//The function returns a structure initialized to NULL
struct List createNewList();
//The buildStruct function receives an empty structure pointer to a string and a character
//The function divides the string according to the character obtained using the strtok function
//and fills the structure fields with the obtained values
int buildStruct(struct studenst* s, char* line, const char c[]);
//The copyFileToStruct function receives an empty structure and the name of a file to openõ
//The function uses a helper function that returns a line from the file 
//The function sends the resulting string and the structure to a helper function 
//that builds and fills the structure with values and then sends the complete structure 
//to the function that puts it in a linked list in order of dictionary value
void copyFileToStruct(struct List* list, const char fileName[]);
void erorMeseg(char* str);
//The addToTail function receives a pointer to a manager structure and a pointer to a student structure
//The function adds the student structure to the end of a linked list
void addToTail(struct List* list, struct student* tmp);
//The function receives a pointer to a manager structure and a pointer to a student structure
//The function adds the student structure to the top of a linked list
void addToHead(struct List* list, struct student* tmp);
//The addByIndex function receives a pointer to a manager structure and a pointer to a student structure 
//and an integer representing a position where the structure should be within the linked list
//The function adds the student structure to a linked list according to the received integer
void addByIndex(struct List* list, struct student* tmp, int index);
//The takeLineFromFile function receives a pointer to a file, 
//copies a line from it and returns a pointer to the beginning of the string copied from the file
char* takeLineFromFile(FILE* pf);
//The takeLineFromUser function receives input from the user and returns a pointer to the beginning of the resulting string
char* takeLineFromUser();
//The fixNameString function accepts a string (name) and modifies it according to the grammar rules
//A capital letter at the beginning of a name and then lowercase letters
void fixNameString(char* str);
//The mainSelectFunck function accepts a pointer to a string and a structure
//The function is a main function for the user's select request
//It fulfills the user's request by operating functions
//The function returns 1 if the task was successful and 0 if not
//then the program sends a message to the user that the operation was not performed
int mainSelectFunck(char* str, struct List list);
//The printStruct function receives a data structure of your studna and prints it
void printStruct(struct student* s);
//The ifStructExist function receives a pointer to the manager structure of a linked list
//and a pointer to a string (ID) The function goes through the structures in the list and checks by comparing
//the identity card if the structure already exists
//If such a structure already exists, it returns its position in the list; if it does not exist, it returns -1
int ifStructExist(struct List* list, char* id);
//The sortList function receives a pointer to a manager structure and a pointer to a student structure 
//and sends the structure to a function that will add it to the list in the correct index
void sortList(struct List* list, struct student* s);
//The addGredAndCours function accepts a pointer to a manager structure, a pointer to a student structure, and a location. 
//The function updates grades and courses in the student structure
void addGredAndCours(struct List* list, struct student* s, int index);
//The changStrinToLower function accepts a pointer to a string and changes all its letters to lowercase
void changStrinToLower(char* str);
//The findchar function receives a pointer to a string, an array of characters and its size.
//The function looks for the character received from the user and returns the character
//In case the character is not found the returned character will be NULL
char findchar(char* str, char st[], int len);
//The selectCmp function receives a pointer to a string, an array of strings and its size.
//The function checks if the input entered by the user corresponds to the instructions.
//It returns 1 if the input is correct and 0 if not.
int selectCmp(char* s1, char* s2[], int len);
//The serchAndPrintStructByFirstName function receives a manager structure with two pointers to strings and a character.
//The function goes through the linked list and checks if the student structure first name responds to the user's request
//The case since the function will send it to a print function
void serchAndPrintStructByFirstName(struct List list, char*, char*, char c);
//The serchAndPrintStructBySecondName function receives a manager structure with two pointers to strings and a character.
//The function goes through the linked list and checks if the student structure second name responds to the user's request
//The case since the function will send it to a print function
void serchAndPrintStructBySecondName(struct List list, char*, char*, char c);
//The serchAndPrintStructById function receives a manager structure with two pointers to strings and a character.
//The function goes through the linked list and checks if the student structure ID responds to the user's request
//The case since the function will send it to a print function
void serchAndPrintStructById(struct List list, char*, char*, char c);
//The serchAndPrintStructByGrade function receives a manager structure with two pointers to strings and a character.
//The function goes through the linked list and checks if the student structure grade responds to the user's request
//The case since the function will send it to a print function
void serchAndPrintStructByGread(struct List list, char*, char*, char c);
//The serchAndPrintStructByAverage function receives a manager structure with two pointers to strings and a character.
//The function goes through the linked list and checks if the student structure average responds to the user's request
//The case since the function will send it to a print function
void serchAndPrintStructByAverage(struct List list, char*, char*, char c);
//The mainSetFunck function accepts a pointer to a manager structure and a pointer to a string
//The function manages the set query by appropriate functions
void mainSetFunck(char* str, struct List* list);
//The function receives a pointer to a string and a character and checks if the character is in the string,
//if it is, the function will return 1, if not, it will return 0
int isCharExist(char* s, char c);
//The isIdCorect function accepts a pointer to a string
//The function checks the correctness of the ID
//The function returns true if the ID is valid and false if not
bool isIdCorect(char* str);
//The function accepts a pointer to a string
//The function returns a string without leading and trailing spaces
//The remove function also \n
char* deleteSpace(char* str);
//The function receives a pointer to a manager structure and prints the list into a file
void copyListToFile(struct List* list);
//The returnPtrStruct function accepts a pointer to a manager structure and a location
//The function returns a pointer to the student structure based on the position received
struct student* returnPtrStruct(struct List* list, int index);
//The isStructlegal function receives a pointer to a student structure and a pointer to a temporary structure
//The function checks if the structure is valid, if so it returns 1, otherwise the function returns 0
int isStructlegal(struct student* s, struct student* tmp);
//The changeSecondName function receives a pointer to a student structure and a pointer to a temporary structure
//The function changes the last name that appears in the studna structure
//If the name is different it returns 1 otherwise the function will return 0
int changeSecondName(struct student* s, struct student* tmp);
void freeStr(char* str, char* sArr[], int length);
//The function accepts a pointer to a manager structure and a pointer to a string
//The function detaches a structure from the list
void freeStructFromList(char* str, struct List* list);
//The freeList function accepts a manager structure and releases it
void freeList(struct List list);

char* returnStrAfterZero(char* str);
//The function receives a pointer to a studna structure and a pointer to a temporary structure
//The function updates a grade in the student structure
void updateGrade(struct student* s, struct student* tmp);
//The function receives a pointer to a string (course name)
//and returns it corrected according to the grammar rules
char* fixCourseName(char** corse);
//The function receives a pointer to a student structure and frees its fields
void freeStruct(struct student* s);
//The function receives a pointer to a student structure and checks whether the first and last name in the array are correct
//If so the function returns true otherwise it will return false
bool isStructValid(struct student* s);
//The function prints a title
void printTitle();
//The function receives a pointer to a string and checks whether it contains a string
//If the score is correct the function will return 1
//If not it will return 0
int isGradeValid(char* str);

#endif
