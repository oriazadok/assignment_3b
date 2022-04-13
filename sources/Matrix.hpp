#include <iostream>
#include <vector>

using namespace std;
namespace zich {
    class Matrix {
        
        private:
            vector<double> _mat;
            size_t _row;
            size_t _col;

            //-------------------------------------
            // setters
            //-------------------------------------
            void setRow(size_t new_row) {
                this->_row = new_row;
            }
            void setCol(size_t new_col) {
                this->_col = new_col;
            }
        public:

        // constructors
        Matrix(int row = 0, int col = 0);
        Matrix(const vector<double> &mat, int row, int col);
        ~Matrix();

        //-------------------------------------
        // getters
        //-------------------------------------
        vector<double> mat() const {
            return _mat;
        }
        size_t row() {
            return _row;
        }

        size_t col() {
            return _col;
        }

        


        //----------------------------------
        // unary operator
        //----------------------------------
        Matrix operator+();
        Matrix operator-();


        //----------------------------------------
        // binary operators
        //----------------------------------------
        Matrix operator+(const Matrix &other);
        Matrix operator+=(const Matrix &other);

        Matrix operator-(const Matrix &other);
        Matrix operator-=(const Matrix &other);

        Matrix operator*(const Matrix &other);
        Matrix operator*=(const Matrix &other);

        Matrix operator*(double scalar);
        Matrix operator*=(double scalar);


        //--------------------------------------------
        // prefix and postfix increment and decrement
        //--------------------------------------------
        Matrix& operator++();
        Matrix& operator--();
        Matrix operator++(int);
        Matrix operator--(int);
    

        //----------------------------------------
        // comparison operators
        //----------------------------------------
        bool operator> (Matrix const &other) const;
        bool operator>= (Matrix const &other) const;
        bool operator< (Matrix const &other) const;
        bool operator<= (Matrix const &other) const;
        bool operator== (Matrix const &other) const;
        bool operator!= (Matrix const &other) const;


        //----------------------------------------
        // IO Operators
        //----------------------------------------
        friend istream& operator>> (istream& input, Matrix& mat); 
        friend ostream& operator<< (ostream& output, const Matrix& mat);
    };
    
    Matrix operator*(const double num, Matrix& mat);
}