#pragma once
#include <utility>
using namespace std;

typedef int TElem;
#define NULL_TELEM 0

class Matrix {
private:
    int nrLines_;
    int nrColumns_;
    int capacity_;
    int count_;
    tuple<int, int, TElem>* keys_;

    int h1(int r, int c) const;
    int h2(int r, int c) const;
    int find(int r, int c) const;
    void resize_up(int capacity);
    void resize_down(int capacity);

public:
    // constructor
    Matrix(int nrLines, int nrCols);

    // returns the number of lines
    int nrLines() const;

    // returns the number of columns
    int nrColumns() const;

    // returns the element from line i and column j (indexing starts from 0)
    // throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    // modifies the value from line i and column j
    // returns the previous value from the position
    // throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    // destructor
    ~Matrix();
};
