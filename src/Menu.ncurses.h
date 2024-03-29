#ifndef MENU_NCURSES_H
#define MENU_NCURSES_H

#include "City.h"
#include "util.ncurses.h"
#include <vector>

using Range_t = std::pair<double, double>;

class Menu_ncurses {
private:
    // This RAII object eliminates the needs to call initscr() and endwin() manually.
    const util::ncurses::Ncurses_initializer nc_init;

    // Common sub-sub-menus.
    class By_string {
    public:
        void show_guides(const Field& field) const;
        std::string get_input_string(bool substr_mode) const;
    };
    class By_number {
    public:
        void show_guides(const Field& field) const;
        Range_t get_input_numbers(bool range_mode) const;
    };

public:
    Menu_ncurses();
    ~Menu_ncurses();
    // Returns any possible char btw '1' and max_option_key.
    char get_input_option_key(char max_option_key) const;
    bool ask_if_user_wants_to_try_again() const;
    void show_main_menu() const;
    void print_matching_records(const std::vector<City>& records) const;

    // Sub-menus:
    class Add_records {
    public:
        void show_guides() const;
        City get_input() const;
        void say_record_exists(const City& city) const; // and print it.
        void say_record_added(const City& city) const;  // and print it.
    } add_records;

    class Find_records {
    public:
        void show_guides() const;
        By_string by_string;
        By_number by_number;
    } find_records;

    class Delete_records {
    public:
        void show_guides() const;
        void say_records_deleted(int how_many) const;
        bool confirm_user_wants_to_delete() const;
        By_string by_string;
        By_number by_number;
    } delete_records;
    
    class List_records {
    public:
        void show_guides() const;
        void show_options_for_strings(const Field& field) const;
        void show_options_for_numbers(const Field& field) const;
    } list_records;
}; // class Menu_ncurses

#endif // MENU_NCURSES_H