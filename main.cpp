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

 void readMe(int choice)
{
    if (choice == 1) { //how to add recipes.
        cout << "This short readme will instruct you on how to add a recipe. The default amount of servings for a recipe will be "
             "4 servings, as this is a standard amount of servings to expect out of a recipe, and will make it easier for users "
             "to modify how many recipes they want in their recipe. First, the program will prompt you for the title of the recipe. "
             "Once you have entered the recipe you want to add to the database, it will ask you for ingredients. Type the ingredient, "
             "then press enter. Afterwards, type the ingredient. Continue adding ingredients until you are finished. When you are done, simply hit enter."
             "The program will then prompt you for steps, if you so choose. Else, you can ignore this and add them later if you so choose!" << endl;
    }
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
//<<<<<<< HEAD
        getline(cin,choice);
        if(choice == "1") {
//======= added by contributor
            while (readme == false) {
                cout << "Do you want to view the readme? This will only display once! Enter yes or no" << endl;
                string ans;
                getline(cin,ans);
                readme = true;
                if(ans == "yes") {
                    readMe(1);
                }
                else if(ans == "no"){
                    //do nothing
                }
                else{
                    cout <<"Please type yes or no!" << endl;
                    readme = false;
                }
            }
//>>>>>>> 37217cc75709db44f0d3e21df61686f6811c6720
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
            rTable->printTable();
            }
        }
        else if(choice == "5") {
            //exit the program.
            cout << "Thanks, for using this software. Good-bye n_n" << endl;
        }
    }

}
