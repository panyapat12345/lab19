#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream fin(filename);
    string s;
    char n[20];
    int a, b, c;
    while(getline(fin, s)){
        sscanf(s.c_str(), "%[^:]: %d %d %d", n, &a, &b, &c);
        names.push_back(n);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
}

void getCommand(string &command, string &key){      // "name Monkey D. Luffy" 
    string s;                                       // "%s %[^\n]" 
    char t1[10], t2[20];
    cout << "Please input your command: ";
    getline(cin, s);
    sscanf(s.c_str(), "%s %[^\n]}", t1, t2);
    command = t1;
    key = t2;

}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool status = false;
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            status = true;
        }
    }

    if(status == false) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool status = false;
    cout << "---------------------------------" << endl;
    for(unsigned int i = 0; i < names.size(); i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            status = true;
        }
    }
    
    if(status == false) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;