#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>

// Define structures
struct Date {
    int day;
    int month;
    int year;
};

struct Student {
    char admissionNo[10];
    char universityNo[10];
    char name[50];
    char department[50];
    char class[10];
    int rollNo;
    struct Date dob;
    char email[50];
    char contact[15];
    int semester;
    char password[20];
};

struct Faculty {
    char facultyID[10];
    char name[50];
    char qualification[50];
    char department[50];
    char subjects[3][50]; // Up to 3 subjects
    char mobile[15];
    char email[50];
    char password[20];
};

struct Attendance {
    char admissionNo[10];
    char universityNo[10];
    int semester;
    char subjectName[50];
    char date[11]; // dd-mm-yyyy
    char status; // 'P' for present, 'A' for absent
};

struct Mark {
    char admissionNo[10];
    char universityNo[10];
    int semester;
    char subjectName[50];
    char subjectCode[20];
    int assignment;
    int series1;
    int series2;
    int semesterExam;
    int total;
};

// Global variables
struct Student currentStudent;
struct Faculty currentFaculty;
int isAdminLoggedIn = 0;
int isStudentLoggedIn = 0;
int isFacultyLoggedIn = 0;

// Function prototypes
void displayMainMenu();
void adminLogin();
void studentLogin();
void facultyLogin();
void displayAdminMenu();
void displayStudentMenu();
void displayFacultyMenu();
void addStudent();
void addFaculty();
void viewStudentDetails();
void viewFacultyDetails();
void generateAttendanceReport();
void generateMarkReport();
void changePasswords();
void viewPersonalDetails();
void viewStudentAttendanceReport();
void viewStudentMarkReport();
void markAttendance();
void enterMarks();
void viewSubjects();
void generateStudentReport();
int validateLogin(char *filename, char *id, char *password, int userType);
void saveToFile(void *data, size_t size, char *filename, char *mode);
void readFromFile(void *data, size_t size, char *filename);

int main() {
    displayMainMenu();
    return 0;
}

void displayMainMenu() {
    int choice;
    
    do {
        system("cls"); // Clear screen (Windows specific)
        printf("=============STUDENT MANAGEMENT SYSTEM(C-PROJECT)===================\n");
        printf("\nLogin Page:\n");
        printf("\t1. Administrator\n");
        printf("\t2. Student Login\n");
        printf("\t3. Faculty Login\n");
        printf("\t4. Exit\n");
        printf("====================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                studentLogin();
                break;
            case 3:
                facultyLogin();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                getch(); // Wait for key press
        }
    } while(choice != 4);
}

void adminLogin() {
    char id[20], password[20];
    
    system("cls");
    printf("=========================ADMINISTRATOR LOGIN =======================\n");
    printf("\tEnter ID: ");
    scanf("%s", id);
    printf("\tEnter password: ");
    // Simple password masking
    int i = 0;
    char ch;
    while((ch = getch()) != 13) { // 13 is Enter key
        if(ch == 8) { // Backspace
            if(i > 0) {
                i--;
                printf("\b \b"); // Move back, print space, move back again
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
    printf("===================================================================\n");
    
    // Hardcoded admin credentials for demonstration
    if(strcmp(id, "admin") == 0 && strcmp(password, "admin123") == 0) {
        isAdminLoggedIn = 1;
        displayAdminMenu();
    } else {
        printf("Invalid credentials. Press any key to return to main menu.\n");
        getch();
    }
}

void studentLogin() {
    char admissionNo[10], password[20];
    
    system("cls");
    printf("=======================STUDENT LOGIN===============================\n");
    printf("\tEnter admission no: ");
    scanf("%s", admissionNo);
    printf("\tEnter password: ");
    // Simple password masking
    int i = 0;
    char ch;
    while((ch = getch()) != 13) { // 13 is Enter key
        if(ch == 8) { // Backspace
            if(i > 0) {
                i--;
                printf("\b \b"); // Move back, print space, move back again
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
    printf("===================================================================\n");
    
    if(validateLogin("students.dat", admissionNo, password, 1)) {
        isStudentLoggedIn = 1;
        displayStudentMenu();
    } else {
        printf("Invalid credentials. Press any key to return to main menu.\n");
        getch();
    }
}

void facultyLogin() {
    char facultyID[10], password[20];
    
    system("cls");
    printf("=====================FACULTY LOGIN=================================\n");
    printf("\tEnter faculty ID: ");
    scanf("%s", facultyID);
    printf("\tEnter password: ");
    // Simple password masking
    int i = 0;
    char ch;
    while((ch = getch()) != 13) { // 13 is Enter key
        if(ch == 8) { // Backspace
            if(i > 0) {
                i--;
                printf("\b \b"); // Move back, print space, move back again
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
    printf("===================================================================\n");
    
    if(validateLogin("faculty.dat", facultyID, password, 2)) {
        isFacultyLoggedIn = 1;
        displayFacultyMenu();
    } else {
        printf("Invalid credentials. Press any key to return to main menu.\n");
        getch();
    }
}

void displayAdminMenu() {
    int choice;
    
    do {
        system("cls");
        printf("=================ADMINISTRATOR PAGE=================================\n");
        printf("Options:\n");
        printf("\t1. Add Student\n");
        printf("\t2. Add Faculty\n");
        printf("\t3. View Student Details\n");
        printf("\t4. View Faculty Details\n");
        printf("\t5. Generate Attendance Report\n");
        printf("\t6. Generate Mark Report\n");
        printf("\t7. Change Passwords\n");
        printf("\t8. Logout\n");
        printf("=====================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                addFaculty();
                break;
            case 3:
                viewStudentDetails();
                break;
            case 4:
                viewFacultyDetails();
                break;
            case 5:
                generateAttendanceReport();
                break;
            case 6:
                generateMarkReport();
                break;
            case 7:
                changePasswords();
                break;
            case 8:
                isAdminLoggedIn = 0;
                printf("Logged out successfully. Press any key to continue.\n");
                getch();
                return;
            default:
                printf("Invalid choice. Press any key to try again.\n");
                getch();
        }
    } while(choice != 8);
}

void displayStudentMenu() {
    int choice;
    
    do {
        system("cls");
        printf("=================STUDENT=============================================\n");
        printf("Options:\n");
        printf("\t1. View Personal Details\n");
        printf("\t2. View Attendance Report\n");
        printf("\t3. View Mark Report\n");
        printf("\t4. Logout\n");
        printf("=====================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                viewPersonalDetails();
                break;
            case 2:
                viewStudentAttendanceReport();
                break;
            case 3:
                viewStudentMarkReport();
                break;
            case 4:
                isStudentLoggedIn = 0;
                printf("Logged out successfully. Press any key to continue.\n");
                getch();
                return;
            default:
                printf("Invalid choice. Press any key to try again.\n");
                getch();
        }
    } while(choice != 4);
}

void displayFacultyMenu() {
    int choice;
    
    do {
        system("cls");
        printf("=========================FACULTY====================================\n");
        printf("Options:\n");
        printf("\t1. Mark Attendance\n");
        printf("\t2. Enter Mark\n");
        printf("\t3. View Student Details\n");
        printf("\t4. Generate Student Report\n");
        printf("\t5. Logout\n");
        printf("====================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                markAttendance();
                break;
            case 2:
                enterMarks();
                break;
            case 3:
                viewStudentDetails();
                break;
            case 4:
                generateStudentReport();
                break;
            case 5:
                isFacultyLoggedIn = 0;
                printf("Logged out successfully. Press any key to continue.\n");
                getch();
                return;
            default:
                printf("Invalid choice. Press any key to try again.\n");
                getch();
        }
    } while(choice != 5);
}

void addStudent() {
    struct Student student;
    
    system("cls");
    printf("===========ADD STUDENT==============================================\n");
    printf("Admission number: ");
    scanf("%s", student.admissionNo);
    printf("University number: ");
    scanf("%s", student.universityNo);
    printf("Name: ");
    scanf(" %[^\n]s", student.name);
    printf("Department: ");
    scanf(" %[^\n]s", student.department);
    printf("Class: ");
    scanf("%s", student.class);
    printf("Roll no: ");
    scanf("%d", &student.rollNo);
    printf("Date of Birth (DD MM YYYY): ");
    scanf("%d %d %d", &student.dob.day, &student.dob.month, &student.dob.year);
    printf("Email: ");
    scanf("%s", student.email);
    printf("Contact: ");
    scanf("%s", student.contact);
    printf("Semester: ");
    scanf("%d", &student.semester);
    printf("Enter password for login: ");
    scanf("%s", student.password);
    printf("====================================================================\n");
    
    FILE *file = fopen("students.dat", "ab");
    if(file == NULL) {
        printf("Error opening file!\n");
        getch();
        return;
    }
    
    fwrite(&student, sizeof(struct Student), 1, file);
    fclose(file);
    
    printf("Student added successfully. Press any key to continue.\n");
    getch();
}

void addFaculty() {
    struct Faculty faculty;
    
    system("cls");
    printf("================ADD FACULTY=========================================\n");
    printf("Faculty ID: ");
    scanf("%s", faculty.facultyID);
    printf("Name: ");
    scanf(" %[^\n]s", faculty.name);
    printf("Qualification: ");
    scanf(" %[^\n]s", faculty.qualification);
    printf("Department: ");
    scanf(" %[^\n]s", faculty.department);
    printf("Subject: ");
    scanf(" %[^\n]s", faculty.subjects[0]);
    printf("Subject-2 (if any, press enter to skip): ");
    scanf(" %[^\n]s", faculty.subjects[1]);
    printf("Subject-3 (if any, press enter to skip): ");
    scanf(" %[^\n]s", faculty.subjects[2]);
    printf("Mobile number: ");
    scanf("%s", faculty.mobile);
    printf("Email ID: ");
    scanf("%s", faculty.email);
    printf("Password: ");
    scanf("%s", faculty.password);
    printf("====================================================================\n");
    
    FILE *file = fopen("faculty.dat", "ab");
    if(file == NULL) {
        printf("Error opening file!\n");
        getch();
        return;
    }
    
    fwrite(&faculty, sizeof(struct Faculty), 1, file);
    fclose(file);
    
    printf("Faculty added successfully. Press any key to continue.\n");
    getch();
}

void viewStudentDetails() {
    char dept[50], class[10], admNo[10];
    struct Student student;
    
    system("cls");
    printf("========================STUDENT DETAILS============================= \n");
    printf("Enter department: ");
    scanf(" %[^\n]s", dept);
    printf("Enter class: ");
    scanf("%s", class);
    printf("Enter admission (enter ALL for every student): ");
    scanf("%s", admNo);
    
    printf("\nDepartment: %s\tClass: %s\n", dept, class);
    printf("------------------------------------------------------------------------\n");
    printf("%-12s %-12s %-15s %-10s %-20s %-10s %-5s\n", "Admission-No", "University-No", "Name", "Contact", "Email", "DOB", "Semester");
    printf("------------------------------------------------------------------------\n");
    
    FILE *file = fopen("students.dat", "rb");
    if(file == NULL) {
        printf("Error opening file or no students added yet!\n");
        getch();
        return;
    }
    
    int found = 0;
    while(fread(&student, sizeof(struct Student), 1, file)) {
        if((strcmp(student.department, dept) == 0) && 
           (strcmp(student.class, class) == 0) && 
           (strcmp(admNo, "ALL") == 0 || strcmp(student.admissionNo, admNo) == 0)) {
            
            printf("%-12s %-12s %-15s %-10s %-20s %02d-%02d-%04d s%d\n", 
                   student.admissionNo, 
                   student.universityNo, 
                   student.name, 
                   student.contact, 
                   student.email, 
                   student.dob.day, 
                   student.dob.month, 
                   student.dob.year, 
                   student.semester);
            found = 1;
            
            if(strcmp(admNo, "ALL") != 0) {
                break;
            }
        }
    }
    
    fclose(file);
    
    if(!found) {
        printf("No matching student records found.\n");
    }
    
    printf("------------------------------------------------------------------------\n");
    printf("Enter e to exit: ");
    char exit;
    scanf(" %c", &exit);
}

void viewFacultyDetails() {
    char facultyID[10];
    struct Faculty faculty;
    
    system("cls");
    printf("========================FACULTY DETAILS============================= \n");
    printf("Enter faculty-ID (enter ALL for all faculty): ");
    scanf("%s", facultyID);
    
    printf("\n");
    printf("------------------------------------------------------------------------\n");
    printf("%-12s %-12s %-15s %-15s %-10s %-20s\n", "Faculty-ID", "Department", "Qualification", "Name", "Contact", "Email");
    printf("------------------------------------------------------------------------\n");
    
    FILE *file = fopen("faculty.dat", "rb");
    if(file == NULL) {
        printf("Error opening file or no faculty added yet!\n");
        getch();
        return;
    }
    
    int found = 0;
    while(fread(&faculty, sizeof(struct Faculty), 1, file)) {
        if(strcmp(facultyID, "ALL") == 0 || strcmp(faculty.facultyID, facultyID) == 0) {
            printf("%-12s %-12s %-15s %-15s %-10s %-20s\n", 
                   faculty.facultyID, 
                   faculty.department, 
                   faculty.qualification, 
                   faculty.name, 
                   faculty.mobile, 
                   faculty.email);
            found = 1;
            
            if(strcmp(facultyID, "ALL") != 0) {
                break;
            }
        }
    }
    
    fclose(file);
    
    if(!found) {
        printf("No matching faculty records found.\n");
    }
    
    printf("------------------------------------------------------------------------\n");
    printf("Enter e to exit: ");
    char exit;
    scanf(" %c", &exit);
}

void generateAttendanceReport() {
    char dept[50], class[10], admNo[10];
    struct Student student;
    struct Attendance att;
    
    system("cls");
    printf("========================ATTENDANCE REPORT============================= \n");
    printf("Enter department: ");
    scanf(" %[^\n]s", dept);
    printf("Enter class: ");
    scanf("%s", class);
    printf("Enter admission (enter ALL for every student): ");
    scanf("%s", admNo);
    
    printf("\nDepartment: %s\tClass: %s\n", dept, class);
    printf("------------------------------------------------------------------------\n");
    printf("%-12s %-12s %-8s %-10s %-10s %-10s\n", 
           "Admission-No", "University-No", "Semester", "Subject1", "Subject2", "Subject3");
    printf("------------------------------------------------------------------------\n");
    
    // First get students
    FILE *sFile = fopen("students.dat", "rb");
    if(sFile == NULL) {
        printf("Error opening student file or no students added yet!\n");
        getch();
        return;
    }
    
    // Open attendance file
    FILE *aFile = fopen("attendance.dat", "rb");
    if(aFile == NULL) {
        printf("No attendance records found.\n");
        fclose(sFile);
        getch();
        return;
    }
    
    int found = 0;
    
    // Dictionary to keep track of attendance percentages
    struct {
        char admNo[10];
        char subject[50];
        int present;
        int total;
    } attDict[100][3]; // Assuming max 100 students and 3 subjects
    
    int studentCount = 0;
    
    // First populate student list
    while(fread(&student, sizeof(struct Student), 1, sFile)) {
        if((strcmp(student.department, dept) == 0) && 
           (strcmp(student.class, class) == 0) && 
           (strcmp(admNo, "ALL") == 0 || strcmp(student.admissionNo, admNo) == 0)) {
            
            strcpy(attDict[studentCount][0].admNo, student.admissionNo);
            strcpy(attDict[studentCount][1].admNo, student.admissionNo);
            strcpy(attDict[studentCount][2].admNo, student.admissionNo);
            
            // Initialize subjects (in a real system, this would be dynamic)
            strcpy(attDict[studentCount][0].subject, "Subject1");
            strcpy(attDict[studentCount][1].subject, "Subject2");
            strcpy(attDict[studentCount][2].subject, "Subject3");
            
            attDict[studentCount][0].present = 0;
            attDict[studentCount][0].total = 0;
            attDict[studentCount][1].present = 0;
            attDict[studentCount][1].total = 0;
            attDict[studentCount][2].present = 0;
            attDict[studentCount][2].total = 0;
            
            studentCount++;
            found = 1;
            
            if(strcmp(admNo, "ALL") != 0) {
                break;
            }
        }
    }
    
    // Now calculate attendance percentages
    while(fread(&att, sizeof(struct Attendance), 1, aFile)) {
        for(int i = 0; i < studentCount; i++) {
            if(strcmp(att.admissionNo, attDict[i][0].admNo) == 0) {
                // Find which subject
                int subjectIndex = -1;
                if(strcmp(att.subjectName, "Subject1") == 0) subjectIndex = 0;
                else if(strcmp(att.subjectName, "Subject2") == 0) subjectIndex = 1;
                else if(strcmp(att.subjectName, "Subject3") == 0) subjectIndex = 2;
                
                if(subjectIndex != -1) {
                    attDict[i][subjectIndex].total++;
                    if(att.status == 'P') {
                        attDict[i][subjectIndex].present++;
                    }
                }
            }
        }
    }
    
    // Display attendance report
    for(int i = 0; i < studentCount; i++) {
        // Find student details to display
        fseek(sFile, 0, SEEK_SET);
        while(fread(&student, sizeof(struct Student), 1, sFile)) {
            if(strcmp(student.admissionNo, attDict[i][0].admNo) == 0) {
                float percentages[3];
                for(int j = 0; j < 3; j++) {
                    if(attDict[i][j].total > 0) {
                        percentages[j] = (float)attDict[i][j].present / attDict[i][j].total * 100;
                    } else {
                        percentages[j] = 0;
                    }
                }
                
                printf("%-12s %-12s %-8d %6.1f%% %9.1f%% %9.1f%%\n", 
                       student.admissionNo, 
                       student.universityNo, 
                       student.semester,
                       percentages[0],
                       percentages[1],
                       percentages[2]);
                break;
            }
        }
    }
    
    fclose(sFile);
    fclose(aFile);
    
    if(!found) {
        printf("No matching student records found.\n");
    }
    
    printf("------------------------------------------------------------------------\n");
    printf("Enter e to exit: ");
    char exit;
    scanf(" %c", &exit);
}

void generateMarkReport() {
    char dept[50], class[10], admNo[10];
    struct Student student;
    struct Mark mark;
    
    system("cls");
    printf("========================MARK REPORT===================================\n");
    printf("Enter department: ");
    scanf(" %[^\n]s", dept);
    printf("Enter class: ");
    scanf("%s", class);
    printf("Enter admission (enter ALL for every student): ");
    scanf("%s", admNo);
    
    printf("\nDepartment: %s\tClass: %s\n", dept, class);
    printf("------------------------------------------------------------------------\n");
    printf("%-12s %-12s %-8s %-10s %-10s %-10s\n", 
           "Admission-No", "University-No", "Semester", "Subject1", "Subject2", "Subject3");
    printf("------------------------------------------------------------------------\n");
    
    // First get students
    FILE *sFile = fopen("students.dat", "rb");
    if(sFile == NULL) {
        printf("Error opening student file or no students added yet!\n");
        getch();
        return;
    }
    
    // Open marks file
    FILE *mFile = fopen("marks.dat", "rb");
    if(mFile == NULL) {
        printf("No mark records found.\n");
        fclose(sFile);
        getch();
        return;
    }
    
    int found = 0;
    
    // Dictionary to keep track of marks
    struct {
        char admNo[10];
        char subject[50];
        int total;
        int hasData;
    } markDict[100][3]; // Assuming max 100 students and 3 subjects
    
    int studentCount = 0;
    
    // First populate student list
    while(fread(&student, sizeof(struct Student), 1, sFile)) {
        if((strcmp(student.department, dept) == 0) && 
           (strcmp(student.class, class) == 0) && 
           (strcmp(admNo, "ALL") == 0 || strcmp(student.admissionNo, admNo) == 0)) {
            
            strcpy(markDict[studentCount][0].admNo, student.admissionNo);
            strcpy(markDict[studentCount][1].admNo, student.admissionNo);
            strcpy(markDict[studentCount][2].admNo, student.admissionNo);
            
            // Initialize subjects (in a real system, this would be dynamic)
            strcpy(markDict[studentCount][0].subject, "Subject1");
            strcpy(markDict[studentCount][1].subject, "Subject2");
            strcpy(markDict[studentCount][2].subject, "Subject3");
            
            markDict[studentCount][0].total = 0;
            markDict[studentCount][0].hasData = 0;
            markDict[studentCount][1].total = 0;
            markDict[studentCount][1].hasData = 0;
            markDict[studentCount][2].total = 0;
            markDict[studentCount][2].hasData = 0;
            
            studentCount++;
            found = 1;
            
            if(strcmp(admNo, "ALL") != 0) {
                break;
            }
        }
    }
    
    // Now get marks
    while(fread(&mark, sizeof(struct Mark), 1, mFile)) {
        for(int i = 0; i < studentCount; i++) {
            if(strcmp(mark.admissionNo, markDict[i][0].admNo) == 0) {
                // Find which subject
                int subjectIndex = -1;
                if(strcmp(mark.subjectName, "Subject1") == 0) subjectIndex = 0;
                else if(strcmp(mark.subjectName, "Subject2") == 0) subjectIndex = 1;
                else if(strcmp(mark.subjectName, "Subject3") == 0) subjectIndex = 2;
                
                if(subjectIndex != -1) {
                    markDict[i][subjectIndex].total = mark.total;
                    markDict[i][subjectIndex].hasData = 1;
                }
            }
        }
    }
    
    // Display marks report
    for(int i = 0; i < studentCount; i++) {
        // Find student details to display
        fseek(sFile, 0, SEEK_SET);
        while(fread(&student, sizeof(struct Student), 1, sFile)) {
            if(strcmp(student.admissionNo, markDict[i][0].admNo) == 0) {
                printf("%-12s %-12s %-8d ", 
                       student.admissionNo, 
                       student.universityNo, 
                       student.semester);
                
                for(int j = 0; j < 3; j++) {
                    if(markDict[i][j].hasData) {
                        printf("%-10d ", markDict[i][j].total);
                    } else {
                        printf("%-10s ", "N/A");
                    }
                }
                printf("\n");
                break;
            }
        }
    }
    
    fclose(sFile);
    fclose(mFile);
    
    if(!found) {
        printf("No matching student records found.\n");
    }
    
    printf("------------------------------------------------------------------------\n");
    printf("Enter e to exit: ");
    char exit;
    scanf(" %c", &exit);
}

void changePasswords() {
    char type[10], userID[10], email[50];
    int day, month, year;
    char newPassword[20], confirmPassword[20];
    
    system("cls");
    printf("===============CHANGE PASSWORDS ========================================\n");
    printf("Enter type (student/faculty): ");
    scanf("%s", type);
    printf("Enter user-ID: ");
    scanf("%s", userID);
    printf("Enter email address: ");
    scanf("%s", email);
    printf("Enter dob (DD MM YYYY): ");
    scanf("%d %d %d", &day, &month, &year);
    printf("Enter new password: ");
    scanf("%s", newPassword);
    printf("Confirm password: ");
    scanf("%s", confirmPassword);
    printf("========================================================================\n");
    
    if(strcmp(newPassword, confirmPassword) != 0) {
        printf("Passwords do not match! Press any key to continue.\n");
        getch();
        return;
    }
    
    if(strcmp(type, "student") == 0) {
        struct Student student;
        FILE *file = fopen("students.dat", "rb+");
        if(file == NULL) {
            printf("Error opening file!\n");
            getch();
            return;
        }
        
        int found = 0;
        while(fread(&student, sizeof(struct Student), 1, file)) {
            if(strcmp(student.admissionNo, userID) == 0 && 
               strcmp(student.email, email) == 0 && 
               student.dob.day == day && 
               student.dob.month == month && 
               student.dob.year == year) {
                
                found = 1;
                strcpy(student.password, newPassword);
                
                // Fix: Cast the offset to (long) to avoid overflow
                fseek(file, -(long)sizeof(struct Student), SEEK_CUR);
                fwrite(&student, sizeof(struct Student), 1, file);
                break;
            }
        }
        
        fclose(file);
        
        if(found) {
            printf("Password changed successfully! Press any key to continue.\n");
        } else {
            printf("Invalid credentials! Press any key to continue.\n");
        }
    } else if(strcmp(type, "faculty") == 0) {
        struct Faculty faculty;
        FILE *file = fopen("faculty.dat", "rb+");
        if(file == NULL) {
            printf("Error opening file!\n");
            getch();
            return;
        }
        
        int found = 0;
        while(fread(&faculty, sizeof(struct Faculty), 1, file)) {
            if(strcmp(faculty.facultyID, userID) == 0 && 
               strcmp(faculty.email, email) == 0) {
                
                found = 1;
                strcpy(faculty.password, newPassword);
                
                // Fix: Cast the offset to (long) to avoid overflow
                fseek(file, -(long)sizeof(struct Faculty), SEEK_CUR);
                fwrite(&faculty, sizeof(struct Faculty), 1, file);
                break;
            }
        }
        
        fclose(file);
        
        if(found) {
            printf("Password changed successfully! Press any key to continue.\n");
        } else {
            printf("Invalid credentials! Press any key to continue.\n");
        }
    } else {
        printf("Invalid user type! Press any key to continue.\n");
    }
    
    getch();
}

void viewPersonalDetails() {
    system("cls");
    printf("========================PERSONAL DETAILS================================\n");
    printf("\tAdmission number: %s\n", currentStudent.admissionNo);
    printf("\tUniversity number: %s\n", currentStudent.universityNo);
    printf("\tName: %s\n", currentStudent.name);
    printf("\tDepartment: %s\n", currentStudent.department);
    printf("\tClass: %s\n", currentStudent.class);
    printf("\tRoll no: %d\n", currentStudent.rollNo);
    printf("\tDOB: %02d-%02d-%04d\n", currentStudent.dob.day, currentStudent.dob.month, currentStudent.dob.year);
    printf("\tEmail: %s\n", currentStudent.email);
    printf("\tContact: %s\n", currentStudent.contact);
    printf("\tSemester: %d\n", currentStudent.semester);
    printf("=========================================================================\n");
    
    printf("Press any key to return to the menu.\n");
    getch();
}

void viewStudentAttendanceReport() {
    struct Attendance att;
    
    system("cls");
    printf("==================ATTENDANCE REPORT============================================\n");
    printf("\tName: %s\n", currentStudent.name);
    printf("\tAdmission no: %s\n", currentStudent.admissionNo);
    printf("\tUniversity no: %s\n", currentStudent.universityNo);
    printf("\n");
    
    FILE *file = fopen("attendance.dat", "rb");
    if(file == NULL) {
        printf("\tNo attendance records found.\n");
        getch();
        return;
    }
    
    // Dictionary to keep track of attendance percentages
    struct {
        char subject[50];
        int present;
        int total;
    } attDict[3]; // Assuming 3 subjects max
    
    // Initialize
    strcpy(attDict[0].subject, "Subject1");
    strcpy(attDict[1].subject, "Subject2");
    strcpy(attDict[2].subject, "Subject3");
    
    for(int i = 0; i < 3; i++) {
        attDict[i].present = 0;
        attDict[i].total = 0;
    }
    
    // Calculate attendance
    while(fread(&att, sizeof(struct Attendance), 1, file)) {
        if(strcmp(att.admissionNo, currentStudent.admissionNo) == 0) {
            int subjectIndex = -1;
            if(strcmp(att.subjectName, "Subject1") == 0) subjectIndex = 0;
            else if(strcmp(att.subjectName, "Subject2") == 0) subjectIndex = 1;
            else if(strcmp(att.subjectName, "Subject3") == 0) subjectIndex = 2;
            
            if(subjectIndex != -1) {
                attDict[subjectIndex].total++;
                if(att.status == 'P') {
                    attDict[subjectIndex].present++;
                }
            }
        }
    }
    
    fclose(file);
    
    // Display attendance
    for(int i = 0; i < 3; i++) {
        float percentage = 0;
        if(attDict[i].total > 0) {
            percentage = (float)attDict[i].present / attDict[i].total * 100;
        }
        
        printf("\tSubject%d:\t%.1f%%\n\n", i+1, percentage);
    }
    
    printf("===========================================================================\n");
    printf("Press any key to return to the menu.\n");
    getch();
}

void viewStudentMarkReport() {
    struct Mark mark;
    
    system("cls");
    printf("==================MARK REPORT============================================\n");
    printf("\tName: %s\n", currentStudent.name);
    printf("\tAdmission no: %s\n", currentStudent.admissionNo);
    printf("\tUniversity no: %s\n", currentStudent.universityNo);
    printf("\n");
    
    printf("\t\t\tAssignment\tSeries1\t\tSeries2\t\tSemester\n");
    
    FILE *file = fopen("marks.dat", "rb");
    if(file == NULL) {
        printf("\tNo mark records found.\n");
        getch();
        return;
    }
    
    int found = 0;
    while(fread(&mark, sizeof(struct Mark), 1, file)) {
        if(strcmp(mark.admissionNo, currentStudent.admissionNo) == 0) {
            printf("\t%s:\t%d\t\t%d\t\t%d\t\t%d\n\n", 
                   mark.subjectName, 
                   mark.assignment, 
                   mark.series1, 
                   mark.series2, 
                   mark.semesterExam);
            found = 1;
        }
    }
    
    fclose(file);
    
    if(!found) {
        printf("\tNo marks recorded yet.\n");
    }
    
    printf("===========================================================================\n");
    printf("Press any key to return to the menu.\n");
    getch();
}

void markAttendance() {
    char date[11], dept[50], class[10];
    int hours;
    char input[100];
    int rollNos[50]; // Assuming max 50 students in a class
    int count = 0;
    
    system("cls");
    printf("====================MARK ATTENDANCE=========================================\n");
    printf("Enter date (dd-mm-yy): ");
    scanf("%s", date);
    printf("Department: ");
    scanf(" %[^\n]s", dept);
    printf("Class: ");
    scanf("%s", class);
    printf("Hours: ");
    scanf("%d", &hours);
    printf("Enter presents roll-no (comma separated): ");
    scanf(" %[^\n]s", input);
    printf("============================================================================\n");
    
    // Parse roll numbers
    char *token = strtok(input, ",");
    while(token != NULL) {
        rollNos[count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    
    // Get all students in the class
    struct Student student;
    FILE *sFile = fopen("students.dat", "rb");
    if(sFile == NULL) {
        printf("Error opening student file!\n");
        getch();
        return;
    }
    
    // Prepare to write attendance
    FILE *aFile = fopen("attendance.dat", "ab");
    if(aFile == NULL) {
        printf("Error opening attendance file!\n");
        fclose(sFile);
        getch();
        return;
    }
    
    // For each student in class, mark attendance
    int marked = 0;
    while(fread(&student, sizeof(struct Student), 1, sFile)) {
        if(strcmp(student.department, dept) == 0 && strcmp(student.class, class) == 0) {
            // Check if student is present
            int isPresent = 0;
            for(int i = 0; i < count; i++) {
                if(student.rollNo == rollNos[i]) {
                    isPresent = 1;
                    break;
                }
            }
            
            // For each subject taught by the faculty
            for(int i = 0; i < hours; i++) {
                struct Attendance att;
                strcpy(att.admissionNo, student.admissionNo);
                strcpy(att.universityNo, student.universityNo);
                att.semester = student.semester;
                sprintf(att.subjectName, "Subject%d", i+1); // Simplified
                strcpy(att.date, date);
                att.status = isPresent ? 'P' : 'A';
                
                fwrite(&att, sizeof(struct Attendance), 1, aFile);
            }
            
            marked++;
        }
    }
    
    fclose(sFile);
    fclose(aFile);
    
    printf("Attendance marked for %d students. Press any key to continue.\n", marked);
    getch();
}

void enterMarks() {
    char admissionNo[10];
    struct Student student;
    struct Mark mark;
    
    system("cls");
    printf("==================ENTER MARK================================================\n");
    printf("Student admission-number: ");
    scanf("%s", admissionNo);
    
    // Find student
    FILE *sFile = fopen("students.dat", "rb");
    if(sFile == NULL) {
        printf("Error opening student file!\n");
        getch();
        return;
    }
    
    int found = 0;
    while(fread(&student, sizeof(struct Student), 1, sFile)) {
        if(strcmp(student.admissionNo, admissionNo) == 0) {
            printf("(automatically fill all)\n");
            printf("University number: %s\n", student.universityNo);
            printf("Name: %s\n", student.name);
            printf("Department: %s\n", student.department);
            printf("Class: %s\n", student.class);
            
            strcpy(mark.admissionNo, student.admissionNo);
            strcpy(mark.universityNo, student.universityNo);
            mark.semester = student.semester;
            
            found = 1;
            break;
        }
    }
    
    fclose(sFile);
    
    if(!found) {
        printf("Student not found! Press any key to continue.\n");
        getch();
        return;
    }
    
    printf("\nSubject name: ");
    scanf(" %[^\n]s", mark.subjectName);
    printf("Subject code: ");
    scanf("%s", mark.subjectCode);
    
    printf("\nMarks-->\n");
    printf("\tAssignments: ");
    scanf("%d", &mark.assignment);
    printf("\tSeries1: ");
    scanf("%d", &mark.series1);
    printf("\tSeries2: ");
    scanf("%d", &mark.series2);
    printf("\tSemester: ");
    scanf("%d", &mark.semesterExam);
    
    // Calculate total
    mark.total = mark.assignment + mark.series1 + mark.series2 + mark.semesterExam;
    printf("\tTotal: %d\n", mark.total);
    
    printf("=============================================================================\n");
    
    // Save to file
    FILE *mFile = fopen("marks.dat", "ab");
    if(mFile == NULL) {
        printf("Error opening marks file!\n");
        getch();
        return;
    }
    
    fwrite(&mark, sizeof(struct Mark), 1, mFile);
    fclose(mFile);
    
    printf("Marks entered successfully! Press any key to continue.\n");
    getch();
}

void generateStudentReport() {
    char dept[50], class[10], admNo[10], subject[50];
    struct Student student;
    struct Mark mark;
    struct Attendance att;
    
    system("cls");
    printf("========================STUDENT REPORT============================= \n");
    printf("Enter department: ");
    scanf(" %[^\n]s", dept);
    printf("Enter class: ");
    scanf("%s", class);
    printf("Enter subject: ");
    scanf(" %[^\n]s", subject);
    printf("Enter admission (enter ALL for every student): ");
    scanf("%s", admNo);
    
    printf("\nDepartment: %s\tClass: %s\tSubject: %s\n", dept, class, subject);
    printf("------------------------------------------------------------------------\n");
    printf("%-12s %-12s %-8s %-10s %-10s\n", 
           "Admission-No", "University-No", "Semester", "Attendance", "Mark");
    printf("------------------------------------------------------------------------\n");
    
    // First get students
    FILE *sFile = fopen("students.dat", "rb");
    if(sFile == NULL) {
        printf("Error opening student file or no students added yet!\n");
        getch();
        return;
    }
    
    // Open attendance and marks files
    FILE *aFile = fopen("attendance.dat", "rb");
    FILE *mFile = fopen("marks.dat", "rb");
    
    if(aFile == NULL || mFile == NULL) {
        printf("Error opening attendance or marks file.\n");
        if(aFile) fclose(aFile);
        if(mFile) fclose(mFile);
        fclose(sFile);
        getch();
        return;
    }
    
    int found = 0;
    
    // Dictionary to keep track of student data
    struct {
        char admNo[10];
        char uniNo[10];
        int semester;
        int attendance_present;
        int attendance_total;
        int mark;
        int has_mark;
    } reportDict[100]; // Assuming max 100 students
    
    int studentCount = 0;
    
    // First populate student list
    while(fread(&student, sizeof(struct Student), 1, sFile)) {
        if((strcmp(student.department, dept) == 0) && 
           (strcmp(student.class, class) == 0) && 
           (strcmp(admNo, "ALL") == 0 || strcmp(student.admissionNo, admNo) == 0)) {
            
            strcpy(reportDict[studentCount].admNo, student.admissionNo);
            strcpy(reportDict[studentCount].uniNo, student.universityNo);
            reportDict[studentCount].semester = student.semester;
            reportDict[studentCount].attendance_present = 0;
            reportDict[studentCount].attendance_total = 0;
            reportDict[studentCount].mark = 0;
            reportDict[studentCount].has_mark = 0;
            
            studentCount++;
            found = 1;
            
            if(strcmp(admNo, "ALL") != 0) {
                break;
            }
        }
    }
    
    // Calculate attendance
    while(fread(&att, sizeof(struct Attendance), 1, aFile)) {
        if(strcmp(att.subjectName, subject) == 0) {
            for(int i = 0; i < studentCount; i++) {
                if(strcmp(att.admissionNo, reportDict[i].admNo) == 0) {
                    reportDict[i].attendance_total++;
                    if(att.status == 'P') {
                        reportDict[i].attendance_present++;
                    }
                }
            }
        }
    }
    
    // Get marks
    while(fread(&mark, sizeof(struct Mark), 1, mFile)) {
        if(strcmp(mark.subjectName, subject) == 0) {
            for(int i = 0; i < studentCount; i++) {
                if(strcmp(mark.admissionNo, reportDict[i].admNo) == 0) {
                    reportDict[i].mark = mark.total;
                    reportDict[i].has_mark = 1;
                }
            }
        }
    }
    
    // Display report
    for(int i = 0; i < studentCount; i++) {
        float attendancePercentage = 0;
        if(reportDict[i].attendance_total > 0) {
            attendancePercentage = (float)reportDict[i].attendance_present / reportDict[i].attendance_total * 100;
        }
        
        printf("%-12s %-12s %-8d %6.1f%%    ", 
               reportDict[i].admNo, 
               reportDict[i].uniNo, 
               reportDict[i].semester,
               attendancePercentage);
        
        if(reportDict[i].has_mark) {
            printf("%-10d\n", reportDict[i].mark);
        } else {
            printf("%-10s\n", "N/A");
        }
    }
    
    fclose(sFile);
    fclose(aFile);
    fclose(mFile);
    
    if(!found) {
        printf("No matching student records found.\n");
    }
    
    printf("------------------------------------------------------------------------\n");
    printf("Enter e to exit: ");
    char exit;
    scanf(" %c", &exit);
}

int validateLogin(char *filename, char *id, char *password, int userType) {
    FILE *file = fopen(filename, "rb");
    if(file == NULL) {
        return 0;
    }
    
    if(userType == 1) { // Student
        struct Student student;
        while(fread(&student, sizeof(struct Student), 1, file)) {
            if(strcmp(student.admissionNo, id) == 0 && strcmp(student.password, password) == 0) {
                // Store current student data
                currentStudent = student;
                fclose(file);
                return 1;
            }
        }
    } else if(userType == 2) { // Faculty
        struct Faculty faculty;
        while(fread(&faculty, sizeof(struct Faculty), 1, file)) {
            if(strcmp(faculty.facultyID, id) == 0 && strcmp(faculty.password, password) == 0) {
                // Store current faculty data
                currentFaculty = faculty;
                fclose(file);
                return 1;
            }
        }
    }
    
    fclose(file);
    return 0;
}