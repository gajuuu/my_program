#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>

Account::Account(const std::string& full_name, int account_number,
                 int duplicates, const std::string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number),
    current_courses_({}),
    complete_courses_({}),
    is_graduated_(false)
{
    std::vector<std::string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += std::to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}

Account::~Account()
{
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email() const
{
    return email_;
}

std::string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}

std::vector<Course*> Account::get_current_courses() const
{
    return current_courses_;
}

bool Account::get_is_graduated() const
{
    return is_graduated_;
}


void Account::set_current(Course *new_course)
{
    for ( unsigned int i = 0; i < complete_courses_.size(); ++i )
    {
        if ( complete_courses_.at(i) == new_course )
        {            
            std::cout << STUDENT_COMPLETED << std::endl;
            return;
        }
    }

    for ( unsigned int i = 0; i < current_courses_.size(); ++i )
    {
        if ( current_courses_.at(i) == new_course )
        {
             std::cout << STUDENT_EXISTS << std::endl;
             return;
        }
    }
    current_courses_.push_back(new_course);
    std::cout << SIGNED_UP << std::endl;
}

bool Account::change_status(Course* course)
{
    std::vector<Course*>::iterator iter;
    iter = find( current_courses_.begin(),
                 current_courses_.end(), course );
    if ( iter == current_courses_.end() )
    {
        std::cout << NO_SIGNUPS << std::endl;
        return false;
    }

    complete_courses_.push_back(course);
    current_courses_.erase(iter);
    return true;
}

void Account::set_complete(Course* completed_course)
{
    if ( !change_status(completed_course) )
    {
        return;
    }
    std::cout << COMPLETED << std::endl;
}

void Account::print_complete() const
{
    int credits = 0;
    if ( !complete_courses_.empty() )
    {
        for( auto& course_ptr : complete_courses_ )
        {
            std::cout << course_ptr->get_code() << " : "
                      << course_ptr->get_name() << std::endl;
            credits += course_ptr->get_credits();
        }
    }
    std::cout << "Total credits: " << credits << std::endl;
}

void Account::print_status() const
{
    std::cout << "Current:" << std::endl;
    if ( !current_courses_.empty() ){
        for ( auto& course_ptr : current_courses_ )
        {
            std::cout << course_ptr->get_code() << " : "
                      << course_ptr->get_name() << std::endl;
        }
    }
    std::cout << "Completed:" << std::endl;
    print_complete();
}

void Account::set_graduate()
{
    is_graduated_ = true;
    for ( auto& course_ptr : current_courses_ )
    {
        change_status(course_ptr);
    }
    std::cout << GRADUATED << std::endl;
}
