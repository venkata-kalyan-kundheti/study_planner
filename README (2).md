# 📚 Study Planner — C++ CLI Application

A lightweight, terminal-based study scheduler written in C++ that helps you build personalized day-by-day study plans based on subject priority, difficulty, deadlines, and available time.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [How It Works](#how-it-works)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Running the App](#running-the-app)
- [Usage Guide](#usage-guide)
- [Schedule Generation Logic](#schedule-generation-logic)
- [Project Structure](#project-structure)
- [Known Limitations](#known-limitations)
- [Future Improvements](#future-improvements)

---

## Overview

Exam season is stressful, and figuring out *how* to split your time across multiple subjects is half the battle. This Study Planner takes the guesswork out of it — you tell it what subjects you have, how important and difficult each one is, and how many days and hours you have available. It does the rest and hands you a clean, day-by-day table of what to study and for how long.

No databases, no internet connection, no external libraries. Just C++ and your terminal.

---

## Features

- **Add multiple subjects** with individual importance weights, deadlines, estimated hours, and difficulty ratings
- **Auto-generate a study schedule** distributed across your available days
- **Priority-based time allocation** — subjects with high importance and lower difficulty get more time
- **Mark subjects as completed** so they're automatically excluded from future plans
- **Edit or delete subjects** at any time without restarting
- **Formatted table output** for a clear, readable daily plan
- **Revision slots** are auto-filled when daily hours aren't fully consumed by subjects

---

## How It Works

When you generate a schedule, the planner runs through a three-step process:

1. **Base coverage** — Every incomplete subject is assigned a minimum number of hours per day based on its estimated total hours.
2. **Priority distribution** — Leftover time is allocated to subjects ranked by a `weight / difficulty` ratio. Higher importance and lower difficulty = higher priority.
3. **Day-wise scheduling** — The final allocations are spread across each day, with leftover slots marked as revision time.

---

## Getting Started

### Prerequisites

- A C++ compiler supporting **C++11 or later** (e.g., `g++`, `clang++`)
- A terminal / command prompt

### Compilation

```bash
g++ -o study_planner study_planner.cpp -std=c++11
```

Or with optimizations:

```bash
g++ -O2 -o study_planner study_planner.cpp -std=c++11
```

### Running the App

```bash
./study_planner
```

On Windows:

```bash
study_planner.exe
```

---

## Usage Guide

Once you launch the app, you'll see the main menu:

```
====== STUDY PLANNER ======
1. Add Subjects
2. Set Study Time
3. Generate Plan
4. Mark Completed
5. Edit Subject
6. Delete Subject
7. Show Subjects
0. Exit
```

### Step-by-step workflow

**1 → Add Subjects**

Enter each subject one at a time. For each subject, you'll be prompted for:

| Field        | Description                                      | Range  |
|--------------|--------------------------------------------------|--------|
| Name         | Subject name (no spaces — use underscores)       | —      |
| Importance   | How critical this subject is to your overall grade | 1–10 |
| Deadline     | How many days until the exam                     | Days   |
| Hours needed | Total hours you estimate you need to study it    | Hours  |
| Difficulty   | How hard the subject is for you personally       | 1–3    |

Type `done` when you're finished adding subjects.

**2 → Set Study Time**

Enter the total number of days in your study window and how many hours per day you can commit.

**3 → Generate Plan**

Outputs a formatted table like this:

```
=========== STUDY PLAN (TABLE) ===========

Day 1:
Subject            Hours
-------------------------
Mathematics        3
Physics            2
Revision           1

Day 2:
Subject            Hours
-------------------------
Mathematics        3
Chemistry          2
Revision           1
...
```

**4 → Mark Completed**

Pulls up the subject list with indices. Enter the index of the subject you've finished — it'll be excluded from all future plan generations.

**5 → Edit Subject**

Select a subject by index and update its weight, deadline, hours, or difficulty.

**6 → Delete Subject**

Permanently removes a subject from the list.

**7 → Show Subjects**

Lists all subjects with their current attributes and completion status.

---

## Schedule Generation Logic

The core scheduling algorithm lives in `generateSchedule()` and works as follows:

```
Total available time = totalDays × dailyHours

For each subject:
    base[i] = max(1, subject.hours / totalDays)   // minimum daily coverage

remainingTime = totalTime - (sum of base allocations × days)

While remainingTime > 0:
    Pick subject with highest (weight / difficulty) ratio
    Increment its daily allocation by 1
    Subtract totalDays from remainingTime

Fill each day up to dailyHours using these allocations
Any leftover time in a day → assigned to "Revision"
```

This ensures every subject gets a floor of coverage while directing surplus study time toward what matters most.

---

## Project Structure

```
study_planner.cpp        ← Single-file application
README.md                ← This file
```

The entire program is self-contained in one `.cpp` file, organized into:

- `struct Subject` — data model for each subject
- `generateSchedule()` — core scheduling logic and table output
- `showSubjects()` — utility to list current subjects
- `main()` — menu loop and user interaction

---

## Known Limitations

- **No persistent storage** — all data is lost when you exit. There's no save/load functionality yet.
- **Single-word subject names only** — `cin >> name` breaks on spaces. Use underscores (e.g., `Linear_Algebra`).
- **Deadline field is stored but not used** in scheduling — priority is based purely on weight and difficulty at the moment.
- **No input validation** — entering a string where a number is expected will cause undefined behavior.
- **Equal priority ties** aren't broken deterministically — `max_element` picks the first match.

---

## Future Improvements

A few things that would make this significantly more useful:

- [ ] File-based save and load (JSON or plain text)
- [ ] Use deadline proximity as a scheduling factor — subjects due sooner should get earlier slots
- [ ] Support for subject names with spaces using `getline()`
- [ ] Input validation and error recovery
- [ ] Weekly view in addition to day-by-day
- [ ] Export schedule to `.txt` or `.csv`
- [ ] Color-coded terminal output using ANSI escape codes

---

## License

This project is open for personal and academic use. Feel free to fork, modify, and build on top of it.
