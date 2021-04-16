/*
* shapes.c
*
* Created: 08-04-2021 08:30:13
*  Author: ander
*/
#include "shapes.h"

Block t[] = { EMPTY, RED, EMPTY, RED, RED, RED };
Block s[] = { EMPTY, MAGENTA, MAGENTA, MAGENTA, MAGENTA, EMPTY };
Block z[] = { LIGHTBLUE, LIGHTBLUE, EMPTY, EMPTY, LIGHTBLUE, LIGHTBLUE };
Block o[] = { YELLOW, YELLOW, YELLOW, YELLOW };
Block l[] = { ORANGE, EMPTY, ORANGE, EMPTY, ORANGE, ORANGE };
Block j[] = { EMPTY, GREEN, EMPTY, GREEN, GREEN, GREEN };
Block i[] = { LIGHTBLUE, LIGHTBLUE, LIGHTBLUE, LIGHTBLUE };

const Shape shapes[DEFAULT_COUNT] = {
	{
		.columns = 3,
		.rows = 2,
		.matrix = t
	},
	{
		.columns = 3,
		.rows = 2,
		.matrix = s
	},
	{
		.columns = 3,
		.rows = 2,
		.matrix = z
	},
	{
		.columns = 2,
		.rows = 2,
		.matrix = o
	},
	{
		.columns = 2,
		.rows = 3,
		.matrix = l
	},
	{
		.columns = 2,
		.rows = 3,
		.matrix = j
	},
	{
		.columns = 4,
		.rows = 1,
		.matrix = i
	}
};

Block* createEmptyMatrix(size_t rows, size_t columns) {
	Block* matrix = malloc(sizeof(Block) * rows * columns);
	for(size_t i = 0; i < (rows * columns); i++) {
		matrix[i] = EMPTY;
	}
	return matrix;
}

void copyMatrix(Block* input, Block* output, size_t rows, size_t columns) {
	for(size_t i = 0; i < (rows * columns); i++) {
		output[i] = input[i];
	}
}

Shape copyShape(Shape* input) {
	Shape output = {
		.columns = input->columns,
		.rows = input->rows,
		.matrix = createEmptyMatrix(input->rows, input->columns)
	};
	copyMatrix(input->matrix, output.matrix, input->rows, input->columns);
	
	return output;
}

Shape createEmptyShape(size_t rows, size_t columns) {
	Shape _emptyShape = {
		.rows = rows,
		.columns = columns,
		.matrix = createEmptyMatrix(rows, columns)
	};
	
	return _emptyShape;
}

Shape createRandomShape() {
	const Shape* _randomShape = &shapes[rand() % DEFAULT_COUNT];
	Shape output = createEmptyShape(_randomShape->rows, _randomShape->columns);
	copyMatrix(_randomShape->matrix, output.matrix, _randomShape->rows, _randomShape->columns);
	
	return output;
}

void deleteShape(Shape* shape) {
	free(shape->matrix);
}

void flipRows(Shape* shape) {
	Shape _shape = copyShape(shape);
	for(size_t y=0; y < shape->rows; y++) {
		for(size_t x=0; x < shape->columns; x++) {
			shape->matrix[(y * shape->columns) + x] = _shape.matrix[(y * _shape.columns) + (_shape.columns - x - 1)];
		}
	}
	deleteShape(&_shape);
}

void transpose(Shape* shape) {
	Shape _shape = copyShape(shape);
	for(size_t y=0; y < shape->rows; y++) {
		for(size_t x=0; x < shape->columns; x++) {
			shape->matrix[(x * shape->rows) + y] = _shape.matrix[(y * _shape.columns) + x];
		}
	}
	shape->rows = _shape.columns;
	shape->columns = _shape.rows;
	deleteShape(&_shape);
}

void rotate(Shape* shape) {
	transpose(shape);
	flipRows(shape);
};

void prependRows(Shape* shape, size_t amount) {
	Block* _matrix = createEmptyMatrix(shape->rows + amount, shape->columns);
	for (size_t i = 0; i < (shape->rows * shape->columns); i++) {
		_matrix[i + (amount * shape->columns)] = shape->matrix[i];
	}
	free(shape->matrix);
	shape->matrix = _matrix;
	shape->rows = shape->rows + amount;
}

void prependColumns(Shape* shape, size_t amount)  {
	Block* _matrix = createEmptyMatrix(shape->rows, shape->columns + amount);
	for(size_t y=0; y < shape->rows; y++) {
		for(size_t x=0; x < shape->columns; x++) {
			_matrix[(y * (shape->columns + amount)) + x + amount] = shape->matrix[(y * shape->columns) + x];
		}
	}
	free(shape->matrix);
	shape->matrix = _matrix;
	shape->columns = shape->columns + amount;
}

void appendRows(Shape* shape, size_t amount) {
	Block* _matrix = createEmptyMatrix(shape->rows + amount, shape->columns);
	for (size_t i = 0; i < (shape->rows * shape->columns); i++) {
		_matrix[i] = shape->matrix[i];
	}
	free(shape->matrix);
	shape->matrix = _matrix;
	shape->rows = shape->rows + amount;
}

void appendColumns(Shape* shape, size_t amount)  {
	Block* _matrix = createEmptyMatrix(shape->rows, shape->columns + amount);
	for(size_t y=0; y < shape->rows; y++) {
		for(size_t x=0; x < shape->columns; x++) {
			_matrix[(y * (shape->columns + amount)) + x] = shape->matrix[(y * shape->columns) + x];
		}
	}
	free(shape->matrix);
	shape->matrix = _matrix;
	shape->columns = shape->columns + amount;
}

void shift(Shape* shape, Vector vector) {
	prependColumns(shape, vector.x);
	prependRows(shape, vector.y);
}

void setSize(Shape* shape, size_t rows, size_t columns) {
	if (rows > shape->rows) {
		appendRows(shape, rows - shape->rows);
	}
	if (columns > shape->columns) {
		appendColumns(shape, columns - shape->columns);
	}
	Block* _matrix = createEmptyMatrix(rows, columns);
	for(size_t y=0; y < rows; y++) {
		for(size_t x=0; x < columns; x++) {
			_matrix[(y * columns) + x] = shape->matrix[(y * columns) + x];
		}
	}
	free(shape->matrix);
	shape->matrix = _matrix;
	shape->rows = rows;
	shape->columns = columns;	
}

bool isCombinePossible(Shape* first, Shape* second) {
	Shape _first = copyShape(first);
	Shape _second = copyShape(second);
	normalizeShapes(&_first, &_second);
	int errors = 0;
	for(int i = 0; i < (_first.rows * _first.columns); i++) {
		if (!_first.matrix[i] == EMPTY && !_second.matrix[i] == EMPTY) {
			errors = errors + 1;
		}
	}
	deleteShape(&_first);
	deleteShape(&_second);
	return (errors == 0);
}

void normalizeShapes(Shape* first, Shape* second) {
	size_t maxRows = (first->rows > second->rows) ? first->rows : second->rows;
	size_t maxColumns = (first->columns > second->columns) ? first->columns : second->columns;
	setSize(first, maxRows, maxColumns);
	setSize(second, maxRows, maxColumns);
}

Shape combineShapes(Shape* first, Shape* second) {
	Shape _first = copyShape(first);
	Shape _second = copyShape(second);
	normalizeShapes(&_first, &_second);
	Shape _shape = createEmptyShape(_first.rows, _first.columns);
	for(int i = 0; i < (_first.rows * _first.columns); i++) {
		_shape.matrix[i] = combinesBlocks(_first.matrix[i], _second.matrix[i]);
	}
	deleteShape(&_first);
	deleteShape(&_second);
	return _shape;
}