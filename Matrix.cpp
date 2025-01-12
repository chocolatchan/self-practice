#include <iostream>
#include <stdlib.h>
using namespace std;

class Matrix {
private:
    int _rows;
    int _cols;
    int** _data;
public:
    Matrix(int rows, int cols, int def) {
        _rows = rows;
        _cols = cols;
        _data = (int**) malloc(rows * sizeof(int*));
        if (_data == nullptr) {
            perror("Failed to allocate memory for rows");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < rows; ++i) {
            _data[i] = (int*) malloc(cols * sizeof(int));
            if (_data[i] == nullptr) {
                perror("Failed to allocate memory for columns");
                exit(EXIT_FAILURE);
            }
            for (int j = 0; j < cols; ++j) {
                _data[i][j] = def;
            }
        }
    }
    static void print(Matrix A) {
        for (int i = 0; i < A._rows; ++i) {
            for (int j = 0; j < A._cols; ++j) {
                cout << A._data[i][j] << " ";
            }
            cout << "\n";
        }
    }
    void set(int row, int col, int value) {
        if (_data == nullptr) {
            perror("Matrix is not allocated");
            exit(EXIT_FAILURE);    
        }
        _data[row][col] = value;
    }
    int get(int row, int col) {
        if (_data == nullptr) {
            perror("Matrix is not allocated");
            exit(EXIT_FAILURE);    
        }
        return _data[row][col];
    }
    Matrix operator+(const Matrix other) {
        if (_rows != other._rows || _cols != other._rows) {
            perror("Dimension not match");
            exit(EXIT_FAILURE);
        }
        Matrix res = Matrix(_rows, _cols, 0);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                res._data[i][j] = _data[i][j] + other._data[i][j];
            }
        }
        return res;
    }
    Matrix operator&(int meow) const {
        Matrix res = Matrix(_rows, _cols, 0);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                res._data[i][j] = meow * _data[i][j];
            }
        }
        return res;
    }
    Matrix operator-(const Matrix other) {
        return *this + (other & -1);
    }
    Matrix operator*(const Matrix other) {
        if (_cols != other._rows) {
            perror("Matrix dimensions are incompatible for multiplication.");
            exit(EXIT_FAILURE);
        }

        Matrix result = Matrix(_rows, other._cols, 0);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < other._cols; ++j) {
                result._data[i][j] = 0;
                for (int k = 0; k < _cols; ++k) {
                    result._data[i][j] += _data[i][k] * other._data[k][j];
                }
            }
        }
        return result;
    }
};

int main() {
    Matrix A = Matrix(2, 2, 0);
    cout << "Enter A's member:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int n;
            cin >> n;
            A.set(i, j, n);
        }
    }
    Matrix B = Matrix(2, 2, 0);
    cout << "Enter B's member:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int n;
            cin >> n;
            B.set(i, j, n);
        }
    }
    cout << "A:\n";
    Matrix::print(A);
    cout << "B:\n";
    Matrix::print(B);
    cout << "After subtraction:\n";
    Matrix::print(A - B);
    
}
