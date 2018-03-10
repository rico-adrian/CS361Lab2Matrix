	#include <iostream>
	#include <algorithm>
	#include <assert.h>
	#include "matrix.h"


// Creates an empty matrix of size 0 times 0.
Matrix::Matrix()
{

	//set up the height and width to 0(empty matrix) and set all the values to null
	this->height=0;
	this->width=0;
	this->values = nullptr;
}

// Creates an identity matrix of size <size> times <size>.
Matrix::Matrix(int size)
{ 
	//set the width and height into size 
	this->height = size;
	this->width = size;

	//create an identity matrix
	values = new double*[height];
	for (int i = 0;i < height;i++) {
		values[i] = new double[width]();
		values[i][i] = 1;

	}


}

// Creates a matrix of size <height> times <width> filled with 0s.
Matrix::Matrix(int row, int col)
{

	//set the height into row and width into col
	this->height = row;
	this->width = col;

	// Creates a matrix of size height times width and fill them with 0s.
	values = new double*[height];
	for (int i = 0;i < height;i++) {
		values[i] = new double[width]();
	}
}


// Copy constructor
Matrix::Matrix(const Matrix & obj)
{

	// assign new <height> and <width> to obj <height> and <width>
	this->height = obj.height;
	this->width = obj.width;

	// build new array for values of obj <height> and <width>
	values = new double*[height];
	for (int i = 0;i < height;i++) {
		values[i] = new double[width]();
	}

	// put obj values in this matrix
	for (int i = 0;i < height;i++) {
		for (int j = 0; j < width; j++ ) {
			values[i][j] = obj(i, j);
		}
	}

}


// Move constructor
Matrix::Matrix(Matrix && obj)
{
	width = obj.width;
	height = obj.height;
	values = nullptr;
	values = obj.values;
	obj.values = nullptr;

}

//deconstructor
Matrix::~Matrix()
{

	//delete values if values are not null
	if (values != nullptr) {
	for (int i = 0; i < height; i++) { 
		delete [] values[i];
	}
		delete [] values;
	}

}

//getter method for width
int Matrix::getWidth() const
{
	return width;
}

//getter method for height
int Matrix::getHeight() const
{
	return height;
}

//resizing method
void Matrix::resize(int rows, int columns)
{
		
		//create a new array to temporarily put values of matrix later, 
		//set all the values to 0 for now
		double **temp=new double*[rows];
		for (int i = 0;i < rows;i++) {
			temp[i] = new double[columns]();
		}

		
		//put all values of matrix into temporary array
		//while i is less than the new height and j is less than the new width
		for(int i=0;i<rows;i++) {
			for(int j=0;j<columns;j++) {
				if (i<height&& j<width) {
					temp[i][j]=values[i][j];
				}
			}
		}


		//put all values in the temporary array into the matrix and set the height and width into the new height and width
		height=rows;
		width=columns;
		values=temp;


}

//transpose method
void Matrix::transpose()
{

		//create a new matrix and swap the width and height
		Matrix m=Matrix(width,height);
		//set all the values of the new matrix into the values of the original matrix
		//but it will transpose the matrix
	    for (int i = 0; i<height; i++) {
			for (int j = 0; j<width; j++) {
				m.values[j][i] = values[i][j];

			}
	  }
		
		//resize the matrix by swapping the width and height and put all the transposed values
		//into the original matrix
		resize(width,height);
	   for (int i = 0; i<height; i++) {
		 for (int j = 0; j<width; j++) {
			 values[i][j] = m.values[i][j];

		 }
	  }
	
}

//copy assignment that copy all the values from original matrix into the new matrix
Matrix & Matrix::operator=(const Matrix & obj)
{
	if (values != nullptr) {
	for (int i = 0; i < height; i++) { 
		delete [] values[i];
	}
		delete [] values;
	}

	// assign new <height> and <width> to obj <height> and <width>
	height = obj.height;
	width = obj.width;

	// build new array for values of obj <height> and <width>
	values = new double*[height];
	for (int i = 0;i < width;i++) {
		values[i] = new double[width]();
	}

	// put obj values in this matrix
	for (int i = 0;i < height;i++) {
		for (int j = 0; j < width; j++ ) {
			values[i][j] = obj.values[i][j];
		}
	}

	return *this;

}

//move assignment that moves the pointer of values into object
Matrix & Matrix::operator=(Matrix && obj)
{
	if (values != nullptr) {
	for (int i = 0; i < height; i++) { 
		delete [] values[i];
	}
		delete [] values;
	}
	width = obj.width;
	height = obj.height;
	values = obj.values;
	obj.values = nullptr;
	return *this;
}

//Returns the value at the specified position in the matrix.(getter)
double & Matrix::operator()(const int row, const int col) 
{
	assert(row >= 0 && row < height && col >= 0 && col < width);
	return values[row][col];
}

//Returns the value at the specified position in the matrix.(setter)
double Matrix::operator()(const int row, const int col) const
{
	assert(row >= 0 && row < height && col >= 0 && col < width);
	return values[row][col];
}

//Creates a new matrix which is the sum of this and another given matrix.
Matrix Matrix::operator+(const Matrix & obj) const
{

	
	int columns;
	int rows;
	//check which height and width are smaller between original matrix and object matrix. and set the width and height into the smaller ones
	if (height > obj.height) {
		rows = obj.height;
	}
	else {
		rows = height;
	}
	if (width > obj.width) {
		columns = obj.width;
	}
	else {
		columns = width;
	}
	//create a new matrix and set the new height and width
	Matrix new_mat(rows,columns);

	//add the values of the original matrix and the object matrix for each index of matrix
	//and assign the values into the new created matrix
	for (int i = 0; i<rows; i++) {
		for (int j = 0; j<columns; j++) {
			new_mat.values[i][j] = values[i][j] + obj.values[i][j];
		}
	}
	return new_mat; //return the new matrix
}

// Adds a given matrix to the current.
Matrix & Matrix::operator+=(const Matrix & obj)
{

	int columns;
	int rows;

	//check which height and width are smaller between original matrix and object matrix. and set the width and height into the smaller ones
	if (height > obj.height) {
		rows = obj.height;
	} 
	else {
		rows = height;
	}

	if (width > obj.width) {
		columns = obj.width;
	}
	else {
		columns = width;
	}

	//change the height and width of the matrix into a new one
	height = rows;
	width = columns;
	
	//add the values of the original matrix and the object matrix for each index of matrix
	//but this time it changes the original matrix instead of creating new matrix
	for (int i = 0; i < height; i++) {
		for (int j = 0; j <width; j++) { 
			values[i][j]+=obj.values[i][j];
		}
	}
	return *this; //return the original matrix
}

// Creates a new matrix which is the product of this and another given matrix.
Matrix Matrix::operator*(const Matrix & obj) const
{
	//bound of matrix to adjust 
	//to make sure the program use the largest sub-matrices which work 
	int bound;
	if(this->width>obj.getHeight()) {
		bound=obj.getHeight();
	}
	else {
		bound=this->width;
	}
	int rows;
	int columns;
	//check which height and width are larger between original matrix and object matrix. and set the width and height into the larger ones
	if (height > obj.height) {
		rows = height;
	}
	else {
		rows = obj.height;
	}

	if (width > obj.width) {
		columns = width;
	}
	else {
		columns = obj.width;
	}

	//create a new matrix and set the new height and width
	Matrix m = Matrix(rows,columns);
	
	//multiply the values of the original matrix and the object matrix for each index of matrix
	//and assign the values into the new created matrix
	 for (int i = 0; i < height; i++)  {
		 for (int j = 0; j < obj.getWidth(); j++) {
			for (int k = 0; k < bound; k++) {
						m.values[i][j]+=values[i][k]*obj.values[k][j];
			}
		 }
	 }

	 return m; //return the new matrix
}

// Multiplies a given matrix with the current.
Matrix & Matrix::operator*=(const Matrix & obj)
{
	
	//bound of matrix to adjust 
	//to make sure the program use the largest sub-matrices which work 
	int bound;
	if(this->width>obj.getHeight()) {
		bound=obj.getHeight();
	}
	else {
		bound=this->width;
	}
	int rows;
	int columns;
	//check which height and width are larger between original matrix and object matrix. and set the width and height into the larger ones
	if (height > obj.height) {
		rows = height;
	}
	else {
		rows = obj.height;
	}

	if (width > obj.width) {
		columns = width;
	}
	else {
		columns = obj.width;
	}

	//create a new matrix and set the new height and width
	Matrix m = Matrix(rows,columns);

	//add the values of the original matrix and the object matrix for each index of matrix
	//but this time it changes the original matrix instead of creating new matrix
	for (int i = 0; i < height; i++)  {
		for (int j = 0; j < obj.getWidth(); j++) {
			for (int k = 0; k < bound; k++) {
						m.values[i][j]+=values[i][k]*obj.values[k][j];
			}
		}
	}

	//resize the original matrix height and width into rows and columns
 	this->resize(rows,columns);
	//put all the values of new created matrix into the original matrix
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			values[i][j]=m.values[i][j];
		}
	}

	 return *this; //return the original matrix
}

// Creates a new matrix which is the product of this and given number.
Matrix Matrix::operator*(double multiply) const
{
	//create a new matrix
	Matrix matrix = Matrix(height, width);

	//multiply all the values in the original matrix by a number
	//and assign all the values into the new matrix
	//it does not change the original matrix
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			matrix.values[i][j] = values[i][j] * multiply;
		}
	}

	return matrix; //return the new matrix
}

// Mutliplies the current matrix with a given number.
Matrix & Matrix::operator*=(double multiply)
{
	//multiply all the values in the original matrix 
	//and assign all the values into the original matrix
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			values[i][j]=values[i][j]*multiply;
		}
	}

	return *this; //return the original matrix(this matrix)
}

// Determines if two matrices are equal.
bool Matrix::operator==(const Matrix & obj) const
{
	
	//create a temporarily variable with value false
	bool temp = false;

	//check if height and width are equal
	//if yes, go into the for loop and check all the values
	//return false(exit the whole loop) if one value is not the same
	//set the variable temp into true if every values are the same
	if (height == obj.getHeight() && width == obj.getWidth() ) {
		for (int i = 0;i < obj.getHeight();i++) {
			for (int j = 0;j < obj.getWidth();j++) {
				if (values[i][j] != obj.values[i][j]) {
					return false;
				}
				else {
					temp = true;
				}
			}
		}
	}

	//return false if height and width are not the same
	//because in this case it will ignore the whole if statements
	return temp;

}