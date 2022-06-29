#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <memory>

namespace matrices {
	using MatrixVec = std::vector<float>;
	using uint = uint32_t;

	class Matrix {
	protected:
		uint rows_;
		uint cols_;
		MatrixVec matrix_;
		mutable MatrixVec ref_matrix_; // row echelon form
		mutable MatrixVec t_matrix_; // transpose

	public:
		Matrix() = default;
		Matrix(const uint rows, const uint cols)
			: rows_(rows), cols_(cols) {
			SetAllMatricesSizes(rows_ * cols_);
		};
		Matrix(const unsigned int rows, const unsigned int cols,
			const MatrixVec& mv) : rows_(rows), cols_(cols),
			matrix_(mv) {
			SetCalculatedMatricesSizes(rows_ * cols_);
		};
		Matrix(const Matrix& m) : rows_(m.rows_), cols_(m.cols_),
			matrix_(m.matrix_), ref_matrix_(m.ref_matrix_),
			t_matrix_(m.t_matrix_) {};
		virtual ~Matrix() = default;

		//virtual std::unique_ptr<Matrix> Clone() const;

		// FIX: implement using the move semantics
		Matrix& operator=(Matrix);

		Matrix& operator+=(const Matrix&);
		Matrix& operator-=(const Matrix&);
		Matrix& operator*=(const Matrix&);

		void Eliminate();
		void SetAllMatricesSizes(const uint);
		virtual void SetCalculatedMatricesSizes(const uint);
		virtual void FindTranspose() const; // implement virtual in derived class

		void PrintRefMatrix() const;
		void PrintTMatrix() const;

		inline const uint GetRows() const { return rows_; }
		inline const uint GetCols() const { return cols_; }
		inline const MatrixVec& GetMatrix() const { return matrix_; }
		inline const MatrixVec& GetREFMatrix() const { return ref_matrix_; }
		inline const MatrixVec& GetTMatrix() const { return t_matrix_; }

		friend Matrix operator+(const Matrix&, const Matrix&);
		friend Matrix operator-(const Matrix&, const Matrix&);
		friend Matrix operator*(const Matrix&, const Matrix&);
	};

	Matrix operator+(const Matrix&, const Matrix&);
	Matrix operator-(const Matrix&, const Matrix&);
	Matrix operator*(const Matrix&, const Matrix&);

	bool operator==(const Matrix&, const Matrix&);
	bool operator!=(const Matrix&, const Matrix&);

	std::ostream& operator<<(std::ostream&, const Matrix&);

	bool IsSameMatrixVec(const MatrixVec&, const MatrixVec&);

	inline bool CanBeMultiplied(const Matrix& lhs, const Matrix& rhs) {
		return (lhs.GetCols() == rhs.GetRows());
	}

	inline bool IsSameDimensions(const Matrix& lhs, const Matrix& rhs) {
		return ((lhs.GetRows() == rhs.GetRows())
			&& (lhs.GetCols() == rhs.GetCols()));
	}

	inline void RoundToZeroCheck(float& num) {
		num = abs(num) < 10E-6 ? 0 : num;
	}
}

#endif

