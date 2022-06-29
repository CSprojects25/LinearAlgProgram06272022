#include "Matrix.h"

matrices::Matrix& matrices::Matrix::operator=(Matrix rhs) {
	std::swap(*this, rhs);
	return *this;
}

void matrices::Matrix::SetAllMatricesSizes(const uint size) {
	matrix_.resize(size);
	ref_matrix_.resize(size);
	t_matrix_.resize(size);
}

void matrices::Matrix::SetCalculatedMatricesSizes(const uint size) {
	ref_matrix_.resize(size);
	t_matrix_.resize(size);
}

void matrices::Matrix::Eliminate() {
	ref_matrix_ = matrix_;
	float temp = 0;
	int count = 0;
	for (int i = 0; i < rows_; i++) {
		for (int j = i + 1; j < rows_; j++) {
			if (ref_matrix_[i * cols_ + i] == 0) { return; }
			temp = ref_matrix_[j * cols_ + i] / ref_matrix_[i * cols_ + i];

			for (int k = i; k < cols_; k++) {
				ref_matrix_[j * cols_ + k] -= ref_matrix_[i * cols_ + k]
					* temp;
				RoundToZeroCheck(ref_matrix_[j * cols_ + k]);
			}
		}
	}
}

void matrices::Matrix::FindTranspose() const {
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			t_matrix_.at(i * cols_ + j) = matrix_.at(j * rows_ + i);
		}
	}
}

void matrices::Matrix::PrintRefMatrix() const {
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			std::cout << std::setw(7) << std::setprecision(6)
				<< ref_matrix_.at(i * cols_ + j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void matrices::Matrix::PrintTMatrix() const {
	for (int i = 0; i < cols_; i++) {
		for (int j = 0; j < rows_; j++) {
			std::cout << std::setw(7) << std::setprecision(6)
				<< t_matrix_.at(i * cols_ + j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

matrices::Matrix matrices::operator+(const Matrix& lhs, const Matrix& rhs) {
	if (!IsSameDimensions(lhs, rhs)) {
		throw std::runtime_error(
			"Cannot add Matrices of different dimensions");
	}

	Matrix m(lhs);
	for (int i = 0; i < m.GetRows() * m.GetCols(); i++) {
		m.matrix_[i] += rhs.matrix_[i];
	}
	return m;
}

matrices::Matrix matrices::operator-(const Matrix& lhs, const Matrix& rhs) {
	if (!IsSameDimensions(lhs, rhs)) {
		throw std::runtime_error(
			"Cannot subtract Matrices of different dimensions");
	}

	Matrix m(lhs);
	for (int i = 0; i < m.GetRows() * m.GetCols(); i++) {
		m.matrix_[i] -= rhs.matrix_[i];
	}
	return m;
}

matrices::Matrix matrices::operator*(const Matrix& lhs, const Matrix& rhs) {
	if (!CanBeMultiplied(lhs, rhs)) {
		throw std::runtime_error(
			"Cannot multiply Matrices where the columns ofA != the rows of B");
	}

	Matrix m(lhs.GetRows(), rhs.GetCols());
	for (int i = 0; i < lhs.GetRows(); i++) {
		for (int j = 0; j < rhs.GetCols(); j++) {
			for (int k = 0; k < lhs.GetCols(); k++) {
				m.matrix_[i * rhs.GetCols() + j]
					+= lhs.matrix_[i * lhs.GetCols() + k]
					* rhs.matrix_[k * rhs.GetCols() + j];
			}
		}
	}
	return m;
}

matrices::Matrix& matrices::Matrix::operator+=(const Matrix& rhs) {
	if (!IsSameDimensions(*this, rhs)) {
		throw std::runtime_error(
			"Cannot add Matrices of different dimensions");
	}

	for (int i = 0; i < GetRows() * GetCols(); i++) {
		matrix_[i] += rhs.matrix_[i];
	}
	return *this;
}

matrices::Matrix& matrices::Matrix::operator-=(const Matrix& rhs) {
	if (!IsSameDimensions(*this, rhs)) {
		throw std::runtime_error(
			"Cannot subtract Matrices of different dimensions");
	}

	for (int i = 0; i < GetRows() * GetCols(); i++) {
		matrix_[i] -= rhs.matrix_[i];
	}
	return *this;
}

matrices::Matrix& matrices::Matrix::operator*=(const Matrix& rhs) {
	if (!CanBeMultiplied(*this, rhs)) {
		throw std::runtime_error(
			"Cannot multiply Matrices where the columns of "
			"A != the rows of B");
	}

	Matrix m(*this);
	for (int i = 0; i < GetRows(); i++) {
		for (int j = 0; j < rhs.GetCols(); j++) {
			for (int k = 0; k < GetCols(); k++) {
				matrix_[i * cols_ + j] += m.matrix_[i * cols_ + k]
					* rhs.matrix_[k * rhs.cols_ + j];
			}
		}
	}
	return *this;
}

bool matrices::operator==(const Matrix& lhs, const Matrix& rhs) {
	if (!IsSameDimensions(lhs, rhs)) { return false; }
	return IsSameMatrixVec(lhs.GetMatrix(), rhs.GetMatrix());
}

bool matrices::operator!=(const Matrix& lhs, const Matrix& rhs) {
	if (!IsSameDimensions(lhs, rhs)) { return true; }
	return !IsSameMatrixVec(lhs.GetMatrix(), rhs.GetMatrix());
}

std::ostream& matrices::operator<<(std::ostream& os, const Matrix& m) {
	for (int i = 0; i < m.GetRows(); i++) {
		for (int j = 0; j < m.GetCols(); j++) {
			os << std::setw(7) << std::setprecision(6)
				<< m.GetMatrix()[i * m.GetCols() + j] << " ";
		}
		os << "\n";
	}
	os << "\n";
	return os;
}

bool matrices::IsSameMatrixVec(const MatrixVec& lhs, const MatrixVec& rhs) {
	if (lhs == rhs) { return true; }
	return false;
}
