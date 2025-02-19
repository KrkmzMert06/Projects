#include <iostream>
#include <fstream>
#include <string>
#include "Recipe.h"
#include "cookbook.h"

using namespace std;

cookbook::cookbook() : listOfRecipes(nullptr), numberOfRecipes(0) {}

cookbook::~cookbook() {
    delete[] listOfRecipes;
}

void cookbook::addRecipe(const Recipe& recipe) {
    Recipe* newList = new Recipe[numberOfRecipes + 1];
    int insertPos = 0;

    while (insertPos < numberOfRecipes && listOfRecipes[insertPos] < recipe) {
        newList[insertPos] = listOfRecipes[insertPos];
        ++insertPos;
    }

    newList[insertPos] = recipe;

    for (int i = insertPos; i < numberOfRecipes; ++i) {
        newList[i + 1] = listOfRecipes[i];
    }

    delete[] listOfRecipes;
    listOfRecipes = newList;
    ++numberOfRecipes;
}

int cookbook::findRecipe(const string& recipeName) const {
    for (int i = 0; i < numberOfRecipes; ++i) {
        if (listOfRecipes[i].getName() == recipeName) {
            return i;
        }
    }
    return -1;
}

void cookbook::removeRecipe(const string& recipeName) {
    int index = findRecipe(recipeName);
    if (index == -1) {
        cout << "Recipe not found!" << endl;
        return;
    }

    Recipe* newList = new Recipe[numberOfRecipes - 1];
    for (int i = 0, j = 0; i < numberOfRecipes; ++i) {
        if (i != index) {
            newList[j++] = listOfRecipes[i];
        }
    }

    delete[] listOfRecipes;
    listOfRecipes = newList;
    --numberOfRecipes;

    cout << "Recipe removed: " << recipeName << endl;
}

void cookbook::displayRecipes() const {
    for (int i = 0; i < numberOfRecipes; ++i) {
        cout << listOfRecipes[i].getName() << endl;
    }
}

void loadRecipesFromFile(const string& fileName, cookbook& book) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        string name = line;

        getline(file, line);
        int numOfInstructions = stoi(line);

        string* instructions = new string[numOfInstructions];
        for (int i = 0; i < numOfInstructions; ++i) {
            getline(file, instructions[i]);
        }

        getline(file, line);
        int numOfIngredients = stoi(line);

        string* ingredients = new string[numOfIngredients];
        for (int i = 0; i < numOfIngredients; ++i) {
            getline(file, ingredients[i]);
        }

        Recipe recipe(name, instructions, numOfInstructions, ingredients, numOfIngredients);
        book.addRecipe(recipe);

        delete[] instructions;
        delete[] ingredients;

        getline(file, line);
    }

    file.close();
}

int main() {
    cookbook myCookbook;
    loadRecipesFromFile("recipes.txt", myCookbook);

    cout << "Recipes in Cookbook (Alphabetical Order):" << endl;
    myCookbook.displayRecipes();

    cout << "\nRemoving 'Omelette':" << endl;
    myCookbook.removeRecipe("Omelette");

    cout << "\nRecipes after removal:" << endl;
    myCookbook.displayRecipes();

    return 0;
}
