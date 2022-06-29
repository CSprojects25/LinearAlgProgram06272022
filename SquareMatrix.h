#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <memory>

#include "Matrix.h"

namespace matrices {
	class SquareMatrix : public Matrix {
	private:
		uint dim_;
		mutable float det_;
		mutable bool decomposable_;
		mutable MatrixVec l_matrix_;

		float FindDet() const;
		void SetLMatrixSize(const uint);

	public:
		SquareMatrix() = default;
		SquareMatrix(const uint dim, const MatrixVec& mv) : dim_(dim),
			det_(1), decomposable_(false),
			Matrix(dim, dim, mv) {
			SetLMatrixSize(dim_ * dim_);
		};
		SquareMatrix(const SquareMatrix& m) : dim_(m.dim_),
			det_(1), decomposable_(false),
			Matrix(dim_, dim_, m.matrix_) {
			SetLMatrixSize(dim_ * dim_);
		};
		~SquareMatrix() = default;

		//std::unique_ptr<Matrix> Clone() const override;

		SquareMatrix& operator=(SquareMatrix);

		SquareMatrix& operator+=(const SquareMatrix&);
		SquareMatrix& operator-=(const SquareMatrix&);
		SquareMatrix& operator*=(const SquareMatrix&);

		void Eliminate(MatrixVec&);
		void GenerateLowerMatrix(const MatrixVec&);
		void LUDecomposition(); // LU Decomposition without row swaps
		// void FindTranspose() const override; // impl optimized version

		void PrintLMatrix() const;
		void PrintLUDecomposedSystem() const;

		inline int GetDim() const { return dim_; }
		inline float GetDet() const { return det_; }
		inline bool IsDecomposable() const { return decomposable_; }
		inline const MatrixVec& GetLMatrix() const { return l_matrix_; }

		friend SquareMatrix operator+(const SquareMatrix&,
			const SquareMatrix&);
		friend SquareMatrix operator-(const SquareMatrix&,
			const SquareMatrix&);
		friend SquareMatrix operator*(const SquareMatrix&,
			const SquareMatrix&);

		friend bool operator==(const Matrix&, const Matrix&);
		friend bool operator!=(const Matrix&, const Matrix&);

		friend std::ostream& operator<<(std::ostream&,
			const MatrixVec&); // impl

		friend bool IsSameDim(const SquareMatrix&, const SquareMatrix&);
	};

	inline bool IsSameDim(const SquareMatrix& lhs,
		const SquareMatrix& rhs) {
		return lhs.GetDim() == rhs.GetDim();
	}

	SquareMatrix operator+(const SquareMatrix&, const SquareMatrix&);
	SquareMatrix operator-(const SquareMatrix&, const SquareMatrix&);
	SquareMatrix operator*(const SquareMatrix&, const SquareMatrix&);

	bool operator==(const Matrix&, const Matrix&);
	bool operator!=(const Matrix&, const Matrix&);

	std::ostream& operator<<(std::ostream&, const MatrixVec&); // impl

	uint NumberOfPivots(uint cols);
}

#endif

