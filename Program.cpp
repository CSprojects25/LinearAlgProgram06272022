#include "Program.h"

void program::ClearCinStream() noexcept {
	std::cin.clear();
	fflush(stdin);
}

void program::ShowMainMenu() noexcept {
	std::cout << "\nMain Menu\n";
	std::cout << "(m) Go to Matrix Menu\n";
	std::cout << "(q) Exit Program\n";
}

std::string program::MainMenuSelection() {
	std::string choice = "";
	while (true) {
		std::getline(std::cin, choice);

		if (std::cin.fail()) {
			std::cerr << "Sorry, I cannot read that. Please try again.\n";
			program::ClearCinStream();
			continue;
		}

		if (!program::main_menu_opts.contains(choice)) {
			std::cout << "Choose from the list." << std::endl;
			program::ClearCinStream();
			continue;
		}
		break;
	}
	return choice;
}

void program::ShowMatrixMenu() noexcept {
	std::cout << "\nSelect a Matrix operation to perform\n";
	std::cout << "(q) Quit\n";
	std::cout << "(b) Back to main menu\n";
	std::cout << "(lu) Lu Decomposition With Determinant\n";

	std::cout << "The below are coming soon\n";

	std::cout << "(add) Addition\n";
	std::cout << "(sub) Subtraction\n";
	std::cout << "(mul) Multiplication\n";
	std::cout << "...And more to come!\n";
}

std::string program::MatrixMenuSelection() {
	std::string choice;
	while (true) {
		std::getline(std::cin, choice);

		if (std::cin.fail()) {
			std::cerr << "Sorry, I cannot read that. Please try again.\n";
			program::ClearCinStream();
			continue;
		}

		if (!program::matrix_menu_opts.contains(choice)) {
			std::cout << "Choose from the list." << std::endl;
			program::ClearCinStream();
			continue;
		}

		program::ClearCinStream();
		break;
	}
	return choice;
}

program::MatrixData program::GetMatrixData() {
	program::MatrixData data;
	while (true) {
		std::cout << "Enter the number of rows as an integer (<1000)\n";
		std::cin >> data.rows;

		std::cout << "Enter the number of cols as an integer (<1000)\n";
		std::cin >> data.cols;

		if (std::cin.fail()) {
			std::cerr << "Sorry, I cannot read that. Please try again.\n";
			program::ClearCinStream();
			continue;
		}

		// FIX: change this to a function
		if ((data.cols < 1) || (data.rows < 1) || (data.cols > 999)
			|| (data.rows > 999)) {
			std::cerr << "Sorry, the number is out of range." << std::endl;
			continue;
		}

		std::cout << "You have entered\n";
		std::cout << "Rows: " << data.rows << std::endl;
		std::cout << "Cols: " << data.cols << std::endl;
		break;
	}

	program::ClearCinStream();

	uint32_t size = data.rows * data.cols;
	data.matrix.resize(size);

	while (true) {
		std::cout << "Enter the " << size << " Matrix coefficients by row.\n";
		for (auto& num : data.matrix) {
			std::cin >> num;
		}

		if (std::cin.fail()) {
			std::cerr << "Sorry, I cannot read that. Please try again.\n";
			program::ClearCinStream();
			continue;
		}

		program::ClearCinStream();
		break;
	}

	return data;
}

std::string program::RunMainArea() {
	program::ShowMainMenu();
	const std::string choice = program::MainMenuSelection();
	return choice;
}

bool program::QuitFromMatrixArea() {

	std::string choice;
	program::MatrixData data;
	while (true) {
		program::ShowMatrixMenu();
		choice = program::MatrixMenuSelection();
		switch (program::matrix_menu_opts.at(choice)) {
			case 0:
				return true;
			case 1:
				return false;
			case 2:
				data = program::GetMatrixData();
				program::LUDecomp(data);
				continue;
			case 3:
			case 4:
			case 5 :
				return true;
		}
	}

	return true;
}

void program::LUDecomp(const program::MatrixData& data) {
	if (data.rows == data.cols) {
		matrices::SquareMatrix sm(data.rows, data.matrix);
		sm.LUDecomposition();
		sm.PrintLUDecomposedSystem();
	}
	else {
		std::cout << "Not a Square Matrix\n";
	}
}

void program::ShowMainMenuGreeting() noexcept {
	std::cout << "Welcome to my Matrix Program!\n";
	std::cout << "Choose an option from the menu to get started.\n";
}

void program::Run() {
	program::ShowMainMenuGreeting();

	std::string choice;
	bool quit;
	while (true) {
		choice = program::RunMainArea();
		switch (program::main_menu_opts.at(choice)) {
		case 0:
			return;
		case 1:
			quit = program::QuitFromMatrixArea();
			if (quit) { return; }
			continue;
		}
	}
}
