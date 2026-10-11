/*
 * Name: Briana Lloyd
 * Course: CS 210 - Programming Languages
 * Assignment: Module Five - Temperature Conversion
 * Purpose: Read city temperatures in Fahrenheit from a text file,
 *          convert them to Celsius, and save both precise and rounded
 *          Celsius temperatures to a separate output file.
 */

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// Convert Fahrenheit to Celsius using the standard conversion formula.
double FahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

int main() {
    const string inputFileName = "FahrenheitTemperature.txt";
    const string outputFileName = "CelsiusTemperature.txt";

    // Open the input file and confirm that it is available before reading.
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open " << inputFileName << "." << endl;
        return 1;
    }

    vector<pair<string, double>> temperatures;
    string city;
    double fahrenheit;

    // Read each city and Fahrenheit temperature from the input file.
    // The assignment uses single-word city names followed by a temperature.
    while (inputFile >> city >> fahrenheit) {
        temperatures.push_back({city, FahrenheitToCelsius(fahrenheit)});
    }

    // Report malformed input instead of silently creating an incomplete file.
    if (!inputFile.eof()) {
        cerr << "Error: Invalid temperature data in " << inputFileName << "." << endl;
        return 1;
    }
    inputFile.close();

    // Open the output file and confirm that it can be written successfully.
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to create " << outputFileName << "." << endl;
        return 1;
    }

    // Write converted temperatures with two decimal places for readability.
    outputFile << "Celsius Temperatures" << endl;
    outputFile << fixed << setprecision(2);
    for (const auto& entry : temperatures) {
        outputFile << entry.first << " " << entry.second << endl;
    }

    // Provide a separate section with temperatures rounded to whole numbers.
    outputFile << endl << "Rounded Celsius Temperatures" << endl;
    for (const auto& entry : temperatures) {
        outputFile << entry.first << " " << static_cast<long long>(round(entry.second)) << endl;
    }

    // Confirm that the output was successfully saved.
    outputFile.close();
    if (outputFile.fail()) {
        cerr << "Error: Unable to finish writing " << outputFileName << "." << endl;
        return 1;
    }

    cout << "Temperature conversion complete. Results saved to "
         << outputFileName << "." << endl;
    return 0;
}
