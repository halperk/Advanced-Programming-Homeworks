/*******************************************

CS 204 (Fall 2021-2022)
Homework #1 - Minesweeper
Huseyin Alper Karadeniz (28029)
Date: 10/14/2021

********************************************/

#include <iostream>
#include <string>
#include <vector>
#include "randgen.h"
using namespace std;

/* In this program, the bomb counts of cells are saved as integers.
   The maximum number of bombs that could be neighbour to a cell is 8.
   The integers of 0, 1, 2, 3, 4, 5, 6, 7, 8 represent bomb counts around a cell.
   The integer 9 represents the cell is a bomb.
   The integer 10 represents the cell is not opened yet.
   All these representations used in the matrixes below. */

/* Checking if a particular coordinate is a bomb, or not.
   If it is a bomb, then the function returns 1; if not, returns 0. */
int isBomb (vector<vector<int>> values, int check_row, int check_column) {

	int total_rows = values.size();
	int total_columns = values.at(0).size();
	
	/* Program firstly checks if checked row and column on the matrix. */
	if (check_row >= 0 && check_row < total_rows && check_column >= 0 && check_column < total_columns) {

		/* Integer 9 means that there is a bomb at that coordinate. */
		if (values.at(check_row).at(check_column) == 9) {
			return 1;
		}
		return 0;
	}
	return 0;
}

/* Calculating the number of bombs around a coordinate by using isBomb function. */
int bombCount (vector<vector<int>> values, int row_number, int column_number) {

	int bomb_count = isBomb(values, row_number-1, column_number-1)
		+ isBomb(values, row_number-1, column_number)
		+ isBomb(values, row_number-1, column_number+1)
		+ isBomb(values, row_number, column_number-1)
		+ isBomb(values, row_number, column_number+1)
		+ isBomb(values, row_number+1, column_number-1)
		+ isBomb(values, row_number+1, column_number)
		+ isBomb(values, row_number+1, column_number+1);

	return bomb_count;

}

int main() {

	int row, col, nrMines;

	/* Getting the number of rows and columns. */
	cout << "Give the dimensions of the matrix: ";
	cin >> row;
	cin >> col;

	/* Getting the number of bombs. */
	cout << "How many bombs: ";
	cin >> nrMines;
	/* Getting a proper number of bombs if it is not valid. */
	while (0 >= nrMines || nrMines >= col * row) {
		if (0 >= nrMines) {
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin >> nrMines;
		} else {
			cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
			cin >> nrMines;
		}
	}

	/* Initializing all row as integer 0 which represents there is no bombs around that coordinate. */
	vector<vector<int>> values;
	for (int y = 0; y < row; y++) {
		vector<int> row_values;
		for (int x = 0; x < col; x++) {
			row_values.push_back(0);
		}
		values.push_back(row_values);
	}

	/* Determining completely random bomb coordinates among all the cells. */
	int total_cells = row * col;
	vector<int> random_bomb_cells;
	int i = 0;
	while (i < nrMines) {

		/* Creating a random integer as a possible bomb coordinate. */
		RandGen rand;
		int random_int = rand.RandInt(total_cells-1);

		/* Checking if there is a bomb on that coordinate. */
		if (find(random_bomb_cells.begin(), random_bomb_cells.end(), random_int) == random_bomb_cells.end()) {
			random_bomb_cells.push_back(random_int);
			i++;
		}
	}

	/* Writing bomb coordinates into the matrix. */
	for (int i = 0; i < nrMines; i++) {
		int bomb_cell = random_bomb_cells.at(i);
		
		int column_index = bomb_cell % col;
		int row_index = bomb_cell / col;

		/* Saving bomb coordinates as integer 9. */
		values.at(row_index).at(column_index) = 9;
	}

	/* Determining the values (bombs around a specific coordinate) for all matrix.
	   Bomb coordinates are excepted since they are represented as integer 9. */
	vector<vector<int>> new_values;
	for (int y = 0; y < row; y++) {
		vector<int> new_row;
		for (int x = 0; x < col; x++) {
			/* Checking if that coordinate is a bomb, or not. */
			if (values.at(y).at(x) == 9) {
				new_row.push_back(9);
			} else {
				/* Writing the number of bombs around a coordinate by using the bombCount function. */
				int bomb_count = bombCount(values, y, x);
				new_row.push_back(bomb_count);
			}
		}
		new_values.push_back(new_row);
	}

	/* Displaying the matrix without the values. */
	for (int i = 0; i < new_values.size(); i++) {
		for (int j=0; j < new_values.at(i).size(); j++) {
			cout << "X\t";
		}
		cout << endl;
	}
	
	/* Initializing opened values matrix.
	   Integer 10 represents X which means the cell is not opened yet. */
	vector<vector<int>> opened_values;
	for (int y = 0; y < row; y++) {
		vector<int> row_values;
		for (int x = 0; x < col; x++) {
			row_values.push_back(10);
		}
		opened_values.push_back(row_values);
	}

	bool exe_cont = true;
	int opened_cells = 0;

	while (exe_cont == true) {

		/* Getting the choice of the user for the program execution. */
		cout << endl;
		string choice;
		cout << "Press: " << endl << "1. If you want to find out the surrounding of a cell" << endl
			<< "2. If you want to open the cell" << endl << "3. If you want to exit." << endl;		cin >> choice;
		/* Checking if the user selected a proper choice. */
		while (choice != "1" && choice != "2"  && choice != "3") {
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
			cin >> choice;		}		if (choice == "1") {			/* Getting the coordinates to show the status of that coordinate on the matrix. */			int coordinate_row, coordinate_col;			cout << "Give the coordinates: ";			cin >> coordinate_row >> coordinate_col;			while (coordinate_row >= row || coordinate_col >= col) {				cout << "It is out of range. Please give a valid coordinates: ";				cin >> coordinate_row >> coordinate_col;			}			cout << "Displaying the surrounding of (" << coordinate_row << "," << coordinate_col << "): " << endl;		
			/* Displaying the matrix with the wanted coordinate value without actually opening it. */
			int bomb_count_at_position = 0;
			for (int i=0; i < new_values.size(); i++) {
				for (int j=0; j < new_values.at(i).size(); j++) {
					int value = opened_values.at(i).at(j);
					if (i == coordinate_row && j == coordinate_col) {
						bomb_count_at_position = bombCount(new_values, i, j);
						cout << bomb_count_at_position << "\t";
					} else {
						if (value == 10) {
							cout << "X\t";
						} else if (value == 9) {
							cout << "B\t";
						} else {
							cout << opened_values.at(i).at(j) << "\t";
							opened_cells++;
						}
					}
				}
				cout << endl;
			}			cout << "Around (" << coordinate_row << "," << coordinate_col << ") you have " << bomb_count_at_position << " bomb(s)" << endl;		} else if (choice == "2") {			/* Getting the coordinates to open the cell on that coordinate on the matrix. */			int coordinate_row, coordinate_col;			cout << "Give the coordinates: ";			cin >> coordinate_row >> coordinate_col;			while (coordinate_row >= row || coordinate_col >= col) {				cout << "It is out of range. Please give a valid coordinates: ";				cin >> coordinate_row >> coordinate_col;			}			cout << "Opening cell (" << coordinate_row << "," << coordinate_col << "): " << endl;			
			int bomb_count_at_position = new_values.at(coordinate_row).at(coordinate_col);

			/* Displaying all opened values on the matrix. */
			opened_values.at(coordinate_row).at(coordinate_col) = bomb_count_at_position;
			for (int i=0; i < opened_values.size(); i++) {
				for (int j=0; j < opened_values.at(i).size(); j++) {
					int value = opened_values.at(i).at(j);
					if (value == 10) {
						cout << "X\t";
					} else if (value == 9) {
						cout << "B\t";
					} else {
						cout << opened_values.at(i).at(j) << "\t";
						opened_cells++;
					}
				}
				cout << endl;
			}

			/* Checking if the given coordinate is a bomb, or not.
			   The integer 9 represents that the cell is a bomb cell. */
			if (bomb_count_at_position == 9) {
				cout << "Unfortunately, you stepped on a mine" << endl << "Arrangement of mines:" << endl;
				for(int i=0; i < new_values.size(); i++) {
					for(int j=0; j < new_values.at(i).size(); j++) {
						int value = new_values.at(i).at(j);
						if (value == 9) {
							cout << "B\t";
						} else {
							cout << new_values.at(i).at(j) << "\t";
						}
					}
					cout << endl;
				}
				cout << ">>>>> Game Over! <<<<<" << endl;				exe_cont = false;
			}			/* Checking if the user won the game. */			if ((opened_cells + nrMines) == (col * row)) {				cout << "Congratulations! All the non-mined cells opened successfully" << endl;				cout << "You won!" << endl;				cout << endl;				cout << ">>>>> Game Over! <<<<<" << endl;				exe_cont = false;			}		} else if (choice == "3") {			/* Exiting program. */			cout << "Program exiting..." << endl;			exe_cont = false;		}
	}

	return 0;

}