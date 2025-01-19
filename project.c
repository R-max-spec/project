#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For remove()

struct S_Student {
    char usn[20];
    char name[40];
    float avg_assignment;
    float avg_lab;
    float avg_cie;
    float avg_see;
    float final_weighted_result;
};

float average(float, float, float, float);
float final_grade(float, float, float, float);

const int weightofAssignment = 20;
const int weightofLab = 15;
const int weightofCie = 25;
const int weightofSee = 40;

void saveStudentData(char *account, struct S_Student student) {
    FILE *file = fopen(account, "a");
    if (file == NULL) {
        printf("Error saving data for account: %s\n", account);
        return;
    }

    fprintf(file, "USN: %s\n", student.usn);
    fprintf(file, "Name: %s\n", student.name);
    fprintf(file, "Assignment Average: %.2f\n", student.avg_assignment);
    fprintf(file, "Lab Average: %.2f\n", student.avg_lab);
    fprintf(file, "CIE Average: %.2f\n", student.avg_cie);
    fprintf(file, "SEE Average: %.2f\n", student.avg_see);
    fprintf(file, "Final Weighted Result: %.2f\n\n", student.final_weighted_result);

    fclose(file);
    printf("Data saved successfully to %s\n", account);
}

void viewAllData(char *account) {
    FILE *file = fopen(account, "r");
    if (file == NULL) {
        printf("No data found for this account.\n");
        return;
    }

    char line[256];
    printf("\n--------------- STUDENT DATA FOR %s ---------------\n", account);
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    printf("---------------------------------------------------\n");

    fclose(file);
}

void deleteAllData(char *account) {
    if (remove(account) == 0) {
        printf("All data deleted successfully for account: %s\n", account);
    } else {
        perror("Error deleting file");
        printf("No data file found for account: %s\n", account);
    }
}

int login(char *account) {
    char username[40], password[40];
    char inputUsername[40], inputPassword[40];

    printf("Enter username: ");
    scanf("%39s", inputUsername);
    printf("Enter password: ");
    scanf("%39s", inputPassword);

    FILE *file = fopen("accounts.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s", username, password) != EOF) {
            if (strcmp(username, inputUsername) == 0 && strcmp(password, inputPassword) == 0) {
                strcpy(account, inputUsername);
                fclose(file);
                return 1; // Login successful
            }
        }
        fclose(file);
    }

    return 0; // Login failed
}

void registerAccount() {
    char username[40], password[40];

    printf("Enter new username: ");
    scanf("%39s", username);
    printf("Enter new password: ");
    scanf("%39s", password);

    FILE *file = fopen("accounts.txt", "a");
    if (file == NULL) {
        printf("Error creating account.\n");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    printf("Account created successfully! You can now log in.\n");
}

int main() {
    char account[40];
    int choice, num_students;
    struct S_Student student;

    while (1) {
        printf("\n=========== Student Grade Calculator ===========\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (login(account)) {
                    printf("Login successful! Welcome, %s.\n", account);

                    while (1) {
                        printf("\n=========== Menu ===========\n");
                        printf("1. Enter student data\n");
                        printf("2. View all data\n");
                        printf("3. Delete all data\n");
                        printf("4. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1:
                                printf("How many students do you want to add? ");
                                scanf("%d", &num_students);

                                for (int i = 0; i < num_students; i++) {
                                    printf("\n--- Enter details for student %d ---\n", i + 1);

                                    printf("Enter USN: ");
                                    scanf("%s", student.usn);

                                    printf("Enter Name: ");
                                    scanf("%s", student.name);

                                    printf("Enter assignment marks (avg): ");
                                    scanf("%f", &student.avg_assignment);

                                    printf("Enter lab marks (avg): ");
                                    scanf("%f", &student.avg_lab);

                                    printf("Enter CIE marks (avg): ");
                                    scanf("%f", &student.avg_cie);

                                    printf("Enter SEE marks (avg): ");
                                    scanf("%f", &student.avg_see);

                                    student.final_weighted_result = final_grade(
                                        student.avg_assignment,
                                        student.avg_lab,
                                        student.avg_cie,
                                        student.avg_see
                                    );

                                    saveStudentData(account, student);
                                }
                                break;

                            case 2:
                                viewAllData(account);
                                break;

                            case 3:
                                deleteAllData(account);
                                break;

                            case 4:
                                printf("Logged out successfully.\n");
                                goto main_menu;

                            default:
                                printf("Invalid choice. Try again.\n");
                        }

                        // Ask the user if they want to continue
                        char proceed;
                        printf("\nDo you want to perform another action? (y/n): ");
                        scanf(" %c", &proceed);

                        if (proceed == 'n' || proceed == 'N') {
                            printf("Signing out...\n");
                            goto main_menu;
                        }
                    }
                } else {
                    printf("Invalid username or password. Try again.\n");
                }
                break;

            case 2:
                registerAccount();
                break;

            case 3:
                printf("Exiting program. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }

    main_menu:;
    }

    return 0;
}

float average(float a, float b, float c, float d) {
    return (a + b + c + d) / 4;
}

float final_grade(float r, float u, float v, float s) {
    return ((r * (weightofAssignment / 100.0)) + (u * (weightofLab / 100.0)) + (v * (weightofCie / 100.0)) + (s * (weightofSee / 100.0)));
}
