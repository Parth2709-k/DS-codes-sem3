
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    int roll;
    char name[50];
    float marks;
};

struct Student s[MAX], temp;
int n = 0;

// Function declarations
void addStudents();
void displayStudents();
void linearSearch();
void binarySearch();
void insertionSort();
void selectionSort();
void shellSort();
void swap(struct Student *a, struct Student *b);

int main() {
    int choice;

    do {
        printf("\n--- STUDENT DATABASE ---\n");
        printf("1. Add Students\n");
        printf("2. Display Students\n");
        printf("3. Linear Search\n");
        printf("4. Binary Search\n");
        printf("5. Insertion Sort\n");
        printf("6. Selection Sort\n");
        printf("7. Shell Sort\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudents();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                linearSearch();
                break;
            case 4:
                binarySearch();
                break;
            case 5:
                insertionSort();
                break;
            case 6:
                selectionSort();
                break;
            case 7:
                shellSort();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

// Add student records
void addStudents() {
    int count, i;

    printf("How many students do you want to add? ");
    scanf("%d", &count);

    if (count < 1 || n + count > MAX) {
        printf("Invalid count or database is full!\n");
        return;
    }

    for (i = 0; i < count; i++) {
        printf("\nEnter roll number: ");
        scanf("%d", &s[n].roll);

        printf("Enter name: ");
        scanf(" %49[^\n]", s[n].name);

        printf("Enter marks: ");
        scanf("%f", &s[n].marks);

        n++;
    }
}

// Display all records
void displayStudents() {
    int i;

    if (n == 0) {
        printf("No student records available.\n");
        return;
    }

    printf("\nRoll\tName\t\tMarks\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%-15s %.2f\n",
               s[i].roll, s[i].name, s[i].marks);
    }
}

// Linear search by roll number
void linearSearch() {
    int key, i, found = 0;

    printf("Enter roll number to search: ");
    scanf("%d", &key);

    for (i = 0; i < n; i++) {
        if (s[i].roll == key) {
            printf("Found: %d %s %.2f\n",
                   s[i].roll, s[i].name, s[i].marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}

// Binary search by roll number
void binarySearch() {
    int key, low = 0, high = n - 1, mid;

    // Binary search requires records sorted by roll number.
    // This program sorts the records first.
    for (int i = 1; i < n; i++) {
        temp = s[i];
        int j = i - 1;

        while (j >= 0 && s[j].roll > temp.roll) {
            s[j + 1] = s[j];
            j--;
        }

        s[j + 1] = temp;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &key);

    while (low <= high) {
        mid = low + (high - low) / 2;

        if (s[mid].roll == key) {
            printf("Found: %d %s %.2f\n",
                   s[mid].roll, s[mid].name, s[mid].marks);
            return;
        }
        else if (s[mid].roll < key) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    printf("Student not found.\n");
}

// Insertion sort by roll number
void insertionSort() {
    int i, j;
    struct Student key;

    for (i = 1; i < n; i++) {
        key = s[i];
        j = i - 1;

        while (j >= 0 && s[j].roll > key.roll) {
            s[j + 1] = s[j];
            j--;
        }

        s[j + 1] = key;
    }

    printf("Records sorted using Insertion Sort.\n");
}

// Swap two complete student records
void swap(struct Student *a, struct Student *b) {
    struct Student t = *a;
    *a = *b;
    *b = t;
}

// Selection sort by roll number
void selectionSort() {
    int i, j, minIndex;

    for (i = 0; i < n - 1; i++) {
        minIndex = i;

        for (j = i + 1; j < n; j++) {
            if (s[j].roll < s[minIndex].roll)
                minIndex = j;
        }

        if (minIndex != i)
            swap(&s[i], &s[minIndex]);
    }

    printf("Records sorted using Selection Sort.\n");
}

// Shell sort by roll number
void shellSort() {
    int gap, i, j;
    struct Student key;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            key = s[i];
            j = i;

            while (j >= gap &&
                   s[j - gap].roll > key.roll) {
                s[j] = s[j - gap];
                j -= gap;
            }

            s[j] = key;
        }
    }

    printf("Records sorted using Shell Sort.\n");
}

