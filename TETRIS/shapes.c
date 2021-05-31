#include "shapes.h"

struct {
	Block t[6];
	Block s[6];
	Block z[6];
	Block o[4];
	Block l[6];
	Block j[6];
	Block i[4];
} shapeMatrices = {
	.t = { EMPTY, RED, EMPTY, RED, RED, RED },
	.s = { EMPTY, MAGENTA, MAGENTA, MAGENTA, MAGENTA, EMPTY },
	.z = { LIGHTBLUE, LIGHTBLUE, EMPTY, EMPTY, LIGHTBLUE, LIGHTBLUE },
	.o = { YELLOW, YELLOW, YELLOW, YELLOW },
	.l = { ORANGE, EMPTY, ORANGE, EMPTY, ORANGE, ORANGE },
	.j = { EMPTY, GREEN, EMPTY, GREEN, GREEN, GREEN },
	.i = { LIGHTBLUE, LIGHTBLUE, LIGHTBLUE, LIGHTBLUE }
};

const Shape defaultShapes[DEFAULT_COUNT] = {
	{
		.columns = 3,
		.rows = 2,
		.matrix = shapeMatrices.t
	},
	{
		.columns = 3,
		.rows = 2,
		.matrix = shapeMatrices.s
	},
	{
		.columns = 3,
		.rows = 2,
		.matrix = shapeMatrices.z
	},
	{
		.columns = 2,
		.rows = 2,
		.matrix = shapeMatrices.o
	},
	{
		.columns = 2,
		.rows = 3,
		.matrix = shapeMatrices.l
	},
	{
		.columns = 2,
		.rows = 3,
		.matrix = shapeMatrices.j
	},
	{
		.columns = 4,
		.rows = 1,
		.matrix = shapeMatrices.i
	}
};

/****************************************************************************************************/
/****************************************** Private Methods ******************************************/
/****************************************************************************************************/

Block* CreateEmptyMatrix(size_t rows, size_t columns);
void CopyMatrix(Block* input, Block* output, size_t rows, size_t columns);
void SetRandomSeed();
int CreateRandomNumber();
void FlipRows(Shape* shape);
void Transpose(Shape* shape);
void SetSize(Shape* shape, size_t rows, size_t columns);
void NormalizeShapes(Shape* first, Shape* second);

Block* CreateEmptyMatrix(size_t rows, size_t columns) {
	Block* matrix = malloc(sizeof(Block) * rows * columns);
	for(size_t i = 0; i < (rows * columns); i++) {
		matrix[i] = EMPTY;
	}
	return matrix;
}

void CopyMatrix(Block* input, Block* output, size_t rows, size_t columns) {
	for(size_t i = 0; i < (rows * columns); i++) {
		output[i] = input[i];
	}
}

void SetRandomSeed(int seed) {
	srand(seed);
}

int CreateRandomNumber() {
	return rand() % DEFAULT_COUNT;
}

void FlipRows(Shape* shape) {
	Shape _shape = CopyShape(shape);
	for(size_t y=0; y < shape->rows; y++) {
		for(size_t x=0; x < shape->columns; x++) {
			shape->matrix[(y * shape->columns) + x] = _shape.matrix[(y * _shape.columns) + (_shape.columns - x - 1)];
		}
	}
	DeleteShape(&_shape);
}

void Transpose(Shape* shape) {
	Shape _shape = CopyShape(shape);
	for(size_t y=0; y < shape->rows; y++) {
		for(size_t x=0; x < shape->columns; x++) {
			shape->matrix[(x * shape->rows) + y] = _shape.matrix[(y * _shape.columns) + x];
		}
	}
	shape->rows = _shape.columns;
	shape->columns = _shape.rows;
	DeleteShape(&_shape);
}

void SetSize(Shape* shape, size_t rows, size_t columns) {
	if (rows > shape->rows) {
		AppendRows(shape, rows - shape->rows);
	}
	if (columns > shape->columns) {
		AppendColumns(shape, columns - shape->columns);
	}
	Block* _matrix = CreateEmptyMatrix(rows, columns);
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

void NormalizeShapes(Shape* first, Shape* second) {
	size_t maxRows = (first->rows > second->rows) ? first->rows : second->rows;
	size_t maxColumns = (first->columns > second->columns) ? first->columns : second->columns;
	SetSize(first, maxRows, maxColumns);
	SetSize(second, maxRows, maxColumns);
}

/****************************************************************************************************/
/****************************************** Public Methods ******************************************/
/****************************************************************************************************/

Shape CopyShape(Shape* input) {
	Shape output = {
		.columns = input->columns,
		.rows = input->rows,
		.matrix = CreateEmptyMatrix(input->rows, input->columns)
	};
	CopyMatrix(input->matrix, output.matrix, input->rows, input->columns);
	
	return output;
}

Shape CreateEmptyShape(size_t rows, size_t columns) {
	Shape _emptyShape = {
		.rows = rows,
		.columns = columns,
		.matrix = CreateEmptyMatrix(rows, columns)
	};
	
	return _emptyShape;
}

Shape CreateRandomShape() {
	const Shape* _randomShape = &defaultShapes[CreateRandomNumber()];
	Shape output = CreateEmptyShape(_randomShape->rows, _randomShape->columns);
	CopyMatrix(_randomShape->matrix, output.matrix, _randomShape->rows, _randomShape->columns);
	
	return output;
}

void DeleteShape(Shape* shape) {
	free(shape->matrix);
}

void Rotate(Shape* shape) {
	Transpose(shape);
	FlipRows(shape);
};

void PrependRows(Shape* shape, size_t amount) {
	Block* _matrix = CreateEmptyMatrix(shape->rows + amount, shape->columns);
	for (size_t i = 0; i < (shape->rows * shape->columns); i++) {
		_matrix[i + (amount * shape->columns)] = shape->matrix[i];
	}
	free(shape->matrix);
	shape->matrix = _matrix;
	shape->rows = shape->rows + amount;
}

void AppendRows(Shape* shape, size_t amount) {
	Block* _matrix = CreateEmptyMatrix(shape->rows + amount, shape->columns);
	for (size_t i = 0; i < (shape->rows * shape->columns); i++) {
		_matrix[i] = shape->matrix[i];
	}
	free(shape->matrix);
	shape->matrix = _matrix;
	shape->rows = shape->rows + amount;
}

void PrependColumns(Shape* shape, size_t amount)  {
	Block* _matrix = CreateEmptyMatrix(shape->rows, shape->columns + amount);
	for(size_t y=0; y < shape->rows; y++) {
		for(size_t x=0; x < shape->columns; x++) {
			_matrix[(y * (shape->columns + amount)) + x + amount] = shape->matrix[(y * shape->columns) + x];
		}
	}
	free(shape->matrix);
	shape->matrix = _matrix;
	shape->columns = shape->columns + amount;
}

void AppendColumns(Shape* shape, size_t amount)  {
	Block* _matrix = CreateEmptyMatrix(shape->rows, shape->columns + amount);
	for(size_t y=0; y < shape->rows; y++) {
		for(size_t x=0; x < shape->columns; x++) {
			_matrix[(y * (shape->columns + amount)) + x] = shape->matrix[(y * shape->columns) + x];
		}
	}
	free(shape->matrix);
	shape->matrix = _matrix;
	shape->columns = shape->columns + amount;
}

void RemoveRow(Shape* shape, size_t row)  {
	Block* _matrix = CreateEmptyMatrix(shape->rows - 1, shape->columns);
	for(size_t y=0; y < shape->rows; y++) {
		if (y == row) {
			continue;
		}
		for(size_t x=0; x < shape->columns; x++) {
			_matrix[((y - (y > row ? 1 : 0)) * (shape->columns)) + x] = shape->matrix[(y * shape->columns) + x];
		}
	}
	free(shape->matrix);
	shape->matrix = _matrix;
	shape->rows = shape->rows - 1;
}

bool IsRowComplete(Shape* shape, size_t row) {
	for(size_t x=(shape->columns * row); x < (shape->columns * row + shape->columns); x++) {
		if (shape->matrix[x] == EMPTY) {
			return false;
		}
	}
	
	return true;
}

void ShiftShape(Shape* shape, Vector vector) {
	PrependColumns(shape, vector.x);
	PrependRows(shape, vector.y);
}

void ShiftVector(Vector* vector, Direction direction) {
		switch (direction) {
			case UP: {
				if (vector->y > 0) {
					vector->y = vector->y - 1;
				}
				break;
			}
			case DOWN: {
				vector->y = vector->y + 1;
				break;
			}
			case LEFT: {
				if (vector->x > 0) {
					vector->x = vector->x - 1;
				}
				break;
			}
			case RIGHT: {
				vector->x = vector->x + 1;
				break;
			}
			default: {}
		}
}

bool IsCombinePossible(Shape* first, Shape* second) {
	Shape _first = CopyShape(first);
	Shape _second = CopyShape(second);
	NormalizeShapes(&_first, &_second);
	int errors = 0;
	for(int i = 0; i < (_first.rows * _first.columns); i++) {
		if (!CanCombine(_first.matrix[i], _second.matrix[i])) {
			errors++;
		}
	}
	DeleteShape(&_first);
	DeleteShape(&_second);
	return (errors == 0);
}

Shape CombineShapes(Shape* first, Shape* second) {
	Shape _first = CopyShape(first);
	Shape _second = CopyShape(second);
	NormalizeShapes(&_first, &_second);
	Shape _shape = CreateEmptyShape(_first.rows, _first.columns);
	for(int i = 0; i < (_first.rows * _first.columns); i++) {
		_shape.matrix[i] = CombinesBlocks(_first.matrix[i], _second.matrix[i]);
	}
	DeleteShape(&_first);
	DeleteShape(&_second);
	return _shape;
}