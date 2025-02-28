# FactorialCalculator

FactorialCalculator is a simple C++ program that calculates the factorial of a number. Except... It works with big numbers, no approximations or loss of information.

The program is developed as a console application that prompts the user for a number, after which it starts computing the factorial of that number. When it is finised, the program creates a file named after the input from the user, followed by the factorial sign (!), with the .txt extension, with the FULL digits of the factorial. It also displays the time it took to compute the result (good for benchmarking) and the number of digits for the result.

It is designed to be as fast as possible, but it could always be faster. If you have any ideas for possible optimizations for this program, feel free to fork this repository and experiment with different changes, and create a pull request if you managed to make it even faster.