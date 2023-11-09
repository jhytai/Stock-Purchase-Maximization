// ============================================================================
// File: main.cpp
// ============================================================================

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
using namespace std;
using namespace std::chrono;

// Function prototypes
string  getNumbersFromString(string &str);
int     totalValue(const vector<pair<int, int>>& items,
                   const vector<bool>& selection);
int     totalStocks(const vector<pair<int, int>>& items,
                    const vector<bool>& selection);
int     exhaustiveSearchUtil(int M, vector<pair<int, int>>& items,
                             vector<bool>& selection, int index);
int     exhaustiveSearch(int M, vector<pair<int, int>> &items);
int     dynamicProgramming(int M, vector<pair<int, int>> &items);
void    printTimeTaken(high_resolution_clock::time_point start);


// ==== main ==================================================================
//
// ============================================================================

int     main()
{
    int             N = 0;
    int             M = 0;
    int             maxStocks = 0;
    ifstream        fin;
    ofstream        fout;
    ofstream        console_out;
    string          line;
    stringstream    ss;
    int             caseLineCount = 0;

    vector<pair<int, int>>  stocks_and_values(N);
    high_resolution_clock::time_point   start;

    // Redirect console log output to console_log.txt file
    console_out.open("console_log.txt");
    auto prevcoutbuf = cout.rdbuf();
    cout.rdbuf(console_out.rdbuf());

    cout << "\n# Stock Purchase Maximation Problem Solver #\n";

    // Check if input.txt file is readable
    fin.open("input.txt");
    if (fin.fail())
        {
        fout.open("output.txt");
        fout << "Error: Unable to open 'input.txt' file for reading...\n";
        fout.close();

        cout << "\nError: Unable to open 'input.txt' file for reading...\n";
        cout << "Program ended.\n\n";

        return 0;
        }

    // Open output.txt file for writing
    fout.open("output.txt");

    while (getline(fin, line))
        {
        ++caseLineCount;

        // Get number of companies, N
        if (caseLineCount == 1 && isdigit(line.at(0)))
            {
            ss = stringstream(line);
            ss >> N;
            cout << "\nNumber of companies, N = " << N << endl;

            if (N < 0 || N > 100000)
                {
                fout << "Error: Constraint violated (0 <= N <= 100000)\n";
                cout << "\nError: Constraint violated (0 <= N <= 100000)\n";
                cout << "Program ended.\n\n";
                return 0;
                }
            }

        // Get amount of stocks and their total value [si,vi]
        else if (caseLineCount == 2 && line.at(0) == '[')
            {
            string  tempStr = getNumbersFromString(line);

            stocks_and_values.resize(N);
            ss = stringstream(tempStr);

            cout << "Quantity of stocks (s) and their total value (v) for"
                 << " each company:\n" << tempStr << endl;

            for (int i = 0; i < N; ++i)
                {
                ss >> stocks_and_values[i].first
                   >> stocks_and_values[i].second;

                if (stocks_and_values[i].first <= 0 ||
                    stocks_and_values[i].second <= 0)
                    {
                    fout << "Error: Constraint violated (s,v > 0)\n";
                    cout << "\nError: Constraint violated (s,v > 0)\n";
                    cout << "Program ended.\n\n";
                    return 0;
                    }
                }
            }

        // Get the amount available for investment, M
        else if (caseLineCount == 3 && isdigit(line.at(0)))
            {
            ss = stringstream(line);
            ss >> M;
            cout << "Amount available for investment, M = " << M << endl;

            // Execute Exhaustive Search approach
            maxStocks = 0;
            start = high_resolution_clock::now();
            maxStocks = exhaustiveSearch(M, stocks_and_values);
            cout << "\n  Exhaustive Search approach." << endl;
            cout << "  Time complexity: O(2^n)" << endl;
            printTimeTaken(start);
            cout << "  Maximum number of stocks: " << maxStocks << endl;

            // Execute Dynamic Programming approach
            maxStocks = 0;
            start = high_resolution_clock::now();
            maxStocks = dynamicProgramming(M, stocks_and_values);
            cout << "\n  Dynamic Programming approach." << endl;
            cout << "  Time complexity: O(n*M) where M is the amount available"
                 << " for investment" << endl;
            printTimeTaken(start);
            cout << "  Maximum number of stocks: " << maxStocks
                 << endl << endl;

            // Write result to output.txt
            fout << maxStocks << endl << endl;
            }

        // Reset for next case
        else if (caseLineCount == 4 && line.empty())
            {
            caseLineCount = 0;
            stocks_and_values.resize(0);
            }

        else
            {
            fout << "Error: Invalid input...\n";
            cout << "\nError: Invalid input...\n";
            cout << "Program ended.\n\n";
            return 0;
            }
        }

    fin.close();
    fout.close();
    cout << "\nProgram ended...\n\n";

    cout.rdbuf(prevcoutbuf);
    console_out.close();
    cout << "\nProgram executed and console log saved in console_log.txt"
         << " file.\n\n";

    return 0;

}  // end of "main"



// ==== getNumbersFromString ==================================================
//
// Helper function to extract only numbers from a string
//
// ============================================================================

string  getNumbersFromString(string &str)
{
    string  numbersStr = str;

    for (int i = 0; i < numbersStr.length(); ++i)
        {
        if (isdigit(str.at(i)) == false)
            {
            numbersStr.replace(i, 1, " ");
            }
        }

    return numbersStr;

}  // end of "getNumbersFromString"



// ==== totalValue ============================================================
//
// Helper function to calculate the total value of the stocks
//
// ============================================================================

int     totalValue(const vector<pair<int, int>>& items,
                   const vector<bool>& selection)
{
    int total = 0;

    for (size_t i = 0; i < selection.size(); ++i)
        {
        if (selection[i])
            {
            total += items[i].second;
            }
        }

    return total;

}  // end of "totalValue"



// ==== totalStocks ===========================================================
//
// Helper function to calculate the total stocks
//
// ============================================================================

int     totalStocks(const vector<pair<int, int>>& items,
                    const vector<bool>& selection)
{
    int stocks = 0;

    for (size_t i = 0; i < selection.size(); ++i)
        {
        if (selection[i])
            {
            stocks += items[i].first;
            }
        }

    return stocks;

}  // end of "totalStocks"



// ==== exhaustiveSearchUtil ==================================================
//
// Exhaustive search recursive call implementation
//
// ============================================================================

int     exhaustiveSearchUtil(int M, vector<pair<int, int>>& items,
                             vector<bool>& selection, int index)
{
    if (index == items.size())
        {
        if (totalValue(items, selection) <= M)
            {
            return totalStocks(items, selection);
            }
        return 0;
        }

    // Select the item
    selection[index] = true;
    int withItem = exhaustiveSearchUtil(M, items, selection, index + 1);

    // Do not select the item
    selection[index] = false;
    int withoutItem = exhaustiveSearchUtil(M, items, selection, index + 1);

    return max(withItem, withoutItem);

}  // end of "exhaustiveSearchUtil"



// ==== exhaustiveSearch ======================================================
//
// Exhaustive search function implementation
//
// ============================================================================

int     exhaustiveSearch(int M, vector<pair<int, int>>& items)
{
    vector<bool> selection(items.size(), false);

    return exhaustiveSearchUtil(M, items, selection, 0);

}  // end of "exhaustiveSearch"



// ==== dynamicProgramming ====================================================
//
// Dynamic programming function implementation
//
// ============================================================================

int     dynamicProgramming(int M, vector<pair<int, int>>& items)
{
    vector<vector<int>> dp(items.size() + 1, vector<int>(M + 1, 0));

    for (int i = 1; i <= items.size(); i++)
        {
        for (int w = 1; w <= M; w++)
            {
            if (items[i - 1].second <= w)
                {
                dp[i][w] = max(dp[i - 1][w], items[i - 1].first
                               + dp[i - 1][w - items[i - 1].second]);
                }
            else
                {
                dp[i][w] = dp[i - 1][w];
                }
            }
        }

    return dp[items.size()][M];

}  // end of "dynamicProgramming"



// ==== printTimeTaken ========================================================
//
// Function to print the time taken by the algorithm in micro-seconds
//
// ============================================================================

void printTimeTaken(high_resolution_clock::time_point start)
{
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double, micro> time_taken = duration_cast<duration<double>>(
        end - start);

    cout << "  Time taken by the algorithm: " << time_taken.count()
         << " microseconds." << endl;

}  // end of "printTimeTaken"
