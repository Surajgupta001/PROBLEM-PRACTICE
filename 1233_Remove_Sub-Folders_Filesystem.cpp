/*
Remove Sub-Folders from the Filesystem - [Leetcode - 1233(Medium)]
-------------------------------------------------------------------
Given a list of folders folder, return the folders after removing all sub-folders in those folders. You may return the answer in any order.

If a folder[i] is located within another folder[j], it is called a sub-folder of it. A sub-folder of folder[j] must start with folder[j], followed by a "/". For example, "/a/b" is a sub-folder of "/a", but "/b" is not a sub-folder of "/a/b/c".

The format of a path is one or more concatenated strings of the form: '/' followed by one or more lowercase English letters.

For example, "/leetcode" and "/leetcode/problems" are valid paths while an empty string and "/" are not.
 
Example 1:

Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
Output: ["/a","/c/d","/c/f"]
Explanation: Folders "/a/b" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.

Example 2:

Input: folder = ["/a","/a/b/c","/a/b/d"]
Output: ["/a"]
Explanation: Folders "/a/b/c" and "/a/b/d" will be removed because they are subfolders of "/a".

Example 3:

Input: folder = ["/a/b/c","/a/b/ca","/a/b/d"]
Output: ["/a/b/c","/a/b/ca","/a/b/d"]
 

Constraints:

1 <= folder.length <= 4 * 104
2 <= folder[i].length <= 100
folder[i] contains only lowercase letters and '/'.
folder[i] always starts with the character '/'.
Each folder name is unique.
*/ 

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
using namespace std;

// Approach: 1 - Using a set to track folders and checking for subfolders
// Time Complexity: O(n * m^2) where n is the number of folders and m is the average length of the folder names
vector<string> removeSubfolders(vector<string>& folder){ // T.C => O(n) where n is the number of folders
    
    unordered_set<string> sets(folder.begin(), folder.end());
    vector<string> result;
    
    for(auto &currFolder : folder){
        bool isSubFolder = false;

        string originalFolder = currFolder;
        
        // Check if the current folder is a subfolder of any other folder
        while(!currFolder.empty()){ // T.C => O(m) where m is the length of the folder name
            size_t position_of_last_slash = currFolder.find_last_of('/'); // O(m) where m is the length of the folder name

            currFolder = currFolder.substr(0, position_of_last_slash); // O(m) where m is the length of the folder name
            if(sets.find(currFolder) != sets.end()){
                // It means currFolder is a subfolder of some other folder
                isSubFolder = true;
                break;
            }
        }

        if (!isSubFolder){
            result.push_back(originalFolder);
        }
    }
    return result;
}

// Approach: 2 - Sorting and checking for subfolders
// Time Complexity: O(n * m log n) where n is the number of folders and m is the average length of the folder names
vector<string> removeSubfolders(vector<string>& folder){
    sort(folder.begin(), folder.end());
    vector<string> result;

    result.push_back(folder[0]); // It is sorted, so folder[0] has no parent folder
    // So it can never be a subfolder of any other folder

    for(int i = 1; i < folder.size(); i++){
        
        string currFolder = folder[i];
        string lastAddedFolder = result.back();
        lastAddedFolder += '/'; // Add a '/' to the end of the last added folder
        
        // Check if the current folder starts with the last added folder
        if(currFolder.find(lastAddedFolder) != 0){ // If it does not start with the last added folder
            result.push_back(currFolder); // It is not a subfolder of the last added folder
        }
    }
    return result;
}

int main() {
    vector<string> folder = {"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"};
    vector<string> result = removeSubfolders(folder);
    
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << "\"" << result[i] << "\"";
        if (i < result.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
    
    return 0;
}