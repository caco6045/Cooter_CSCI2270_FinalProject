#include "RecipeTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
using namespace std;
///////////////////////////////////////////// rNode Class Functions /////////////////////////////////////////////
void rNode::addIngredient(string name, string tQuant)
{
    //this splits apart the ingredient string to an int and a string, and adds it to the ingredient list
    //the ingredient list is a linked list
    double quant;
    string unit,token;
    stringstream ss(tQuant);
    ss >> quant;
    getline(ss,unit);
    if(this -> ingredient == nullptr)
    {
        this->ingredient = new Ingredient(name,quant,unit);
    }
    else
    {
        Ingredient * current = this -> ingredient;
        Ingredient * previous;
        while (current != nullptr)
        {
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
    //deletes an element from the ingredient linked list, accounting for all
    //cases that could go wrong
    rNode * current = this;
    rNode * previous;
    bool found = false;
    while(current != nullptr)
    {

        if(current -> ingredient -> name != title)
        {
            previous = current;
            current = current -> next;
        }
        else
        {
            found = true;
            break;
        }
    }

    if (found == true)
    {
        if (current -> previous == nullptr)
        {
            current -> ingredient = current -> ingredient -> next;
        }
        else if (current -> next == nullptr)
        {
            previous -> next = nullptr;
            delete current;
        }
        else
        {
            previous -> next = current -> next;
            current -> next -> previous = previous;
            delete current;
        }
        cout << "successfully deleted" << endl;
    }
    else
    {
        cout << "Ingredient not found." << endl;
    }
}

void rNode::printIngredients()
{
    //prints the ingredient -> simply transverses the linked list
    cout << "This recipe makes a total of " << this->servingSize << " servings." << endl;
    Ingredient * current = this -> ingredient;
    if (current == nullptr)
    {
        cout << "No ingredients found." << endl;
    }
    else
    {
        while(current != nullptr)
        {
            cout << current -> quantity << " " << current -> unit << " of " << current -> name << endl;
            current = current -> next;
        }
    }
}

void rNode::adjustSize(double sSize)
{
    //adjusts the size. Since the size is given in double, allows for half portions too.
    //Allows you to adjust the size to anything such as 1, 2, 3, or 10 servings!
    double servingRatio = (sSize/this -> servingSize);
    this -> servingSize = sSize;
    Ingredient * current = this -> ingredient;
    while(current != nullptr)
    {
        current -> quantity = current -> quantity * servingRatio;
        current = current -> next;
    }
}
void rNode::addStep(string step)
{
    //adds a step to the linked list functionality.
    if (this->dList == nullptr)
    {
        this -> dList = new Directions(step);
    }
    else
    {
        Directions * current = this -> dList;
        Directions * temp;
        while(current != nullptr)
        {
            temp = current;
            current = current -> next;
        }
        current = new Directions(step);
        temp -> next = current;
        current -> previous = temp;
    }
}

void rNode::insertStep(string step, int stepNum)
{
    //insert a step after the step
    int counter = 1;
    Directions * current = this -> dList;
    while(current != nullptr && counter != stepNum && stepNum != 0)
    {
        current = current -> next;
        counter++;
    }

    if(current == nullptr)
    {
        cout << "Invalid step input." << endl;
    }
    else
    {
        Directions * temporary = new Directions(step);
        if(stepNum == 0)
        {
            this -> dList = temporary;
            temporary -> next = current;
        }
        else if (current -> next == nullptr)
        {
            current -> next = temporary;
        }
        else
        {
            temporary -> next = current -> next;
            current -> next = temporary;
            temporary -> next -> previous = temporary;
        }
    }
}

void rNode::printDirections()
{
    //prints the direction linked list (step)
    int counter = 1;
    Directions * current = this -> dList;
    if (current == nullptr)
    {
        cout << "No steps found" << endl;
    }
    else
    {
        while(current != nullptr)
        {
            if(current -> step == "")
                break;
            cout << counter << ". " << current -> step << endl;
            current = current -> next;
            counter++;
        }
    }
}

void rNode::deleteStep(int stepNum)
{
    int counter = 1;
    Directions * current = this -> dList;
    while(current != nullptr && counter != stepNum)
    {
        counter++;
        current = current -> next;
    }

    if (current == nullptr)
    {
        cout << "Error, not a valid step." << endl;
    }
    else
    {
        if (current -> previous == nullptr || stepNum == 1)
        {
            this -> dList = current -> next;
        }
        else if (current -> next == nullptr)
        {
            current -> previous -> next = nullptr;
        }
        else
        {
            current -> previous -> next = current -> next;
            current -> next -> previous = current -> previous;
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
    rNode* current = hashTable[index];
    rNode * previous;
    //adds an entry to the hash table/linked list
    if (hashTable[index] == nullptr)
    {
        hashTable[index] = new rNode(title);
        current = hashTable[index];
    }
    else
    {
        if(current != nullptr)
            previous = current;
        current -> next= new rNode (title);
        current = current -> next;
        current -> previous = previous;

    }
    string ingredient = "3", tQuant;
    cout << "Now, begin entering ingredients. The program will prompt you for the ingredient, followed by the number "
         "of ingredients. For example:" << endl;
    cout << "-> Enter an ingredient: Milk" << endl;
    cout << "-> Enter the quantity and units: 2 cups" << endl;
    cout <<"Remember - the default portion is 4 serving sizes per serving! Simply press enter without any input to stop adding ingredients." << endl;
    while(ingredient != "")   //prompts the user for an ingredient until they hit enter.
    {
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
    while(step != "")
    {
        cout << "Enter a step:" << endl;
        getline(cin,step);
        current->addStep(step);
    }
}


void RecipeTable::searchRecipe(string title)
{
    //search for a recipe in the hash table
    int sum = hashSum(title, tableSize);
    rNode * current = hashTable[sum];

    if(current == nullptr)
        cout << "Not found. Consider adding it." << endl;
    else
    {
        while(current != nullptr && current -> name != title)
        {
            current = current -> next;
        }
        if (current != nullptr)
        {
            cout <<"The recipe: " << current -> name << " was found." << endl;
            Menu(current -> name, current);
        }
        else
            cout << "Not found. Consider adding it." << endl;
    }

}

void RecipeTable::deleteRecipe(std::string name)
{
    //deletes the recipe, and fixes errors that happen when the linked list is broken
    int sum = hashSum(name, tableSize);
    if (hashTable[sum] == nullptr)
        cout << "Not found. Did you perhaps mistype it? Or, maybe you haven't added this." << endl;
    else
    {
        bool found = false;
        rNode * q = hashTable[sum];
        while(q != nullptr)
        {
            if (q->name == name)
            {
                found = true;
                if(q == hashTable[sum] && q-> next != nullptr)
                {
                    q -> next -> previous = nullptr;
                    hashTable[sum] = q->next;
                    cout << "Deleting " << q->name << "..." << endl;
                    delete q;
                    break;
                }
                else if(q == hashTable[sum] && q -> next == nullptr)
                {
                    hashTable[sum] = nullptr;
                    cout << "Deleting " << q->name << "..." << endl;
                    delete q;
                    break;
                }
                else if(q -> next == nullptr)
                {
                    q -> previous -> next = nullptr;
                    cout << "Deleting " << q->name << "..." << endl;
                    delete q;
                    break;
                }
                else
                {
                    q -> previous -> next = q -> next;
                    q -> next -> previous = q -> previous;
                    cout << "Deleting " << q->name << "..." << endl;
                    delete q;
                    break;
                }
            }
            else
                q = q -> next;
        }
        if (found == false)
            cout << "Not found. Did you perhaps mistype it? Or, maybe you haven't added this." << endl;
    }
}

void RecipeTable::printMenu(string title)
{
    cout << endl;
    cout << "====== Recipe Menu for: '" << title << "' ======" << endl;
    cout << "1. Print Ingredients" << endl;
    cout << "2. Add an Ingredient" << endl;
    cout << "3. Delete an Ingredient" << endl;
    cout << "4. Modify serving sizes" << endl;
    cout << "5. Print Directions" << endl;
    cout << "6. Add a Step" << endl;
    cout << "7. Delete a Step" << endl;
    cout << "8. Return to Main Menu" << endl;
}

void RecipeTable::Menu(string title, rNode * current)
{
    string choice = "0";
    double sSize;
    int stepNum;
    string step;
    string iName,tQuant;
    while(choice != "8")
    {
        printMenu(title);
        getline(cin,choice);
        if(choice == "1")
        {
            cout << endl;
            cout << "Printing Ingredients..." << endl;
            current -> printIngredients();
        }
        else if (choice == "2")
        {
            cout << endl;
            cout << "Enter an ingredient (Don't worry about amount yet): " << endl;
            getline(cin,iName);
            cout << "Enter the quantity and unit (Ex enter: '3 grams): " << endl;
            getline(cin,tQuant);
            current -> addIngredient(iName,tQuant);
        }
        else if (choice == "3")
        {
            cout << endl;
            cout << "Which ingredient would you like to delete?" << endl;
            getline(cin,iName);
            current -> deleteIngredient(iName);
        }
        else if (choice == "4")
        {
            cout << endl;
            cout << "This recipe makes " << current -> servingSize << " servings. How many servings would you like to adjust it to? : ";
            cin >> sSize;
            current -> adjustSize(sSize);
            cout << "Done" << endl;
            cout << endl;
        }
        else if (choice == "5")
        {
            cout << endl;
            cout << "Printing Directions..." << endl;
            current -> printDirections();
            cout << endl;
        }
        else if (choice == "6")
        {
            cout << "Enter which number you wish to add a step after (use 0 for start): ";
            getline(cin,tQuant);
            stepNum = stoi(tQuant);
            cout << "Now enter the step you wish to add on the next line: " << endl;
            getline(cin,step);
            current -> insertStep(step,stepNum);
            cout << "Done!" << endl;
        }
        else if(choice == "7")
        {
            cout << "Which step number do you wish to delete?" << endl;
            getline(cin,tQuant);
            stepNum = stoi(tQuant);
            current -> deleteStep(stepNum);
        }
        else if (choice == "8")
        {
            cout << endl;
            cout << "Returning to main menu..." << endl;
            break;
        }
    }
}

void RecipeTable::printTable()
{
    //uses the list functionality to print the hash table in alphabetical order
    list<string> myList;
    for (int i = 0; i < tableSize; i++)
    {
        rNode * current = hashTable[i];
        if (current != nullptr)
        {
            while(current != nullptr)
            {
                myList.push_back(current -> name);
                current = current -> next;
            }
        }
    }
    myList.sort();
    for (auto i = myList.begin(); i != myList.end(); ++i)
    {
        cout << *i << endl;
    }
}


//Lose file to load a small text file of sample recipes - added to demonstrate functionality a bit better
void RecipeTable::loadFile()
{
    string line,section,phrase1,phrase2;
    ifstream inFile("Recipes.txt");
    while(getline(inFile,line))
    {
        stringstream ss(line);
        getline(ss,section,',');
        int index = hashSum(section, tableSize);
        rNode* current = hashTable[index];
        rNode * previous;
        //adds an entry to the hash table/linked list
        if (hashTable[index] == nullptr)
        {
            hashTable[index] = new rNode(section);
            current = hashTable[index];
        }
        else
        {
            while(current != nullptr)
                previous = current;
            current = current -> next;
            current = new rNode (section);
            current -> previous = previous;
        }

        while(getline(ss,section,','))
        {
            if(section == "END")
            {
                break;
            }
            stringstream nS(section);
            getline(nS,phrase2,'-');
            getline(nS,phrase1);
            current -> addIngredient(phrase1,phrase2);
        }
        while(getline(ss,section,'/'))
        {
            current -> addStep(section);
        }
    }

}
