#ifndef DATABASE_H
#define DATABASE_H

#include "song.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>

using namespace std;

class database{
private: 
    song songs;
    vector <song> data;
    vector <string> selected_songs;
    int file_size=0;

public:
    database();
    void read_file(string line);
    void print(int index);
    string lower_case(string str);
    int get_size()const;

    //methods for adding a song
    void add(string input, string fname);
    void name_error(string & input, string artist);
    void artist_error(string & input);
    void year_error(string & input);
    void album_error(string & input);
    void plays_error(string & input);
    void label_error(string & input);

    //finding song
    void find_int_rec(string s, char c);
    void find_name(string s);
    void find_artist(string s);
    void find_album(string s);
    void find_label(string s);
    void find_year(string s, string temp, string sub_s);
    void find_plays(string s,string temp, string sub_s);

    //remove song
    void delete_record();
    void store_string(int index);
    void clear_info();

    //list song
    bool reverse_order();
    void sort_name();
    void sort_artist();
    void sort_album();
    void sort_label();
    void sort_year();
    void sort_plays();
    ~database();
};


#endif