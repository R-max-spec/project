#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct S_User {
    char username[40];
    char password[40];
};

float average(float, float, float, float);
float final_grade(float, float, float, float);

const int weightofAssignment = 20;
const int weightofLab = 15;
const int weightofCie = 25;
const int weightofSee = 40;

void Flush() {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
}

int authenticate(FILE *userFile) {
    struct S_User user;
    char inputUsername[40], inputPassword[40];

    printf("Enter username: ");
    scanf("%39s", inputUsername);
    getchar();

    printf("Enter password: ");
    scanf("%39s", inputPassword);
    getchar();

    rewind(userFile);
    while (fread(&user, sizeof(struct S_User), 1, userFile) == 1) {
        if (strcmp(user.username, inputUsername) == 0 && strcmp(user.password, inputPassword) == 0) {
            return 1;
        }
    }
    return 0;
}

void registerUser(FILE *userFile) {
    struct S_User newUser;

    printf("Enter new username: ");
    scanf("%39s", newUser.username);
    getchar();

    printf("Enter new password: ");
    scanf("%39s", newUser.password);
    getchar();

    fseek(userFile, 0, SEEK_END);
    fwrite(&newUser, sizeof(struct S_User), 1, userFile);

    printf("Registration successful!\n");
}

int main() {
    FILE *userFile;
    char userChoice;
    float math, pop, physics, electronics, final_weighted_result;
    char name[20];
    float avg_assignment, avg_lab, avg_cie, avg_see;

    userFile = fopen("USERS.DAT", "rb+");

    if (userFile == NULL) {
        userFile = fopen("USERS.DAT", "wb+");

        if (userFile == NULL) {
            printf("Unable to open USERS.DAT\n");
            exit(1);
        }
    }

    int authenticated = 0;
    while (!authenticated) {
        printf("Please authenticate.\n");

        if (authenticate(userFile)) {
            authenticated = 1;
            printf("Authentication successful!\n");
        } else {
            printf("Invalid username or password!\n");
            printf("1. Try again\n2. Register\n3. Exit\n");
            printf("Enter your choice: ");
            scanf(" %c", &userChoice);
            getchar();

            switch (userChoice) {
                case '1':
                    continue;
                case '2':
                    registerUser(userFile);
                    break;
                case '3':
                    fclose(userFile);
                    exit(0);
                default:
                    printf("Invalid choice. Exiting...\n");
                    fclose(userFile);
                    exit(1);
            }
        }
    }

    printf("Enter Your Name: ");
    scanf("%s", name);

    printf("---------------FOR ASSIGNMENTS----------------\n");
    printf("Enter Your marks in Maths : ");
    scanf("%f", &math);
    printf("Enter Your marks in POP : ");
    scanf("%f", &pop);
    printf("Enter Your marks in Physics : ");
    scanf("%f", &physics);
    printf("Enter Your marks in Electronics : ");
    scanf("%f", &electronics);

    avg_assignment = average(math, pop, physics, electronics);
    printf("\nYour Average marks for assignments are = %.2f\n", avg_assignment);

    printf("\n--------------FOR LABS----------------\n");
    printf("Enter Your marks in Maths : ");
    scanf("%f", &math);
    printf("Enter Your marks in POP : ");
    scanf("%f", &pop);
    printf("Enter Your marks in Physics : ");
    scanf("%f", &physics);
    printf("Enter Your marks in Electronics : ");
    scanf("%f", &electronics);

    avg_lab = average(math, pop, physics, electronics);
    printf("\nYour Average marks for Labs are = %.2f\n", avg_lab);

    printf("\n---------------FOR CIE----------------\n");
    printf("Enter Your marks in Maths : ");
    scanf("%f", &math);
    printf("Enter Your marks in POP : ");
    scanf("%f", &pop);
    printf("Enter Your marks in Physics : ");
    scanf("%f", &physics);
    printf("Enter Your marks in Electronics : ");
    scanf("%f", &electronics);

    avg_cie = average(math, pop, physics, electronics);
    printf("\nYour Average marks for CIE are = %.2f\n", avg_cie);

    printf("\n---------------FOR SEE----------------\n");
    printf("Enter Your marks in Maths : ");
    scanf("%f", &math);
    printf("Enter Your marks in POP : ");
    scanf("%f", &pop);
    printf("Enter Your marks in Physics : ");
    scanf("%f", &physics);
    printf("Enter Your marks in Electronics : ");
    scanf("%f", &electronics);

    avg_see = average(math, pop, physics, electronics);
    printf("\nYour Average marks for SEE are = %.2f\n", avg_see);

    final_weighted_result = final_grade(avg_assignment, avg_lab, avg_cie, avg_see);

    printf("\n-----------------------------------------------------");
    printf("\nFinal Weighted Result of %s = %.2f\n", name, final_weighted_result);
    printf("-----------------------------------------------------\n");

    fclose(userFile);

    return 0;
}

float average(float a, float b, float c, float d) {
    return (a + b + c + d) / 4;
}

float final_grade(float r, float u, float v, float s) {
    return ((r * (weightofAssignment / 100.0)) + (u * (weightofLab / 100.0)) + (v * (weightofCie / 100.0)) + (s * (weightofSee / 100.0)));
}