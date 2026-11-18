#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CODE_LEN 10
#define MAX_NAME_LEN 50
#define MAX_CREDITS_PER_SEM 18

// Structure to represent a weekly time slot
typedef struct {
    int day;         // 1 = Mon, 2 = Tue, 3 = Wed, 4 = Thu, 5 = Fri
    int start_time;  // 24-hour format (e.g., 9 for 9:00 AM)
    int end_time;    // 24-hour format (e.g., 11 for 11:00 AM)
} TimeSlot;

// Structure to represent a Course
typedef struct Course {
    char code[MAX_CODE_LEN];
    char name[MAX_NAME_LEN];
    int credits;
    int num_prereqs;
    char **prereq_codes; // Dynamic array of strings for prerequisite course codes
    TimeSlot schedule;
} Course;

// Structure to represent a Student and their semester plan
typedef struct {
    char name[MAX_NAME_LEN];
    
    // Completed course tracking
    char **completed_courses;
    int num_completed;
    
    // Current semester plan
    Course **planned_courses; // Array of pointers to Courses in the catalog
    int num_planned;
    int total_credits;
} Student;

// Function Prototypes
Course* create_course(const char* code, const char* name, int credits, int day, int start, int end);
void add_prerequisite(Course *c, const char* prereq_code);
Student* create_student(const char* name);
void add_completed_course(Student *s, const char* code);
bool has_completed(Student *s, const char* code);
bool check_prerequisites(Student *s, Course *c);
bool check_time_conflict(Student *s, Course *c);
void enroll_course(Student *s, Course *c);
void free_memory(Course **catalog, int cat_size, Student *s);

int main() {
    printf("--- University Course Enrollment Assistant ---\n\n");

    // 1. Initialize Course Catalog using dynamic memory and arrays of pointers
    int catalog_size = 5;
    Course **catalog = (Course **)malloc(catalog_size * sizeof(Course *));
    
    catalog[0] = create_course("CS101", "Intro to Programming", 3, 1, 9, 11);
    catalog[1] = create_course("CS102", "Data Structures", 4, 3, 9, 11);
    add_prerequisite(catalog[1], "CS101");
    
    catalog[2] = create_course("MTH101", "Calculus I", 4, 2, 10, 12);
    
    catalog[3] = create_course("CS201", "Algorithms", 4, 1, 14, 16);
    add_prerequisite(catalog[3], "CS102");
    add_prerequisite(catalog[3], "MTH101");
    
    catalog[4] = create_course("PHY101", "Physics I", 3, 1, 10, 12); // Conflicts with CS101

    // 2. Initialize a Student
    Student *student1 = create_student("Alice Smith");
    
    // Simulate past completed courses
    add_completed_course(student1, "CS101");
    printf("Student %s has previously completed: CS101\n\n", student1->name);

    // 3. Attempt Enrollments (Control & Validation)
    printf("--- Attempting Enrollments ---\n");
    
    // Attempt 1: Enroll in Data Structures (Prereq CS101 met)
    enroll_course(student1, catalog[1]);
    
    // Attempt 2: Enroll in Algorithms (Prereqs CS102, MTH101 NOT met)
    enroll_course(student1, catalog[3]);
    
    // Attempt 3: Enroll in Calculus I (No prereqs, no conflicts)
    enroll_course(student1, catalog[2]);
    
    // Attempt 4: Enroll in Physics I (Time conflict with CS102 which is Wed 9-11 vs PHY101 Mon 10-12? Wait, CS102 is Wed. Let's check CS101 - wait, not enrolled in CS101. No conflict).
    enroll_course(student1, catalog[4]);

    // 4. Display Final Semester Plan
    printf("\n--- Final Semester Plan for %s ---\n", student1->name);
    printf("Total Planned Credits: %d\n", student1->total_credits);
    for (int i = 0; i < student1->num_planned; i++) {
        Course *c = student1->planned_courses[i];
        printf("- %s (%s) | Credits: %d | Day: %d, Time: %d:00 - %d:00\n", 
               c->code, c->name, c->credits, c->schedule.day, c->schedule.start_time, c->schedule.end_time);
    }

    // 5. Clean up dynamic memory
    free_memory(catalog, catalog_size, student1);
    
    return 0;
}

// --- Function Implementations ---

Course* create_course(const char* code, const char* name, int credits, int day, int start, int end) {
    Course *c = (Course *)malloc(sizeof(Course));
    strcpy(c->code, code);
    strcpy(c->name, name);
    c->credits = credits;
    c->schedule.day = day;
    c->schedule.start_time = start;
    c->schedule.end_time = end;
    c->num_prereqs = 0;
    c->prereq_codes = NULL;
    return c;
}

void add_prerequisite(Course *c, const char* prereq_code) {
    c->num_prereqs++;
    c->prereq_codes = (char **)realloc(c->prereq_codes, c->num_prereqs * sizeof(char *));
    c->prereq_codes[c->num_prereqs - 1] = (char *)malloc(MAX_CODE_LEN * sizeof(char));
    strcpy(c->prereq_codes[c->num_prereqs - 1], prereq_code);
}

Student* create_student(const char* name) {
    Student *s = (Student *)malloc(sizeof(Student));
    strcpy(s->name, name);
    s->num_completed = 0;
    s->completed_courses = NULL;
    s->num_planned = 0;
    s->planned_courses = NULL;
    s->total_credits = 0;
    return s;
}

void add_completed_course(Student *s, const char* code) {
    s->num_completed++;
    s->completed_courses = (char **)realloc(s->completed_courses, s->num_completed * sizeof(char *));
    s->completed_courses[s->num_completed - 1] = (char *)malloc(MAX_CODE_LEN * sizeof(char));
    strcpy(s->completed_courses[s->num_completed - 1], code);
}

bool has_completed(Student *s, const char* code) {
    for (int i = 0; i < s->num_completed; i++) {
        if (strcmp(s->completed_courses[i], code) == 0) return true;
    }
    return false;
}

bool check_prerequisites(Student *s, Course *c) {
    if (c->num_prereqs == 0) return true;
    
    bool all_met = true;
    for (int i = 0; i < c->num_prereqs; i++) {
        if (!has_completed(s, c->prereq_codes[i])) {
            printf("[WARNING] Missing prerequisite: %s for %s\n", c->prereq_codes[i], c->code);
            all_met = false;
        }
    }
    return all_met;
}

bool check_time_conflict(Student *s, Course *c) {
    for (int i = 0; i < s->num_planned; i++) {
        Course *planned = s->planned_courses[i];
        if (planned->schedule.day == c->schedule.day) {
            // Check for overlap in hours
            if ((c->schedule.start_time >= planned->schedule.start_time && c->schedule.start_time < planned->schedule.end_time) ||
                (c->schedule.end_time > planned->schedule.start_time && c->schedule.end_time <= planned->schedule.end_time)) {
                printf("[ERROR] Time conflict: %s overlaps with %s on Day %d\n", 
                       c->code, planned->code, c->schedule.day);
                return true;
            }
        }
    }
    return false;
}

void enroll_course(Student *s, Course *c) {
    printf("Request to enroll in %s...\n", c->code);
    
    // Check overloading
    if (s->total_credits + c->credits > MAX_CREDITS_PER_SEM) {
        printf("[ERROR] Credit overload! Max allowed is %d. Cannot add %s.\n", MAX_CREDITS_PER_SEM, c->code);
        return;
    }

    // Algorithmic checks
    if (!check_prerequisites(s, c)) {
        printf("-> Enrollment failed for %s due to missing prerequisites.\n", c->code);
        return;
    }
    
    if (check_time_conflict(s, c)) {
        printf("-> Enrollment failed for %s due to schedule conflict.\n", c->code);
        return;
    }

    // Allocate memory and enroll
    s->num_planned++;
    s->planned_courses = (Course **)realloc(s->planned_courses, s->num_planned * sizeof(Course *));
    s->planned_courses[s->num_planned - 1] = c;
    s->total_credits += c->credits;
    
    printf("-> Successfully enrolled in %s.\n", c->code);
}

void free_memory(Course **catalog, int cat_size, Student *s) {
    for (int i = 0; i < cat_size; i++) {
        for (int j = 0; j < catalog[i]->num_prereqs; j++) {
            free(catalog[i]->prereq_codes[j]);
        }
        free(catalog[i]->prereq_codes);
        free(catalog[i]);
    }
    free(catalog);

    for (int i = 0; i < s->num_completed; i++) {
        free(s->completed_courses[i]);
    }
    free(s->completed_courses);
    free(s->planned_courses);
    free(s);
}
