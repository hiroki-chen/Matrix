#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>
#include <vector>

#include "MyList.hpp"

template<typename T>
class UpperTriangularMatrix {
private:
    T* content;
    int n;

public:
    UpperTriangularMatrix() = delete;
    UpperTriangularMatrix(int size);

    void set(int i, int j, const T& value);

    template<typename Q>
    friend std::ostream& operator << (std::ostream& os, UpperTriangularMatrix<Q>& matrix);
};

template<typename T>
class LowerTriangularMatrix {
private:
    T* content;
    int n;

public:
    LowerTriangularMatrix() = delete;
    LowerTriangularMatrix(int size);

    void set(int i, int j, const T& value);
    UpperTriangularMatrix<T> transpose(void);

    template<typename Q>
    friend std::ostream& operator << (std::ostream& os, LowerTriangularMatrix<Q>& matrix);
};

template<typename T>
class item {
public:
    int row;
    int col;
    T value;

    item() = default;
    item(int r, int c) : row(r), col(c) {}
    item(int r, int c, const T& v) : row(r), col(c), value(v) {}

    template<typename Q>
    friend bool operator == (const item<Q>& lhs, const item<Q>& rhs);
};

template<typename T>
class SparseMatrix {

    int rows;
    int cols;

    //vector terms stores the item of the sparsematrix by list.
    std::vector<item<T> > terms;


public:
    template<typename Q>
    friend std::istream& operator >> (std::istream& is, SparseMatrix<Q>& matrix);

    template<typename Q>
    friend std::ostream& operator << (std::ostream& os, SparseMatrix<Q>& matrix);

    template<typename Q>
    friend SparseMatrix<Q> operator * (const SparseMatrix<Q>& lhs, const SparseMatrix<Q>& rhs);
};


template<typename T>
class LinkedMatrix {
    std::vector<List<item<T> > > terms;
    int rows;
    int cols;

public:
    LinkedMatrix();
    LinkedMatrix(int r, int c) : rows(r), cols(c) {
        this->terms.resize(r + 1);
    }

    void set(int i, int j, const T& value);
    T get(int i, int j);

    LinkedMatrix<T>& operator - (void);

    template<typename Q>
    friend std::ostream& operator << (std::ostream& os, LinkedMatrix<Q>& matrix);

    template<typename Q>
    friend LinkedMatrix<Q> operator + (LinkedMatrix<Q>& lhs, LinkedMatrix<Q>& rhs);

    template<typename Q>
    friend LinkedMatrix<Q> operator - (LinkedMatrix<Q>& lhs, LinkedMatrix<Q>& rhs);

    template<typename Q>
    friend LinkedMatrix<Q> operator * (LinkedMatrix<Q>& lhs, LinkedMatrix<Q>& rhs);
};

template<typename T>
LowerTriangularMatrix<T>::LowerTriangularMatrix(int size) : n(size) {
    int length = size * (size + 1) >> 1;
    content = new T[length];
    for (int i = 0; i < length; i++) { content[i] = 1; }
}

template<typename T>
void LowerTriangularMatrix<T>::set(int i, int j, const T& value) {
    if (i < 0 || j < 0 || i > n || j > n) { std::cout << "Wrong position!" << std::endl; }

    if (i >= j) {
        content[i * (i - 1) / 2 + j - 1] = value;
    } else {
        std::cout << "You cannot modify here." << std::endl;
    }
}

template<typename T>
std::ostream& operator << (std::ostream& os, LowerTriangularMatrix<T>& matrix) {
    for (int i = 1; i <= matrix.n; i++) {
        for (int j = 1; j <= matrix.n; j++) {
            os.width(6);
            os.flags(std::ios::left);
            os << (i >= j ? matrix.content[i * (i - 1) / 2 + j - 1] : 0);
            if (j == matrix.n) { os << std::endl; }
        }
    }
    return os;
}

template<typename T>
UpperTriangularMatrix<T> LowerTriangularMatrix<T>::transpose(void) {
    UpperTriangularMatrix<T> ans(n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            ans.set(j, i, content[i * (i - 1) / 2 + j - 1]);
        }
    }
    return ans;
}

template<typename T>
UpperTriangularMatrix<T>::UpperTriangularMatrix(int size) : n(size) {
    int length = size * (size + 1) / 2;
    content = new T[length];
    for (int i = 0; i < length; i++) { content[i] = 1; }
}

template<typename T>
void UpperTriangularMatrix<T>::set(int i, int j, const T& value) {
    if (i < 0 || j < 0 || i > n || j > n) { std::cout << "Wrong position." << std::endl; }

    if (i <= j) {
        content[j * (j - 1) / 2 + i - 1] = value;
    } else {
        std::cout << "You cannot modify here." << std::endl;
    }
}

template<typename T>
std::ostream& operator << (std::ostream& os, UpperTriangularMatrix<T>& matrix) {
    for (int i = 1; i <= matrix.n; i++) {
        for (int j = 1; j <= matrix.n; j++) {
            os.width(6);
            os.flags(std::ios::left);
            os << (i <= j ? matrix.content[j * (j - 1) / 2 + i - 1] : 0);
            if (j == matrix.n) { os << std::endl; }
        }
    }
    return os;
}

template<typename T>
std::ostream& operator << (std::ostream& os, SparseMatrix<T>& matrix) {
    T** ans = new T*[matrix.rows + 1];
    for (int i = 1; i <= matrix.rows; i++) {
        ans[i] = new T[matrix.cols + 1];
    }

    for (int i = 1; i <= matrix.rows; i++) {
        for (int j = 1; j <= matrix.cols; j++) {
            ans[i][j] = 0;
        }
    }

    for (int i = 0; i < matrix.terms.size(); i++) {
        os << "item(" << matrix.terms[i].row << ", " << matrix.terms[i].col << ") = "
           << matrix.terms[i].value << std::endl;
        ans[matrix.terms[i].row][matrix.terms[i].col] = matrix.terms[i].value;
    }

    for (int i = 1; i <= matrix.rows; i++) {
        for (int j = 1; j <= matrix.cols; j++) {
            os.width(6);
            os.flags(std::ios::left);
            os << ans[i][j];
            if (j == matrix.cols) { os << std::endl; }
        }
    }

    return os;
}

template<typename T>
std::istream& operator >> (std::istream& is, SparseMatrix<T>& matrix) {
    std::cout << "Please input the number of rows, columns, and terms." << std::endl;

    int itemNum = 0;
    is >> matrix.rows >> matrix.cols >> itemNum;
    matrix.terms.resize(itemNum);

    item<T> term;
    for (int i = 0; i < itemNum; i++) {
        std::cout << "Input the row, column and value of term " << (i + 1) << std::endl;
        is >> term.row >> term.col >> term.value;

        if (term.row < 0 || term.col < 0 || term.row > matrix.rows || term.col > matrix.cols) {
            std::cout << "WRONG INPUT!" << std::endl;
            i--;
            continue;
        }
        matrix.terms[i] = term;
    }

    return is;
}

template<typename T>
SparseMatrix<T> operator * (const SparseMatrix<T>& lhs, const SparseMatrix<T>& rhs) {
    if (lhs.cols != rhs.rows) { return lhs; }
    SparseMatrix<T> ans;
    ans.rows = lhs.rows;
    ans.cols = rhs.cols;
    item<T> tmp;

    for (int i = 1; i <= lhs.rows; i++) {
        for (int j = 1; j <= rhs.cols; j++) {
            tmp.row = i; tmp.col = j; tmp.value = 0;
            for (int k = 1; k <= lhs.cols; k++) {
                auto it1 = std::find(lhs.terms.begin(), lhs.terms.end(), item<T>(i, k));
                auto it2 = std::find(rhs.terms.begin(), rhs.terms.end(), item<T>(k, j));
                if (it1 != lhs.terms.end() && it2 != rhs.terms.end() && (*it1).value * (*it2).value) {
                    tmp.value += (*it1).value * (*it2).value;
                }
            }
            if (tmp.value != 0) { ans.terms.push_back(tmp); }
        }
    }

    return ans;
}

template<typename T>
LinkedMatrix<T>::LinkedMatrix() {
    int n;
    std::cout << "Input the number of rows, columns and terms here:" << std::endl;
    std::cin >> this->rows >> this->cols >> n;

    terms.resize(this->rows + 1);

    for (int i = 0; i < n; i++) {
        item<T> tmp;
        std::cout << "Input the row, col, and values of term " << (i + 1) << std::endl;
        std::cin >> tmp.row >> tmp.col >> tmp.value;
        if (tmp.row < 0 || tmp.col < 0 || tmp.row > this->rows || tmp.col > this->cols) {
            std::cout << "OutOfBound!!" << std::endl;
            i--;
        } else if (this->terms[tmp.row].find(terms[tmp.row].begin(), terms[tmp.row].end(), tmp) 
                        != terms[tmp.row].end()) {
                        std::cout << "Repeated." << std::endl;
                        i--;
        } else {
            this->terms[tmp.row].push_back(tmp);
        }
    }
}

template<typename T>
void LinkedMatrix<T>::set(int i, int j, const T& value) {
    if (i < 0 || j < 0 || i > this->rows || j > this->cols) {
        std::cout << "Wrong position." << std::endl;
    } else {
        auto it = this->terms[i].find(this->terms[i].begin(), this->terms[i].end(), item<T>(i, j, value));

        if (it == this->terms[i].end()) { this->terms[i].push_back(item<T>(i, j, value)); }
        else { (*it).value = value; }
    }
}

template<typename T>
LinkedMatrix<T>& LinkedMatrix<T>::operator - (void) {
    for (auto it = this->terms.begin(); it != this->terms.end(); it++) {
        for (auto item = (*it).begin(); item != (*it).end(); item++) {
            (*item).value = -(*item).value;
        }
    }
    return *this;
}

template<typename T>
std::ostream& operator << (std::ostream& os, LinkedMatrix<T>& matrix) {
    std::cout << "------------Result-------------" << std::endl;
    T** ans = new T*[matrix.rows + 1];
    for (int i = 1; i <= matrix.rows; i++) {
        ans[i] = new T[matrix.cols + 1];
    }

    for (int i = 1; i <= matrix.rows; i++) {
        for (int j = 1; j <= matrix.cols; j++) {
            ans[i][j] = 0;
        }
    }
    
    for (int i = 1; i <= matrix.rows; i++) {
        for (auto it = matrix.terms[i].begin(); it != matrix.terms[i].end(); it++) {
            ans[(*it).row][(*it).col] = (*it).value;
        }
    }

    for (int i = 1; i <= matrix.rows; i++) {
        for (int j = 1; j <= matrix.cols; j++) {
            os.width(6);
            os.setf(std::ios::left);
            os << ans[i][j];
            if (j == matrix.cols) { os << std::endl; }
        }
    }
    return os;
}

template<typename T>
LinkedMatrix<T> operator + (LinkedMatrix<T>& lhs, LinkedMatrix<T>& rhs) {
    LinkedMatrix<T> ans(rhs);
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols) {
        std::cout << "Wrong size, these two are not corresponding!" << std::endl;
    } else {
        for (int i = 1; i <= lhs.rows; i++) {
            for (auto it = lhs.terms[i].begin(); it != lhs.terms[i].end(); it++) {
                auto pos = rhs.terms[i].find(rhs.terms[i].begin(), rhs.terms[i].end(), (*it));
                    if (pos == rhs.terms[i].end()) { ans.terms[i].push_back(*it); }
                    else {
                        if ((*pos).value + (*it).value != 0) { ans.set(i, (*it).col, (*pos).value + (*it).value); }
                    }
            }
        }
    }
    return ans;
}

template<typename T>
LinkedMatrix<T> operator - (LinkedMatrix<T>& lhs, LinkedMatrix<T>& rhs) {
    return lhs + (-rhs);
}

template<typename T>
LinkedMatrix<T> operator * (LinkedMatrix<T>& lhs, LinkedMatrix<T>& rhs) {
    if (lhs.cols != rhs.rows) { return lhs; }
    LinkedMatrix<T> ans(lhs.rows, rhs.cols);
    item<T> tmp(0, 0, 0);
    
    for (int i = 1; i <= lhs.rows; i++) {
        for (int j = 1; j <= rhs.cols; j++) {
            //Initialize the temporary item.
            tmp.row = i; tmp.col = j; tmp.value = 0;
            for (int k = 1; k <= lhs.cols; k++) {
                auto it1 = lhs.terms[i].find(lhs.terms[i].begin(), lhs.terms[i].end(), item<T>(i, k));
                auto it2 = rhs.terms[k].find(rhs.terms[k].begin(), rhs.terms[k].end(), item<T>(k, j));
                if (it1 != lhs.terms[i].end() && it2 != rhs.terms[k].end() && (*it1).value * (*it2).value) {
                    //For debug.
                    //std::cout << "added" << (*it1).value * (*it2).value << std::endl;
                    tmp.value += (*it1).value * (*it2).value;
                }
            }
            if (tmp.value != 0) { ans.terms[i].push_back(tmp); }
        }
    }

    return ans;
}

template<typename T>
bool operator == (const item<T>& lhs, const item<T>& rhs) {
    return lhs.col == rhs.col && lhs.row == rhs.row;
}

#endif