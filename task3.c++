// PUT UR CODE FOR TEST HERE

 // Function to calculate the minimum number of moves required
// to turn off all switches
unsigned long long min_moves(int n) 
{
    // Create an array to store the minimum moves required
    // for each number of switches from 1 to n
    vector<unsigned long long>dp(n + 1);

    // Initialize the base cases
    dp[1] = 1; // Minimum number of moves to turn off one switch is 1
    if(n>=2)
       dp[2] = 2; // Minimum number of moves to turn off two switches is 2

    // Loop through each number of switches from 3 to n
    for (int i = 3; i <= n; i++) 
    {
        // Use the recurrence relation to calculate the minimum
        // number of moves required for i switches
        dp[i] = dp[i - 1] + 2 * dp[i - 2] + 1;
    }

    // Return the minimum number of moves required to turn off all switches
    return dp[n];
}
//........TASK 3 .......
