#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void menu();
void insert();
void list_all();
void modify();
void delete();
void search_sid();
void list_branch();
void list_address();
void list_address_branch();

struct Student {
    char SID[15];
    char NAME[30];
    char BRANCH[5];
    int SEMESTER;
    char ADDRESS[125];
};

typedef struct Student student;

student stu;

void file_check(FILE *fp) {
    if(fp == NULL) {
        printf("Error opening the file\n");
        exit(2);
    } else {
        return;
    }
}

void insert() {

    student stu;
    FILE *fp;
    char another_add = 'y', ch;
    system("cls"); // system("clear") on Linux based terminals

    fp = fopen("record.txt", "ab+");
    file_check(fp);

    fflush(stdin);
    while(another_add == 'y') {
        printf("\n--------------------Add New Record---------------------------\n");
        printf("Enter the SID or USN: \n");
        scanf("%s", stu.SID);
        //gets(stu.SID);
        fflush(stdin);
        printf("Enter Name: \n");
        scanf("%[^\n]", stu.NAME);
        //gets(stu.NAME);
        //fflush(stdin);
        printf("Enter Branch: \n");
        scanf("%s", stu.BRANCH);
        //gets(stu.BRANCH);
        //fflush(stdin);
        printf("Enter Semester: \n");
        scanf("%d", &stu.SEMESTER);
        fflush(stdin);
        printf("Enter address: \n");
        scanf("%[^\n]", stu.ADDRESS);
        //gets(stu.ADDRESS);

        fwrite(&stu, sizeof(stu), 1, fp);
        printf("To add another record press 'y', else press 'n': ");
        //fflush(stdin);
        another_add = scanf("%c", &another_add);//getch();
        system("cls"); // system("clear") for Linux based terminals
        //fflush(stdin);
    }

    fclose(fp);
    printf("Press any key to continue");
    scanf("%c", &ch);
    //getch();
    menu();
}

void list_all() {
    FILE *fp;
    student stu;
    char ch;
     // system("clear") for Linux based terminals
    printf("\n------------------- Record List -----------------------\n");
    printf("SID\t\tName\t\tBranch\tSemester\t\tAddress\n");

    fp = fopen("record.txt", "rb+");
    file_check(fp);

    while(fread(&stu, sizeof(stu), 1, fp) == 1) {
        printf("%s\t%s\t%s\t%d\t\t%s\n", stu.SID, stu.NAME, stu.BRANCH, stu.SEMESTER, stu.ADDRESS);
    }
    fclose(fp);
    printf("Press any key to continue");
    scanf("%c", &ch);
    //getch();
    menu();
}

// Modifies the student data on basis of SID
void modify() {
    char stID[15], ch;
    FILE *fp;
    student stu;
    int flag = 0;
    system("cls"); // system("clear") for linux based terminals
    printf("\n------------------------------ Modify Record ---------------------------------------\n\n");
    printf("Enter the SID of the student to be modified: \n");
    //fflush(stdin);
    //gets(stID);
    scanf("%s", stID);
    fp = fopen("record.txt", "rb+");
    file_check(fp);
    fflush(stdin);

    while(fread(&stu, sizeof(stu), 1, fp) == 1) {
        if(strcmp(stID, stu.SID) == 0) {
            flag = 1;
            printf("Enter the SID or USN: \n");
            scanf("%s", stu.SID);
            //gets(stu.SID); 
            fflush(stdin);
            printf("Enter Name: \n");
            scanf("%[^\n]", stu.NAME);
            //gets(stu.NAME);
            //fflush(stdin);
            printf("Enter Branch: \n");
            scanf("%s", stu.BRANCH);
            //gets(stu.BRANCH);
            //fflush(stdin);
            printf("Enter Semester: \n");
            scanf("%d", &stu.SEMESTER);
            fflush(stdin);
            printf("Enter address: \n");
            scanf("%[^\n]", stu.ADDRESS);
            //gets(stu.ADDRESS);
            
            fseek(fp, -sizeof(stu), SEEK_CUR);
            fwrite(&stu, sizeof(stu), 1, fp);
            break;
        }
    }

    if(flag == 0) {
        printf("Student not found, enter a valid SID\n");
        scanf("%c", &ch);
        //getch();
        modify();
    }

    fclose(fp);
    printf("Press any key to continue:");
    scanf("%c", &ch);
//    getch();
    menu();
}

// Deletes record on the basis of SID, if SID not present, the record remains unchanged
void delete() {
    char stID[15], ch;
    FILE *fp, *ft;
    student stu;
    system("cls"); // system("clear") for Linux based terminals
    printf("\n------------------------ Delete Record --------------------------\n\n");
    printf("Enter the SID of the student to be deleted:\n");
    scanf("%s", stID);
    //fflush(stdin);
    //gets(stID);
    fp = fopen("record.txt", "rb+");
    file_check(fp);
    ft = fopen("temp.txt", "wb+");
    file_check(ft);

    while(fread(&stu, sizeof(stu), 1, fp) == 1) {
        if(strcmp(stID, stu.SID) != 0) {
            fwrite(&stu, sizeof(stu), 1, ft);
        }
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");
    rename("temp.txt", "record.txt");
    printf("Press any key to continue:");
    scanf("%c", &ch);
    //getch();
    menu();
}

// Searchs a student record based on SID
// Not asked in the description
void search_sid() {
    char stID[15], ch;
    FILE *fp;
    student stu;
    int flag = 0;
    system("cls"); // system("clear") for linux based terminals
    printf("\n------------------------------ Search Record ---------------------------------------\n\n");
    printf("Enter the SID of the student to be found: \n");
    scanf("%s", stID);
    //fflush(stdin);
    //gets(stID);
    fp = fopen("record.txt", "rb+");
    file_check(fp);
    fflush(stdin);

    while(fread(&stu, sizeof(stu), 1, fp) == 1) {
        if(strcmp(stID, stu.SID) == 0) {
            printf("SID\t\tName\t\tBranch\tSemester\t\tAddress\n");
            printf("%s\t%s\t%s\t%d\t\t%s\n", stu.SID, stu.NAME, stu.BRANCH, stu.SEMESTER, stu.ADDRESS);
            flag = 1;
        }
    }

    if(flag == 0) {
        printf("Student not found, enter a valid SID\n");
        scanf("%c", &ch);
      //  getch();
    }

    fclose(fp);
    printf("Press any key to continue:");
    scanf("%c", &ch);
    //getch();
    menu();
}

// Lists all the students in a given branch
void list_branch() {
    char stBr[5], ch;
    FILE *fp;
    student stu;
    int flag = 0;
    system("cls"); // system("clear") for linux based terminals
    printf("\n------------------------------ List Branch ---------------------------------------\n\n");
    printf("Enter the Branch of the student to be found: \n");
    scanf("%s", stBr);
    //fflush(stdin);
    //gets(stBr);
    fp = fopen("record.txt", "rb+");
    file_check(fp);
    fflush(stdin);

    printf("SID\t\tName\t\tBranch\tSemester\t\tAddress\n");
    while(fread(&stu, sizeof(stu), 1, fp) == 1) {
        if(strcmp(stBr, stu.BRANCH) == 0) {
            printf("%s\t%s\t%s\t%d\t\t%s\n", stu.SID, stu.NAME, stu.BRANCH, stu.SEMESTER, stu.ADDRESS);
        }
    }

    fclose(fp);
    printf("Press any key to continue:");
    scanf("%c", &ch);
    //getch();
    menu();
}

// Lists all the students of a given address substring
// Not required as per description
void list_address() {
    char stAr[25], ch;
    FILE *fp;
    student stu;
    system("cls"); // system("clear") for linux based terminals
    printf("\n------------------------------ List by Address ---------------------------------------\n\n");
    printf("Enter the Address of the student to be found: \n");
    fflush(stdin);
    scanf("%[^\n]", stAr);
    //gets(stAr);
    fp = fopen("record.txt", "rb+");
    file_check(fp);
    fflush(stdin);

    printf("SID\t\tName\t\tBranch\tSemester\t\tAddress\n");
    while(fread(&stu, sizeof(stu), 1, fp) == 1) {
        if(strstr(stu.ADDRESS, stAr) != NULL) {
            printf("%s\t%s\t%s\t%d\t\t%s\n", stu.SID, stu.NAME, stu.BRANCH, stu.SEMESTER, stu.ADDRESS);
        }
    }

    fclose(fp);
    printf("Press any key to continue:");
    scanf("%c", &ch);
   // getch();
    menu();
}

// Lists students of a given branch with given address substring
void list_address_branch() {
    char stBr[5], stAr[25], ch;
    FILE *fp;
    student stu;
    system("cls"); // system("clear") for linux based terminals
    printf("\n------------------------------ List Branch and Address ---------------------------------------\n\n");
    printf("Enter the Branch of the student to be found: \n");
    scanf("%s", stBr);
    fflush(stdin);
//    gets(stBr);
    printf("Enter the Address substring of the student to be found: \n");
    scanf("%[^\n]", stAr);
//    fflush(stdin);
//    gets(stAr);
    fp = fopen("record.txt", "rb+");
    file_check(fp);
    fflush(stdin);

    printf("SID\t\tName\t\tBranch\tSemester\t\tAddress\n");
    while(fread(&stu, sizeof(stu), 1, fp) == 1) {
        if(strcmp(stBr, stu.BRANCH) == 0 && strstr(stu.ADDRESS, stAr) != NULL) {
            printf("%s\t%s\t%s\t%d\t\t%s\n", stu.SID, stu.NAME, stu.BRANCH, stu.SEMESTER, stu.ADDRESS);
        }
    }

    fclose(fp);
    printf("Press any key to continue:");
    scanf("%c", &ch);
//    getch();
    menu();
}

// Prints out the menu and takes the user choice
void menu() {

    int choice;
    system("cls"); // system("clear") for Linux based terminals
    printf("1) Add new student Record\n2) View all student records\n");
    printf("3) Search Record using SID\n4) List students based on Branch\n");
    printf("5) List students based on address\n6) List students based on address and branch\n");
    printf("7) Modify a student record\n8) Delete a student record\n9) Exit\n");
    printf("Enter your choice from the above operations: \n");
    fflush(stdin);
    scanf("%d", &choice);

    switch(choice) {
        case 1: insert(); break;

        case 2: list_all(); break;

        case 3: search_sid(); break;

        case 4: list_branch(); break;

        case 5: list_address(); break;

        case 6: list_address_branch(); break;

        case 7: modify(); break;

        case 8: delete(); break;

        case 9: exit(1); break;
        
        default: printf("Invalid Choice, enter new choice");
                menu(); break;
    }
}

int main() {

    menu();
    return 0;
}
