#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<string>
#include<chrono>
#include<locale>
#include<sstream>
#include<fstream>
#include<cctype>

int menuChoice;
const int ARRAY_SIZE = 15;
std::vector<int> yourArray;
std::vector<int> unsortedArray;

int goodBye(){
    std::cout << "You have chosen to end the program, goodbye! " << std::endl;
    return 0;
}

std::string formatWithCommas(long long value) {
    std::stringstream ss;
    ss.imbue(std::locale("en_US.UTF-8")); // Using United States locale
    ss << value;
    return ss.str();
}

void analyzeFileContents() {
    std::ifstream file("Character.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    char ch;
    std::string line;
    int upperCaseCount = 0, lowerCaseCount = 0, digitCount = 0;

    std::cout << "Sentence within the file: ";
    while (std::getline(file, line)) {
        std::cout << line << std::endl; // Print each line

        // Analyze the characters in the line
        for (char ch : line) {
            if (std::isupper(ch)) {
                ++upperCaseCount;
            } else if (std::islower(ch)) {
                ++lowerCaseCount;
            } else if (std::isdigit(ch)) {
                ++digitCount;
            }
        }
    }

    std::cout << "Number of uppercase letters: " << upperCaseCount << std::endl;
    std::cout << "Number of lowercase letters: " << lowerCaseCount << std::endl;
    std::cout << "Number of digits: " << digitCount << std::endl;

    file.close();
}

void insertionSort(std::vector<int> & array){
    int n = array.size();

    for(int i = 1; i < n; ++i){
        int current = array[i];
        int j = i -1;

        while(j >= 0 && array[j] > current){
            array[j+1] = array[j];
            j = j-1;
        }
        array[j+1] = current;
    }
}

int binarySearch(std::vector<int>&array, int target){

int left = 0;
int right = array.size() - 1;

    while(left <= right){
    int mid = left + (right - left) / 2;


        if(array[mid] == target){
        return mid;
        }
        else if(array[mid] < target){
        left = mid + 1;
        }
        else {
        right = mid -1;
        }
    }
return -1;
}

void printArray(){
 std::cout << "You have entered: ";
    for (int num : unsortedArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    insertionSort(unsortedArray);
     std::cout << "Your list sorted: ";
    for (int num : unsortedArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;    
    std::cout << std::endl;


}

void printMinimum(){
std::vector<int>sortedArray = yourArray;
int minTarget = sortedArray[0];
int result =  binarySearch(sortedArray, minTarget);

    if(result != -1){
    std::cout << "Element found at index " << result<< std::endl;
    std::cout << "Minimum value is: "<< minTarget << std::endl;
    }
    else {
    std::cout << "Element not found within array" << std::endl;
    }
}

void printMaximum(){
std::vector<int>sortedArray = yourArray;
int maxTarget = sortedArray.back();
int result =  binarySearch(sortedArray, maxTarget);

    if(result != -1){
    std::cout << "Element found at index " << result<< std::endl;
    std::cout << "Maximum value is: "<< maxTarget << std::endl;
    }
    else {
    std::cout << "Element not found within array" << std::endl;
    }

}

long long printRecursiveProduct(const std::vector<int> &arr, int index){
if(index == arr.size()){
    return 1;
}
long long finalProduct = arr[index] * printRecursiveProduct(arr, index + 1);
  std::string formattedProduct =   formatWithCommas(finalProduct);  

if (index == 0) {
        std::string formattedProduct = formatWithCommas(finalProduct);
        std::cout << "The total product of your listed numbers: " << formattedProduct << std::endl;
    }

  return finalProduct;

}

long long printRecursiveSummation(const std::vector<int> &arr, int index){
if(index == arr.size()){
    return 0;
}
long long finalSum = arr[index] + printRecursiveSummation(arr, index + 1);
  std::string formattedSum =   formatWithCommas(finalSum);  

if (index == 0) {
        std::string formattedSum = formatWithCommas(finalSum);
        std::cout << "The total sum of your listed numbers: " << formattedSum << std::endl;
    }

  return finalSum;

}


void commenceProgram(){

    std::cout << "Please list 15 numbers." << std::endl;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        while (true) {
            int num;
            std::cout << "Please enter your number of choice " << i + 1 << ": ";
            
            if (std::cin >> num) {
                yourArray.push_back(num); // Correctly add the number to the vector
                break;
            } else {
                std::cout << "Invalid selection, please enter a number. " << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
unsortedArray = yourArray;
insertionSort(yourArray);

}
bool repeatProgram() {
    char programChoice;
    std::cout << "Would you like to re-enter a new set of 15 numbers? Y for yes, N for no " << std::endl;
    std::cin >> programChoice;

    if (programChoice == 'Y' || programChoice == 'y') {
        yourArray.clear();
        return true; // Indicate that the program should repeat
    } else if (programChoice == 'N' || programChoice == 'n') {
        return false; // Indicate that the program should not repeat
    } else {
        std::cout << "Invalid choice, please enter either Y for yes or N for no. " << std::endl;
        return repeatProgram(); // Recursive call for invalid input
    }
}

void promptMenu(){

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

        switch(menuChoice){
        case 1: std::cout << "You have chosen Choice 1" << std::endl;
        printArray();
        break;

        case 2: std::cout << "You have chosen Choice 2" << std::endl;
        printMinimum();
        break;
       
        case 3: std::cout << "You have chosen Choice 3" << std::endl;
        printMaximum();
        break;

        case 4: std::cout << "You have chosen Choice 4" << std::endl;
        printRecursiveProduct(yourArray, 0);
        break;

        case 5: std::cout << "You have chosen Choice 5" << std::endl;
        printRecursiveSummation(yourArray, 0);
        break;
    }
    std::cout<< std::endl;

}






int main(){
char choice;    
    do {
        commenceProgram();
        promptMenu();
    } while (repeatProgram());
    std::cout << std::endl;
    do {
        analyzeFileContents();
        std::cout << "Would you like to read the same file again? (Y/N): ";
        std::cin >> choice;
    } while (choice == 'Y' || choice == 'y');
    std::cout << std::endl;
    goodBye();
return 0;
}
