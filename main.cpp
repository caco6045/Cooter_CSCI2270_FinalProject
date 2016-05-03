#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "RecipeTable.h"
using namespace std;

//create a menu function
void printMenu()
{
    cout << endl;
    cout << "=======Main Menu=======" << endl;
    cout << "1. Add Recipe" << endl;
    cout << "2. Search Recipe" << endl;
    cout << "3. Delete Recipe" << endl;
    cout << "4. Print contents" << endl;
    cout << "5. Exit" << endl;
}




//begin main function
int main()
{
    //create a new instance of Recipe Table
    RecipeTable * rTable = new RecipeTable();
    rTable -> loadFile();
    bool readme = false; //bool value to keep track of readme so it doesn't display every time
    string choice = "null";
    string rName;
    while(choice != "5") { //menu case
        printMenu();
        getline(cin,choice);
        if(choice == "1") {
            cout << "Enter the name of the recipe you wish to add: ";
            getline(cin,rName);
            //adds the recipe to the recipe table
            rTable->addRecipe(rName);
        }
        else if(choice == "2") {
            //search the recipes
            cout << "Enter the name of the recipe you wish to search for: ";
            getline(cin,rName);
            rTable->searchRecipe(rName);
        }
        else if(choice == "3") {
            //delete a recipe
            cout << "Enter what recipe you wish to delete: ";
            getline(cin,rName);
            rTable->deleteRecipe(rName);
        }
        else if(choice == "4") {
            //print the database in alphabetical order
            {
            cout << "Printing database..." << endl;
            rTable->printTable();
            }
        }
        else if(choice == "5") {
            //exit the program.
            cout << "Thanks, for using this software. Good-bye n_n" << endl;
        }
    }

}
