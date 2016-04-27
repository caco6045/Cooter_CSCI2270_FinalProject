#ifndef RECIPETABLE_H
#define RECIPETABLE_H
#include <string>

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
class rNode
{
public:
    std::string name;
    int servingSize;
    rNode * next;
    rNode * previous;
    Ingredient * ingredient;
    Directions * dList;
    rNode();
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
    void printIngredients();
    void deleteIngredient(std::string title);
    void adjustSize(double sSize);
    void addStep(std::string step);
    void printDirections();
private:
};

class RecipeTable
{
public:
    int hashSum(std::string inString,int tableSize);
    void addRecipe(std::string title);
    void searchRecipe(std::string title);
    void deleteRecipe(std::string title);
    void printMenu(std::string title);
    void printTable();
    void Menu(std::string title, rNode * current);
    RecipeTable();
protected:
private:
    static int const tableSize = 20;
    rNode * hashTable[tableSize];

};

#endif // RECIPETABLE_H
