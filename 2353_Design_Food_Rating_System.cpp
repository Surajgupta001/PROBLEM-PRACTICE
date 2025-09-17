/*
Design a Food Rating System - [Leetcode - 2353(Medium)]
---------------------------------------------------------
Design a food rating system that can do the following:

Modify the rating of a food item listed in the system.
Return the highest-rated food item for a type of cuisine in the system.
Implement the FoodRatings class:

FoodRatings(String[] foods, String[] cuisines, int[] ratings) Initializes the system. The food items are described by foods, cuisines and ratings, all of which have a length of n.
foods[i] is the name of the ith food,
cuisines[i] is the type of cuisine of the ith food, and
ratings[i] is the initial rating of the ith food.
void changeRating(String food, int newRating) Changes the rating of the food item with the name food.
String highestRated(String cuisine) Returns the name of the food item that has the highest rating for the given type of cuisine. If there is a tie, return the item with the lexicographically smaller name.
Note that a string x is lexicographically smaller than string y if x comes before y in dictionary order, that is, either x is a prefix of y, or if i is the first position such that x[i] != y[i], then x[i] comes before y[i] in alphabetic order.

Example 1:

Input
["FoodRatings", "highestRated", "highestRated", "changeRating", "highestRated", "changeRating", "highestRated"]
[[["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"], ["korean", "japanese", "japanese", "greek", "japanese", "korean"], [9, 12, 8, 15, 14, 7]], ["korean"], ["japanese"], ["sushi", 16], ["japanese"], ["ramen", 16], ["japanese"]]
Output
[null, "kimchi", "ramen", null, "sushi", null, "ramen"]

Explanation
FoodRatings foodRatings = new FoodRatings(["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"], ["korean", "japanese", "japanese", "greek", "japanese", "korean"], [9, 12, 8, 15, 14, 7]);
foodRatings.highestRated("korean"); // return "kimchi"
                                    // "kimchi" is the highest rated korean food with a rating of 9.
foodRatings.highestRated("japanese"); // return "ramen"
                                      // "ramen" is the highest rated japanese food with a rating of 14.
foodRatings.changeRating("sushi", 16); // "sushi" now has a rating of 16.
foodRatings.highestRated("japanese"); // return "sushi"
                                      // "sushi" is the highest rated japanese food with a rating of 16.
foodRatings.changeRating("ramen", 16); // "ramen" now has a rating of 16.
foodRatings.highestRated("japanese"); // return "ramen"
                                      // Both "sushi" and "ramen" have a rating of 16.
                                      // However, "ramen" is lexicographically smaller than "sushi".
 

Constraints:

1 <= n <= 2 * 104
n == foods.length == cuisines.length == ratings.length
1 <= foods[i].length, cuisines[i].length <= 10
foods[i], cuisines[i] consist of lowercase English letters.
1 <= ratings[i] <= 108
All the strings in foods are distinct.
food will be the name of a food item in the system across all calls to changeRating.
cuisine will be a type of cuisine of at least one food item in the system across all calls to highestRated.
At most 2 * 104 calls in total will be made to changeRating and highestRated.
*/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

class FoodRatings {
public:
    // Maps food name to its cuisine
    unordered_map<string, string> food_cuisine;
    // Maps cuisine to a set of pairs (-rating, food name) for fast retrieval of highest-rated food
    unordered_map<string, set<pair<int, string>>> cuisine_rating_food;
    // Maps food name to its current rating
    unordered_map<string, int> food_rating;

    // Constructor: initializes the system with foods, cuisines, and ratings
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size();
        for(int i=0; i<n; i++){
            string food = foods[i];
            string cuisine = cuisines[i];
            int rating = ratings[i];

            // Insert into cuisine's set, using -rating for descending order
            cuisine_rating_food[cuisine].insert({-rating, food});
            
            // Map food to its cuisine
            food_cuisine[food] = cuisine;
            
            // Map food to its rating
            food_rating[food] = rating;
        }
    }
    
    // Change the rating of a food item
    void changeRating(string food, int newRating) {
        string cuisine = food_cuisine[food];
        int oldRating = food_rating[food];
        
        // Update the rating
        food_rating[food] = newRating;

        // Remove old rating-food pair and insert new one
        cuisine_rating_food[cuisine].erase({-oldRating, food});
        cuisine_rating_food[cuisine].insert({-newRating, food});
    }
    
    // Return the highest-rated food for a given cuisine
    string highestRated(string cuisine) {
        // The set is ordered by -rating, then lexicographically by food name
        return cuisine_rating_food[cuisine].begin()->second;
    }
};

int main() {
    // Example usage
    vector<string> foods = {"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"};
    vector<string> cuisines = {"korean", "japanese", "japanese", "greek", "japanese", "korean"};
    vector<int> ratings = {9, 12, 8, 15, 14, 7};

    FoodRatings foodRatings(foods, cuisines, ratings);

    cout << foodRatings.highestRated("korean") << endl;    // Output: kimchi
    cout << foodRatings.highestRated("japanese") << endl;  // Output: ramen

    foodRatings.changeRating("sushi", 16);
    cout << foodRatings.highestRated("japanese") << endl;  // Output: sushi

    foodRatings.changeRating("ramen", 16);
    cout << foodRatings.highestRated("japanese") << endl;  // Output: ramen

    return 0;
}