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

    fprintf(file, "%s|%s|%.2f|%.2f|%.2f|%.2f|%.2f\n", 
            student.usn, 
            student.name, 
            student.avg_assignment, 
            student.avg_lab, 
            student.avg_cie, 
            student.avg_see, 
            student.final_weighted_result);

    fclose(file);
    printf("Data saved successfully for USN: %s\n", student.usn);
}

void searchStudentData(char *account, char *usn) {
    FILE *file = fopen(account, "r");
    if (file == NULL) {
        printf("No data found for this account.\n");
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char record_usn[20];
        sscanf(line, "%[^|]", record_usn); // Extract the USN
        if (strcmp(record_usn, usn) == 0) {
            printf("\n--- Student Found ---\n");
            printf("Details: %s", line);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No student found with USN: %s\n", usn);
    }

    fclose(file);
}

void deleteStudentData(char *account, char *usn) {
    FILE *file = fopen(account, "r");
    if (file == NULL) {
        printf("No data found for this account.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char record_usn[20];
        sscanf(line, "%[^|]", record_usn); // Extract the USN
        if (strcmp(record_usn, usn) == 0) {
            found = 1;
            continue; // Skip writing the matched record
        }
        fprintf(temp, "%s", line);
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(account);
        rename("temp.txt", account);
        printf("Student with USN %s deleted successfully.\n", usn);
    } else {
        remove("temp.txt");
        printf("No student found with USN: %s\n", usn);
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
    char username[40], password[40], existingUsername[40], existingPassword[40];
    int isDuplicate = 0;

    printf("Enter new username: ");
    scanf("%39s", username);

    FILE *file = fopen("accounts.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s", existingUsername, existingPassword) != EOF) {
            if (strcmp(existingUsername, username) == 0) {
                isDuplicate = 1;
                break;
            }
        }
        fclose(file);
    }

    if (isDuplicate) {
        printf("Username already exists. Please try again.\n");
        return;
    }

    printf("Enter new password: ");
    scanf("%39s", password);

    file = fopen("accounts.txt", "a");
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
        printf("\n=========== Student Grade Manager ===========\n");
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
                        printf("2. Search student by USN\n");
                        printf("3. Delete student by USN\n");
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
                                    getchar(); // Clear the newline character from the buffer
                                    fgets(student.name, sizeof(student.name), stdin);
                                    student.name[strcspn(student.name, "\n")] = '\0'; // Remove the trailing newline

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

                            case 2: {
                                char usn[20];
                                printf("Enter USN to search: ");
                                scanf("%s", usn);
                                searchStudentData(account, usn);
                                break;
                            }

                            case 3: {
                                char usn[20];
                                printf("Enter USN to delete: ");
                                scanf("%s", usn);
                                deleteStudentData(account, usn);
                                break;
                            }

                            case 4:
                                printf("Logged out successfully.\n");
                                goto main_menu;

                            default:
                                printf("Invalid choice. Try again.\n");
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

float final_grade(float r, float u, float v, float s) {
    return ((r * (weightofAssignment / 100.0)) + (u * (weightofLab / 100.0)) + (v * (weightofCie / 100.0)) + (s * (weightofSee / 100.0)));
}
