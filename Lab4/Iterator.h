#pragma once

template<typename T>
class Iterator {
private:
    const T* matrix_;
    int numRows_;
    int numCols_;
    int currentRow_;
    int currentCol_;

public:
    Iterator(const T* matrix, int numRows, int numCols);
    bool valid() const;
    void nextRow();
    void nextColumn();
    const T& getCurrent() const;
};
