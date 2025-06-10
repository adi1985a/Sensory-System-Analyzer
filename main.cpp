#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include "helpers.h"
#include <thread> // Dodane do animacji
#include <chrono> // Dodane do animacji

using namespace std;

void showHeader(bool showDefault = true) {
    helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
    if (showDefault) {
        helpers::drawLine('*');
        cout << "                 REPRESENTATIVE SYSTEM ANALYZER" << endl;
        cout << "                    by Adrian Lesniak" << endl;
        helpers::drawLine('*');
        helpers::setColor(helpers::ConsoleColor::COL_INFO);
        cout << "\nThis program analyzes text to determine a person's preferred sensory system" << endl;
        cout << "(Visual, Auditory, or Kinesthetic) based on their word choices.\n" << endl;
        helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
    } else {
        // Nic nie rysuj, nagłówek zostanie zastąpiony animacją
    }
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
            "scene", "perspective", "visible", "observe", "vivid", "glance", "sparkle", "spectrum", "glare", "glimpse",
            "horizon", "shadow", "reflect", "luminous", "vibrant", "silhouette",
            "panorama", "kaleidoscope", "static", "pixel", "contrast", "hue",
            "shade", "streak", "shimmer", "beam", "spotlight",
            "flicker", "mosaic", "outline", "gradient", "vignette", "dazzle", "twinkle",
            "blurred", "contour", "lens", "prism", "tint", "translucent", "radiant", 
            "glossy", "glint", "gaze", "flash", "glow", "shine", "dull", "brilliance"
        };
        const vector<string> auditory_words = {
            "music", "hear", "deaf", "voice", "speech", "sound", "listen", "tell",
            "talk", "silence", "loud", "quiet", "rhythm", "melody", "whisper", "sing",
            "noise", "echo", "harmony", "say", "tone", "pitch", "volume", "murmur", "clang", "buzz", "chant",
            "chatter", "roar", "babble", "tune", "drum", "beat", "acoustic",
            "cacophony", "resonance", "trill", "static", "intonation", "reverb",
            "sibilant", "clangor", "drone", "flutter", "hush", "shriek", "swell", "hiss",
            "jangle", "pluck", "ring", "squeal", "thump", "chirp", "crackle", "rustle",
            "hum", "plink", "whistle", "clap", "snap", "pop", "groan", "sigh", "gurgle",
            "whine", "squawk", "bark", "howl", "caw", "chirrup", "yell", "scream"
        };
        const vector<string> kinesthetic_words = {
            "feel", "feeling", "emotions", "peace", "work", "touch", "hold", "move",
            "grasp", "heavy", "light", "warm", "cold", "smooth", "rough", "comfort",
            "handle", "pressure", "soft", "hard", "squeeze", "sway", "tremble", "pulse", "vibration", "tension",
            "weight", "balance", "lean", "stumble", "jog", "sprint", "caress",
            "pat", "stroke", "compress", "knead", "bounce", "tilt", "shift",
            "ripple", "jolt", "jiggle", "fidget", "sway", "wobble", "twitch",
            "clutch", "grip", "clench", "caress", "embrace", "hug", "tap", "flick"
        };

        // For fast lookup
        set<string> visual_set(visual_words.begin(), visual_words.end());
        set<string> auditory_set(auditory_words.begin(), auditory_words.end());
        set<string> kinesthetic_set(kinesthetic_words.begin(), kinesthetic_words.end());

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

        // ANIMACJA na górze rezultatów
        for (int i = 0; i < 3; ++i) {
            helpers::clearScreen();
            showHeader(false);
            helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
            cout << "\n\n";
            cout << string(10 + i * 10, ' ') << "*     *     *\n";
            cout << string(10 + i * 10, ' ') << "  *     *\n";
            cout << string(10 + i * 10, ' ') << "*     *     *\n";
            helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        helpers::clearScreen();
        showHeader(false);

        // Nagłówek "RESULTS"
        helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
        helpers::drawLine('=');
        cout << "                   R E S U L T S\n";
        helpers::drawLine('=');
        helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);

        // Wyświetl grafikę ASCII odpowiadającą rezultatowi (oko, ucho, ręka)
        string system_ascii;
        if (sys_wzr > sys_aud && sys_wzr > sys_kin) {
            // VISUAL
            system_ascii =
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣄⠀⠀⢿⡇⠀⠀⣾⢀⣸⣄⠀⢠⡐⡄⣹⠀⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⢧⢘⣼⣤⠴⠾⣿⡛⠋⣿⡏⢹⡏⠉⣽⢻⢛⡟⢲⡿⣤⣠⣆⡔⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⢻⣤⡼⠿⣟⣿⣷⣤⣸⣿⣦⣿⣷⣿⣷⣾⣿⣿⣿⣷⣟⣁⣴⡿⠟⠲⣤⣴⠃⠀⢀⠄⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠰⣼⣶⣎⣉⣙⣿⣿⠿⢻⣿⠟⠋⠉⠙⢟⣛⠀⠀⠀⠙⠟⢿⡙⠛⠿⣶⣶⡾⠋⢉⣳⣴⡟⡠⠀⢀⢀⠀⠀\n"
                "⠀⠀⠀⠠⣄⣠⣋⣉⣹⣿⠟⠋⠀⠀⡾⠁⠀⠀⢀⣾⣿⣿⣿⠷⠀⢤⡀⠈⣷⠀⠀⠀⠉⠻⢿⣿⣿⡿⠛⢧⣠⣾⠞⠀⠀\n"
                "⠀⠀⠦⣀⣞⣭⣽⡿⠟⠁⠀⠀⠀⠀⡇⠀⠀⠀⢸⣿⣿⣿⣿⣄⣀⣠⠇⠀⢸⠀⠀⠀⠀⠀⠀⠈⠛⣾⣿⣿⣯⠴⠂⣀⡴\n"
                "⠀⠐⠦⠴⣶⡿⡟⠀⠀⠀⠀⠀⠀⠀⣷⠀⠀⠀⠘⢿⣿⣿⣿⡿⠃⠀⠀⠀⡿⠀⠀⠀⠀⠀⠀⢀⣾⣿⣭⣍⡉⠉⠉⠁⠀\n"
                "⢠⠎⢩⠟⠋⢃⢳⠀⠀⠀⠀⠀⠀⠀⠘⣷⡀⠀⠀⠀⠀⠉⠀⠀⠀⠀⢀⡾⠁⠀⠀⠀⠀⣀⣴⣿⣟⣋⠉⠉⡓⠦⠀⠀⠀\n"
                "⠘⣄⠘⠒⠒⠘⠢⠧⢤⣀⡀⠀⠀⠀⠀⠈⠻⢦⣀⠀⠀⠀⠀⢀⣀⡴⠛⠁⠀⠀⣀⣤⣾⣿⣏⡉⠉⢉⡿⠿⠀⠀⠀⠀⠀\n"
                "⠀⠀⠉⠁⠀⠀⠀⠦⢤⡾⣿⡿⣷⣶⣦⣤⣄⣀⣈⣉⣉⣉⣉⣉⣁⣠⣤⣴⣾⡿⣿⣿⢧⡀⠈⣹⠶⠋⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠤⣋⠁⡼⠛⠛⡿⣿⠖⢛⣿⠛⠛⣿⡟⠛⠻⣿⡱⠄⠉⣣⠼⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠓⠤⢤⣹⣁⠀⢸⡇⠀⠀⠸⡃⣀⣀⠬⠷⠒⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀\n";
        } else if (sys_aud > sys_wzr && sys_aud > sys_kin) {
            // AUDITORY
            system_ascii =
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡄⠀⠀⠀⠀⠀⣠⢤⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠈⠓⢤⣀⠀⠀⠀⠀⣾⠿⡄⠀⠀⠀⠀⠀⠀⠀⢀⣶⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣷⣀⣀⣀⡠⠤⠿⢧⡧⠓⠀⠀⣀⣤⠤⠤⢄⣀⣰⠷⡆⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠈⠉⠒⠦⢤⣏⣰⡇⠀⠀⠀⠀⠀⠀⢀⡾⠿⣯⣽⣻⡏⠀⠀⠀⠀⣠⣀⣀⡤⠤⠴⠒⠒⠀⡏⣻⣇⡤⠤⠖⠒⢲⣚⡩⠭⠭⠽⣛⣟⣛⣛⣻⣿⣿⣿⣷⣦⣄⠀⠀⠀⠀\n"
                "⠀⠉⠒⠤⣀⠀⠀⣠⣿⠟⠉⠙⠒⠒⢒⣶⡄⡞⠀⠐⠒⢒⡟⠒⠚⠉⠉⠁⡿⣦⣀⣠⠤⠤⠒⢾⡿⣁⣯⠤⠔⣒⣫⣭⠤⠐⣒⡫⠭⣤⡞⠒⠚⠉⠉⠉⠙⠚⠛⠿⢿⣿⣦⣷⡀\n"
                "⠀⣀⠀⠀⠀⣽⡿⠿⡧⠤⢀⣀⣀⣀⣿⣿⣿⣁⣠⣶⣶⣼⠡⠤⠤⠖⢒⢺⠉⡹⢁⣀⡠⠤⣶⡆⢉⣁⠤⠖⢂⣏⠭⢿⠂⠉⠁⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢹⡇⠇\n"
                "⠀⠀⠉⠒⣼⣏⣠⣴⣷⣦⡄⠀⠀⠀⠀⠀⡀⠀⠈⠛⠛⠁⠀⠀⣀⣠⠿⠟⠒⠋⠉⢀⣠⢼⠟⠛⢉⡠⠔⠚⣩⡇⢰⡾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀\n"
                "⠀⠠⢄⡀⢸⡇⢿⠉⣿⠛⣿⠲⠤⠤⠤⢴⣧⠴⠒⠒⠒⠈⠉⠉⡄⠀⣀⡀⠤⠒⠊⠉⣀⣸⠖⠊⠉⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠉⠓⠻⢤⣕⣿⡴⠋⠀⠀⠀⠀⣾⡟⣧⢀⣀⣠⠤⢄⡞⠛⠉⠁⠀⣠⠤⠒⠋⣥⣼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠐⠦⢀⡀⣠⣤⡀⢹⠈⠉⠉⠉⠉⠉⡏⢻⣿⠁⠀⠀⢀⣜⣹⡧⠖⠊⠉⠀⠀⠀⠀⠙⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠉⢿⣛⣣⡾⢤⣀⣀⣀⣤⣴⣅⣴⠧⠄⠒⠚⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠉⠉⠀⠀⠀⠀⠘⠛⠋⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
        } else if (sys_kin > sys_wzr && sys_kin > sys_aud) {
            // KINESTHETIC
            system_ascii =
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡖⠉⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⡤⣄⠀⠀⠀⠀⠀⢰⠀⠀⢸⠀⠀⠀⡸⠉⢣⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⢸⡀⠈⢧⠀⠀⠀⠀⢸⣀⣀⢸⠀⠀⠀⠇⠀⢸⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠸⡇⠀⢈⡆⠀⠀⠀⢸⠀⠀⠸⠀⠀⢸⠠⠄⡘⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⢻⠉⠀⠱⠀⠀⠀⡆⢀⡀⣄⠀⠀⡆⠀⠀⠇⠀⠀⠀⡔⢢\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠸⡆⠀⣀⢇⠀⠀⡇⠉⠙⢹⠀⠘⠰⠦⢼⠀⠀⠀⡰⠀⢰\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⡉⠁⠈⠆⠀⡇⠀⠀⢸⠀⡇⠀⠀⠸⠀⠀⡰⠁⢂⠄\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⠀⠀⠘⣄⡇⢴⡤⢸⣤⢁⡀⠀⠇⢀⡎⠠⣀⠎⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡖⠊⠁⠈⠒⠀⠀⠀⠀⠉⠒⠸⣄⡜⠀⢀⠟⠀⠀\n"
                "⡠⠖⠒⠢⢤⡀⠀⠀⠀⠀⢠⠁⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢗⡞⠀⠀⠀\n"
                "⠉⠒⢄⠀⠀⠘⢆⠀⠀⠀⠘⣄⠤⠀⠤⢀⠈⠁⠐⠤⢀⡀⠀⠀⠀⠀⡇⠀⠀⠀\n"
                "⠀⠀⠀⠛⢄⠀⠈⠓⣄⠀⢸⢠⠀⠀⠑⢄⠈⠢⣀⠀⠀⠈⠁⠢⡀⢠⠃⠀⠀⠀\n"
                "⠀⠀⠀⠀⠈⢳⠀⠀⠈⠓⠚⠁⠀⠀⠀⠈⡆⠀⠀⠑⠂⠀⠀⠀⠀⢸⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠙⢆⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⢠⠇⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠈⢆⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⠀⠀⠀⡸⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢣⡀⠀⠀⠀⢀⡜⠀⠀⠀⠀⠀⠀⢠⠁⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣒⢄⣀⣀⣀⠀⠤⠀⣀⡀⠀⡸⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠀⠉⠉⢠⡶⠀⢠⡶⠀⠀⢠⠁⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠁⠀⠀⠂⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀\n";
        } else if (sys_wzr == sys_aud && sys_wzr > 0) {
            // VISUAL + AUDITORY
            system_ascii =
                // Visual
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣄⠀⠀⢿⡇⠀⠀⣾⢀⣸⣄⠀⢠⡐⡄⣹⠀⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⢧⢘⣼⣤⠴⠾⣿⡛⠋⣿⡏⢹⡏⠉⣽⢻⢛⡟⢲⡿⣤⣠⣆⡔⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⢻⣤⡼⠿⣟⣿⣷⣤⣸⣿⣦⣿⣷⣿⣷⣾⣿⣿⣿⣷⣟⣁⣴⡿⠟⠲⣤⣴⠃⠀⢀⠄⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠰⣼⣶⣎⣉⣙⣿⣿⠿⢻⣿⠟⠋⠉⠙⢟⣛⠀⠀⠀⠙⠟⢿⡙⠛⠿⣶⣶⡾⠋⢉⣳⣴⡟⡠⠀⢀⢀⠀⠀\n"
                "⠀⠀⠀⠠⣄⣠⣋⣉⣹⣿⠟⠋⠀⠀⡾⠁⠀⠀⢀⣾⣿⣿⣿⠷⠀⢤⡀⠈⣷⠀⠀⠀⠉⠻⢿⣿⣿⡿⠛⢧⣠⣾⠞⠀⠀\n"
                "⠀⠀⠦⣀⣞⣭⣽⡿⠟⠁⠀⠀⠀⠀⡇⠀⠀⠀⢸⣿⣿⣿⣿⣄⣀⣠⠇⠀⢸⠀⠀⠀⠀⠀⠀⠈⠛⣾⣿⣿⣯⠴⠂⣀⡴\n"
                "⠀⠐⠦⠴⣶⡿⡟⠀⠀⠀⠀⠀⠀⠀⣷⠀⠀⠀⠘⢿⣿⣿⣿⡿⠃⠀⠀⠀⡿⠀⠀⠀⠀⠀⠀⢀⣾⣿⣭⣍⡉⠉⠉⠁⠀\n"
                "⢠⠎⢩⠟⠋⢃⢳⠀⠀⠀⠀⠀⠀⠀⠘⣷⡀⠀⠀⠀⠀⠉⠀⠀⠀⠀⢀⡾⠁⠀⠀⠀⠀⣀⣴⣿⣟⣋⠉⠉⡓⠦⠀⠀⠀\n"
                "⠘⣄⠘⠒⠒⠘⠢⠧⢤⣀⡀⠀⠀⠀⠀⠈⠻⢦⣀⠀⠀⠀⠀⢀⣀⡴⠛⠁⠀⠀⣀⣤⣾⣿⣏⡉⠉⢉⡿⠿⠀⠀⠀⠀⠀\n"
                "⠀⠀⠉⠁⠀⠀⠀⠦⢤⡾⣿⡿⣷⣶⣦⣤⣄⣀⣈⣉⣉⣉⣉⣉⣁⣠⣤⣴⣾⡿⣿⣿⢧⡀⠈⣹⠶⠋⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠤⣋⠁⡼⠛⠛⡿⣿⠖⢛⣿⠛⠛⣿⡟⠛⠻⣿⡱⠄⠉⣣⠼⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠓⠤⢤⣹⣁⠀⢸⡇⠀⠀⠸⡃⣀⣀⠬⠷⠒⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀\n"
                // Auditory (side by side)
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡄⠀⠀⠀⠀⠀⣠⢤⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "    ⠈⠓⢤⣀⠀⠀⠀⠀⣾⠿⡄⠀⠀⠀⠀⠀⠀⠀⢀⣶⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣷⣀⣀⣀⡠⠤⠿⢧⡧⠓⠀⠀⣀⣤⠤⠤⢄⣀⣰⠷⡆⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠈⠉⠒⠦⢤⣏⣰⡇⠀⠀⠀⠀⠀⠀⢀⡾⠿⣯⣽⣻⡏⠀⠀⠀⠀⣠⣀⣀⡤⠤⠴⠒⠒⠀⡏⣻⣇⡤⠤⠖⠒⢲⣚⡩⠭⠭⠽⣛⣟⣛⣛⣻⣿⣿⣿⣷⣦⣄⠀⠀⠀⠀\n"
                "    ⠀⠉⠒⠤⣀⠀⠀⣠⣿⠟⠉⠙⠒⠒⢒⣶⡄⡞⠀⠐⠒⢒⡟⠒⠚⠉⠉⠁⡿⣦⣀⣠⠤⠤⠒⢾⡿⣁⣯⠤⠔⣒⣫⣭⠤⠐⣒⡫⠭⣤⡞⠒⠚⠉⠉⠉⠙⠚⠛⠿⢿⣿⣦⣷⡀\n"
                "    ⠀⣀⠀⠀⠀⣽⡿⠿⡧⠤⢀⣀⣀⣀⣿⣿⣿⣁⣠⣶⣶⣼⠡⠤⠤⠖⢒⢺⠉⡹⢁⣀⡠⠤⣶⡆⢉⣁⠤⠖⢂⣏⠭⢿⠂⠉⠁⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢹⡇⠇\n"
                "    ⠀⠀⠉⠒⣼⣏⣠⣴⣷⣦⡄⠀⠀⠀⠀⠀⡀⠀⠈⠛⠛⠁⠀⠀⣀⣠⠿⠟⠒⠋⠉⢀⣠⢼⠟⠛⢉⡠⠔⠚⣩⡇⢰⡾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀\n"
                "    ⠀⠠⢄⡀⢸⡇⢿⠉⣿⠛⣿⠲⠤⠤⠤⢴⣧⠴⠒⠒⠒⠈⠉⠉⡄⠀⣀⡀⠤⠒⠊⠉⣀⣸⠖⠊⠉⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠉⠓⠻⢤⣕⣿⡴⠋⠀⠀⠀⠀⣾⡟⣧⢀⣀⣠⠤⢄⡞⠛⠉⠁⠀⣠⠤⠒⠋⣥⣼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠐⠦⢀⡀⣠⣤⡀⢹⠈⠉⠉⠉⠉⠉⡏⢻⣿⠁⠀⠀⢀⣜⣹⡧⠖⠊⠉⠀⠀⠀⠀⠙⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠉⢿⣛⣣⡾⢤⣀⣀⣀⣤⣴⣅⣴⠧⠄⠒⠚⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠉⠉⠀⠀⠀⠀⠘⠛⠋⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
        } else if (sys_kin == sys_aud && sys_kin > 0) {
            // AUDITORY + KINESTHETIC
            system_ascii =
                // Auditory
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡄⠀⠀⠀⠀⠀⣠⢤⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠈⠓⢤⣀⠀⠀⠀⠀⣾⠿⡄⠀⠀⠀⠀⠀⠀⠀⢀⣶⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣷⣀⣀⣀⡠⠤⠿⢧⡧⠓⠀⠀⣀⣤⠤⠤⢄⣀⣰⠷⡆⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠈⠉⠒⠦⢤⣏⣰⡇⠀⠀⠀⠀⠀⠀⢀⡾⠿⣯⣽⣻⡏⠀⠀⠀⠀⣠⣀⣀⡤⠤⠴⠒⠒⠀⡏⣻⣇⡤⠤⠖⠒⢲⣚⡩⠭⠭⠽⣛⣟⣛⣛⣻⣿⣿⣿⣷⣦⣄⠀⠀⠀⠀\n"
                "⠀⠉⠒⠤⣀⠀⠀⣠⣿⠟⠉⠙⠒⠒⢒⣶⡄⡞⠀⠐⠒⢒⡟⠒⠚⠉⠉⠁⡿⣦⣀⣠⠤⠤⠒⢾⡿⣁⣯⠤⠔⣒⣫⣭⠤⠐⣒⡫⠭⣤⡞⠒⠚⠉⠉⠉⠙⠚⠛⠿⢿⣿⣦⣷⡀\n"
                "⠀⣀⠀⠀⠀⣽⡿⠿⡧⠤⢀⣀⣀⣀⣿⣿⣿⣁⣠⣶⣶⣼⠡⠤⠤⠖⢒⢺⠉⡹⢁⣀⡠⠤⣶⡆⢉⣁⠤⠖⢂⣏⠭⢿⠂⠉⠁⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢹⡇⠇\n"
                "⠀⠀⠉⠒⣼⣏⣠⣴⣷⣦⡄⠀⠀⠀⠀⠀⡀⠀⠈⠛⠛⠁⠀⠀⣀⣠⠿⠟⠒⠋⠉⢀⣠⢼⠟⠛⢉⡠⠔⠚⣩⡇⢰⡾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀\n"
                "⠀⠠⢄⡀⢸⡇⢿⠉⣿⠛⣿⠲⠤⠤⠤⢴⣧⠴⠒⠒⠒⠈⠉⠉⡄⠀⣀⡀⠤⠒⠊⠉⣀⣸⠖⠊⠉⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠉⠓⠻⢤⣕⣿⡴⠋⠀⠀⠀⠀⣾⡟⣧⢀⣀⣠⠤⢄⡞⠛⠉⠁⠀⣠⠤⠒⠋⣥⣼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠐⠦⢀⡀⣠⣤⡀⢹⠈⠉⠉⠉⠉⠉⡏⢻⣿⠁⠀⠀⢀⣜⣹⡧⠖⠊⠉⠀⠀⠀⠀⠙⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠉⢿⣛⣣⡾⢤⣀⣀⣀⣤⣴⣅⣴⠧⠄⠒⠚⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠉⠉⠀⠀⠀⠀⠘⠛⠋⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                // Kinesthetic (side by side)
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⡖⠉⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⡤⣄⠀⠀⠀⠀⠀⢰⠀⠀⢸⠀⠀⠀⡸⠉⢣⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⢸⡀⠈⢧⠀⠀⠀⠀⢸⣀⣀⢸⠀⠀⠀⠇⠀⢸⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠸⡇⠀⢈⡆⠀⠀⠀⢸⠀⠀⠸⠀⠀⢸⠠⠄⡘⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⢻⠉⠀⠱⠀⠀⠀⡆⢀⡀⣄⠀⠀⡆⠀⠀⠇⠀⠀⠀⡔⢢\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠸⡆⠀⣀⢇⠀⠀⡇⠉⠙⢹⠀⠘⠰⠦⢼⠀⠀⠀⡰⠀⢰\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⡉⠁⠈⠆⠀⡇⠀⠀⢸⠀⡇⠀⠀⠸⠀⠀⡰⠁⢂⠄\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⠀⠀⠘⣄⡇⢴⡤⢸⣤⢁⡀⠀⠇⢀⡎⠠⣀⠎⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡖⠊⠁⠈⠒⠀⠀⠀⠀⠉⠒⠸⣄⡜⠀⢀⠟⠀⠀\n"
                "    ⡠⠖⠒⠢⢤⡀⠀⠀⠀⠀⢠⠁⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢗⡞⠀⠀⠀\n"
                "    ⠉⠒⢄⠀⠀⠘⢆⠀⠀⠀⠘⣄⠤⠀⠤⢀⠈⠁⠐⠤⢀⡀⠀⠀⠀⠀⡇⠀⠀⠀\n"
                "    ⠀⠀⠀⠛⢄⠀⠈⠓⣄⠀⢸⢠⠀⠀⠑⢄⠈⠢⣀⠀⠀⠈⠁⠢⡀⢠⠃⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠈⢳⠀⠀⠈⠓⠚⠁⠀⠀⠀⠈⡆⠀⠀⠑⠂⠀⠀⠀⠀⢸⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠙⢆⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⢠⠇⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠈⢆⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⠀⠀⠀⡸⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢣⡀⠀⠀⠀⢀⡜⠀⠀⠀⠀⠀⠀⢠⠁⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣒⢄⣀⣀⣀⠀⠤⠀⣀⡀⠀⡸⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠀⠉⠉⢠⡶⠀⢠⡶⠀⠀⢠⠁⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠁⠀⠀⠂⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀\n";
        } else if (sys_wzr == sys_kin && sys_wzr > 0) {
            // VISUAL + KINESTHETIC
            system_ascii =
                // Visual
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣄⠀⠀⢿⡇⠀⠀⣾⢀⣸⣄⠀⢠⡐⡄⣹⠀⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⢧⢘⣼⣤⠴⠾⣿⡛⠋⣿⡏⢹⡏⠉⣽⢻⢛⡟⢲⡿⣤⣠⣆⡔⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⢻⣤⡼⠿⣟⣿⣷⣤⣸⣿⣦⣿⣷⣿⣷⣾⣿⣿⣿⣷⣟⣁⣴⡿⠟⠲⣤⣴⠃⠀⢀⠄⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠰⣼⣶⣎⣉⣙⣿⣿⠿⢻⣿⠟⠋⠉⠙⢟⣛⠀⠀⠀⠙⠟⢿⡙⠛⠿⣶⣶⡾⠋⢉⣳⣴⡟⡠⠀⢀⢀⠀⠀\n"
                "⠀⠀⠀⠠⣄⣠⣋⣉⣹⣿⠟⠋⠀⠀⡾⠁⠀⠀⢀⣾⣿⣿⣿⠷⠀⢤⡀⠈⣷⠀⠀⠀⠉⠻⢿⣿⣿⡿⠛⢧⣠⣾⠞⠀⠀\n"
                "⠀⠀⠦⣀⣞⣭⣽⡿⠟⠁⠀⠀⠀⠀⡇⠀⠀⠀⢸⣿⣿⣿⣿⣄⣀⣠⠇⠀⢸⠀⠀⠀⠀⠀⠀⠈⠛⣾⣿⣿⣯⠴⠂⣀⡴\n"
                "⠀⠐⠦⠴⣶⡿⡟⠀⠀⠀⠀⠀⠀⠀⣷⠀⠀⠀⠘⢿⣿⣿⣿⡿⠃⠀⠀⠀⡿⠀⠀⠀⠀⠀⠀⢀⣾⣿⣭⣍⡉⠉⠉⠁⠀\n"
                "⢠⠎⢩⠟⠋⢃⢳⠀⠀⠀⠀⠀⠀⠀⠘⣷⡀⠀⠀⠀⠀⠉⠀⠀⠀⠀⢀⡾⠁⠀⠀⠀⠀⣀⣴⣿⣟⣋⠉⠉⡓⠦⠀⠀⠀\n"
                "⠘⣄⠘⠒⠒⠘⠢⠧⢤⣀⡀⠀⠀⠀⠀⠈⠻⢦⣀⠀⠀⠀⠀⢀⣀⡴⠛⠁⠀⠀⣀⣤⣾⣿⣏⡉⠉⢉⡿⠿⠀⠀⠀⠀⠀\n"
                "⠀⠀⠉⠁⠀⠀⠀⠦⢤⡾⣿⡿⣷⣶⣦⣤⣄⣀⣈⣉⣉⣉⣉⣉⣁⣠⣤⣴⣾⡿⣿⣿⢧⡀⠈⣹⠶⠋⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠤⣋⠁⡼⠛⠛⡿⣿⠖⢛⣿⠛⠛⣿⡟⠛⠻⣿⡱⠄⠉⣣⠼⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠓⠤⢤⣹⣁⠀⢸⡇⠀⠀⠸⡃⣀⣀⠬⠷⠒⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀"
                // Kinesthetic (side by side)
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ ⡖⠉⢆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⡤⣄⠀⠀⠀⠀⠀⢰⠀⠀⢸⠀⠀⠀⡸⠉⢣⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⢸⡀⠈⢧⠀⠀⠀⠀⢸⣀⣀⢸⠀⠀⠀⠇⠀⢸⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠸⡇⠀⢈⡆⠀⠀⠀⢸⠀⠀⠸⠀⠀⢸⠠⠄⡘⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⢻⠉⠀⠱⠀⠀⠀⡆⢀⡀⣄⠀⠀⡆⠀⠀⠇⠀⠀⠀⡔⢢\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠸⡆⠀⣀⢇⠀⠀⡇⠉⠙⢹⠀⠘⠰⠦⢼⠀⠀⠀⡰⠀⢰\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⡉⠁⠈⠆⠀⡇⠀⠀⢸⠀⡇⠀⠀⠸⠀⠀⡰⠁⢂⠄\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⠀⠀⠘⣄⡇⢴⡤⢸⣤⢁⡀⠀⠇⢀⡎⠠⣀⠎⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡖⠊⠁⠈⠒⠀⠀⠀⠀⠉⠒⠸⣄⡜⠀⢀⠟⠀⠀\n"
                "    ⡠⠖⠒⠢⢤⡀⠀⠀⠀⠀⢠⠁⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢗⡞⠀⠀⠀\n"
                "    ⠉⠒⢄⠀⠀⠘⢆⠀⠀⠀⠘⣄⠤⠀⠤⢀⠈⠁⠐⠤⢀⡀⠀⠀⠀⠀⡇⠀⠀⠀\n"
                "    ⠀⠀⠀⠛⢄⠀⠈⠓⣄⠀⢸⢠⠀⠀⠑⢄⠈⠢⣀⠀⠀⠈⠁⠢⡀⢠⠃⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠈⢳⠀⠀⠈⠓⠚⠁⠀⠀⠀⠈⡆⠀⠀⠑⠂⠀⠀⠀⠀⢸⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⢧⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠙⢆⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⢠⠇⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠈⢆⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀⠀⠀⠀⡸⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢣⡀⠀⠀⠀⢀⡜⠀⠀⠀⠀⠀⠀⢠⠁⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣒⢄⣀⣀⣀⠀⠤⠀⣀⡀⠀⡸⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠀⠉⠉⢠⡶⠀⢠⡶⠀⠀⢠⠁⠀⠀⠀⠀⠀⠀\n"
                "    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠁⠀⠀⠂⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀\n";
        } else {
            // Brak rozpoznania
        //    system_ascii = "RESULTS:\n";
        }

        helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
        cout << system_ascii << endl;
        helpers::drawLine('-');
        helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);

        // Analyze only characteristic words for sensory systems
        map<string, int> rep_word_count;
        for (const auto& w : words) {
            if (visual_set.count(w)) {
                ++sys_wzr;
                ++rep_word_count[w];
            } else if (auditory_set.count(w)) {
                ++sys_aud;
                ++rep_word_count[w];
            } else if (kinesthetic_set.count(w)) {
                ++sys_kin;
                ++rep_word_count[w];
            }
        }

        // Display frequent representative words only
        helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
        cout << "\nMost frequently used representative words:\n\n";
        helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);

        vector<pair<string, int>> rep_words_sorted(rep_word_count.begin(), rep_word_count.end());
        sort(rep_words_sorted.begin(), rep_words_sorted.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        if (rep_words_sorted.empty()) {
            cout << "(No representative words found in your text)\n";
        } else {
            for (const auto& p : rep_words_sorted) {
                // Color by system
                if (visual_set.count(p.first)) {
                    helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
                } else if (auditory_set.count(p.first)) {
                    helpers::setColor(helpers::ConsoleColor::COL_INFO);
                } else if (kinesthetic_set.count(p.first)) {
                    helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
                }
                cout << "  " << p.first << ": " << p.second << '\n';
            }
            helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
        }

        // Results analysis with ASCII art and colors
        helpers::drawLine('-');
        cout << endl;
        string result_msg;
        helpers::ConsoleColor result_color = helpers::ConsoleColor::COL_DEFAULT;
        string ascii_art;

        if (sys_wzr == 0 && sys_aud == 0 && sys_kin == 0) {
            result_msg = "Unable to determine the representative system.\nNo characteristic words found.";
            result_color = helpers::ConsoleColor::COL_ERROR;
            ascii_art =
                "   .--.      .-'.      .--.      .--.      .--.      .--.\n"
                "  :::::.\\::::::::.\\::::::::.\\::::::::.\\::::::::.\\::::::::.\\\n"
                "  '      '      '      '      '      '      '      '      '\n";
        } else if (sys_wzr > sys_aud && sys_wzr > sys_kin) {
            result_msg = "The person uses mainly the VISUAL system.";
            result_color = helpers::ConsoleColor::COL_HIGHLIGHT;
            ascii_art =
                "   /\\   \n"
                "  /  \\  \n"
                " /----\\ \n"
                " | () |\n"
                "  \\__/  (eye)\n";
        } else if (sys_aud > sys_wzr && sys_aud > sys_kin) {
            result_msg = "The person uses mainly the AUDITORY system.";
            result_color = helpers::ConsoleColor::COL_INFO;
            ascii_art =
                "   (  )   \n"
                "  (    )  \n"
                " (      ) (ear)\n"
                "  \\    /  \n"
                "   \\__/   \n";
        } else if (sys_kin > sys_wzr && sys_kin > sys_aud) {
            result_msg = "The person uses mainly the KINESTHETIC system.";
            result_color = helpers::ConsoleColor::COL_DEFAULT;
            ascii_art =
                "   o   \n"
                "  /|\\  (body)\n"
                "  / \\  \n";
        } else if (sys_wzr == sys_aud && sys_wzr > 0) {
            result_msg = "The person uses mainly the VISUAL and AUDITORY system.";
            result_color = helpers::ConsoleColor::COL_HIGHLIGHT;
            ascii_art =
                "   /\\    (  ) \n"
                "  /  \\  (    )\n"
                " /----\\(      )\n"
                " | () | \\    /\n"
                "  \\__/   \\__/\n";
        } else if (sys_wzr == sys_kin && sys_wzr > 0) {
            result_msg = "The person uses mainly the VISUAL and KINESTHETIC system.";
            result_color = helpers::ConsoleColor::COL_HIGHLIGHT;
            ascii_art =
                "   /\\    o \n"
                "  /  \\  /|\\\n"
                " /----\\ / \\\n"
                " | () |\n"
                "  \\__/\n";
        } else if (sys_kin == sys_aud && sys_kin > 0) {
            result_msg = "The person uses mainly the AUDITORY and KINESTHETIC system.";
            result_color = helpers::ConsoleColor::COL_INFO;
            ascii_art =
                "   (  )   o\n"
                "  (    ) /|\\\n"
                " (      )/ \\\n"
                "  \\    /\n"
                "   \\__/\n";
        } else {
            result_msg = "Unable to determine the representative system.";
            result_color = helpers::ConsoleColor::COL_ERROR;
        }

        helpers::setColor(result_color);
        cout << "\n" << ascii_art << endl;
        cout << result_msg << endl;
        helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);

        // Zaczekaj na ENTER po pokazaniu rezultatów (przed animacją!)
        helpers::setColor(helpers::ConsoleColor::COL_INFO);
        cout << "\nPress ENTER to continue...";
        helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Wyczyść bufor
        cin.get(); // Czeka na ENTER

        // Prosta animacja gwiazdek zamiast dużego napisu
        for (int i = 0; i < 3; ++i) {
            helpers::clearScreen();
            showHeader();
            helpers::setColor(helpers::ConsoleColor::COL_HIGHLIGHT);
            cout << "\n\n";
            cout << string(10 + i * 10, ' ') << "*     *     *\n";
            cout << string(10 + i * 10, ' ') << "  *     *\n";
            cout << string(10 + i * 10, ' ') << "*     *     *\n";
            helpers::setColor(helpers::ConsoleColor::COL_DEFAULT);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        helpers::drawLine('-');

        // Save results to file (only representative words)
        ofstream outFile("analysis_results.txt", ios::app);
        outFile << "Analysis Results:\n";
        for (const auto& p : rep_words_sorted) {
            outFile << p.first << ": " << p.second << '\n';
        }
        outFile << result_msg << "\n";
        outFile << "--------------------*-------------------\n";
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
