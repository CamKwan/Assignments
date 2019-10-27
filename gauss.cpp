/* gauss.cpp
   CSC 116 - Fall 2019 - Assignment 2

   Cameron Kwan
   V00910702
   11/10/2019
   
*/

#include <vector>
#include <iostream>
#include <cmath>
#include <exception>

/* DO NOT MODIFY ANY CODE BETWEEN THIS LINE AND main() */
using Matrix = std::vector< std::vector< double > >;

/* read_matrix()
   Attempt to read a matrix (in the format described in the assignment specification)
   from standard input. If a matrix is read successfully, it will be returned. If
   any kind of read error occurs, the function will throw an instance of std::runtime_error.
*/
Matrix read_matrix(){
    int rows, cols;
    std::cin >> rows;
    if (!std::cin)
        throw std::runtime_error("Unable to read number of rows");
    
    std::cin >> cols;
    if (!std::cin)
        throw std::runtime_error("Unable to read number of columns");
    
    Matrix result {};
    //Now read each row and add it to the matrix
    for(int i = 0; i < rows; i++){
        std::vector<double> row {};
        for (int j = 0; j < cols; j++){
            double entry;
            std::cin >> entry;
            if (!std::cin){
                throw std::runtime_error("Unable to read entry "+std::to_string(i)+","+std::to_string(j));
            }
            row.push_back(entry);
        }
        result.push_back(row);
    }
    return result;
}

/* PUT YOUR SOLUTION BELOW THIS LINE */
/* You may add extra functions if necessary */


void checkMatrix( Matrix M){
    for (unsigned int i {0}; i < M.size(); i++){
        if ((unsigned)M.at(i).at(i) < 0.0000001 ){
            throw std::domain_error("Matrix is ill-conditioned");
        }
    }
}

//Row Swap
void RowSwap(Matrix& M){
    for (unsigned int i = 0; i < M.size(); i++){

            double rowi = M.at(i).at(i);

            for (unsigned int q = i; q < M.size(); q++){
                if (rowi < M.at(q).at(i)){
                    std::vector<double> temp {};

                    for (auto num: M.at(q))
                        temp.push_back(num);
                    M.at(q) = M.at(i);
                    M.at(i) = temp;
                }

            }
        }
}

//Row Reduction
void RowRedux(Matrix& M){

    for (unsigned int i = 0; i < M.size(); i++){
        std::vector<double> rowi = M.at(i);
        double pivot {};

        for (unsigned int r = i + 1; r < M.size(); r++){
            pivot = M.at(r).at(i) / rowi.at(i);

            for (unsigned int k = i; k < M.size() + 1; k++)
                M.at(r).at(k) -= pivot * M.at(i).at(k);
        
        }
    }
}

//Back Substitution
void BackSub(Matrix& M, std::vector<double>& Vex){
    double t{};
    int n = M.size() - 1;
    for (unsigned int i = 0; i < M.size(); i++){
        t = M.at(n - i).at(n + 1);
        for (unsigned int k{}; k < M.size(); k++){
            t -= Vex.at(n - k)*M.at(n - i).at(n - k);
        }
        Vex.at(n - i) = t/M.at(n - i).at(n - i);
    }
}

int main(){
    try{
        Matrix M = read_matrix();
        std::vector<double> Vex {};
        
        for(auto V: M){
            if(V.size() != M.size() + 1){
                throw std::domain_error("Input is not an augmented square matrix.");
            }
        }
        //initialize solution vector
        for (unsigned int i = 0; i < M.size(); i++){
            Vex.push_back(0);
        }
        
        RowSwap(M);

        checkMatrix(M);

        RowRedux(M);
    
        BackSub(M, Vex);
        
        // Print Output
        for (auto num: Vex){
            std::cout << num << std::endl;
        }

    } catch(std::runtime_error e){
        std::cout << "Error: Unable to read input matrix." << std::endl;
        return 0;
    } catch(std::domain_error e){
        std::cout << "Error: " << e.what() << std::endl;
        return 0;
    }
    

    return 0;
}