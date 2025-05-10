#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include "helpers.h"

using namespace std;

void showHeader() {
    helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
    helpers::drawLine('*');
    cout << "                 REPRESENTATIVE SYSTEM ANALYZER" << endl;
    cout << "                    by Adrian Lesniak" << endl;
    helpers::drawLine('*');
    helpers::setColor(helpers::ConsoleColor::COL_INFO);
    cout << "\nThis program analyzes text to determine a person's preferred sensory system" << endl;
    cout << "(Visual, Auditory, or Kinesthetic) based on their word choices.\n" << endl;
    helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
}

void viewResults() {
    helpers::clearScreen();
    showHeader();
    
    ifstream inFile("analysis_results.txt");
    if (!inFile) {
        helpers::setColor(helpers::ConsoleColor::COL_ERROR);
        cout << "No previous results found!\n";
        helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
        helpers::waitForKeyPress();
        return;
    }

    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
    helpers::waitForKeyPress();
}

void analyzeText() {
    map<string, int> word_count;
    vector<string> words;
    string word;
    int sys_wzr = 0;
    int sys_aud = 0;
    int sys_kin = 0;

    helpers::clearScreen();
    showHeader();
    
    try {
        // Enhanced word categories with more examples
        const vector<string> visual_words = {
            "look", "see", "watch", "picture", "eyes", "view", "show", "appear",
            "sight", "vision", "color", "bright", "dark", "clear", "focus", "image",
            "scene", "perspective", "visible", "observe"
        };
        const vector<string> auditory_words = {
            "music", "hear", "deaf", "voice", "speech", "sound", "listen", "tell",
            "talk", "silence", "loud", "quiet", "rhythm", "melody", "whisper", "sing",
            "noise", "echo", "harmony", "say"
        };
        const vector<string> kinesthetic_words = {
            "feel", "feeling", "emotions", "peace", "work", "touch", "hold", "move",
            "grasp", "heavy", "light", "warm", "cold", "smooth", "rough", "comfort",
            "handle", "pressure", "soft", "hard"
        };

        cout << "\nEnter text (type 'end' to finish):\n";
        helpers::setColor(helpers::ConsoleColor::COL_INFO);
        
        while ((cin >> word) && (word != "end")) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            ++word_count[word];
            words.push_back(word);
        }

        // Sort words by number of occurrences
        sort(words.begin(), words.end(), [&](const string& a, const string& b)
        {
            return word_count[a] > word_count[b];
        });

        helpers::clearScreen();
        showHeader();
        
        helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
        cout << "Analysis Results:\n";
        helpers::drawLine('-');
        helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);

        // First, analyze all words for sensory systems
        for (const auto& word : words) {
            // Check if the word belongs to one of the categories
            if (find(visual_words.begin(), visual_words.end(), word) != visual_words.end())
            {
                ++sys_wzr;
            }
            else if (find(auditory_words.begin(), auditory_words.end(), word) != auditory_words.end())
            {
                ++sys_aud;
            }
            else if (find(kinesthetic_words.begin(), kinesthetic_words.end(), word) != kinesthetic_words.end())
            {
                ++sys_kin;
            }
        }

        // Then display frequent words (separate from analysis)
        cout << "Most frequently used words:\n" << endl;
        set<string> displayed_words;
        for (const auto& word : words) {
            if (word_count[word] > 1 && displayed_words.find(word) == displayed_words.end()) {
                cout << word << ": " << word_count[word] << '\n';
                displayed_words.insert(word);
            }
        }

        // Results analysis
        if (sys_wzr == 0 && sys_aud == 0 && sys_kin == 0) {
            cout << "\nUnable to determine the representative system. No characteristic words found." << endl;
        } else if (sys_wzr > sys_aud && sys_wzr > sys_kin) {
            cout << "\nThe person uses mainly the visual system." << endl;
        } else if (sys_aud > sys_wzr && sys_aud > sys_kin) {
            cout << "\nThe person uses mainly the auditive system." << endl;
        } else if (sys_kin > sys_wzr && sys_kin > sys_aud) {
            cout << "\nThe person uses mainly the kinesthetic system." << endl;
        } else if (sys_wzr == sys_aud && sys_wzr > 0) {
            cout << "\nThe person uses mainly the visual and auditive system." << endl;
        } else if (sys_wzr == sys_kin && sys_wzr > 0) {
            cout << "\nThe person uses mainly the visual and kinesthetic system." << endl;
        } else if (sys_kin == sys_aud && sys_kin > 0) {
            cout << "\nThe person uses mainly the auditive and kinesthetic system." << endl;
        } else {
            cout << "\nUnable to determine the representative system." << endl;
        }
        
        // Save results to file
        ofstream outFile("analysis_results.txt", ios::app);
        outFile << "Analysis Results:\n";
        for (const auto& word : displayed_words) {
            outFile << word << ": " << word_count[word] << '\n';
        }
        outFile.close();

    } catch (const exception& e) {
        helpers::setColor(helpers::ConsoleColor::COL_ERROR);
        cout << "Error: " << e.what() << endl;
        helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
    }

    helpers::waitForKeyPress();
}

void showHelp() {
    helpers::clearScreen();
    showHeader();
    
    helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
    cout << "HELP GUIDE\n";
    helpers::drawLine('-');
    helpers::setColor(helpers::ConsoleColor::COL_INFO);
    
    cout << "\nProgram Functions:\n";
    cout << "1. Analyze Text (Option 1)\n";
    cout << "   - Enter your text naturally\n";
    cout << "   - Type 'end' when finished\n";
    cout << "   - Program will analyze word frequency\n";
    cout << "   - Results show preferred sensory system\n\n";
    
    cout << "2. View Results (Option 2)\n";
    cout << "   - Shows previously saved analyses\n";
    cout << "   - Results are stored in 'analysis_results.txt'\n\n";
    
    cout << "3. Word Categories:\n";
    cout << "   Visual: see, look, watch, view, etc.\n";
    cout << "   Auditory: hear, listen, sound, etc.\n";
    cout << "   Kinesthetic: feel, touch, grasp, etc.\n";
    
    helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
    helpers::waitForKeyPress();
}

int main() {
    while (true) {
        helpers::clearScreen();
        showHeader();
        
        helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
        cout << "\nMAIN MENU:\n";
        helpers::drawLine('-');
        helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
        cout << "1. Analyze new text\n";
        cout << "2. View previous results\n";
        cout << "3. Help\n";
        cout << "4. Exit\n\n";
        cout << "Choose your option: ";
        
        char choice;
        cin >> choice;
        
        switch (choice) {
            case '1':
                analyzeText();
                break;
            case '2':
                viewResults();
                break;
            case '3':
                showHelp();
                break;
            case '4':
                return 0;
            default:
                helpers::setColor(helpers::ConsoleColor::COL_ERROR);
                cout << "Invalid option!\n";
                helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
                helpers::waitForKeyPress();
        }
    }
    
    return 0;
}
