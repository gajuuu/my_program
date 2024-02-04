/* Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a student or a staff account in the university system.
 *
 * In the project, this class should be expanded to
 * include necessary methods and attributes.
 * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
#include <vector>
#include <algorithm>

class Course;

const std::string NO_SIGNUPS = "No signups found on this course.";
const std::string SIGNED_UP = "Signed up on the course.";
const std::string COMPLETED = "Course completed.";
const std::string GRADUATED = "Graduated, all courses completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "firstname lastname"
     * @param account_number
     * @param duplicates tells the number of full namesakes
     * @param university_suffix is the e-mail suffix e.g. "tuni.fi"
     */
    Account(const std::string& full_name, int account_number, int duplicates,
            const std::string& university_suffix);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email() const;

    /**
     * @brief get_full_name
     * @return full name of this account
     */
    std::string get_full_name() const;

    /**
     * @brief get_account_number
     * @return account number linked to this account as int
     */
    int get_account_number() const;

    /**
     * @brief print courses and credits of the student completed
     */
    void print_complete() const;

    /**
     * @brief print current study status of the student
     */
    void print_status() const;

    /**
     * @brief set_current
     * @param new_course, a pointer to the `Course` object
     * to be added to the student's list of current courses.
     * Add the address of the course object to the student's list of
     * current courses, and print a specific message.
     */
    void set_current(Course* new_course);


    /**
     * @brief set_complete
     * @param completed_course, a pointer to the `Course` object
     * Call the `change_status` method to update the status of the course
     * to "completed", remove the course from the list of current couses,
     * and print a specific message.
     */
    void set_complete(Course* completed_course);

    /**
     * @brief set_graduate
     * Call the `change_status` method to update the status of all course
     * to "completed", remove the course from the list of current couses,
     * and print a specific message.
     */
    void set_graduate();

    /**
     * @brief get_current_courses
     * @return a vector of <Course*> which is the vector of pointers
     * of a student's current courses
     */
    std::vector<Course*> get_current_courses() const;

    /**
     * @brief get_is_graduated
     * @return true or false whether the student has graduated or not
     */
    bool get_is_graduated() const;


private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Course*> current_courses_;
    std::vector<Course*> complete_courses_;
    bool is_graduated_;

    /**
     * @brief change_status
     * @param course, a pointer to the `Course` object
     * @return true or false whether the status change happens or not.
     * Change the status of the course from "current" to "completed".
     * Specifically, remove courses from current_courses and add them
     * to completed_courses.
     */
    bool change_status(Course *course);
};

#endif // ACCOUNT_HH


