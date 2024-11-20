#include <stdio.h> #include <stdlib.h> #include <string.h>

#define MAX 100

typedef struct {
int Outcome_id;
char Outcome_code[10]; char Outcome_name[50];
char Outcome_description[100]; char Outcome_outcome[100];
} CourseOutcome;

CourseOutcome courseOutcomes[MAX]; int courseOutcome_count = 0;
const char* FILE_NAME = "course_outcome_setting.txt"; void createOutcome();
void updateOutcome();
void retrieveOutcomes(); void deleteOutcome(); void storeOutcomes();
void quickSortOutcomes(int low, int high); int partitionOutcomes(int low, int high); void searchOutcomeLinear();

void load_from_file() {
FILE *file = fopen(FILE_NAME, "r"); if (file == NULL) {
return;
}
courseOutcome_count = 0;
while (fscanf(file, "%d %s %s %s %s\n", &courseOutcomes[courseOutcome_count].Outcome_id,
courseOutcomes[courseOutcome_count].Outcome_code,
 
courseOutcomes[courseOutcome_count].Outcome_name, courseOutcomes[courseOutcome_count].Outcome_description, courseOutcomes[courseOutcome_count].Outcome_outcome) != EOF) {
courseOutcome_count++;
}
fclose(file);
}

void storeOutcomes() {
FILE *file = fopen(FILE_NAME, "w"); if (file == NULL) {
printf("Error opening file!\n"); return;
}
for (int i = 0; i < courseOutcome_count; i++) {
fprintf(file, "%d %s %s %s %s\n", courseOutcomes[i].Outcome_id, courseOutcomes[i].Outcome_code, courseOutcomes[i].Outcome_name, courseOutcomes[i].Outcome_description, courseOutcomes[i].Outcome_outcome);
}
fclose(file);
}

void createOutcome() {
if (courseOutcome_count >= MAX) { printf("Course outcome list is full!\n"); return;
}

CourseOutcome c; printf("Enter Outcome ID: "); scanf("%d", &c.Outcome_id); printf("Enter Outcome Code: "); scanf("%s", c.Outcome_code);
printf("Enter Outcome Name: "); scanf("%s", c.Outcome_name); printf("Enter Outcome Description: "); scanf("%s", c.Outcome_description); printf("Enter Outcome: "); scanf("%s", c.Outcome_outcome);

courseOutcomes[courseOutcome_count++] = c; storeOutcomes();
printf("Course outcome created successfully!\n");
}

void updateOutcome() { int id;
printf("Enter Outcome ID to update: "); scanf("%d", &id);
 
for (int i = 0; i < courseOutcome_count; i++) { if (courseOutcomes[i].Outcome_id == id) {
printf("Enter new Outcome Code: ");
scanf("%s", courseOutcomes[i].Outcome_code); printf("Enter new Outcome Name: ");
scanf("%s", courseOutcomes[i].Outcome_name); printf("Enter new Outcome Description: ");
scanf("%s", courseOutcomes[i].Outcome_description); printf("Enter new Outcome: ");
scanf("%s", courseOutcomes[i].Outcome_outcome);

storeOutcomes();
printf("Course outcome updated successfully!\n"); return;
}
}
printf("Course outcome with ID %d not found.\n", id);
}

void retrieveOutcomes() {
printf("\nList of Course Outcomes:\n");
for (int i = 0; i < courseOutcome_count; i++) {
printf("ID: %d\nCode: %s\nName: %s\nDescription: %s\nOutcome: %s\n\n", courseOutcomes[i].Outcome_id, courseOutcomes[i].Outcome_code, courseOutcomes[i].Outcome_name, courseOutcomes[i].Outcome_description, courseOutcomes[i].Outcome_outcome);
}
}

void deleteOutcome() { int id;
printf("Enter Outcome ID to delete: "); scanf("%d", &id);

for (int i = 0; i < courseOutcome_count; i++) { if (courseOutcomes[i].Outcome_id == id) {
for (int j = i; j < courseOutcome_count - 1; j++) { courseOutcomes[j] = courseOutcomes[j + 1];
}
courseOutcome_count--; storeOutcomes();
printf("Course outcome deleted successfully!\n"); return;
}
}
printf("Course outcome with ID %d not found.\n", id);
}

int partitionOutcomes(int low, int high) { char pivot[10];
 
strcpy(pivot, courseOutcomes[high].Outcome_code); int i = low - 1;

for (int j = low; j < high; j++) {
if (strcmp(courseOutcomes[j].Outcome_code, pivot) < 0) { i++;
CourseOutcome temp = courseOutcomes[i]; courseOutcomes[i] = courseOutcomes[j]; courseOutcomes[j] = temp;
}
}
CourseOutcome temp = courseOutcomes[i + 1]; courseOutcomes[i + 1] = courseOutcomes[high]; courseOutcomes[high] = temp;
return i + 1;
}

void quickSortOutcomes(int low, int high) { if (low < high) {
int pi = partitionOutcomes(low, high); quickSortOutcomes(low, pi - 1); quickSortOutcomes(pi + 1, high);
}
}

void searchOutcomeLinear() { char code[10];
printf("Enter Outcome Code to search: "); scanf("%s", code);

for (int i = 0; i < courseOutcome_count; i++) {
if (strcmp(courseOutcomes[i].Outcome_code, code) == 0) {
printf("ID: %d\nCode: %s\nName: %s\nDescription: %s\nOutcome: %s\n", courseOutcomes[i].Outcome_id, courseOutcomes[i].Outcome_code, courseOutcomes[i].Outcome_name, courseOutcomes[i].Outcome_description, courseOutcomes[i].Outcome_outcome);
return;
}
}
printf("Course outcome with code %s not found.\n", code);
}

int main() { load_from_file();

int choice; while (1) {
printf("\n1. Create Outcome\n2. Update Outcome\n3. Retrieve Outcomes\n4. Delete Outcome\n5. Search by Code (Linear)\n6. Sort by Code (Quick Sort)\n7. Exit\n");
printf("Enter your choice: ");
 
scanf("%d", &choice);

switch (choice) { case 1:
createOutcome(); break;
case 2:
updateOutcome(); break;
case 3:
retrieveOutcomes(); break;
case 4:
deleteOutcome(); break;
case 5:
searchOutcomeLinear(); break;
case 6:
quickSortOutcomes(0, courseOutcome_count - 1); printf("Course outcomes sorted by code!\n"); retrieveOutcomes();
break; case 7:
exit(0); default:
printf("Invalid choice!\n");
}
}

return 0;
