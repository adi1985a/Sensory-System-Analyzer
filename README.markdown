# 👁️👂✋ Sensory System Analyzer Pro - Analyzing prefered sensory system 🧠
_A C++ console application to identify preferred sensory systems (Visual, Auditory, Kinesthetic) by analyzing word choices in text._

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)

## 📋 Table of Contents
1.  [Project Description](#-project-description)
2.  [Key Features](#-key-features)
3.  [Screenshots](#-screenshots)
4.  [System Requirements](#-system-requirements)
5.  [Installation and Running](#️-installation-and-running)
6.  [How to Use](#️-how-to-use)
7.  [Technical Details & Program Logic](#-technical-details--program-logic)
8.  [Contributing](#-contributing)
9.  [Author](#️-author)
10. [License](#-license)

## 📝 Project Description

**Sensory System Analyzer Pro** is an innovative C++ console application designed to analyze text and identify a person's likely preferred sensory representational system: **Visual (V)**, **Auditory (A)**, or **Kinesthetic (K)**. By examining the frequency of specific sensory-based words used in a provided text, the program offers insights into how an individual might primarily perceive and process information. It features detailed word frequency analysis, the ability to save and view analysis results, a helpful guide explaining word categories, and an engaging colorful user interface.

![Demo GIF](screenshots/1.gif)

## ✨ Key Features

*   🧠 **Sensory System Analysis**: Processes input text to count occurrences of Visual, Auditory, and Kinesthetic keywords.
*   📊 **Dominant System Identification**: Determines the likely preferred sensory system based on word frequency counts.
*   🔍 **Word Frequency Display**: Shows a list or summary of the most frequent sensory-related words found in the analyzed text.
*   💾 **Save & Load Results**:
    *   Saves detailed analysis results (word counts, dominant system) to `analysis_results.txt`.
    *   Allows viewing of previously saved analysis results from the file.
*   ❓ **Help Guide**: Provides an in-app guide listing example words categorized under Visual, Auditory, and Kinesthetic systems.
*   🌈 **Colorful Console Interface**: Enhanced user experience with colored text for menus, prompts, and results, facilitated by `helpers.h` (Windows-specific for full effect).
*   📋 **Menu-Driven Operation**: User-friendly menu for easy navigation and access to all features.
*   ✍️ **Multi-Line Text Input**: Supports input of extended text for analysis (e.g., terminated by a keyword like 'end').

## 🖼️ Screenshots

_Screenshots showcasing the text input, analysis results (word frequencies, dominant system), the help guide, and other interface elements._

<p align="center">
  <img src="screenshots\1.jpg" width="300"/>
  <img src="screenshots\2.jpg" width="300"/>
  <img src="screenshots\3.jpg" width="300"/>
  <img src="screenshots\4.jpg" width="300"/>
  <img src="screenshots\5.jpg" width="300"/>
  <img src="screenshots\6.jpg" width="300"/>
  <img src="screenshots\7.jpg" width="300"/>
  <img src="screenshots\8.jpg" width="300"/>
</p>

## ⚙️ System Requirements

*   **Operating System**: Windows is recommended for full color functionality, as the color and console manipulation system likely relies on Windows-specific API calls abstracted in `helpers.h`.
*   **C++ Compiler**: Any modern C++ compiler that supports C++11 or newer (e.g., g++, MinGW, Clang, MSVC).
*   📄 **`helpers.h` Header File (User-Provided)**: This project **critically requires** a header file named `helpers.h`. **This file is not included in the repository and must be created by the user.** It should define utility functions for console manipulation like setting colors, clearing the screen, drawing lines, and pausing. See the "Installation and Running" section for more details.

## 🛠️ Installation and Running

1.  **Clone the Repository**:
    ```bash
    git clone <repository-url>
    ```
    (Replace `<repository-url>` with the actual URL of your repository)

2.  **Navigate to the Project Directory**:
    ```bash
    cd <repository-directory>
    ```
    (Replace `<repository-directory>` with the name of the cloned folder)

3.  **Create `helpers.h`**:
    Before compiling, you **must** create a file named `helpers.h` in the project's root directory. This file should define necessary utility functions. Here's an illustrative example of what it might contain:
    ```cpp
    #ifndef HELPERS_H
    #define HELPERS_H

    #include <string>
    #include <vector> // If used by any helper function
    #ifdef _WIN32
    #include <windows.h> // For SetConsoleTextAttribute, system("cls")
    #include <conio.h>   // For _getch()
    #endif
    #include <iostream>  // For std::cout, std::cin
    #include <fstream>   // If helpers include logging or file ops

    // Example: Console Color Constants (Windows-specific or mapped to ANSI)
    const int CLR_DEFAULT = 7;
    const int CLR_TITLE = 14;   // Yellow
    const int CLR_MENU = 11;    // Light Cyan
    const int CLR_PROMPT = 10;  // Light Green
    const int CLR_RESULT_V = 9; // Light Blue (Visual)
    const int CLR_RESULT_A = 13; // Light Magenta (Auditory)
    const int CLR_RESULT_K = 12; // Light Red (Kinesthetic)
    const int CLR_ERROR = 4;    // Red

    // Function declarations - implement these in helpers.cpp or as inline
    void setColor(int colorCode);
    void clearScreen();
    void drawLine(char c = '-', int length = 60);
    void waitForKeyPress(const std::string& message = "Press any key to continue...");
    // Potentially:
    // std::string readMultiLineText(const std::string& endKeyword = "end");
    // void logMessage(const std::string& message, const std::string& logFilePath = "analyzer.log");

    #endif // HELPERS_H
    ```
    *Adjust these constants and function declarations to precisely match what your `main.cpp` expects. You will need to implement these functions, likely in a `helpers.cpp` file that you'll compile alongside `main.cpp`.*

4.  **Compile the Program**:
    Open a terminal (like Command Prompt or PowerShell) in the project directory.
    **Example using g++ (MinGW):**
    ```bash
    g++ main.cpp helpers.cpp -o sensory_analyzer.exe -static-libgcc -static-libstdc++
    ```
    *(This assumes you have `helpers.cpp` for the implementations of functions declared in `helpers.h`. If all utility logic is inline in `helpers.h`, the `helpers.cpp` part can be omitted from the compile command).*

5.  **Run the Application**:
    After successful compilation, execute the generated program:
    ```bash
    ./sensory_analyzer.exe
    ```
    or simply in CMD:
    ```bash
    sensory_analyzer.exe
    ```

## ▶️ How to Use

Upon launching, **Sensory System Analyzer Pro** will display a main menu. Enter the number for your desired action:

1.  **Analyze new text**:
    *   Prompts you to enter or paste the text you wish to analyze.
    *   You'll typically type or paste multiple lines and then enter a specific keyword (e.g., "end" on a new line) to signify the end of your input.
    *   The program will then process the text, count word frequencies, determine the dominant sensory system, and display the results.
2.  **View previous results**:
    *   Loads and displays the analysis data from the last saved session in `analysis_results.txt`.
3.  **Show help guide**:
    *   Displays a list of example words categorized under Visual (e.g., see, look, picture, bright), Auditory (e.g., hear, sound, listen, loud), and Kinesthetic (e.g., feel, touch, grasp, heavy) systems to help users understand the analysis basis.
4.  **Exit**:
    *   Terminates the application. Analysis results from the current session might be automatically saved before exiting.

*Analysis results are typically saved to `analysis_results.txt`.*

## 💡 Technical Details & Program Logic

*   **Text Processing**: The core logic involves parsing the input text, tokenizing it into words, and then comparing these words (often after converting to lowercase and removing punctuation) against predefined lists of Visual, Auditory, and Kinesthetic keywords.
*   **Keyword Dictionaries**: The program maintains internal lists or maps of words associated with each sensory system (V, A, K). These are crucial for the analysis.
*   **Frequency Counting**: Uses data structures (e.g., `std::map<std::string, int>`) to count the occurrences of relevant sensory words.
*   **Dominant System Logic**: Determines the dominant system by comparing the total counts of V, A, and K words. The system with the highest count is typically identified as dominant.
*   **`helpers.h`**: This essential user-provided header contains utility functions like `setColor()` for console text colors, `clearScreen()` for a cleaner UI, `drawLine()` for visual separation, and `waitForKeyPress()` for pausing program flow.
*   **File I/O**: Employs C++ file streams (`fstream`) to save analysis summaries to `analysis_results.txt` and potentially load them.
*   **User Interface**: Relies on `helpers.h` functions for creating a structured and colorful menu-driven experience in the console.

## 🤝 Contributing

Contributions to **Sensory System Analyzer Pro** are highly encouraged! If you have ideas for expanding the keyword dictionaries, improving the analysis algorithm, adding new features (like percentage breakdowns), or refining the UI:

1.  Fork the repository.
2.  Create a new branch for your feature: `git checkout -b feature/your-sensory-enhancement`
3.  Implement your changes and commit them: `git commit -m "Feature: Add your sensory enhancement"`
4.  Push your changes to your branch: `git push origin feature/your-sensory-enhancement`
5.  Open a Pull Request.

Please ensure your code is well-commented and aligns with the project's existing style.

## ✍️ Author

**Adrian Lesniak**
_C++ Developer & Text Analysis Enthusiast_

## 📃 License

This project is licensed under the **MIT License**.
The full text of the license is available at: [https://opensource.org/licenses/MIT](https://opensource.org/licenses/MIT)

---
💬 _Unlock deeper understanding through the power of words!_
