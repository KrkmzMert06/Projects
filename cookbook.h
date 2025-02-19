#pragma once
#include "Recipe.h"

class cookbook {
    Recipe* listOfRecipes;
    int numberOfRecipes;

public:
    cookbook();
    ~cookbook();
    void addRecipe(const Recipe& recipe);
    void removeRecipe(const string& recipeName);
    int findRecipe(const string& recipeName) const;
    void displayRecipes() const;
};
