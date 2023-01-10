#ifndef DATABASE_MENU_H
#define DATABASE_MENU_H

#include "song.h"
#include "database.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

class menu{
private:
    database records;
    song songs;
    char c;

public:
    menu();
    char user_input();
    void show_menu();
    void add_song();
    void find_song();
    void delete_song();
    void sort_song();
    ~menu();
};

#endif