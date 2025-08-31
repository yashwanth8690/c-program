#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Patient structure
typedef struct {
    char name[50];
    int age;
    char disease[50];
    char admittedDate[20];
} Patient;

// Function prototypes
void addPatient(Patient **patients, int *count);
void displayPatients(Patient *patients, int count);
void searchPatient(Patient *patients, int count);
void generateBill();
void saveToFile(Patient *patients, int count);

int main() {
    Patient *patients = NULL;
    int choice, count = 0;

    while (1) {
        printf("\n===== Hospital Patient Record System =====\n");
        printf("1. Add Patient\n2. Display All Patients\n3. Search Patient\n4. Generate Bill\n5. Save to File\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(&patients, &count); break;
            case 2: displayPatients(patients, count); break;
            case 3: searchPatient(patients, count); break;
            case 4: generateBill(); break;
            case 5: saveToFile(patients, count); break;
            case 6: free(patients); printf("Thank You!\n"); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Add a new patient
void addPatient(Patient **patients, int *count) {
    *patients = realloc(*patients, (*count + 1) * sizeof(Patient));
    Patient *p = &((*patients)[*count]);

    printf("Enter Name: "); scanf(" %[^\n]", p->name);
    printf("Enter Age: "); scanf("%d", &p->age);
    printf("Enter Disease: "); scanf(" %[^\n]", p->disease);
    printf("Enter Admitted Date (DD/MM/YYYY): "); scanf(" %[^\n]", p->admittedDate);

    (*count)++;
    printf("Patient added successfully!\n");
}

// Display all patients
void displayPatients(Patient *patients, int count) {
    if (count == 0) {
        printf("No patients to display.\n");
        return;
    }

    printf("\n----- Patient List -----\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s | Age: %d | Disease: %s | Admitted: %s\n",
               patients[i].name, patients[i].age, patients[i].disease, patients[i].admittedDate);
    }
}

// Search patient by name or disease
void searchPatient(Patient *patients, int count) {
    char keyword[50];
    int choice, found = 0;

    if (count == 0) {
        printf("No patient records available.\n");
        return;
    }

    printf("Search by: 1. Name  2. Disease\nEnter choice: ");
    scanf("%d", &choice);
    printf("Enter keyword: ");
    scanf(" %[^\n]", keyword);

    for (int i = 0; i < count; i++) {
        if ((choice == 1 && strcasecmp(patients[i].name, keyword) == 0) ||
            (choice == 2 && strcasecmp(patients[i].disease, keyword) == 0)) {
            printf("Found -> Name: %s | Age: %d | Disease: %s | Admitted: %s\n",
                   patients[i].name, patients[i].age, patients[i].disease, patients[i].admittedDate);
            found = 1;
        }
    }

    if (!found) printf("No matching record found!\n");
}

// Generate patient bill
void generateBill() {
    int days;
    float chargePerDay, total;

    printf("Enter number of days admitted: ");
    scanf("%d", &days);
    printf("Enter charge per day: ");
    scanf("%f", &chargePerDay);

    total = days * chargePerDay;
    printf("Total Bill = Rs. %.2f\n", total);
}

// Save patient records to file
void saveToFile(Patient *patients, int count) {
    FILE *fp = fopen("patients.txt", "w");
    if (!fp) {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %s %s\n",
                patients[i].name, patients[i].age, patients[i].disease, patients[i].admittedDate);
    }

    fclose(fp);
    printf("Patients data saved successfully to 'patients.txt'\n");
}
