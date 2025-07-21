/*
Delete Duplicate Folders in System - [Leetcode - 1948(Hard)]
-------------------------------------------------------------
Due to a bug, there are many duplicate folders in a file system. You are given a 2D array paths, where paths[i] is an array representing an absolute path to the ith folder in the file system.

For example, ["one", "two", "three"] represents the path "/one/two/three".
Two folders (not necessarily on the same level) are identical if they contain the same non-empty set of identical subfolders and underlying subfolder structure. The folders do not need to be at the root level to be identical. If two or more folders are identical, then mark the folders as well as all their subfolders.

For example, folders "/a" and "/b" in the file structure below are identical. They (as well as their subfolders) should all be marked:
/a
/a/x
/a/x/y
/a/z
/b
/b/x
/b/x/y
/b/z
However, if the file structure also included the path "/b/w", then the folders "/a" and "/b" would not be identical. Note that "/a/x" and "/b/x" would still be considered identical even with the added folder.
Once all the identical folders and their subfolders have been marked, the file system will delete all of them. The file system only runs the deletion once, so any folders that become identical after the initial deletion are not deleted.

Return the 2D array ans containing the paths of the remaining folders after deleting all the marked folders. The paths may be returned in any order.

Example 1:

Input: paths = [["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]]
Output: [["d"],["d","a"]]
Explanation: The file structure is as shown.
Folders "/a" and "/c" (and their subfolders) are marked for deletion because they both contain an empty
folder named "b".

Example 2:

Input: paths = [["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]]
Output: [["c"],["c","b"],["a"],["a","b"]]
Explanation: The file structure is as shown. 
Folders "/a/b/x" and "/w" (and their subfolders) are marked for deletion because they both contain an empty folder named "y".
Note that folders "/a" and "/c" are identical after the deletion, but they are not deleted because they were not marked beforehand.

Example 3:

Input: paths = [["a","b"],["c","d"],["c"],["a"]]
Output: [["c"],["c","d"],["a"],["a","b"]]
Explanation: All folders are unique in the file system.
Note that the returned array can be in a different order as the order does not matter.
 

Constraints:

1 <= paths.length <= 2 * 104
1 <= paths[i].length <= 500
1 <= paths[i][j].length <= 10
1 <= sum(paths[i][j].length) <= 2 * 105
path[i][j] consists of lowercase English letters.
No two paths lead to the same folder.
For any folder not at the root level, its parent folder will also be in the input.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//Approach (Using trie)
//T.C : O(N * L * ClogC), N = total Paths, L = average length of each path, C is the average number of children per node
//S.C : ~O(N * L), we store all the paths in the trie, approximated value.

class node {
    public:
    string value; // Name
    string subfolder; // Subfolder structure
    unordered_map<string, node*> children; // Children nodes
};

node *getNode(string data){
    node *newNode = new node();
    newNode->value = data;
    newNode->subfolder = "";

    return newNode;
}

void insert(node *root, vector<string> &path){
    for(auto &folder : path){
        if(!root->children.count(folder)){ // If the folder does not exist, create a new node
            root->children[folder] = getNode(folder); // Create a new node for the folder
        }
        root = root->children[folder]; // Move to the child node
    }
}

string populateNodes(node *root, unordered_map<string, int> &subfolderCountMap){
    vector<pair<string, string>> subfoldersPaths; // To store subfolder paths structure and its count

    if(!root) return "";

    for(auto it = root->children.begin(); it != root->children.end(); ++it){
        string subFolderResult = populateNodes(it->second, subfolderCountMap);
        subfoldersPaths.push_back({it->first, subFolderResult});
    }
    sort(subfoldersPaths.begin(), subfoldersPaths.end()); // Sort the subfolders to ensure consistent structure

    string completePath = ""; // Construct the complete subfolder structure
    for(auto it = subfoldersPaths.begin(); it != subfoldersPaths.end(); ++it){
        completePath += "(" + it->first + it->second + ")"; // Append the child name and its subfolder structure
    }

    root->subfolder = completePath; // Set the subfolder structure for the current node
    
    if(!completePath.empty()){
        subfolderCountMap[completePath]++; // Increment the count of this subfolder structure
    }

    return completePath; // Return the complete subfolder structure
}

void removeDuplicates(node *root, unordered_map<string, int> &subfolderCountMap){
    if(!root) return;

    for(auto itr = root->children.begin(); itr != root->children.end();){
        string childName = itr->first;
        node *childNode = itr->second;

        if(!childNode->subfolder.empty() && subfolderCountMap[childNode->subfolder] > 1){
            // If the subfolder structure is marked for deletion, remove this child
            itr = root->children.erase(itr); // Erase the child node
        } else {
            removeDuplicates(childNode, subfolderCountMap); // Recursion for children
            ++itr; // Move to the next child
        }
    }
}

void constructResult(node *root, vector<string> &path, vector<vector<string>> &ans){
    if(!root) return;

    for(auto it = root->children.begin(); it != root->children.end(); ++it){
        path.push_back(it->first);
        ans.push_back(path); // Add the current path to the result
        constructResult(it->second, path, ans);
        path.pop_back(); // Backtrack to the previous path
    }
}

vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths){
    node *root = getNode("/");

    // Step 1: Construct the trie
    for(auto &path : paths){
        insert(root, path);
    }

    // Step 2: Populate the subfolder structure
    unordered_map<string, int> subfolderCountMap;
    populateNodes(root, subfolderCountMap);

    // Step 3: Remove duplicate folders
    removeDuplicates(root, subfolderCountMap);

    // Step 4: Collect remaining folders
    vector<vector<string>> ans;
    vector<string> path;
    constructResult(root, path, ans);

    return ans;
}

int main() {
    vector<vector<string>> paths = {{"a"}, {"c"}, {"d"}, {"a", "b"}, {"c", "b"}, {"d", "a"}};
    vector<vector<string>> result = deleteDuplicateFolder(paths);

    // Output the result in the requested format
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << "[";
        for (int j = 0; j < result[i].size(); j++) {
            cout << "\"" << result[i][j] << "\"";
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;

    return 0;
}