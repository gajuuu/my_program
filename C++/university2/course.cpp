#include "course.hh"
#include <iostream>
#include <algorithm>

Course::Course(const std::string& code, const std::string& name, int credits):
    course_code_(code), name_(name), credits_(credits)
{
}

Course::~Course()
{
}

void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        std::cout << std::endl;
    }
}

void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
}

void Course::print_staff()
{
    std::cout << "* Staff: " << std::endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}

void Course::add_staff(Account *new_staff_member)
{
    // Checking if account is already a staff member
    for ( unsigned int i = 0; i < course_staff_.size(); ++i )
    {
        if ( course_staff_.at(i) == new_staff_member )
        {
            std::cout << STAFF_EXISTS << std::endl;
            return;
        }
    }

    course_staff_.push_back(new_staff_member);
    std::cout << STAFF_ADDED << std::endl;
}

const std::string Course::get_code() const
{
    return course_code_;
}

const std::string Course::get_name() const
{
    return name_;
}

int Course::get_credits() const
{
    return credits_;
}

void Course::sign_up(Account *new_student)
{
    int student_num = new_student->get_account_number();
    if ( enrolled_students_.find(student_num)
         != enrolled_students_.end() )
    {
        return;
    }
    enrolled_students_.insert({new_student->get_account_number(),
                               new_student});
}

void Course::print_enrolled_students()
{
    if ( !enrolled_students_.empty() )
    {
        for ( auto& student : enrolled_students_ )
        {
            student.second->print();
        }
    }
}
