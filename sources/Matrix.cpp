#include <sstream>
#include "Matrix.hpp"

using namespace std;
namespace zich {

    // constructors
    Matrix::Matrix(int row, int col) {
            this->_row= (size_t)row;
            this->_col = (size_t)col;
    }
    Matrix::Matrix(const vector<double> &mat, int row, int col) {
            if(mat.size() != row * col || row<= 0 || col<=0) {
                throw invalid_argument("Wrong input");
            }
            this->_mat = mat;
            this->_row= (size_t)row;
            this->_col = (size_t)col;
    }

    // distructor
    Matrix::~Matrix() {
        this->_mat.clear();
    }

    //----------------------------------
    // unary operator
    //----------------------------------

    Matrix Matrix::operator+() {
        vector<double> m;
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            m.push_back(this->_mat[i]);
        }
        
        return Matrix(m, this->_row, this->_col);
    }
    Matrix Matrix::operator-() {
        vector<double> m;
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            m.push_back(-1 * this->_mat[i]);
        }
        
        return Matrix(m, this->_row, this->_col);
    }

    
    //----------------------------------------
    // binary operators
    //----------------------------------------
   
    Matrix Matrix::operator+(const Matrix &other) {
        if((this->_row != other._row) || (this->_col != other._col)) {
            throw invalid_argument("Wrong Input");
        }
        vector<double> m;
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            m.push_back(this->_mat[i] + other._mat[i]);
        }
        
        return Matrix(m, this->_row, this->_col);
    }
    Matrix Matrix::operator+=(const Matrix &other) {
        if((this->_row != other._row) || (this->_col != other._col)) {
            throw invalid_argument("Wrong Input");
        }
        vector<double> m;
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            this->_mat[i] += other._mat[i];
        }
        
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &other) {
        if((this->_row != other._row) || (this->_col != other._col)) {
            throw invalid_argument("Wrong Input");
        }
        vector<double> m;
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            m.push_back(this->_mat[i] - other._mat[i]);
        }
        
        return Matrix(m, this->_row, this->_col);
    }
    Matrix Matrix::operator-=(const Matrix &other) {
        if((this->_row != other._row) || (this->_col != other._col)) {
            throw invalid_argument("Wrong Input");
        }
        vector<double> m;
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            this->_mat[i] -= other._mat[i];
        }
        
        return *this;
    }

    Matrix Matrix::operator*(const Matrix &other) {
        if(this->_col != other._row) {
            throw invalid_argument("Wrong Input");
        }
        vector<double> m;
        for (size_t i=0; i<this->_row; i++) {
            for(size_t j=0; j<other._col; j++) {
                double a = 0;
                for(size_t k=0; k<this->_col; k++) {
                    a += this->_mat[i*this->_col + k] * other._mat[k*other._col+j];
                }
                m.push_back(a);
            }
        }
        
        return Matrix(m, this->_row, other._col);
    }
    Matrix Matrix::operator*=(const Matrix &other) {
        if(this->_col != other._row) {
            throw invalid_argument("Wrong Input");
        }
        vector<double> m;
        for (size_t i=0; i<this->_row; i++) {
            for(size_t j=0; j<other._col; j++) {
                double a = 0;
                for(size_t k=0; k<this->_col; k++) {
                    a += this->_mat[i*this->_col + k] * other._mat[k*other._col+j];
                }
                m.push_back(a);
            }
        }
        this->_mat = m;

        return *this;
    }

    Matrix Matrix::operator*(double scalar) {
        vector<double> m;
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            m.push_back(this->_mat[i] * scalar);
        }
        
        return Matrix(m, this->_row, this->_col);
    }
    Matrix Matrix::operator*=(double scalar) {
        vector<double> m;
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            this->_mat[i] *= scalar;
        }
        
        return *this;
    }
    
    //--------------------------------------------
    // prefix and postfix increment and decrement
    //--------------------------------------------
    Matrix& Matrix::operator++() {
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            this->_mat[i] += 1;
        }
        
        return *this;
    }
    Matrix& Matrix::operator--() {
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            this->_mat[i] -= 1;
        }
        
        return *this;
    }
    
    Matrix Matrix::operator++(int) {
        vector<double> new_mat;
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            new_mat.push_back(this->_mat[i]++);
        }
        return Matrix(new_mat, this->_row, this->_col);
    }      
    Matrix Matrix::operator--(int) {
        Matrix copy = *this;
        vector<double> new_mat;
        size_t size = this->_row * this->_col;
        for (size_t i=0; i<size; i++) {
            new_mat.push_back(this->_mat[i]--);
        }
        return Matrix(new_mat, this->_row, this->_col);
    }
    

    //----------------------------------------
    // comparison operators
    //----------------------------------------
    bool Matrix::operator> (Matrix const &other) const {
        if((this->_row != other._row) || (this->_col != other._col)) {
            throw invalid_argument("Wrong Input");
        }
        vector<double> m;
        size_t size = this->_row * this->_col;
        int sumofMat = 0;
        int sumOfOther = 0;
        for (size_t i=0; i<size; i++) {
            sumofMat += this->_mat[i];
            sumOfOther += other._mat[i];
        }
        
        return sumofMat > sumOfOther;
    }
    bool Matrix::operator>= (Matrix const &other) const {
        if((this->_row != other._row) || (this->_col != other._col)) {
            throw invalid_argument("Wrong Input");
        }
        vector<double> m;
        size_t size = this->_row * this->_col;
        int sumofMat = 0;
        int sumOfOther = 0;
        bool equal = true;
        for (size_t i=0; i<size; i++) {
            if(this->_mat[i] != other._mat[i]) {
                equal = false;
            }
            sumofMat += this->_mat[i];
            sumOfOther += other._mat[i];
        }
        
        return equal || (sumofMat > sumOfOther);
    }
    bool Matrix::operator< (Matrix const &other) const {
        if((this->_row != other._row) || (this->_col != other._col)) {
            throw invalid_argument("Wrong Input");
        }
        vector<double> m;
        size_t size = this->_row * this->_col;
        int sumofMat = 0;
        int sumOfOther = 0;
        for (size_t i=0; i<size; i++) {
            sumofMat += this->_mat[i];
            sumOfOther += other._mat[i];
        }
        
        return sumofMat < sumOfOther;
    }
    bool Matrix::operator<= (Matrix const &other) const {
        if((this->_row != other._row) || (this->_col != other._col)) {
            throw invalid_argument("Wrong Input");
        }
       vector<double> m;
        size_t size = this->_row * this->_col;
        int sumofMat = 0;
        int sumOfOther = 0;
        bool equal = true;
        for (size_t i=0; i<size; i++) {
            if(this->_mat[i] != other._mat[i]) {
                equal = false;
            }
            sumofMat += this->_mat[i];
            sumOfOther += other._mat[i];
        }
        
        return equal || (sumofMat < sumOfOther);
    }
    bool Matrix::operator== (Matrix const &other) const {
        if((this->_row != other._row) || (this->_col != other._col)) {
            throw invalid_argument("Wrong Input");
        }
        const double eps = 0.001;
        vector<double> m;
        size_t size = this->_row * this->_col;
        bool equal = true;
        for (size_t i=0; i<size; i++) {
            if(!((other._mat[i] - eps <= this->_mat[i]) && (this->_mat[i] <= other._mat[i] + eps))) {
                equal = false;
            }
        }
        
        return equal;
    }
    bool Matrix::operator!= (Matrix const &other) const {
        if((this->_row != other._row) || (this->_col != other._col)) {
            throw invalid_argument("Wrong Input");
        }
        vector<double> m;
        size_t size = this->_row * this->_col;
        bool equal = true;
        for (size_t i=0; i<size; i++) {
            if(this->_mat[i] != other._mat[i]) {
                equal = false;
            }
        }
        
        return !equal;
    }


    //----------------------------------------
    // IO Operators
    //----------------------------------------
    istream& operator>> (istream& input, Matrix& mat) {
        string in;
        getline(input, in);

        size_t rows = 0;
        size_t cols = 0;
        bool firstTime = true;

        size_t i=0;
        while(i<in.length()) {

            // rows counter
            rows++;
            // this if block check the first char in each row
            if(in[i] != '[') {
                throw invalid_argument("Wrong Input");
            }
            i++;

            size_t t_cols = 0; //count the amount of numbers in each row

            // This while loop is looping the current row
            while(in[i] != ']') {
                string str_num;

                // This while achive the a number in the column
                while(in[i] != ' ' && in[i] != ']' )  {
                    str_num += in[i];
                    i++;
                }
                try {
                    mat._mat.push_back(stod(str_num));
                } catch (...) {
                    throw invalid_argument("Wrong Input");
                }

                t_cols++;
                if(in[i] == ']') {
                    break;
                }
                if(in[i] != ' ') { 
                    throw invalid_argument("Wrong Input");
                }
                i++;
            }
            i++;

            // the block below verify that all the rows have equal col
            if(firstTime) {
                cols = t_cols;        
            } else if(t_cols != cols) {
                throw invalid_argument("Wrong Input");
            }
            

            // these two blocks check if between two rows there is only ", "
            if((in[i] != ',') && (i<in.length())) {
                throw invalid_argument("Wrong Input");
            }
            i++;
            if((in[i] != ' ') && (i<in.length())) { 
                throw invalid_argument("Wrong Input"); }
            i++;
            
            
        }
        mat.setRow(rows);
        mat.setCol(cols);
        
        return input;
    }
    ostream& operator<< (ostream& output, const Matrix& mat) {
        for(size_t i=0; i<mat._row; i++) {
            output << "[";
            for (size_t j = 0; j < mat._col; j++) {
                output << mat._mat[i * mat._col + j];
                if(j < mat._col - 1) {
                    output << " ";
                }
            }
            output << "]";
            if(i < mat._row - 1) {
                output << "\n";
            }
        }
        return output;
    }


    Matrix operator*(double num, Matrix &mat) {
        vector<double> new_mat;
        size_t size = mat.row() * mat.col();
        for (size_t i=0; i<size; i++) {
            new_mat.push_back(mat.mat()[i] * num);
        }
        return Matrix(new_mat, mat.row(), mat.col());
    }
}