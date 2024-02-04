/* University
 *
 * Desc:
 *  This program implementsa university that creates accounts of new students,
 * and new teachers, creates new courses, adds a staff to courses, and changes
 * the study status of students. The program works by reading user input,
 * and the same results can be obtained by reading a user-specified file.
 *
 * command "QUIT"
 *  - Terminates with the return value EXIT_SUCCESS without printing anything.
 *  If parameters are given, they will be ignored.
 *
 * command "HELP"
 *  - prints all available commands with their acronyms.
 *
 * command "HELP" <command>/ <acronym>
 *  - shows details on how each command works.
 *
 * command "READ_FROM" <file>
 *  - Reads other commands with their parameters from the given file.
 *  If the file given as a parameter is unknown, an error message will be
 *  printed, and the program terminates with a return value of EXIT_SUCCESS.
 *
 * command "NEW_ACCOUNT" <name>
 *  - Creates the account of a person whether they are students or teachers.
 *  The account has the information of an account number, the person's name,
 *  and an email address. If the course already exists, an error message
 *  will be printed.
 *
 * command PRINT_ACCOUNTS"
 *  - Prints information about all persons, ordered according to their
 *  account numbers.
 *
 * command "NEW_COURSE" <code> <name>
 *  - Creates a new course. By default, all courses are worth of 5 ects.
 *  If the course already exists, an error message will be printed.
 *
 * In the following, if the given course or account does not exist,
 * a common error message will be printed.
 *
 * command "ADD_STAFF" <code> <account number>
 *  - Adds the given teacher for the given course. If the staff already
 *  exists in the course, an error message will be printed.
 *
 * command "PRINT_COURSE" <code>
 *  - Prints information about the given course: name, code, and teachers.
 * The teachers of the course are printed in the same order in which they
 * have been added.
 *
 * command "PRINT_COURSES"
 *  - Prints all the courses in the university according to their codes.
 *
 * command "SIGN_UP" <code> <student number>
 *  - Signs up the given student for the given course.
 *  If the course already exists in the student's current list of courses,
 *  or the student has already completed the course,
 *  or the student has graduated,
 *  the specific error message will be printed, respectively.
 *
 * command "COMPLETE" <code> <student number>
 *  - Completes the given course of the given student.
 *  If the course does not exist in the student's current list of courses,
 *  or if the student has already completed the course,
 *  or if the student has graduated,
 *  the specific error message will be printed, respectively.
 *
 * command "PRINT_STUDY_STATE" <student number>
 *  - Prints the study state of the given student: current courses,
 *  completed courses, and the total credits of the completed courses.
 *  Current courses are printed in the same order in which the student
 *  has signed up for them. Similarly, the completed courses are printed
 *  in the same order in which the student has passed them.
 *
 * command "PRINT_COMPLETED" <student number>
 *  - The command prints the courses completed by the given student and
 *  the total credits of them. Courses are printed in the same order in which
 *  the student has passed them.
 *
 * command "PRINT_SIGNUPS" <code>
 *  - Prints all the students signed up for the given course,
 *  ordered according to their account numbers. After a student passed
 *  the course, the student's sign-up still remains in the course data.
 *
 * command "GRADUATE" <student number>
 *  - Mkes the given student graduated from the university. All their courses
 *  become completed, and they cannot sign up for any courses. If the student
 *  has already graduated but is given the GRADUATE command again,
 *  the same message as the first one wil be printed.
 *  If a student attempts to sign up for a course after graduation,
 *  a common error message will be printed, regardless of whether the course
 *  has already been completed or the student has not previously signed up
 *  for the course.
 *
 *
 * Program author
 * Name: Fumika Matsuda
 * Student number: 151243936
 * UserID: qkfuma
 * E-Mail: fumika.matsuda@tuni.fi
 *
 * */

//#include "utils.hh"
#include "cli.hh"
#include "university.hh"
//#include <iostream>
//#include <string>
//#include <vector>
//#include <fstream>

const std::string PROMPT = "Uni> ";


int main()
{
    University* university = new University("tuni.fi");
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    delete university;
    return EXIT_SUCCESS;
}

