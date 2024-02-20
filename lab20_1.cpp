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

void importDataFromFile(const string& filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Unable to open the file." << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(file,line)){
        size_t pos = line.find(":");
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            names.push_back(name);

            string scoreStr = line.substr(pos + 1);
            int score1 = 0, score2 = 0, score3 = 0;
            sscanf(scoreStr.c_str(), "%d %d %d", &score1, &score2, &score3);
            int totalScore = score1 + score2 + score3;
            scores.push_back(totalScore);
            
            char grade = score2grade(totalScore);
            grades.push_back(grade);
        }
    }
    file.close();
}

void getCommand(string& command, string& key) {
    cout << "Please input your command: ";
    string input;
    getline(cin, input);

    size_t pos = input.find(" ");
    if (pos != string::npos) {
        command = input.substr(0, pos);
        key = input.substr(pos + 1);
    } else {
        command = input;
        key = "";
    }
}

void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key) {
    bool found = false;
    for (size_t i = 0; i < names.size(); ++i) {
        if (toUpperStr(names[i]) == key) {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            found = true;
        }
    }
    if (!found) {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key) {
    bool found = false;
    cout << "---------------------------------\n";
    for (size_t i = 0; i < grades.size(); ++i) {
        if (toUpperStr(string(1, grades[i])) == key) {
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    
    if (!found) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
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
}