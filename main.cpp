// ============================================================================
// File: main.cpp
// ============================================================================

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function prototypes
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
    int N;
    int M;
    int option;

    cout << "\n# Stock Purchase Maximation Problem Solver #\n\n";

    // Get from the user number of companies N
    cout << "Enter the number of companies: ";
    cin >> N;

    // Get from the user amount of stocks and their total value (s, v)
    vector<pair<int, int>>  stocks_and_values(N);
    cout << "Enter the quantity of stocks and their total value for"
         << " each company (i.e. 3 2): " << endl;
    for (int i = 0; i < N; ++i)
        {
        cin >> stocks_and_values[i].first >> stocks_and_values[i].second;
        }

    // Get from the user the amount available for investment
    cout << "Enter the amount available for investment: ";
    cin >> M;

    cout << "\nSelect the algorithm approach:\n"
         << "1) Exhaustive Search\n"
         << "2) Dynamic Programming\n"
         << ">> ";
    cin >> option;

    int maxStocks = 0;
    high_resolution_clock::time_point start = high_resolution_clock::now();

    if (option == 1)
        {
        maxStocks = exhaustiveSearch(M, stocks_and_values);
        cout << "\nExhaustive Search selected." << endl;
        cout << "Time complexity: O(2^n)" << endl;
        }
    else if (option == 2)
        {
        maxStocks = dynamicProgramming(M, stocks_and_values);
        cout << "\nDynamic Programming selected." << endl;
        cout << "Time complexity: O(n*M) where M is the amount available"
             << " for investment" << endl;
        }
    else
        {
        cout << "\nInvalid option selected.\n"
             << "Exiting program.\n";
        return 0;
        }

    printTimeTaken(start);
    cout << "\nMaximum number of stocks: " << maxStocks << endl << endl;

    return 0;

}  // end of "main"



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
    duration<double, micro> time_taken = duration_cast<duration<double>>(end -
                                                                        start);

    cout << "Time taken by selected algorithm: " << time_taken.count()
         << " microseconds." << endl;

}  // end of "printTimeTaken"
