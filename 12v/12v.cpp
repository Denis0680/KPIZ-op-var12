#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Функція для підрахунку кількості великих літер у тексті
int countUpperCase(const string& text) {
    int count = 0;
    for (char c : text) {
        if (isupper(c)) {
            count++;
        }
    }
    return count;
}

// Функція для знаходження слів з мінімальною кількістю літер
vector<string> findMinLengthWords(const string& text) {
    istringstream iss(text);
    vector<string> words;
    string word;

    while (iss >> word) {
        words.push_back(word);
    }

    sort(words.begin(), words.end(),
        [](const string& a, const string& b) {
            return a.length() < b.length();
        });

    vector<string> minWords;
    int minLength = words[0].length();

    for (const string& w : words) {
        if (w.length() == minLength) {
            minWords.push_back(w);
        }
    }

    return minWords;
}

// Функція для видалення слів, які починаються з малої літери
string removeLowerCaseWords(const string& text) {
    istringstream iss(text);
    string result;
    string word;

    while (iss >> word) {
        if (!islower(word[0])) {
            result += word + " ";
        }
    }

    return result;
}

int main() {
    string inputFileName = "input.txt";
    string outputFileName = "output.txt";

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Unable to open input file: " << inputFileName << endl;
        return 1;
    }

    string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    inputFile.close();

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Unable to open output file: " << outputFileName << endl;
        return 1;
    }

    outputFile << "Original content:\n" << content << "\n\n";

    int digitCount = countUpperCase(content);
    outputFile << "The count of uppercase letters in the text: " << digitCount << endl;

    vector<string> minWords = findMinLengthWords(content);
    outputFile << "Words with minimum length: ";
    for (const string& word : minWords) {
        outputFile << word << " ";
    }

    string modifiedContent = removeLowerCaseWords(content);

    outputFile << "\nModified content:\n" << modifiedContent;
    outputFile.close();

    cout << "Results have been written to: " << outputFileName << endl;

    return 0;
}
