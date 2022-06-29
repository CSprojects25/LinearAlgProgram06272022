#include "SquareMatrix.h"

float matrices::SquareMatrix::FindDet() const {
    det_ = 1; // det_ is a product so it's ok
    for (int i = 0; i < dim_ * dim_; i += dim_ + 1) {
        det_ *= ref_matrix_[i];
    }

    if (det_ == 0) { decomposable_ = false; }
    else { decomposable_ = true; }

    return det_;
}

void matrices::SquareMatrix::SetLMatrixSize(const uint size) {
    l_matrix_.resize(size);
}
/*
std::unique_ptr<matrices::Matrix>
matrices::SquareMatrix::Clone() const {
    return std::make_unique<Matrix>(*this);
}
*/
matrices::SquareMatrix&
matrices::SquareMatrix::operator=(SquareMatrix rhs) {
    std::swap(*this, rhs);
    return *this;
}

matrices::SquareMatrix&
matrices::SquareMatrix::operator+=(const SquareMatrix& rhs) {
    if (!IsSameDim(*this, rhs)) {
        throw std::runtime_error("Cannot add"
            " Matrices of different dimensions");
    }

    for (int i = 0; i < rows_ * cols_; i++) {
        matrix_[i] += rhs.matrix_[i];
    }
    return *this;
}

matrices::SquareMatrix&
matrices::SquareMatrix::operator-=(const SquareMatrix& rhs) {
    if (!IsSameDim(*this, rhs)) {
        throw std::runtime_error("Cannot subtract"
            " Matrices of different dimensions");
    }

    for (int i = 0; i < rows_ * cols_; i++) {
        matrix_[i] -= rhs.matrix_[i];
    }
    return *this;
}

matrices::SquareMatrix&
matrices::SquareMatrix::operator*=(const SquareMatrix& rhs) {
    if (!CanBeMultiplied(*this, rhs)) {
        throw std::runtime_error("Cannot multiply"
            " Matrices of different dimensions");
    }

    SquareMatrix m(*this);
    std::fill(this->matrix_.begin(), this->matrix_.end(), (float)0);
    for (int i = 0; i < dim_; i++) {
        for (int j = 0; j < dim_; j++) {
            for (int k = 0; k < dim_; k++) {
                matrix_[i * dim_ + j] += m.matrix_[i * dim_ + k]
                    * rhs.matrix_[k * dim_ + j];
            }
        }
    }
    return *this;
}

void matrices::SquareMatrix::Eliminate(MatrixVec& pivots) {
    ref_matrix_ = matrix_;
    float temp = 0;
    int count = 0;
    for (int i = 0; i < rows_; i++) {
        for (int j = i + 1; j < rows_; j++) {
            if (ref_matrix_[i * cols_ + i] == 0) { return; }
            temp = ref_matrix_[j * cols_ + i] / ref_matrix_[i * cols_ + i];
            pivots.push_back(temp);
            RoundToZeroCheck(pivots.back());

            for (int k = i; k < cols_; k++) {
                ref_matrix_[j * cols_ + k] -= ref_matrix_[i * cols_ + k]
                    * temp;
                RoundToZeroCheck(ref_matrix_[j * cols_ + k]);
            }
        }
    }
}

void matrices::SquareMatrix::GenerateLowerMatrix(const MatrixVec& pivots) {
    int num = 0;
    for (int i = 0; i < dim_; i++) {
        for (int j = 0; j < dim_; j++) {
            l_matrix_[i * dim_ + j] = (i == j) ? 1 :
                (j > i) ? 0 : (pivots[num], num++);
        }
    }
}

void matrices::SquareMatrix::LUDecomposition() {
    const uint size = NumberOfPivots(dim_);
    MatrixVec pivots; // used to create the lower triangular matrix
    pivots.reserve(size);

    Eliminate(pivots);
    GenerateLowerMatrix(pivots);

    FindDet();
    return;
}

// implement an optimized version later
/*
void matrices::SquareMatrix::FindTranspose() {
    int size = 0;
    for (int i = 0; i < cols_; i++) {
        size += cols_ - i;
    }
}
*/

void matrices::SquareMatrix::PrintLMatrix() const {
    for (int i = 0; i < dim_; i++) {
        for (int j = 0; j < dim_; j++) {
            std::cout << std::setw(7) << std::setprecision(6)
                << l_matrix_.at(i * dim_ + j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void matrices::SquareMatrix::PrintLUDecomposedSystem() const {
    std::cout << "\nThe matrix is\n";
    std::cout << *this;
    std::cout << "The Upper matrix is\n";
    PrintRefMatrix();
    std::cout << "The Lower matrix is\n";
    PrintLMatrix();
    std::cout << "Determinant: " << GetDet() << "\n\n";
}

matrices::uint matrices::NumberOfPivots(uint dim) {
    matrices::uint size = 0; // find the needed number of pivot points
    for (int i = 1; i < dim; i++) {
        size += (dim - i);
    }
    return size;
}

matrices::SquareMatrix
matrices::operator+(const SquareMatrix& lhs, const SquareMatrix& rhs) {
    if (!IsSameDimensions(lhs, rhs)) {
        throw std::runtime_error(
            "Cannot subtract Matrices of different dimensions");
    }

    SquareMatrix m(lhs);
    for (int i = 0; i < m.dim_ * m.dim_; i++) {
        m.matrix_[i] += rhs.matrix_[i];
    }
    return m;
}

matrices::SquareMatrix
matrices::operator-(const SquareMatrix& lhs, const SquareMatrix& rhs) {
    matrices::Matrix m = static_cast<matrices::Matrix>(lhs) -
        static_cast<matrices::Matrix>(rhs);
    return dynamic_cast<matrices::SquareMatrix&>(m);
}

matrices::SquareMatrix
matrices::operator*(const SquareMatrix& lhs, const SquareMatrix& rhs) {
    if (!CanBeMultiplied(lhs, rhs)) {
        throw std::runtime_error("Cannot multiply"
            " Matrices of different dimensions");
    }

    SquareMatrix m(lhs);
    std::fill(m.matrix_.begin(), m.matrix_.end(), (float)0);
    for (int i = 0; i < m.GetDim(); i++) {
        for (int j = 0; j < m.GetDim(); j++) {
            for (int k = 0; k < m.GetDim(); k++) {
                m.matrix_[i * m.GetDim() + j] += m.matrix_[i * m.GetDim() + k]
                    * rhs.matrix_[k * m.GetDim() + j];
            }
        }
    }
    return m;
}
