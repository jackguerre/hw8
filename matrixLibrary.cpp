#include <iostream>
#include <vector>
using namespace std;

class Matrix{

public:
    Matrix(int r, int c){
        rows = r;
        cols = c;
        data = vector<vector<int>>(r, vector<int>(c));
    }

    Matrix(const vector<vector<int>>& d){
        data = d;
        rows = d.size();
        cols = d[0].size();
    }

    int getRows() const{
        return rows; 
    }
    int getCols() const{ 
        return cols; 
    }

    int& at(int r, int c){ 
        return data[r][c]; 
    }
    int at(int r, int c) const{
        return data[r][c]; 
    }

    Matrix operator+(const Matrix& myMatrix) const{
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                result.at(i, j) = data[i][j] + myMatrix.at(i, j);
            }
        }
        return result;
    }

    Matrix operator*(int scalar) const{
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                result.at(i, j) = data[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix transpose() const{
        Matrix result(cols, rows);
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                result.at(j, i) = data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& myMatrix) const{
        Matrix result(rows, myMatrix.cols);
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < myMatrix.cols; j++){
                for (int k = 0; k < cols; k++){
                    result.at(i, j) += data[i][k] * myMatrix.at(k, j);
                }
            }
        }
        return result;
    }

    void print() const{
        for (const auto& row : data){
            for (int val : row){
                cout << val << " ";
            }
            cout << "\n";
        }
    }
private:
    vector<vector<int>> data;
    int rows, cols;
};

int main() {
    Matrix A({{6, 4}, {8, 3}});
    Matrix B({{1, 2, 3}, {4, 5, 6}});
    Matrix C({{2, 4, 6}, {1, 3, 5}});

    Matrix D = A + (B * 3) * C.transpose();
    std::cout << "Matrix D:\n";
    D.print();

    return 0;
}
