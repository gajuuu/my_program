#include "cards.hh"
#include <iostream>

Cards::Cards() : top_(nullptr),
                 bottom_(nullptr)
{
}

Cards::~Cards()
{
    while (top_ != nullptr)
    {
        Card_data *item_to_be_released = top_;
        top_ = top_->next;
        delete item_to_be_released;
    }
}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    Card_data *new_card = new Card_data{id, nullptr};
    if (top_ == nullptr)
    {
        top_ = new_card;
        bottom_ = new_card;
    }
    else
    {
        new_card->next = top_;
        top_ = new_card;
    }
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{

    Card_data *current = top_;
    int counter = 1;
    while (current != nullptr)
    {
        s << counter << ": " << current->data << std::endl;
        ++counter;
        current = current->next;
    }
}

bool Cards::remove(int &id)
{

    if (top_ == nullptr)
    {
        return false;
    }

    Card_data *item_to_be_removed = top_;
    id = item_to_be_removed->data;

    if (top_ == bottom_)
    {
        top_ = nullptr;
        bottom_ = nullptr;
        return true;
    }
    else
    {
        top_ = top_->next;
        delete item_to_be_removed;
        return true;
    }
}

bool Cards::bottom_to_top()
{
    if (top_ == nullptr or top_ == bottom_)
    {
        return false;
    }

    Card_data *current = top_;
    while (current->next != bottom_)
    {
        current = current->next;
    }

    bottom_->next = top_;
    top_ = bottom_;
    bottom_ = current;
    bottom_->next = nullptr;
    return true;
}

bool Cards::top_to_bottom()
{
    if (top_ == nullptr or top_ == bottom_)
    {
        return false;
    }

    Card_data *newBottom = top_;
    Card_data *current = top_;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    current->next = newBottom;
    bottom_ = newBottom;
    top_ = top_->next;
    newBottom->next = nullptr;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    Card_data *current = top_;
    Card_data *prev = nullptr;
    Card_data *next = current->next;

    if (top_ == nullptr or top_ == bottom_)
    {
        return;
    }

    while (current != nullptr)
    {
        current->next = prev;
        prev = current;
        current = next;
        if (current != nullptr)
        {
            next = current->next;
        }
    }
    top_ = prev;

    current = top_;
    int counter = 1;
    while (current != nullptr)
    {
        s << counter << ": " << current->data << std::endl;
        ++counter;
        current = current->next;
    }

    current = prev;
    prev = nullptr;
    next = current->next;

    while (current != nullptr)
    {
        current->next = prev;
        prev = current;
        current = next;
        if (current != nullptr)
        {
            next = current->next;
        }
    }

    top_ = prev;
}
