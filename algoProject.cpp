#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>
#include <locale>
#include <sstream>
#include <fstream>
#include <cctype>

// Global Variables for Functions used below
int menuChoice;
const int ARRAY_SIZE = 15;
std::vector<int> yourArray;
std::vector<int> unsortedArray;

// Function that displays a goodbye message upon termination of program.
int goodBye(){
    std::cout << "You have chosen to end the program, goodbye! " << std::endl;
    return 0;
}

// Function that formats number values with commas as necessary
std::string formatWithCommas(long long value){
    std::stringstream ss;
    ss.imbue(std::locale("en_US.UTF-8")); // Using United States locale
    ss << value;
    return ss.str();
}

// Function that retrieves file name from user input.
std::string getFileName(){
    std::string fileName;
    std::cout << "Please enter the file name: ";
    std::cin >> fileName;
    return fileName;
}

// Function that analyzes the text file and displays the number of characters, uppercase, lowercase and digits.
void disectFileContents(const std::string &fileName){
    std::ifstream file(fileName);
    if (!file.is_open()){
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    char ch;
    std::string line;
    int upperCaseCount = 0, lowerCaseCount = 0, digitCount = 0;

    std::cout << "Sentence within the file: ";
    while (std::getline(file, line)){
        std::cout << line << std::endl; // Print each line

        // Analyze the characters in the line
        for (char ch : line){
            if (std::isupper(ch)){
                ++upperCaseCount;
            }
            else if (std::islower(ch)){
                ++lowerCaseCount;
            }
            else if (std::isdigit(ch)){
                ++digitCount;
            }
        }
    }

    std::cout << "Number of uppercase letters: " << upperCaseCount << std::endl;
    std::cout << "Number of lowercase letters: " << lowerCaseCount << std::endl;
    std::cout << "Number of digits: " << digitCount << std::endl;

    file.close();
}

// Function that sorts the list of numbers using insertion.
void insertionSort(std::vector<int> &array){
    int n = array.size();

    for (int i = 1; i < n; ++i){
        int current = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > current){
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = current;
    }
}

// Function that performs binary search to target specific values.
int binarySearch(std::vector<int> &array, int target){

    int left = 0;
    int right = array.size() - 1;

    while (left <= right){
        int mid = left + (right - left) / 2;

        if (array[mid] == target){
            return mid;
        }
        else if (array[mid] < target){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return -1;
}

// Function that prints the user's list of numbers in the order they've inputted, also displays numbers once sorted.
void printArray(){
    std::cout << "You have entered: ";
    for (int num : unsortedArray){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // Insertion Sort deployed on unsorted array from user.
    insertionSort(unsortedArray);
    std::cout << "Your list sorted: ";
    for (int num : unsortedArray){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

// Prints the minimum value within user's list of numbers.
void printMinimum(){
    std::vector<int> sortedArray = yourArray;
    // Minimum value is the target for the binary search.

    int minTarget = sortedArray[0];
    // Binary Search deployed on sorted array to find the minimum value.
    int result = binarySearch(sortedArray, minTarget);

    if (result != -1){
        std::cout << "Element found at index " << result << std::endl;
        std::cout << "Minimum value is: " << minTarget << std::endl;
    }
    else{
        std::cout << "Element not found within array" << std::endl;
    }
}

// Prints the maximum value within the user's list of numbers.
void printMaximum(){
    std::vector<int> sortedArray = yourArray;
    // Maximum value is the target for the binary search.

    int maxTarget = sortedArray.back();
    // Binary Search deployed on sorted array to find the maximum value.
    int result = binarySearch(sortedArray, maxTarget);

    if (result != -1){
        std::cout << "Element found at index " << result << std::endl;
        std::cout << "Maximum value is: " << maxTarget << std::endl;
    }
    else{
        std::cout << "Element not found within array" << std::endl;
    }
}

// Function that finds the product of all items within user's list using recursion.
long long printRecursiveProduct(const std::vector<int> &arr, int index){
    if (index == arr.size()){
        return 1;
    }
    // Storing the value of the final product into a variable.
    long long finalProduct = arr[index] * printRecursiveProduct(arr, index + 1);

    // Deploying function that formats with a comma on the variable finalProduct.
    std::string formattedProduct = formatWithCommas(finalProduct);

    if (index == 0){
        std::string formattedProduct = formatWithCommas(finalProduct);
        std::cout << "The total product of your listed numbers: " << formattedProduct << std::endl;
    }

    return finalProduct;
}

// Function that finds the sum of all items within user's list using recursion.
long long printRecursiveSummation(const std::vector<int> &arr, int index){
    if (index == arr.size()){
        return 0;
    }
    // Storing the value of the final sum into a variable.
    long long finalSum = arr[index] + printRecursiveSummation(arr, index + 1);
    // Deploying function that formats with a comma on the variable finalSum.
    std::string formattedSum = formatWithCommas(finalSum);

    if (index == 0){
        std::string formattedSum = formatWithCommas(finalSum);
        std::cout << "The total sum of your listed numbers: " << formattedSum << std::endl;
    }

    return finalSum;
}

// Function responsible for commencing part 1 of the program.
void commenceProgram(){

    std::cout << "Please list 15 numbers." << std::endl;

    for (int i = 0; i < ARRAY_SIZE; i++){
        while (true){
            int num;
            std::cout << "Please enter your number of choice " << i + 1 << ": ";

            if (std::cin >> num){
                yourArray.push_back(num); // Correctly add the number to the vector
                break;
            }
            else{
                std::cout << "Invalid selection, please enter a number. " << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    unsortedArray = yourArray;
    insertionSort(yourArray);
}

// Function that loops the user upon choice, repeating part 1 of the program.
bool repeatProgram(){
    char programChoice;
    std::cout << "Would you like to re-enter a new set of 15 numbers? Y for yes, N for no " << std::endl;
    std::cin >> programChoice;

    if (programChoice == 'Y' || programChoice == 'y'){
        yourArray.clear();
        return true; // Indicate that the program should repeat
    }
    else if (programChoice == 'N' || programChoice == 'n'){
        return false; // Indicate that the program should not repeat
    }
    else{
        std::cout << "Invalid choice, please enter either Y for yes or N for no. " << std::endl;
        return repeatProgram(); // Recursive call for invalid input
    }
}

// Function that prompts menu for the user.
void promptMenu(){

    std::cout << std::endl;
    std::cout << "Select from the menu below entering  1 - 5 " << std::endl;
    std::cout << std::endl;

    std::cout << "Choice 1: Print Elements of Array " << std::endl;
    std::cout << "Choice 2: Print Minimum Value of Array " << std::endl;
    std::cout << "Choice 3: Print Maximum Value of Array " << std::endl;
    std::cout << "Choice 4: Print Product of All Numbers " << std::endl;
    std::cout << "Choice 5: Print Sum of All Numbers " << std::endl;

    std::cout << std::endl;
    std::cout << "Your choice: ";
    std::cin >> menuChoice;
    std::cout << std::endl;

    switch (menuChoice){
    case 1:
        std::cout << "You have chosen Choice 1" << std::endl;
        printArray();
        break;

    case 2:
        std::cout << "You have chosen Choice 2" << std::endl;
        printMinimum();
        break;

    case 3:
        std::cout << "You have chosen Choice 3" << std::endl;
        printMaximum();
        break;

    case 4:
        std::cout << "You have chosen Choice 4" << std::endl;
        printRecursiveProduct(yourArray, 0);
        break;

    case 5:
        std::cout << "You have chosen Choice 5" << std::endl;
        printRecursiveSummation(yourArray, 0);
        break;
    }
    std::cout << std::endl;
}

// Main program that utilizes all of the functions above.

int main(){
    // Capture runtime of program.
    auto start_time = std::chrono::high_resolution_clock::now();

    char choice;
    std::string fileName = "Character.txt";

    // Part 1 of the program.
    do{
        commenceProgram();
        promptMenu();
    } while (repeatProgram());
    std::cout << std::endl;

    // Part 2 of the Program.
    do{
        disectFileContents(fileName);
        std::cout << "Would you like to analyze another file? (Y/N): ";
        char choice;
        std::cin >> choice;
        if (choice == 'Y' || choice == 'y'){
            fileName = getFileName();
        }
        else{
            break;
        }
    } while (true);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    // Display the runtime in seconds
    std::cout << std::endl;
    std::cout << "Runtime: " << duration.count() << " seconds" << std::endl;
    std::cout << std::endl;

    goodBye();
    
    return 0;
}
