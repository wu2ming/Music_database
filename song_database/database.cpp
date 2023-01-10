#include "database.h"
#include "limits.h"

//database containing songs
database:: database(){
    ifstream fileIn;
    string line;
    fileIn.open("database.txt");
    while (!fileIn.eof()){
        getline(fileIn, line);
        read_file(line);
    }

    fileIn.close();
}

//read from given text file containg information
void database:: read_file(string line){ 
    int sep=0;
    string temp="";
    for (int i =0; i < line.size(); i++){ 
        if (line[i]=='|' || i == line.size()-1){ 
            sep++;

            if (sep == 1) songs.set_name(temp);
            else if (sep ==2) songs.set_artist(temp);
            else if (sep == 3) songs.set_year(stoi(temp));
            else if (sep ==4 ) songs.set_album(temp);
            else if (sep == 5) songs.set_plays(stoi(temp));
            else {
                temp += line[i];
                songs.set_label(temp);
            } 

            i++;
            temp="";
        }

        else temp += line[i];
    }
    data.push_back(songs);
    file_size ++;
}

int database:: get_size() const{
    return data.size();
}


//let user add a song to the database
void database :: add(string input,  string fname){
    ofstream fileOut;
    fileOut.open(fname, ios::app);
    if (file_size==0) fileOut << input; //empty file situation
    else fileOut << endl << input;
    fileOut.close();

    read_file(input);
}   

//convert string to lower case
string database:: lower_case(string str){
    for (int i=0; i<str.size(); i++){
        if (str[i]-'A' >=0 && str[i] - 'Z' <=0){
            str[i]=str[i]+32;
        }
    }
    
    return str;
}


//user input error
void database:: name_error(string & input, string artist){
    bool error=false;
    string name{};
    string temp{};
    string a{};
    temp = lower_case(input);
    string temp_a = lower_case(artist);

    for (int i=0; i<data.size(); i++){
        name = data[i].get_name();
        name = lower_case(name);
        if (temp==name){
            a = data[i].get_artist();
            a=lower_case(a);
            cout << a << endl;
            if (temp_a==a){ // two songs can have the same name but must have different artist to be considered different
                cout << "Song already exist in database, please enter a new song:";
                getline(cin, input);
                name_error(input, artist); //check if new input has error
                break;
            }
        }
    }

    if (input.size()>50){ //any song that has a name size over 50 charcters is considered invalid
        error=true;
    }

    if (error==true){
        cout << "Error!!! Please re-enter a song name: ";
        getline(cin, input);
        name_error(input, artist);
    }
}

void database:: artist_error(string & input){
    bool error= false;
    if (input.size()>50){
        error = true;
    }
    
    if (error==true){
        cout << "Error!!! Please re-enter an artist name: ";
        getline(cin, input);
        artist_error(input);
    }
}

void database:: year_error(string & input){
    bool error=false;

    for (int i=0; i < input.size(); i++){
        if (input[i]-'0' < 0 || input[i]-'9' > 0){ 
            error=true;
            break;
        }
    }

    if (error==false && (stoi(input)>2023 || stoi(input) < 0)){
        error=true;
    }

    if (error==true){
        cout << "Error!!! Please re-enter year published: ";
        getline(cin, input);
        year_error(input);
        return;
    } 
}

void database:: plays_error(string & input){
    bool error=false;
    for (int i=0; i < input.size(); i++){
        if (input[i]-'0' < 0 || input[i]-'9' > 0){
            error=true;
        }
    }

    if (error==false && stoi(input)<0){
        error=true;
    }

    if (error==true){
        cout << "Error!!! Please re-enter number of plays: ";
        getline(cin, input);
        plays_error(input);
        return;
    }
}

void database:: album_error(string & input){
    bool error=false;
    if (input.size()>50){
        error=true;
    }

    if (error==true){
        cout << "Error!!! Please re-enter the name of album: " ;
        getline(cin, input);
        album_error(input);
    }
   
}


void database:: label_error(string & input){
    bool error = false;
    if (input.size()>50){
        error=true;
    }

    if (error==true){
        cout << "Error!!! Please re-enter the name of label: " ;
        getline(cin, input);
        label_error(input);
    }
     
}


//finding songs in database


void database:: find_name(string s){
    bool found = false;
    for(int i=0; i<data.size(); i++){
        string str= data[i].get_name();
        int l1=str.length();

        for(int j=0; l1>=s.length() && j<=l1-s.length(); j++){
            int k=0;
            while(k<s.length()){
                if (s[k]!=str[j+k]+32 && s[k]!=str[j+k]-32 && s[k]!=str[j+k]){
                    k=0;
                    break;
                }
                k++;
            }

            if(k==s.length()){
                print(i);
                store_string(i);
                found =true;
                break;
            }
            
        }
    }

    if(found==false) cout << "NO records found" << endl;
}

void database:: find_artist(string s){
    bool found = false;
    for(int i=0; i<data.size(); i++){
        string str= data[i].get_artist();
        int l1=str.length();

        for(int j=0; l1>=s.length() && j<=l1-s.length(); j++){
            int k=0;
            while(k<s.length()){
                if (s[k]!=str[j+k]+32 && s[k]!=str[j+k]-32 && s[k]!=str[j+k]){
                    k=0;
                    break;
                }
                k++;
            }

            if(k==s.length()){
                print(i);
                store_string(i);
                found =true;
                break;
            }
            
        }
    }

    if(found==false) cout << "NO records found" << endl;
}

void database:: find_album(string s){
    bool found = false;
    for(int i=0; i<data.size(); i++){
        string str= data[i].get_album();
        int l1=str.length();

        for(int j=0; l1>=s.length() && j<=l1-s.length(); j++){
            int k=0;
            while(k<s.length()){
                if (s[k]!=str[j+k]+32 && s[k]!=str[j+k]-32 && s[k]!=str[j+k]){
                    k=0;
                    break;
                }
                k++;
            }

            if(k==s.length()){
                print(i);
                store_string(i);
                found =true;
                break;
            }
            
        }
    }

    if(found==false) cout << "NO records found" << endl;
}

void database:: find_label(string s){
    bool found = false;
    for(int i=0; i<data.size(); i++){
        string str= data[i].get_label();
        int l1=str.length();

        for(int j=0; l1>=s.length() && j<=l1-s.length(); j++){
            int k=0;
            while(k<s.length()){
                if (s[k]!=str[j+k]+32 && s[k]!=str[j+k]-32 && s[k]!=str[j+k]){
                    k=0;
                    break;
                }
                k++;
            }

            if(k==s.length()){
                print(i);
                store_string(i);
                found =true;
                break;
            }
            
        }
    }

    if(found==false) cout << "NO records found" << endl;
}

void database:: find_int_rec(string s, char c){
    bool error=false;
    string first_int= "";
    string second_int = "";
    int range_count =0;

    for (int i=0; i < s.size(); i++){
        if(s[i]=='-' && range_count==0 && i!=0 && i!=s.size()-1){  // when user enters a range
            second_int=first_int;
            first_int = "";
            range_count++;
        }

        else if (s[i]-'0' < 0 || s[i]-'9' > 0){
            error=true;
            break;
        }
        else{
            first_int+=s[i];
        }
    }

    if(error==true){
        cout << "enter an appropriate value for an integer field:";
        getline(cin, s);
        find_int_rec(s,c);
        return;
    }

    if(c=='p' || c=='P') find_plays(s,first_int, second_int);
    else find_year(s,first_int,second_int);
}

void database :: find_year(string s, string year1, string year2){
    int year=0;
    int begin=0;
    int end=0;
    bool found =false;

    if(year2!=""){  // input is a range
        begin = min(stoi(year1), stoi(year2));
        end = max(stoi(year1), stoi(year2));

        if (begin <0 || begin>2023 || end<0 || end>2023){ 
            cout << "enter an appropriate search value:";
            getline(cin, s);
            find_int_rec(s, 'y');
            return;
        }

        for (int i=0; i<data.size(); i++){
            year=data[i].get_year();
            if (year>=begin && year<=end){
                print(i);
                store_string(i);
                found =true;
            }
        }
    }

    else { // input not a range
        begin = stoi(s);
        if(begin <0 || begin>2023){
            cout << "enter an appropriate search value:";
            getline(cin, s);
            find_int_rec(s,'y');
            return;
        }

        for (int i=0; i<data.size(); i++){
            year=data[i].get_year();
            if (year==begin){
                print(i);
                store_string(i);
                found = true;
            }
        }
    }

    if (found==false) cout << "no records found" <<endl;
}

void database:: find_plays(string s, string plays1, string plays2){
    int plays=0;
    int begin=0;
    int end=0;
    bool found =false;

    if(plays2!=""){  // input is a range
        begin = min(stoi(plays1), stoi(plays2));
        end = max(stoi(plays1), stoi(plays2));

        if (begin <0 || begin>INT_MAX || end<0 || end>INT_MAX){ 
            cout << "enter an appropriate search value:";
            getline(cin, s);
            find_int_rec(s, 'y');
            return;
        }

        for (int i=0; i<data.size(); i++){
            plays=data[i].get_plays();
            if (plays>=begin && plays<=end){
                print(i);
                store_string(i);
                found =true;
            }
        }
    }

    else { // input not a range
        begin = stoi(s);
        if(begin <0 || begin>INT_MAX){
            cout << "enter an appropriate search value:";
            getline(cin, s);
            find_int_rec(s,'y');
            return;
        }

        for (int i=0; i<data.size(); i++){
            plays=data[i].get_plays();
            if (plays==begin){
                print(i);
                store_string(i);
                found = true;
            }
        }
    }

    if (found==false) cout << "no records found" <<endl;
}



void database:: print(int index){
    cout << data[index].get_name() << ", " << data[index].get_artist()<< ", " <<data[index].get_year()
    <<", " << data[index].get_album() << ", " <<data[index].get_plays() << ", "<< data[index].get_label() <<endl;
}

void database:: clear_info(){ selected_songs.clear();}

void database:: store_string (int index){ //stores information that the user wants to find 
    string str;
    string sep= "| ";
    string str_year = to_string(data[index].get_year());
    string str_plays = to_string(data[index].get_plays());
    str = data[index].get_name()+ sep + data[index].get_artist()+ sep+ str_year + sep + 
    data[index].get_album() + sep + str_plays + sep + data[index].get_label();
    selected_songs.push_back(str);
}

void database:: delete_record(){
    char choice = 'n';
    if (selected_songs.size()>0){
        cout << "-----------------" << endl << "Are you sure about deleting the above songs (Y/N): ";
        cin >> choice;
    }

    if (choice=='y' || choice == 'Y') {
        cout << choice <<endl;
        ifstream fileIn;
        string line;
        int count=0;
        ofstream fileOut ("temp.txt");
        data.clear();
        file_size=0;
        fileIn.open("database.txt");

        while (!fileIn.eof()){
            getline(fileIn, line);
            count=0;

            for (int i=0; i<selected_songs.size(); i++){
                if(line!=selected_songs[i]) count ++;
                else break; 
            }

            if(count == selected_songs.size()){
                add(line, "temp.txt");
                read_file(line);
            }
        }

        remove("database.txt");
        rename("temp.txt","database.txt");
        fileOut.close();
        fileIn.close();
    }
}

bool database:: reverse_order(){
    char c;
    cout << "Type R for sorting the records in reverse alphabetic order, or type anything else to continue:";
    cin >> c;
    cout << endl;
    if (c=='r' || c=='R') return true;
    return false;
}


//using heapsort to sort songs
void database:: sort_name(){
    bool reverse = reverse_order();

    if (reverse==false){
        for(int i=0; i<data.size(); i++){
            int index= i;

            //heapinsert
            while(lower_case(data[index].get_name())>lower_case(data[(index-1)/2].get_name())){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int largest =(left+1 < heapsize && lower_case(data[left+1].get_name())>lower_case(data[left].get_name()))?left+1:left;
                largest = lower_case(data[largest].get_name()) > lower_case(data[index].get_name())? largest:index;
                
                if(largest == index) break;
                swap (data[index], data[largest]);
                index=largest;
                left = 2*index+1;
            }

            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }

    else {
        for(int i=0; i<data.size(); i++){
            int index=i;

            //heapinsert
            while(lower_case(data[index].get_name())<lower_case(data[(index-1)/2].get_name())){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int smallest =(left+1 < heapsize && lower_case(data[left+1].get_name())<lower_case(data[left].get_name()))?left+1:left;
                smallest = lower_case(data[smallest].get_name()) < lower_case(data[index].get_name())? smallest:index;
                if(smallest == index) break;
                swap (data[index], data[smallest]);
                index=smallest;
                left = 2*index+1;
            }
            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }
}

void database:: sort_artist(){
    bool reverse = reverse_order();
    if (reverse==false){
        for(int i=0; i<data.size(); i++){
            int index= i;

            //heapinsert
            while(lower_case(data[index].get_artist())>lower_case(data[(index-1)/2].get_artist())){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int largest =(left+1 < heapsize && lower_case(data[left+1].get_artist())>lower_case(data[left].get_artist()))?left+1:left;
                largest = lower_case(data[largest].get_artist()) > lower_case(data[index].get_artist())? largest:index;
                
                if(largest == index) break;
                swap (data[index], data[largest]);
                index=largest;
                left = 2*index+1;
            }

            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }

    else {
        for(int i=0; i<data.size(); i++){
            int index=i;

            //heapinsert
            while(lower_case(data[index].get_artist())<lower_case(data[(index-1)/2].get_artist())){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int smallest =(left+1 < heapsize && lower_case(data[left+1].get_artist())<lower_case(data[left].get_artist()))?left+1:left;
                smallest = lower_case(data[smallest].get_artist()) < lower_case(data[index].get_artist())? smallest:index;
                if(smallest == index) break;
                swap (data[index], data[smallest]);
                index=smallest;
                left = 2*index+1;
            }

            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }
}

void database:: sort_album(){
   bool reverse = reverse_order();

    if (reverse==false){
        for(int i=0; i<data.size(); i++){
            int index= i;

            //heapinsert
            while(lower_case(data[index].get_album())>lower_case(data[(index-1)/2].get_album())){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int largest =(left+1 < heapsize && lower_case(data[left+1].get_album())>lower_case(data[left].get_album()))?left+1:left;
                largest = lower_case(data[largest].get_album()) > lower_case(data[index].get_album())? largest:index;
                
                if(largest == index) break;
                swap (data[index], data[largest]);
                index=largest;
                left = 2*index+1;
            }

            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }

    else {
        for(int i=0; i<data.size(); i++){
            int index=i;

            //heapinsert
            while(lower_case(data[index].get_album())<lower_case(data[(index-1)/2].get_album())){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int smallest =(left+1 < heapsize && lower_case(data[left+1].get_album())<lower_case(data[left].get_album()))?left+1:left;
                smallest = lower_case(data[smallest].get_album()) < lower_case(data[index].get_album())? smallest:index;
                if(smallest == index) break;
                swap (data[index], data[smallest]);
                index=smallest;
                left = 2*index+1;
            }
            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }
}

void database:: sort_label(){
   bool reverse = reverse_order();

    if (reverse==false){
        for(int i=0; i<data.size(); i++){
            int index= i;

            //heapinsert
            while(lower_case(data[index].get_label())>lower_case(data[(index-1)/2].get_label())){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int largest =(left+1 < heapsize && lower_case(data[left+1].get_label())>lower_case(data[left].get_label()))?left+1:left;
                largest = lower_case(data[largest].get_label()) > lower_case(data[index].get_label())? largest:index;
                
                if(largest == index) break;
                swap (data[index], data[largest]);
                index=largest;
                left = 2*index+1;
            }

            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }

    else {
        for(int i=0; i<data.size(); i++){
            int index=i;

            //heapinsert
            while(lower_case(data[index].get_label())<lower_case(data[(index-1)/2].get_label())){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int smallest =(left+1 < heapsize && lower_case(data[left+1].get_label())<lower_case(data[left].get_label()))?left+1:left;
                smallest = lower_case(data[smallest].get_label()) < lower_case(data[index].get_label())? smallest:index;
                if(smallest == index) break;
                swap (data[index], data[smallest]);
                index=smallest;
                left = 2*index+1;
            }
            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }
}

void database :: sort_year(){
    bool reverse = reverse_order();

    if (reverse==true){
        for(int i=0; i<data.size(); i++){
            int index= i;

            //heapinsert
            while(data[index].get_year()>data[(index-1)/2].get_year()){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int largest =(left+1 < heapsize && data[left+1].get_year()>data[left].get_year())?left+1:left;
                largest = data[largest].get_year() > data[index].get_year()? largest:index;
                
                if(largest == index) break;
                swap (data[index], data[largest]);
                index=largest;
                left = 2*index+1;
            }

            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }

    else {
        for(int i=0; i<data.size(); i++){
            int index=i;

            //heapinsert
            while(data[index].get_year()<data[(index-1)/2].get_year()){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int smallest =(left+1 < heapsize && data[left+1].get_album()<data[left].get_album())?left+1:left;
                smallest = data[smallest].get_year() < data[index].get_year()? smallest:index;
                if(smallest == index) break;
                swap (data[index], data[smallest]);
                index=smallest;
                left = 2*index+1;
            }
            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }
}

void database :: sort_plays(){
    bool reverse = reverse_order();

    if (reverse==true){
        for(int i=0; i<data.size(); i++){
            int index= i;

            //heapinsert
            while(data[index].get_plays()>data[(index-1)/2].get_plays()){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int largest =(left+1 < heapsize && data[left+1].get_plays()>data[left].get_plays())?left+1:left;
                largest = data[largest].get_plays() > data[index].get_plays()? largest:index;
                
                if(largest == index) break;
                swap (data[index], data[largest]);
                index=largest;
                left = 2*index+1;
            }

            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }

    else {
        for(int i=0; i<data.size(); i++){
            int index=i;

            //heapinsert
            while(data[index].get_plays()<data[(index-1)/2].get_plays()){
                swap (data[index], data[(index-1)/2]);
                index=(index-1)/2;
            }
        }

        int heapsize = data.size();
        int left = 1;
        int index =0;

        swap(data[0], data[heapsize-1]);
        heapsize--;

        while (heapsize>0){
            while (left<heapsize){
                int smallest =(left+1 < heapsize && data[left+1].get_plays()<data[left].get_plays())?left+1:left;
                smallest = data[smallest].get_plays() < data[index].get_plays()? smallest:index;
                if(smallest == index) break;
                swap (data[index], data[smallest]);
                index=smallest;
                left = 2*index+1;
            }
            swap(data[0], data[--heapsize]);
            index=0;
            left=1;
        }
    }
}

database::~database(){}
