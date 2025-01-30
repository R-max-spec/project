Student Grade Manager
A simple C program that manages student grades with user authentication, data entry, search, and deletion functionality.

Features
User Authentication:

Register new accounts
Login with existing accounts
Student Data Management:

Add student records (USN, name, assignment, lab, CIE, and SEE marks)
Calculate final weighted grade
Search student records by USN
Delete student records
How It Works
User Authentication:

Users must register before logging in.
Accounts are stored in accounts.txt.
Managing Student Records:

Each user has a separate file named <username>.txt to store student data.

Final_Grade = (Assignment * 0.2) + (Lab * 0.15) + (CIE * 0.25) + (SEE * 0.4)

Installation & Usage

./student_grade_manager
Commands in the Program:
Login/Register
Add Student Data
Search by USN
Delete Student by USN
Logout/Exit
File Structure

  Student Grade Manager
student_grade_manager.c
accounts.txt (stores usernames & passwords)
<username>.txt (stores student records for each user)

