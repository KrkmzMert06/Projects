#pragma once
#include <string>


class Recipe {
    string name;
    string* instructions;
    int numberOfInstructions;
    string* ingredients;
    int numberOfIngredients;

public:
    Recipe(string, string*, int, string*, int);
    ~Recipe();
    Recipe(const Recipe& other);
    Recipe();

    string getName();
    string* getInstructions();
    int getNumberOfInstructions();
    string* getIngredients();
    int getNumberOfIngredients();

    bool operator==(const Recipe&);
    bool operator<(const Recipe&) const;
};
