#include "database_menu.h"

menu:: menu(){
    cout << "welcome to the j-pop database\n----------------" << endl;
    show_menu();
};

void menu:: show_menu(){
    cout << "(A) add a song" <<endl;
    cout << "(F) find a song" <<endl;
    cout <<"(L) list the songs" <<endl;
    cout <<"(D) Delete a song" <<endl;
    cout << "(Q) Quit" << endl;

    cout << "Enter the letter of your choice: ";
    cin >> c;
    cin.ignore();

    if (c == 'a' || c =='A') add_song();
    else if (c == 'f' || c=='F') find_song();
    else if (c == 'd' || c == 'D') delete_song();
    else if (c == 'L' || c == 'l') sort_song();
    else if (c == 'q' || c == 'Q') return;
    else {
        cout << "Invalid selection, enter new value" << endl;
        show_menu();
        return;
    }

    if(c == 'a' || c =='A' || c == 'f' || c=='F' ||c == 'd' || c == 'D' ||c == 'L' || c == 'l'){
        cout << "----------\n";
        show_menu();
    }
}


char menu:: user_input (){
    char choice;
    cout << "\n(N) Name of song" <<endl;
    cout << "(A) Artist of song" <<endl;
    cout << "(B) Song Album" << endl;
    cout <<"(Y) Year published of song" <<endl;
    cout <<"(L) Record Label of song" <<endl;
    cout << "(P) Plays on spotify" << endl;
    cout << "(R) Return to main menu" << endl; 

    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice!= 'n' && choice!= 'N' &&choice!= 'a'&& choice!= 'A'&& choice!= 'y'&& choice!= 'Y' && choice!= 'l'
    && choice!= 'L'&& choice!= 'p' &&choice!= 'P' && choice!= 'b' &&choice!= 'B' &&choice!= 'r'&&choice!= 'R'){
        cout << "invalid selection, enter new value" <<endl;
        choice=user_input();
        return choice;
    }
    return choice;
}

void menu:: add_song(){
    string input="";
    string temp;
    string line ="";

    cout << "Enter song name: ";
    getline(cin, input);

    cout << "Enter artist name: ";
    getline(cin, temp);
    records.name_error(input,temp); 
    line+=input + "| "; //construct user input into one string

    records.artist_error(temp);
    line+=temp + "| ";

    cout << "Enter year published: ";
    getline(cin, input);
    records.year_error(input);
    line+=input + "| ";

    input="";
    cout << "Enter name of album: ";
    getline(cin, input);
    records.album_error(input);
    line+=input + "| ";

    input="";
    cout << "Enter number of plays on spotify: ";
    getline(cin, input);
    records.plays_error(input);
    line+=input + "| ";

    input="";
    cout << "Enter name of label: ";
    getline(cin, input);
    records.label_error(input);
    line+=input;
    cout << endl;

    records.add(line, "database.txt");
}


void menu:: find_song(){
    cout << "\nFind A Song \n---------------" <<endl;
    cout << "You can search by: ";
    char choice= user_input();

    if (choice == 'r' || choice=='R'){
        c='a';
        return;
    }

    string search;
    cout<< "Enter your search: ";
    cin.ignore();
    getline(cin, search);

    if (choice == 'n' || choice=='N') records.find_name(search);
    else if (choice == 'a' || choice=='A') records.find_artist(search);
    else if (choice == 'y' || choice=='Y') records.find_int_rec(search, choice);
    else if (choice == 'l' || choice=='L') records.find_label(search);
    else if (choice == 'p' || choice=='P') records.find_int_rec(search, choice);
    else records.find_album(search);

    records.clear_info(); //clears the information of stored songs
}

void menu:: delete_song(){
    cout << "\nDelete A Song \n---------------" <<endl;
    cout << "You can delete a song by: ";
    char choice= user_input();

    if (choice == 'r' || choice=='R'){
        c='a';
        return;
    }
    
    string search;
    cout<< "Enter your search: ";
    cin.ignore();
    getline(cin,search);
    
    if (choice == 'n' || choice=='N') records.find_name(search);
    else if (choice == 'a' || choice=='A') records.find_artist(search);
    else if (choice == 'y' || choice=='Y') records.find_int_rec(search, choice);
    else if (choice == 'l' || choice=='L') records.find_label(search);
    else if (choice == 'p' || choice=='P') records.find_int_rec(search, choice);
    else  records.find_album(search);

    records.delete_record(); 
    records.clear_info();
}

void menu:: sort_song(){
    cout << "Sort Songs" << "\n--------------\n";
    cout << "You can sort a song by:";
    char choice= user_input();

    if (choice == 'r' || choice=='R'){
        show_menu();
        c='a';
        return;
    }

    switch (choice){
        case 'n': case 'N': records.sort_name();
            break;
        case 'a' : case 'A': records.sort_artist();
            break;
        case 'b' : case 'B' : records.sort_album();
            break;
        case 'l' : case 'L' : records.sort_label();
            break;
        case 'Y': case 'y':   records.sort_year();
            break;
        case 'p': case 'P': records.sort_plays();
            break;
        default:
            return;
    }

    for(int i=0; i<records.get_size(); i++){
        records.print(i);
    }
}

menu::~menu(){}