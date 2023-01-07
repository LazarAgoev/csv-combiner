#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
//#include <thread> for optimization purposes


using namespace std;

void process(string path, vector<string> header); 
vector<string> get_header(int argc, char *argv[]);
vector<string> split(string line);
string get_file_name(string path);

int main(int argc, char *argv[]){

    if(argc<2){
        cout<<"No arguments were provided"<<endl;
        return 0;
    }

    //Prints out the first line of the header
    vector<string> header = get_header(argc, argv);
    
    //Prints the rest of the lines
    for(int i = 1; i<argc; i++){
        process(argv[i], header);
    }
    
    return 0;
}

string get_file_name(string path){
    /*
        This function takes in the path of a file 
        and returns only the name of the file
    */
    string name = path;
    for(int i=path.length()-1;i>0;i--){
        if(path[i] == '/'){
            name = path.substr(i+1);
            break;
        }
    }
    name = '\"'+name+'\"';
    return name;
}
vector<string> get_header(int argc, char *argv[]){
    /*
        This function takes in the paths of a files,
        prints out the header, 
        and returns a vector of all columns' names
    */

    vector<string> header = {};
    vector<string> temp;
    for(int i = 1; i<argc; i++){
        ifstream fin(argv[i]);
        if(!fin){
            cout<<"Error. Could not open file "<<argv[i]<<endl;
            throw(1);
        }
        string line;
        getline(fin, line);
        temp = split(line);
        for(int i=0; i<temp.size();i++){
            if(find(header.begin(), header.end(), temp[i]) == header.end()){
                header.push_back(temp[i]);
            }
        }
        fin.close();
    }

    header.push_back("\"filename\"");

    for(int i=0; i<header.size()-1;i++){
        cout<<header.at(i)<<',';
    }
    cout<<header.at(header.size()-1)<<endl;
    

    return header;
}
void process(string path, vector<string> header){
    /*
        Prints out all the lines
    */
    ifstream fin(path);
    string line, name;
    name = get_file_name(path);
    getline(fin, line);
    vector<string> temp = split(line);
    vector<string> temp_header ={};


    for(int i = 0; i<header.size();i++){
        /*
            Checking wich columns are mising from this file
        */
        if(header[i] == "\"filename\"" || find(temp.begin(), temp.end(), header[i]) != temp.end()){
            temp_header.push_back(header[i]);
        }
        else{
            temp_header.push_back(" ");
        }
    }


    
    while(getline(fin, line)){
        temp = split(line);
        int j=0;
        for(int i=0; i<temp_header.size()-1;i++){
            if(temp_header[i]==" "){
                cout<<" ,";
            }
            else{
                cout<<temp[j]<<",";
                j++;
            }

        }
        cout<<name<<endl;
    }

    fin.close();
    return;
}
vector<string> split(string line){
    /*
        This function is an equivalent to a python function ".split(',')"
        Takes in a string (a row of a table) and returns a vector to all the cells in the row
    */
    vector<string> ans = {};
    line.pop_back();
    for(int i=0; i<line.length(); i++){
        if(line[i]==','){
            ans.push_back(line.substr(0,i));
            line=line.substr(i+1);
        }
    }
    ans.push_back(line);
    return ans;
}