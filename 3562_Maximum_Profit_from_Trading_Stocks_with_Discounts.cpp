/*
Maximum Profit from Trading Stocks with Discounts - [Leetcode - 3562(Hard)]
------------------------------------------------------------------------------
You are given an integer n, representing the number of employees in a company. Each employee is assigned a unique ID from 1 to n, and employee 1 is the CEO. You are given two 1-based integer arrays, present and future, each of length n, where:

=> present[i] represents the current price at which the ith employee can buy a stock today.
=> future[i] represents the expected price at which the ith employee can sell the stock tomorrow.

The company's hierarchy is represented by a 2D integer array hierarchy, where hierarchy[i] = [ui, vi] means that employee ui is the direct boss of employee vi.

Additionally, you have an integer budget representing the total funds available for investment.

However, the company has a discount policy: if an employee's direct boss purchases their own stock, then the employee can buy their stock at half the original price (floor(present[v] / 2)).

Return the maximum profit that can be achieved without exceeding the given budget.

Note:

=> You may buy each stock at most once.
=> You cannot use any profit earned from future stock prices to fund additional investments and must buy only from budget.

Example 1:

Input: n = 2, present = [1,2], future = [4,3], hierarchy = [[1,2]], budget = 3

Output: 5

Explanation:

Employee 1 buys the stock at price 1 and earns a profit of 4 - 1 = 3.
Since Employee 1 is the direct boss of Employee 2, Employee 2 gets a discounted price of floor(2 / 2) = 1.
Employee 2 buys the stock at price 1 and earns a profit of 3 - 1 = 2.
The total buying cost is 1 + 1 = 2 <= budget. Thus, the maximum total profit achieved is 3 + 2 = 5.

Example 2:

Input: n = 2, present = [3,4], future = [5,8], hierarchy = [[1,2]], budget = 4

Output: 4

Explanation:

Employee 2 buys the stock at price 4 and earns a profit of 8 - 4 = 4.
Since both employees cannot buy together, the maximum profit is 4.

Example 3:

Input: n = 3, present = [4,6,8], future = [7,9,11], hierarchy = [[1,2],[1,3]], budget = 10

Output: 10

Explanation:

Employee 1 buys the stock at price 4 and earns a profit of 7 - 4 = 3.
Employee 3 would get a discounted price of floor(8 / 2) = 4 and earns a profit of 11 - 4 = 7.
Employee 1 and Employee 3 buy their stocks at a total cost of 4 + 4 = 8 <= budget. Thus, the maximum total profit achieved is 3 + 7 = 10.
Example 4:

Input: n = 3, present = [5,2,3], future = [8,5,6], hierarchy = [[1,2],[2,3]], budget = 7

Output: 12

Explanation:

Employee 1 buys the stock at price 5 and earns a profit of 8 - 5 = 3.
Employee 2 would get a discounted price of floor(2 / 2) = 1 and earns a profit of 5 - 1 = 4.
Employee 3 would get a discounted price of floor(3 / 2) = 1 and earns a profit of 6 - 1 = 5.
The total cost becomes 5 + 1 + 1 = 7 <= budget. Thus, the maximum total profit achieved is 3 + 4 + 5 = 12.
 
Constraints:

1 <= n <= 160
present.length, future.length == n
1 <= present[i], future[i] <= 50
hierarchy.length == n - 1
hierarchy[i] == [ui, vi]
1 <= ui, vi <= n
ui != vi
1 <= budget <= 160
There are no duplicate edges.
Employee 1 is the direct or indirect boss of every employee.
The input graph hierarchy is guaranteed to have no cycles.
*/ 

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

void DFS(int u, const vector<int>& present, const vector<int>& future, unordered_map<int, vector<int>>& graph, vector<vector<vector<int>>>& statesProfit, int budget) {
    
    // childrenStatesProfit:
    // first  -> child profit if parent NOT bought
    // second -> child profit if parent IS bought
    
    vector<pair<vector<int>, vector<int>>> childrenStatesProfit;
    
    //Process children first
    for (int v : graph[u]) {
        DFS(v, present, future, graph, statesProfit, budget);
        childrenStatesProfit.push_back({statesProfit[v][0], statesProfit[v][1]});
    }
    
    // parentBought = 0 or 1
    for (int parentBought = 0; parentBought <= 1; ++parentBought) {
        int price  = (parentBought == 1) ? present[u] / 2 : present[u];
        int profit = future[u] - price;
        
        vector<int> bestProfitAtU(budget + 1, 0);
        
        // Case 1: Do NOT buy node u
        vector<int> childrenProfitIfUNotBought(budget + 1, 0);
        
        for (const auto& child : childrenStatesProfit) { //from all child
            vector<int> temp(budget + 1, 0);
            for (int used = 0; used <= budget; ++used) { 
                for (int take = 0; used + take <= budget; ++take) { 
                    temp[used + take] = max(temp[used + take], childrenProfitIfUNotBought[used] + child.first[take]);
                }
            }
            childrenProfitIfUNotBought = move(temp);
        }
        
        for (int b = 0; b <= budget; ++b) {
            bestProfitAtU[b] = max(bestProfitAtU[b], childrenProfitIfUNotBought[b]);
        }
        
        // Case 2: Buy node u
        if (price <= budget) {
            
            vector<int> childrenProfitIfUBought(budget + 1, 0);
            
            for (const auto& child : childrenStatesProfit) { //from all child
                
                vector<int> temp(budget + 1, 0);
                
                for (int used = 0; used <= budget; ++used) {
                    for (int take = 0; used + take <= budget; ++take) {
                        temp[used + take] = max(temp[used + take], childrenProfitIfUBought[used] + child.second[take]);
                    }
                }
                childrenProfitIfUBought = move(temp);
            }
            
            for (int b = price; b <= budget; ++b) {
                bestProfitAtU[b] = max(bestProfitAtU[b], childrenProfitIfUBought[b - price] + profit);
            }
        }
        statesProfit[u][parentBought] = move(bestProfitAtU);
    }
}

int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
    
    unordered_map<int, vector<int>> graph;
    for (auto& h : hierarchy) {
        int u = h[0]-1;
        int v = h[1]-1;
        graph[u].push_back(v);
    }
    
    //statesProfit[u][0][b] = profit at u when it's parent had not bought stock
    //statesProfit[u][1][b] = profit at v when it's parent bought had bought stock
    vector<vector<vector<int>>> statesProfit(n, vector<vector<int>>(2, vector<int>(budget + 1, 0)));
    
    DFS(0, present, future, graph, statesProfit, budget);
    
    int ans = 0;
    for (int b = 0; b <= budget; ++b) {
        ans = max(ans, statesProfit[0][0][b]);
    }
    
    return ans;
}

int main() {
    int n = 3;
    vector<int> present = {5,2,3};
    vector<int> future = {8,5,6};
    vector<vector<int>> hierarchy = {{1,2},{2,3}};
    int budget = 7;
    
    cout << maxProfit(n, present, future, hierarchy, budget) << endl; // Output: 12
    
    return 0;
}