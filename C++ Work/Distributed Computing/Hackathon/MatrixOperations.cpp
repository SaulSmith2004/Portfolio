#include <vector>
#include <stdexcept>
#include <thread>
#include <iostream>
#include <iomanip>

#include "MatrixOperations.h"
#include "FileWrite.h"

// Initialise and Run the Full Matrix Operation: Transpose -> Zone Sum -> Matrix Multiplication
void matrixOperationsInit(std::vector<std::vector<double>>* srcMatrix, std::vector<std::vector<double>>* dstMatrix)
{
    int dim = srcMatrix->size();

    // Create intermediate matrices for each stage of the operation chain
    std::vector<std::vector<double>> op1Matrix(dim); // After Transpose
    std::vector<std::vector<double>> op2Matrix(dim); // After Zone Sum
    std::vector<std::vector<double>> op3Matrix(dim); // After Matrix Multiplication (Final Result)

    // Gets CPU core count 
    int cpuCount = std::thread::hardware_concurrency();

    // Resize all rows for intermediate matrices to match dimensions
    for (int i = 0; i < dim; i++)
    {
        op1Matrix[i].resize(dim);
        op2Matrix[i].resize(dim);
        op3Matrix[i].resize(dim);
    }

    // Execute the operations sequentially, passing results forward to the next
    operation1(srcMatrix, &op1Matrix);    // Transpose
    operation2(&op1Matrix, &op2Matrix);   // Zone sum
    operation3(&op2Matrix, &op3Matrix);   // Matrix multiplication

    // Copies final result to the destination matrix
    for (int i = 0; i < dim; i++)
    {
        dstMatrix->at(i).resize(dim);
        for (int j = 0; j < dim; j++)
        {
            dstMatrix->at(i).at(j) = op3Matrix.at(i).at(j);
        }
    }


    // Uncomment to write matrices to files for verification/debugging
 
    // fileWrite("srcMatrix.txt", srcMatrix);
    // fileWrite("op1Matrix.txt", &op1Matrix);
    // fileWrite("op2Matrix.txt", &op2Matrix);
    // fileWrite("op3Matrix.txt", &op3Matrix);
    // fileWrite("dstMatrix.txt", dstMatrix);
}




//Operation 1: Transpose a matrix using one thread per row approach
void operation1(std::vector<std::vector<double>>* srcMatrix, std::vector<std::vector<double>>* dstMatrix)
{
    int size = srcMatrix->size();
    dstMatrix->resize(size);
    for (int i = 0; i < size; i++)
        (*dstMatrix)[i].resize(size);

    std::vector<std::thread> threads;

    // Each thread processes a single row of the source matrix
    for (int row = 0; row < size; ++row)
    {
        threads.emplace_back([=]() {
            for (int col = 0; col < size; ++col)
            {
                // Transpose: flip rows and columns against eachother 
                (*dstMatrix)[row][col] = (*srcMatrix)[col][row];
            }
            });
    }

    // Wait for all threads to complete then join
    for (auto& t : threads)
        t.join();
}





//Operation 2: Perform Zone Sum: Each cell becomes the sum of its own value and its neighbours, as shown in example on brief
void operation2(std::vector<std::vector<double>>* srcMatrix, std::vector<std::vector<double>>* dstMatrix)
{
    int size = srcMatrix->size();
    dstMatrix->resize(size);
    for (int i = 0; i < size; ++i)
        (*dstMatrix)[i].resize(size);

    std::vector<std::thread> threads;

    // Each thread is responsible for computing all zone sums in one row
    for (int row = 0; row < size; ++row)
    {
        threads.emplace_back([=]() {
            for (int col = 0; col < size; ++col)
            {
                double sum = 0.0;

                // Loop through the 3x3 zone around the current cell
                for (int i = row - 1; i <= row + 1; ++i)
                {
                    for (int j = col - 1; j <= col + 1; ++j)
                    {
                        // Ensure indices are within matrix bounds
                        if (i >= 0 && i < size && j >= 0 && j < size)
                        {
                            sum += (*srcMatrix)[i][j];
                        }
                    }
                }

                // Store the sum in the destination matrix
                (*dstMatrix)[row][col] = sum;
            }
            });
    }

    // Wait for all threads to finish then join
    for (auto& t : threads)
        t.join();
}





// Perform matrix multiplication: dst = src x src
// Multithreaded version: one thread per row
void operation3(std::vector<std::vector<double>>* srcMatrix, std::vector<std::vector<double>>* dstMatrix)
{
    int size = srcMatrix->size();
    dstMatrix->resize(size);
    for (int i = 0; i < size; ++i)
        (*dstMatrix)[i].resize(size);

    std::vector<std::thread> threads;

    // Each thread computes one row of the result matrix
    for (int row = 0; row < size; ++row)
    {
        threads.emplace_back([=]() {
            for (int col = 0; col < size; ++col)
            {
                double sum = 0.0;
                for (int k = 0; k < size; ++k)
                {
                    // Multiply row from A by column from A (i.e., A x A)
                    sum += (*srcMatrix)[row][k] * (*srcMatrix)[k][col];
                }
                (*dstMatrix)[row][col] = sum;
            }
            });
    }

    // Wait for all threads to complete
    for (auto& t : threads)
        t.join();
}


