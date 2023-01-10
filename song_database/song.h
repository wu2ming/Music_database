#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

class song{
private:
    string name;
    string artist;
    int year_pub;
    string album;
    int plays;
    string label;
public:
    song();
    void set_name(string s_name );
    void set_album(string s_album );
    void set_label(string s_label );
    void set_artist(string s_artist );
    void set_plays(int s_plays );
    void set_year(int s_year );
    string get_album() const;
    string get_artist() const;
    string get_label() const;
    string get_name() const ;
    int get_year() const ;
    int get_plays() const ;
    int string_int(string line) const;

    ~song();
};

#endif