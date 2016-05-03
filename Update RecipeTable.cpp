#include "RecipeTable.h"
#include <iostream>
#include <sstream>
#include <list>
using namespace std;
///////////////////////////////////////////// rNode Class Functions /////////////////////////////////////////////
void rNode::addIngredient(string name, string tQuant)
{
    double quant;
    string unit,token;
    stringstream ss(tQuant);
    ss >> quant;
    getline(ss,unit);
    if(this -> ingredient == nullptr) {
        this->ingredient = new Ingredient(name,quant,unit);
    } else {
        Ingredient * current = this -> ingredient;
        Ingredient * previous;
        while (current != nullptr) {
            previous = current;
            current = current -> next;
        }
        current = new Ingredient(name,quant,unit);
        previous -> next = current;
        current -> previous = previous;

    }
}

void rNode::deleteIngredient(string title)
{
    rNode * current = this;
    bool found = false;
    while(current != nullptr) {
        cout << current -> name << " " << current -> ingredient -> name << endl;
        if(current -> ingredient -> name != title) {
            current = current -> next;
        } else {
            found = true;
            break;
        }
    }

    if (found == true) {
        cout << "Found it ;)" << endl;
    } else {
        cout << "Ingredient not found." << endl;
    }
}

void rNode::printIngredients()
{
    cout << "This recipe makes a total of " << this->servingSize << " servings." << endl;
    Ingredient * current = this -> ingredient;
    if (current == nullptr) {
        cout << "No ingredients found." << endl;
    } else {
        while(current != nullptr) {
            cout << current -> quantity << " " << current -> unit << " of " << current -> name << endl;
            current = current -> next;
        }
    }
}

void rNode::adjustSize(double sSize)
{
    double servingRatio = (sSize/this -> servingSize);
    this -> servingSize = sSize;
    Ingredient * current = this -> ingredient;
    while(current != nullptr) {
        current -> quantity = current -> quantity * servingRatio;
        current = current -> next;
    }
}
void rNode::addStep(string step)
{

    if (this->dList == nullptr) {
        this -> dList = new Directions(step);
    } else {
        Directions * current = this -> dList;
        Directions * temp;
        while(current != nullptr) {
            temp = current;
            current = current -> next;
        }
        current = new Directions(step);
        temp -> next = current;
        current -> previous = temp;
    }
}

void rNode::printDirections()
{
    int counter = 1;
    Directions * current = this -> dList;
    if (current == nullptr) {
        cout << "No steps found" << endl;
    } else {
        while(current != nullptr) {
            cout << counter << ". " << current -> step;
            current = current -> next;
            counter++;
        }
    }
}
///////////////////////////////////////////// RecipeTable Class Functions /////////////////////////////////////////////
RecipeTable::RecipeTable()
{
    for (int i = 0; i < tableSize; i++)
        hashTable[i] = nullptr;
}

int RecipeTable::hashSum(string inString, int tableSize)
{
    int sum = 0;
    for (int i = 0; i < inString.size(); i++)
        sum = sum + inString[i];
    return sum % 20;
}
void RecipeTable::addRecipe(string title)
{

    int index = hashSum(title, tableSize);
    cout << index << endl;
    rNode* current = hashTable[index];
    rNode * previous;
    if (hashTable[index] == nullptr) {
        hashTable[index] = new rNode(title);
        current = hashTable[index];
        //return hashTable[index];
    } else {
        while(current != nullptr)
            previous = current;
        current = current -> next;
        current = new rNode (title);
        current -> previous = previous;
        // return current -> next;
    }
    string ingredient = "3", tQuant;
    cout << "Now, begin entering ingredients. The program will prompt you for the ingredient, followed by the number "
         "of ingredients. Remember - the default portion is 4 serving sizes per serving!" << endl;
    while(ingredient != "") {
        cout << "Enter an ingredient: ";
        getline(cin,ingredient);
        if (ingredient == "")
            break;
        cout << "Enter the quantity and units: ";
        getline(cin,tQuant);
        current->addIngredient(ingredient, tQuant);
    }
    string step = "placeholder";
    cout << "Awesome! Now, we will begin inputting the steps. The program won't update the quantities in the steps, "
         "so try to be general! When you are done, simply hit enter." << endl;
    while(step != "") {
        cout << "Enter a step:" << endl;
        getline(cin,step);
        current->addStep(step);
    }
}

void RecipeTable::searchRecipe(string title)
{
   int sum = hashSum(title, tableSize);
    rNode * current = hashTable[sum];
    if(current == nullptr || title == "")
        cout << "Recipe Not found" << endl;
    else if(current != nullptr || title != "") {
        while(current != nullptr) {
            if(current->name == title) {
                cout <<"The recipe: " << current -> name << " was found." << endl;
                Menu(current -> name, current);
            }
            else if(current->name != title){

            }
            current = current -> next;
        }
            //cout << "Recipe Not found, Consider adding it." << endl;
    }
}

void RecipeTable::deleteRecipe(std::string name)
{
    int sum = hashSum(name, tableSize);
    if (hashTable[sum] == nullptr)
        cout << "Not found. Did you perhaps mistype it? Or, maybe you haven't added this." << endl;
    else {
        bool found = false;
        rNode * q = hashTable[sum];
        while(q != nullptr) {
            if (q->name == name) {
                found = true;
                if(q == hashTable[sum] && q-> next != nullptr) {
                    q -> next -> previous = nullptr;
                    hashTable[sum] = q->next;
                    cout << "Deleting " << q->name << "..." << endl;
                    delete q;
                    break;
                } else if(q == hashTable[sum] && q -> next == nullptr) {
                    hashTable[sum] = nullptr;
                    cout << "Deleting " << q->name << "..." << endl;
                    delete q;
                    break;
                } else if(q -> next == nullptr) {
                    q -> previous -> next = nullptr;
                    cout << "Deleting " << q->name << "..." << endl;
                    delete q;
                    break;
                } else {
                    q -> previous -> next = q -> next;
                    q -> next -> previous = q -> previous;
                    cout << "Deleting " << q->name << "..." << endl;
                    delete q;
                    break;
                }
            } else
                q = q -> next;
        }
        if (found == false)
            cout << "Not found. Did you perhaps mistype it? Or, maybe you haven't added this." << endl;
    }
}

void RecipeTable::printMenu(string title)
{
    cout << "====== Recipe Menu for: '" << title << "' ======" << endl;
    cout << "1. Print Ingredients" << endl;
    cout << "2. Add an Ingredient" << endl;
    cout << "3. Delete an Ingredient" << endl;
    cout << "4. Modify serving sizes" << endl;
    cout << "5. Print Directions" << endl;
    cout << "6. Return to Main Menu" << endl;
}

void RecipeTable::Menu(string title, rNode * current)
{
    char choice = '0';
    double sSize;
    string iName,tQuant;
    while(choice != '6') {
        printMenu(title);
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case '1':
            cout << "Printing Ingredients..." << endl;
            current -> printIngredients();
            break;
        case '2':
            cout << "Enter an ingredient: " << endl;
            getline(cin,iName);
            cout << "Enter the quantity and unit (Ex enter: '3 grams of sugar): " << endl;
            getline(cin,tQuant);
            current -> addIngredient(iName,tQuant);
            break;
        case '3':
            cout << "Which ingredient would you like to delete?" << endl;
            getline(cin,iName);
            current -> deleteIngredient(iName);
            break;
        case '4':
            cout << "This recipe makes " << current -> servingSize << " servings. How many servings would you like to adjust it to? :" << endl;
            cin >> sSize;
            current -> adjustSize(sSize);
            cout << "Done" << endl;
        case '5':
            cout << "Printing Directions..." << endl;
            current -> printDirections();
            break;
        case '6':
            cout << "Returning to main menu..." << endl;
            break;
        }
    }
}

void RecipeTable::printTable()
{
    list<string> myList;
    bool isEmpty = true;
    for (int i = 0; i < tableSize; i++) {
        rNode * current = hashTable[i];
        if (current != nullptr) {
            while(current != nullptr) {
                isEmpty = false;
                myList.push_back(current -> name);
                current = current -> next;
            }
        }
    }
    if(isEmpty == true){
        cout << "database is empty" << endl;
    }
    myList.sort();
    for (auto i = myList.begin(); i != myList.end(); ++i) {
        cout << *i << endl;
    }
}
