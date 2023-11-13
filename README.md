# CPSC-335_Stock-Purchase-Maximization #

My submission for CPSC 335 - Project 2: Exhaustive vs Dynamic Programming
* The Stock Purchase Maximization Problem

## My Information ##

* Institution: California State University Fullerton (CSUF)
* Course: CPSC 335 - Algorithm Engineering (Fall 2023, Section 02, 13543)
* Name: Josue Han Yan Tai Liu
* Email: josue.tai@csu.fullerton.edu

## How to run the program ##

* The programming language used is C++.
* The executable file is already compiled to run from a Linux terminal.
* If needed, you can recompile again from a Linux terminal by using the command
    - $g++ main.cpp -o StockPurchaseMaximization
    - Also your compiler should support C++11 or newer standard
* To run the executable file from a Linux terminal, use the command
    - $./StockPurchaseMaximization
* The console log output is being redirected to a console_log.txt file.
* The program reads input from a input.txt file.
    - Each case is represented by 3 lines, and a newline should separate each case.
    - In each case, the first line represents the number of companies (N), the second line represents quantity of stocks and their total value as a pair of values (s,v) using the notation of an array of arrays, the third line represents the amount available for investment (M).
    - Only integer values are accepted.
* The output results are saved in a output.txt file.
    - The output for each case is represented by one single line containing the max amount of stocks that is possible to purchase on each case. And a newline separates each case.
* An 'input.txt' file is provided with 10 sample cases, and the respective 'output.txt' and 'console_log.txt' for running the program with this sample 'input.txt' file.

    - Sample case input:

    ```
    4
    [[1,2],[4,3],[3,6],[6,7]]
    12
    ```

    - Sample case output:

    ```
    11
    ```

    - Console log output for this case:

    ```
    Number of companies, N = 4
    Quantity of stocks (s) and their total value (v) for each company:
      1 2   4 3   3 6   6 7  
    Amount available for investment, M = 12

      Exhaustive Search approach.
      Time complexity: O(2^n)
      Time taken by the algorithm: 38 microseconds.
      Maximum number of stocks: 11

      Dynamic Programming approach.
      Time complexity: O(n*M) where M is the amount available for investment
      Time taken by the algorithm: 18.1 microseconds.
      Maximum number of stocks: 11
    ```

    - In this sample case, the best combination is given by the pairs (s,v) on the indexes 0, 1 and 3. This combination maximizes the quantity of stocks purchased given the limited amount available to invest. Giving a total amount invested of 2 + 3 + 7 = 12, and a total quantity of stocks of 1 + 4 + 6 = 11.

    - Also, as we can see on the console log, this program solves the same problem using two algorithmic approaches, Exhaustive Search and Dynamic Programming. Both approaches give the same result, but the processing time differs, especially when the case input is bigger (the array is bigger). See the result of the sample case input below, which is the last case in the provided sample 'input.txt' file, it has an array size of 10 elements.

    ```
    10
    [[3,2],[4,3],[5,3],[5,3],[6,7],[4,4],[7,7],[5,2],[1,1],[2,2]]
    20
    ```

    ```
    29
    ```

    ```
    Number of companies, N = 10
    Quantity of stocks (s) and their total value (v) for each company:
      3 2   4 3   5 3   5 3   6 7   4 4   7 7   5 2   1 1   2 2  
    Amount available for investment, M = 20

      Exhaustive Search approach.
      Time complexity: O(2^n)
      Time taken by the algorithm: 1929.6 microseconds.
      Maximum number of stocks: 29

      Dynamic Programming approach.
      Time complexity: O(n*M) where M is the amount available for investment
      Time taken by the algorithm: 18.4 microseconds.
      Maximum number of stocks: 29
    ```