#ifndef RECIPETABLE_H
#define RECIPETABLE_H
#include <string>

//structure to hold each step of directions
struct Directions
{
    std::string step;
    Directions * next;
    Directions * previous;
    Directions(std::string inStep)
    {
        step = inStep;
        next = nullptr;
        previous = nullptr;
    }
};
//structure to hold the ingredients
struct Ingredient
{
    double quantity;
    std::string name;
    std::string unit;
    Ingredient * next;
    Ingredient * previous;
    Ingredient(std::string in_name, double in_quantitiy, std::string in_unit)
    {
        quantity = in_quantitiy;
        name = in_name;
        unit = in_unit;
        next = nullptr;
        previous = nullptr;
    }
};

//rNode class - could have moved this to a second file, but left it as it's own
//to facilitate organization (even if it didn't pan out that way)
class rNode
{
public:
    std::string name;
    int servingSize;
    rNode * next;
    rNode * previous;
    //create an instance of ingredient and dList
    Ingredient * ingredient;
    Directions * dList;
    rNode();
    //constructor
    rNode(std::string in_name)
    {
        name = in_name;
        next = nullptr;
        previous = nullptr;
        ingredient = nullptr;
        dList = nullptr;
        servingSize = 4;
    }
    void addIngredient(std::string name, std::string tQuant);
      //add the ingredient to the rNode class
    void printIngredients();
      //print the ingredient list
    void deleteIngredient(std::string title);
      //delete an ingredient
    void adjustSize(double sSize);
      //adjust portion size;
    void addStep(std::string step);
      //add a direction. Note - no function to remove steps exists as of this version
    void printDirections();
      //print the directions in alphabetical order
    void insertStep(std::string step, int stepNum);
      //accepts a user input on where to add the step to the linked list, different from addStep.
    void deleteStep(int stepNum);
      //delete a step from the dList linked list
private:
};

//class to hold the recipe (hash) table
//each hash table holds an rNode, which is the head of a linked list to resolve
//collision conflicts
class RecipeTable
{
public:
    int hashSum(std::string inString,int tableSize);
      //calculate the hash sum
    void addRecipe(std::string title);
      //creates an rNode and adds it to the structure
    void searchRecipe(std::string title);
      //search fpr a recipe.
    void deleteRecipe(std::string title);
      //delete a recipe from the table
    void printMenu(std::string title);
      //a menu function to handle working on the object
    void printTable();
      //prints the contents of the table in alphabetical order. Cool!
    void Menu(std::string title, rNode * current);
      //Handles the switch case for working within the table.
    void loadFile();
    RecipeTable();
protected:
private:
    static int const tableSize = 20;
    rNode * hashTable[tableSize];
      //table nodes
};

#endif // RECIPETABLE_H
