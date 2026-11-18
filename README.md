# Course Pilot

## 📌 Project Overview

The **University Course Enrollment Assistant** is a C language-based project designed to simplify the university course enrollment process. It helps students select courses for a semester while ensuring that all enrollment requirements are satisfied.

The system uses data structures, pointers, dynamic memory allocation, and validation algorithms to manage course information and student enrollment.

It automatically checks prerequisites, detects timetable conflicts, and prevents students from exceeding the maximum allowed credit limit.

## 🎯 Objectives

- Manage a university course catalog.
- Track previously completed courses.
- Verify course prerequisites before enrollment.
- Detect timetable conflicts between courses.
- Prevent credit overload during enrollment.
- Generate a final semester plan for students.
- Demonstrate the practical use of dynamic memory allocation in C.

## ✨ Features

1. **Course Management:** Stores course codes, names, credits, prerequisites, and schedules.
2. **Prerequisite Validation:** Checks whether a student has completed all required prerequisite courses.
3. **Time Conflict Detection:** Prevents enrollment in courses with overlapping schedules on the same day.
4. **Credit Limit Validation:** Restricts students to a maximum of 18 credits per semester.
5. **Dynamic Memory Allocation:** Uses `malloc()`, `realloc()`, and `free()` to manage memory efficiently.
6. **Student Management:** Maintains completed courses and current semester enrollment.
7. **Semester Plan Generation:** Displays successfully enrolled courses and total planned credits.

## 🛠️ Technologies Used

- **Programming Language:** C
- **Header Files:**
  - `stdio.h` – Input and output operations.
  - `stdlib.h` – Dynamic memory allocation.
  - `string.h` – String handling operations.
  - `stdbool.h` – Boolean data types.

## 📚 Concepts Used

- Structures (`struct`)
- Pointers
- Arrays of pointers
- Dynamic memory allocation
- Functions and function prototypes
- String manipulation
- Conditional statements
- Loops
- Boolean logic
- Memory management

## 📂 Project Structure

```text
University-Course-Enrollment-Assistant/
│
├── main.c
└── README.md
```

## ⚙️ Course Catalog

The project contains five sample courses:

| Course Code | Course Name | Credits | Day | Time |
|---|---|---:|---|---|
| CS101 | Intro to Programming | 3 | Monday | 9–11 AM |
| CS102 | Data Structures | 4 | Wednesday | 9–11 AM |
| MTH101 | Calculus I | 4 | Tuesday | 10 AM–12 PM |
| CS201 | Algorithms | 4 | Monday | 2–4 PM |
| PHY101 | Physics I | 3 | Monday | 10 AM–12 PM |

### Prerequisites

- CS102 requires CS101.
- CS201 requires CS102 and MTH101.
- CS101, MTH101, and PHY101 have no prerequisites.

## 🚀 How to Run the Project

### Step 1: Clone the Repository

```bash
git clone <repository-url>
```

### Step 2: Navigate to the Project Folder

```bash
cd University-Course-Enrollment-Assistant
```

### Step 3: Compile the Program

Using GCC:

```bash
gcc main.c -o enrollment
```

### Step 4: Execute the Program

**Windows:**
```bash
enrollment.exe
```

**Linux/macOS:**
```bash
./enrollment
```

## 📊 Sample Output

```text
--- University Course Enrollment Assistant ---

Student Alice Smith has previously completed: CS101

--- Attempting Enrollments ---

Request to enroll in CS102...
-> Successfully enrolled in CS102.

Request to enroll in CS201...
[WARNING] Missing prerequisite: MTH101 for CS201
-> Enrollment failed for CS201 due to missing prerequisites.

Request to enroll in MTH101...
-> Successfully enrolled in MTH101.

Request to enroll in PHY101...
-> Successfully enrolled in PHY101.

--- Final Semester Plan for Alice Smith ---
Total Planned Credits: 11
- CS102 (Data Structures) | Credits: 4 | Day: 3, Time: 9:00 - 11:00
- MTH101 (Calculus I) | Credits: 4 | Day: 2, Time: 10:00 - 12:00
- PHY101 (Physics I) | Credits: 3 | Day: 1, Time: 10:00 - 12:00
```

## 🔍 Working Process

1. Initialize the course catalog with course details.
2. Create a student profile.
3. Add previously completed courses.
4. Request enrollment in selected courses.
5. Validate prerequisites.
6. Check for timetable conflicts.
7. Verify the semester credit limit.
8. Enroll the student if all conditions are satisfied.
9. Display the final semester plan.
10. Release dynamically allocated memory.

## 🔮 Future Enhancements

- Add an interactive menu-driven interface.
- Allow students to enter their own details.
- Support adding and removing courses dynamically.
- Store student and course information in files.
- Add multiple student profiles.
- Implement a graphical user interface.
- Generate printable semester enrollment reports.

## 👨‍💻 Author

**Project:** University Course Enrollment Assistant  
**Language:** C  
**Category:** Data Structures and Programming

---

⭐ If you find this project useful, consider giving the repository a star!
