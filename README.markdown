# Sensory System Analyzer

## Description
A C++ console application that analyzes text to identify a person's preferred sensory system (Visual, Auditory, or Kinesthetic) based on word choices. Features word frequency analysis, result storage, and a colorful interface. Created by Adrian Lesniak.

## Features
- Analyze text for sensory system preferences
- Display most frequent words
- Save analysis results to `analysis_results.txt`
- View previous analysis results
- Provide help guide with word categories
- Colorful console interface

## Requirements
- C++ compiler (e.g., g++)
- Header file: `helpers.h` (not provided)
- Windows OS for full color functionality (via `helpers.h`)

## Installation
1. Clone the repository:
   ```bash
   git clone <repository-url>
   ```
2. Ensure `helpers.h` is in the project directory.
3. Compile the program:
   ```bash
   g++ main.cpp -o sensory_analyzer
   ```

## Usage
1. Run the program:
   ```bash
   ./sensory_analyzer
   ```
2. Choose options 1-4 from the menu:
   - 1: Analyze new text (enter text, type 'end' to finish)
   - 2: View previous results
   - 3: Show help guide
   - 4: Exit
3. Analysis results are saved to `analysis_results.txt`.

## Notes
- Requires `helpers.h` for functions like `setColor()`, `clearScreen()`, `drawLine()`, and `waitForKeyPress()`.
- Word categories include Visual (e.g., see, look), Auditory (e.g., hear, sound), and Kinesthetic (e.g., feel, touch).
- Results include word frequency and dominant sensory system.

## Author
Adrian Lesniak

## License
MIT License