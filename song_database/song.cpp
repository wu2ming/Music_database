#include "song.h"

//storing information for one song
song :: song(): name(""),artist(""), year_pub(0), album(""), plays(0), label(""){}

void song:: set_name(string s_name ) {name=s_name;}
void song:: set_artist(string s_artist ) {artist=s_artist;}
void song :: set_album(string s_album ) {album=s_album;}
void song :: set_label(string s_label ) {label=s_label;}
void song:: set_plays(int s_plays ) {plays=s_plays;}
void song:: set_year(int s_year ) {year_pub=s_year;}


string song:: get_name () const {return name;}
string song:: get_artist () const {return artist;}
string song:: get_album () const {return album;}
string song:: get_label () const {return label;}
int song:: get_plays () const {return plays;}
int song:: get_year () const {return year_pub;}

song:: ~song(){}
