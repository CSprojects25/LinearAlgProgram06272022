#pragma once

#include "Matrix.h"
#include "SquareMatrix.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <map>

namespace program {
	const std::map<std::string, uint8_t> main_menu_opts = {
		{"q", 0},
		{"m", 1},
	};

	const std::map<std::string, uint8_t> matrix_menu_opts = {
		{"q", 0},
		{"b", 1},
		{"lu", 2},
		{"add", 3},
		{"sub", 4},
		{"mul", 5},
	};

	struct MatrixData {
		matrices::MatrixVec matrix{ 0 };
		uint32_t rows{ 0 };
		uint32_t cols{ 0 };
	};

	void ClearCinStream() noexcept;

	void ShowMainMenuGreeting() noexcept;
	void ShowMainMenu() noexcept;
	std::string MainMenuSelection();
	std::string RunMainArea();

	void LUDecomp(const program::MatrixData&);

	void ShowMatrixMenu() noexcept;
	std::string MatrixMenuSelection();
	MatrixData GetMatrixData();
	bool QuitFromMatrixArea();

	void Run();
}
