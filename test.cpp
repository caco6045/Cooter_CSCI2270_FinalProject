#include <iostream>
using namespace std;

void printMenu()
{
    cout << "1. This is the only option" << endl;
}
int main()
{
    bool readme = false;
    char choice = 0;
    while(choice != '2'){
        printMenu();
        cin >> choice;
        cin.ignore();
        switch (choice){
            case '1':{
                if(readme == false){
                    cout <<"Do you want to view the readme?" << endl;
                    string ans;
                    getline(cin,ans);
                    readme = true;
                    if(ans == "yes"){
                        //display the readme
                    }
                }
                cout << "Enter what you want to add" << endl;
                string item;
                getline(cin,item);
                cout << item << endl;
                //add item to class, gets some more inputs from user
                break;
                }
            case '2':
                cout << "bye" << endl;
                break;
            }
        }
    }
