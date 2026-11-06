# Exam Seat Allocation System

A console-based Exam Seat Allocation System written in C++. It helps administrators manage courses, rooms, students, and exam schedules, and automatically allocates seats across multiple rooms — while students can check their exam tickets through a simple portal.

---

## Features

### Admin Portal
- **Manage Courses** — Add, view, and update courses.
- **Manage Rooms** — Add rooms with location and capacity, view, and update details.
- **Manage Students** — Register students, assign multiple courses, update names or enrolled courses.
- **Manage Exams** — Create exams with a course, time, and one or more rooms. Add or remove rooms after creation.
- **Seat Allocation** — Automatically assign available seats to all students enrolled in the exam's course. Validates that total room capacity is sufficient before allocating.
- **Ticket Viewing** — View all generated tickets for an exam.

### Student Portal
- Look up exam tickets by student ID.
- View assigned room, seat number, exam date/time, and course name.

---

## Tech Stack
- **Language:** C++ (C++11 or later)
- **Libraries:** Standard Library only (`iostream`, `vector`, `string`, `iomanip`, `limits`, `cstdlib`)

---

## Project Structure


### Core Data Structures
| Struct   | Purpose |
|----------|---------|
| `Course` | Course name and ID |
| `Student`| Student name, ID, and enrolled course IDs |
| `Room`   | Room ID, location, and seat capacity |
| `Seat`   | Seat number, associated room, and assignment status |
| `Exam`   | Exam ID, course, time, assigned rooms, and seat pool |
| `Ticket` | Final allocation record: student, room, seat, time, course |

---

## How to Run

### Prerequisites
- A C++ compiler (g++, clang++, or MSVC)

### Compile
```bash
g++ -std=c++11 -o exam_system "Exam Allocation System.cpp"

./exam_system        # Linux / macOS
exam_system.exe      # Windows
