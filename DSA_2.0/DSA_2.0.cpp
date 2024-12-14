#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <fstream>

using namespace std;

// Define the Recipe structure
struct Recipe {
    string name;
    vector<string> ingredients;
    string instructions;
    string nutritionInfo;
    string category;
};

// Class to manage the collection of recipes
class RecipeManager {
private:
    vector<Recipe> recipes;  // Vector na i store so all recipes             Ano ang vector? > naga store siya ning elements of a given type na linear arrangement and allows fast random access to any element
    unordered_map<string, vector<Recipe>> categoryMap;  // HashMap for searching by category

public:
    void saveIngredients() {
        std::ofstream record("Lusi.txt", std::ios_base::app);
        if (!record) {
            std::cout<< "file not found" << std::endl;
        }
        

    }
    // Add a new recipe
    void addRecipe(const Recipe& recipe) {
        recipes.push_back(recipe);
        categoryMap[recipe.category].push_back(recipe);
    }

    // Display all recipes
    void displayRecipes() {
        if (recipes.empty()) {
            cout << "No recipes available." << endl;
            return;
        }

        for (const auto& recipe : recipes) { // const auto& in a range for to process the elements
            cout << "Recipe: " << recipe.name << endl;
            cout << "Category: " << recipe.category << endl;
            cout << "Ingredients: ";
            for (const auto& ingredient : recipe.ingredients) {
                cout << ingredient << ", ";
            }
            cout << endl;
            cout << "Instructions: " << recipe.instructions << endl;
            cout << "Nutrition Info: " << recipe.nutritionInfo << endl;
            cout << "-------------------------------------" << endl;
        }
    }

    // Display recipes by category
    void displayByCategory(const string& category) {
        if (categoryMap.find(category) == categoryMap.end()) {
            cout << "No recipes found for category: " << category << endl;
            return;
        }

        for (const auto& recipe : categoryMap[category]) {
            cout << "Recipe: " << recipe.name << endl;
            cout << "Ingredients: ";
            for (const auto& ingredient : recipe.ingredients) {
                cout << ingredient << ", ";
            }
            cout << endl;
            cout << "Instructions: " << recipe.instructions << endl;
            cout << "Nutrition Info: " << recipe.nutritionInfo << endl;
            cout << "-------------------------------------" << endl;
        }
    }

    // Search recipes by name
    void searchRecipeByName(const string& name) {
        bool found = false;
        for (const auto& recipe : recipes) {
            if (recipe.name == name) {
                found = true;
                cout << "Recipe: " << recipe.name << endl;
                cout << "Category: " << recipe.category << endl;
                cout << "Ingredients: ";
                for (const auto& ingredient : recipe.ingredients) {
                    cout << ingredient << ", ";
                }
                cout << endl;
                cout << "Instructions: " << recipe.instructions << endl;
                cout << "Nutrition Info: " << recipe.nutritionInfo << endl;
                cout << "-------------------------------------" << endl;
            }
        }

        if (!found) {
            cout << "No recipe found with the name: " << name << endl;
        }
    }

    // Sort recipes by name
    void sortRecipesByName() {
        sort(recipes.begin(), recipes.end(), [](const Recipe& a, const Recipe& b) {
            return a.name < b.name;
            });
        cout << "Recipes sorted by name." << endl;
    }

    // Sort recipes by category
    void sortRecipesByCategory() {
        sort(recipes.begin(), recipes.end(), [](const Recipe& a, const Recipe& b) {
            return a.category < b.category;
            });
        cout << "Recipes sorted by category." << endl;
    }
};

// Function to take input for a recipe
Recipe inputRecipe() {
    Recipe recipe;
    cout << "Enter recipe name: ";
    getline(cin, recipe.name);

    cout << "Enter recipe category (e.g., Breakfast, Lunch, Dinner): ";
    getline(cin, recipe.category);

    cout << "Enter ingredients (comma-separated): ";
    string ingredientsLine;
    getline(cin, ingredientsLine);
    size_t pos = 0; // size_t > can store maximum size of any type(kasabay and array)
    while ((pos = ingredientsLine.find(',')) != string::npos) {
        recipe.ingredients.push_back(ingredientsLine.substr(0, pos));
        ingredientsLine.erase(0, pos + 1); 
    }
    if (!ingredientsLine.empty()) {
        recipe.ingredients.push_back(ingredientsLine);
    }

    cout << "Enter instructions: ";
    getline(cin, recipe.instructions);

    cout << "Enter nutritional information: ";
    getline(cin, recipe.nutritionInfo);

    return recipe;
}

int main() {
    RecipeManager manager;

    while (true) {
        cout << "\n--- Recipe Management System ---\n";
        cout << "1. Add a new recipe\n";
        cout << "2. Display all recipes\n";
        cout << "3. Display recipes by category\n";
        cout << "4. Search for a recipe by name\n";
        cout << "5. Sort recipes by name\n";
        cout << "6. Sort recipes by category\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();  // Para ma clear so newline character pakatapos ning choice input

        switch (choice) {
        case 1: {
            Recipe recipe = inputRecipe();
            manager.addRecipe(recipe);
            cout << "Recipe added successfully!" << endl;
            break;
        }
        case 2:
            manager.displayRecipes();
            break;
        case 3: {
            cout << "Enter category to search: ";
            string category;
            getline(cin, category);
            manager.displayByCategory(category);
            break;
        }
        case 4: {
            cout << "Enter recipe name to search: ";
            string name;
            getline(cin, name);
            manager.searchRecipeByName(name);
            break;
        }
        case 5:
            manager.sortRecipesByName();
            break;
        case 6:
            manager.sortRecipesByCategory();
            break;
        case 7:
            cout << "Exiting the application...\n";
            return 0;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
