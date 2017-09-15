/*
Adnan Menderes University Faculty of Engineering
Computer Engineering Department
Algorithm and Programming Term Project

Group Members :

161805025 Kemal Yildirim
151805005 Alper Caliskan
161805059 Oguz Bardakci

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

struct studentData			//global struct defination
{
	int number; char name[21]; char surname[21]; int examgrade;

}student; //struct variable



void newRegister()
{
	FILE *fPtr;


	if ((fPtr = fopen("students.txt", "ab+")) == NULL) //ab+ takes new register to end of the file
	{
		puts("File cannot be opened.");
	}
	else
	{
		puts("Enter student's number, name, surname and exam grade :");
		scanf("%d%20s%20s%d", &student.number, student.name, student.surname, &student.examgrade); // it wants the student number twice.
		fwrite(&student, sizeof(struct studentData), 1, fPtr);					// we couldnt find a way out.
		puts("Registration successful.");

	}
	fclose(fPtr);
}

void searchByNumber()
{
	int request;
	printf("Enter the student number: ");
	scanf("%d", &request);
	FILE *fPtr;
	if ((fPtr = fopen("students.txt", "rb+")) == NULL) 
	{
		puts("File cannot be opened.");
	}
	else
	{
		while (fread(&student, sizeof(struct studentData), 1, fPtr))
		{
			if (student.number == request)
			{
				printf("Student found. Student information:\nStudent number : %d\tName : %s\tSurname : %s\tExam Grade : %d\n\n", student.number, student.name, student.surname, student.examgrade);
				break;
			}
			
		}
		fclose(fPtr);
		puts("");
	}
	}

void searchByName()
{
	char request[21];
	printf("Enter the student name: ");
	scanf("%s", request);
	FILE *fPtr;
	fPtr = fopen("students.txt", "rb+");

	while (fread(&student, sizeof(struct studentData), 1, fPtr))
	{
		if (strcmp(student.name, request) == 0)
		{
			printf("Student found. Student information:\nStudent number : %d\tName : %s\tSurname : %s\tExam Grade : %d\n\n", student.number, student.name, student.surname, student.examgrade);
			break;
		}
	}
	fclose(fPtr);
}

void updateRegister()
{
	FILE *fPtr;
	if ((fPtr = fopen("students.txt", "rb+")) == NULL)
	{
		puts("File cannot be opened.");
	}
	else
	{
		int intrequest;
		int record = 0; //file begins with 0th line and continues like 1-2-3 so ..
		printf("Enter the student's number: ");
		scanf("%d", &intrequest);
		while (fread(&student, sizeof(struct studentData), 1, fPtr))
		{
			if (student.number == intrequest) 
			{
				puts("Student found.");
				printf("Student number : %d\tName : %s\tSurname : %s\nExam Grade : %d", student.number, student.name, student.surname, student.examgrade);
				puts("Enter the new values of student's number, name, surname and exam grade: ");
				scanf("%d%s%s%d", &student.number, student.name, student.surname, &student.examgrade);
				fseek(fPtr, sizeof(struct studentData) * record, SEEK_SET); //takes the pointer to beginning of the line 
				fwrite(&student, sizeof(struct studentData), 1, fPtr);
				puts("Update successful.\n");
				break;
			}
			record++; // if dont find the student increases the line count

		}
		fclose(fPtr);


	}
}

void deleteRegister()
{
	FILE *fPtr, *temp;
	if ((fPtr = fopen("students.txt", "rb")) == NULL)
	{
		puts("File cannot be opened.");
	}
	else
	{
		int request;
		temp = fopen("Temp.txt", "wb+");
		printf("Enter the student's number you want to delete: ");
		scanf("%d", &request);
		while (fread(&student, sizeof(struct studentData), 1, fPtr))
		{
			if (student.number != request)
			{
				fwrite(&student, sizeof(struct studentData), 1, temp);
			}
		}
		fclose(fPtr);
		fclose(temp);
		remove("students.txt");
		rename("Temp.txt", "students.txt");
		puts("Delete successful.");
	}
}

void listRegisters()
{
	FILE *fPtr;
	if ((fPtr = fopen("students.txt", "rb+")) == NULL)
	{
		puts("File cannot be opened");
	}
	else
	{
		puts("\nStudent number\tStudent name\tExam grade\n");
		int i = 1;
		while (fread(&student, sizeof(struct studentData), 1, fPtr))
		{
			printf("%d. %d\t%s %s\t%d\t\n", i, student.number, student.name, student.surname, student.examgrade);
			i++;	
		}
		printf("\n**********************************************\n\n");
		fclose(fPtr);
	}

}

int main(void) {

	unsigned int process;
	
	puts("\t\tStudent Grade\n\t     Management System\n");
	puts("1. New Register\n2. Search by ID Number\n3. Search by Name\n4. Update a Register\n5. Delete a Register\n6. List Registers\n7. Exit");
	puts("\nPlease choose one process: ");
	scanf_s("%u", &process);

	while (1)
		{
		switch (process)
		{
		case 1:
			newRegister();
			break;

		case 2:
			searchByNumber();
			break;
		case 3:
			searchByName();
			break;
		case 4:
			updateRegister();
			break;
		case 5:
			deleteRegister();
			break;
		case 6:
			listRegisters();
			break;
		
		case 7:
			puts("Exiting...");
			exit(EXIT_SUCCESS);
			break;
		default:
			puts("Invalid process.");
			break;
		}
		puts("1. New Register\n2. Search by Student Number\n3. Search by Name\n4. Update a Register\n5. Delete a Register\n6. List Registers\n7. Exit");
		printf("\nPlease choose one process: ");
		scanf_s("%d", &process);	
		}	
	}