#include <bits/stdc++.h>
using namespace std;

struct Subject {
    string name;
    int weight, deadline, hours, difficulty;
    bool completed = false;
};

vector<Subject> subjects;
int totalDays = 0, dailyHours = 0;

// ---------------- SCHEDULE (FIXED LOGIC) ----------------
void generateSchedule() {
    if (subjects.empty() || totalDays == 0) {
        cout << "⚠️ Add subjects and set time first!\n";
        return;
    }

    vector<vector<pair<string,int>>> plan(totalDays + 1);

    int totalTime = totalDays * dailyHours;

    // Step 1: Give each subject minimum coverage
    vector<int> base(subjects.size(), 0);
    int usedTime = 0;

    for (int i = 0; i < subjects.size(); i++) {
        if (!subjects[i].completed) {
            base[i] = max(1, subjects[i].hours / totalDays);
            usedTime += base[i] * totalDays;
        }
    }

    // Step 2: Distribute remaining time based on importance
    int remainingTime = totalTime - usedTime;

    vector<double> priority(subjects.size());

    for (int i = 0; i < subjects.size(); i++) {
        if (!subjects[i].completed)
            priority[i] = (double)subjects[i].weight / subjects[i].difficulty;
        else
            priority[i] = -1;
    }

    while (remainingTime > 0) {
        int idx = max_element(priority.begin(), priority.end()) - priority.begin();

        if (priority[idx] <= 0) break;

        base[idx]++;
        remainingTime -= totalDays;
    }

    // Step 3: Fill schedule day-wise
    for (int d = 1; d <= totalDays; d++) {
        int timeLeft = dailyHours;

        for (int i = 0; i < subjects.size(); i++) {
            if (subjects[i].completed) continue;

            int give = min(base[i], timeLeft);

            if (give > 0) {
                plan[d].push_back({subjects[i].name, give});
                timeLeft -= give;
            }
        }

        if (timeLeft > 0)
            plan[d].push_back({"Revision", timeLeft});
    }

    // -------- TABLE OUTPUT --------
    cout << "\n=========== STUDY PLAN (TABLE) ===========\n\n";

    for (int d = 1; d <= totalDays; d++) {
        cout << "Day " << d << ":\n";
        cout << left << setw(18) << "Subject" << setw(8) << "Hours\n";
        cout << "-------------------------\n";

        for (auto &p : plan[d]) {
            cout << left << setw(18) << p.first << setw(8) << p.second << "\n";
        }
        cout << "\n";
    }
}

// ---------------- SHOW ----------------
void showSubjects() {
    if (subjects.empty()) {
        cout << "No subjects!\n";
        return;
    }

    cout << "\n--- SUBJECT LIST ---\n";
    for (int i = 0; i < subjects.size(); i++) {
        cout << i << ". " << subjects[i].name
             << " | W:" << subjects[i].weight
             << " | D:" << subjects[i].deadline
             << " | H:" << subjects[i].hours
             << " | Diff:" << subjects[i].difficulty
             << (subjects[i].completed ? " | Done" : "")
             << "\n";
    }
}

// ---------------- MAIN ----------------
int main() {
    int choice;

    while (true) {
        cout << "\n====== STUDY PLANNER ======\n";
        cout << "1. Add Subjects\n";
        cout << "2. Set Study Time\n";
        cout << "3. Generate Plan\n";
        cout << "4. Mark Completed\n";
        cout << "5. Edit Subject\n";
        cout << "6. Delete Subject\n";
        cout << "7. Show Subjects\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n=== Add Subjects (type 'done' to stop) ===\n";

            while (true) {
                Subject s;

                cout << "\nEnter subject name (or 'done'): ";
                cin >> s.name;

                if (s.name == "done") break;

                cout << "Importance (1-10): ";
                cin >> s.weight;

                cout << "Exam in how many days: ";
                cin >> s.deadline;

                cout << "Hours required: ";
                cin >> s.hours;

                cout << "Difficulty (1-3): ";
                cin >> s.difficulty;

                subjects.push_back(s);
                cout << "Added!\n";
            }
        }

        else if (choice == 2) {
            cout << "Total days: ";
            cin >> totalDays;

            cout << "Daily hours: ";
            cin >> dailyHours;
        }

        else if (choice == 3) {
            generateSchedule();
        }

        else if (choice == 4) {
            showSubjects();
            int idx;
            cout << "Enter index: ";
            cin >> idx;

            if (idx < 0 || idx >= subjects.size()) {
                cout << "❌ Invalid index!\n";
            } else {
                subjects[idx].completed = true;
                cout << "Marked done!\n";
            }
        }

        else if (choice == 5) {
            showSubjects();
            int idx;
            cout << "Enter index to edit: ";
            cin >> idx;

            if (idx < 0 || idx >= subjects.size()) {
                cout << "❌ Invalid index!\n";
            } else {
                cout << "New weight: ";
                cin >> subjects[idx].weight;

                cout << "New deadline: ";
                cin >> subjects[idx].deadline;

                cout << "New hours: ";
                cin >> subjects[idx].hours;

                cout << "New difficulty: ";
                cin >> subjects[idx].difficulty;

                cout << "Updated!\n";
            }
        }

        else if (choice == 6) {
            showSubjects();
            int idx;
            cout << "Enter index to delete: ";
            cin >> idx;

            if (idx < 0 || idx >= subjects.size()) {
                cout << "❌ Invalid index!\n";
            } else {
                subjects.erase(subjects.begin() + idx);
                cout << "Deleted!\n";
            }
        }

        else if (choice == 7) {
            showSubjects();
        }

        else if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}