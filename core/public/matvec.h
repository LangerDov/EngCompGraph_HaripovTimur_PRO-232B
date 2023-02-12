#ifndef _LINEAR_MATH_H
#define _LINEAR_MATH_H

#ifdef _WIN32
#pragma once
#endif

#ifdef _WIN32
#include <intrin.h>
#elif __linux
#include <x86intrin.h>
#endif
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

// о да, эта же та самая функция из квейка
extern float Q_rsqrt(float number);

class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(__m128 xy);
	Vector2D(float a);
	Vector2D(float* xy);

	static float Dot(Vector2D a, Vector2D b); // скалярное произведение векторов
	static float Length(Vector2D a); // длина вектора
	static float Distance(Vector2D a, Vector2D b);
	static Vector2D Normalize(Vector2D a); // нормализация

	//returns an array
	const float* Array();

	// операторы присвоения

	Vector2D operator=(Vector2D b);

	Vector2D operator+(Vector2D b);
	Vector2D operator-(Vector2D b);
	Vector2D operator*(Vector2D b);
	Vector2D operator/(Vector2D b);

	Vector2D operator*(float b);
	Vector2D operator/(float b);

	void operator+=(Vector2D b);
	void operator-=(Vector2D b);
	void operator*=(Vector2D b);
	void operator/=(Vector2D b);

	void operator*=(float b);
	void operator/=(float b);

	// операторы сравнения

	bool operator==(Vector2D b);
	bool operator!=(Vector2D b);

	float x, y;
};

__inline Vector2D::Vector2D()
{
	x = y = 0.f;
}

__inline Vector2D::Vector2D(float _x, float _y)
{
	x = _x, y = _y;
}

__inline Vector2D::Vector2D(float a)
{
	x = y = a;
}

__inline Vector2D::Vector2D(float* xyz)
{
	x = xyz[0], y = xyz[1];
}

inline float Vector2D::Dot(Vector2D a, Vector2D b)
{
	// ничего сложного
	return a.x * b.x + a.y * b.y;
}

inline float Vector2D::Distance(Vector2D a, Vector2D b)
{
	return fabsf(Length(a - b));
}

__inline float Vector2D::Length(Vector2D a)
{
	// √(x^2 + y^2 + z^2)
	// w лучше не менять)
	return sqrtf(powf(a.x, 2) + powf(a.y, 2));
}

inline Vector2D Vector2D::Normalize(Vector2D a)
{
	float length = Length(a);
	return Vector2D(a.x / length, a.y / length);
}

inline const float* Vector2D::Array()
{
	return (const float*)this;
}

__inline Vector2D Vector2D::operator=(Vector2D b)
{
	x = b.x, y = b.y;
	return *this;
}

__inline Vector2D Vector2D::operator+(Vector2D b)
{
	return Vector2D(x + b.x, y + b.y);
}

__inline Vector2D Vector2D::operator-(Vector2D b)
{
	return Vector2D(x - b.x, y - b.y);
}

__inline Vector2D Vector2D::operator*(Vector2D b)
{
	return Vector2D(x * b.x, y * b.y);
}

__inline Vector2D Vector2D::operator/(Vector2D b)
{
	return Vector2D(x / b.x, y / b.y);
}

inline Vector2D Vector2D::operator*(float b)
{
	return Vector2D(x * b, y * b);
}

inline Vector2D Vector2D::operator/(float b)
{
	return Vector2D(x / b, y / b);
}

inline void Vector2D::operator+=(Vector2D b)
{
	x += b.x, y += b.y;
}

inline void Vector2D::operator-=(Vector2D b)
{
	x -= b.x, y -= b.y;
}

inline void Vector2D::operator*=(Vector2D b)
{
	x *= b.x, y *= b.y;
}

inline void Vector2D::operator/=(Vector2D b)
{
	x /= b.x, y /= b.y;
}

inline void Vector2D::operator*=(float b)
{
	x *= b, y *= b;
}

inline void Vector2D::operator/=(float b)
{
	x /= b, y /= b;
}

inline bool Vector2D::operator==(Vector2D b)
{
	return x == b.x && y == b.y;
}

inline bool Vector2D::operator!=(Vector2D b)
{
	return !(*this == b);
}

// вектор трехмерный
class Vector
{
public:
	Vector();
	Vector(float x, float y, float z);
	Vector(__m128 xyzw);
	Vector(float a);
	Vector(float* xyzw);

	static float Dot(Vector a, Vector b); // скалярное произведение векторов
	static float Length(Vector a); // длина вектора
	static float InvLength(Vector a);
	static float Distance(Vector a, Vector b);
	static Vector Normalize(Vector a); // нормализация
	static Vector cross(Vector a, Vector b);
	
	//returns an array
	const float* Array();

	// операторы присвоения

	Vector operator=(Vector b);

	Vector operator+(Vector b);
	Vector operator-(Vector b);
	Vector operator-();
	Vector operator*(Vector b);
	Vector operator/(Vector b);

	Vector operator*(float b);
	Vector operator/(float b);

	void operator+=(Vector b);
	void operator-=(Vector b);
	void operator*=(Vector b);
	void operator/=(Vector b);

	void operator*=(float b);
	void operator/=(float b);

	// операторы сравнения

	bool operator==(Vector b);
	bool operator!=(Vector b);

	float x, y, z;
};

#define TO_RADIANS 0.0174533f

__inline Vector::Vector()
{
	x = y = z = 0.f;
}

__inline Vector::Vector(float _x, float _y, float _z)
{
	x = _x, y = _y, z = _z;
}

__inline Vector::Vector(__m128 _xyzw)
{
	float nums[4] = {};
	_mm_store_ps(nums, _xyzw);
	x = nums[0], y = nums[1], z = nums[2];
}

__inline Vector::Vector(float a)
{
	x = y = z = a;
}

__inline Vector::Vector(float* xyz)
{
	x = xyz[0], y = xyz[1], z = xyz[2];
}

inline float Vector::Dot(Vector a, Vector b)
{
	// ничего сложного
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Vector::Distance(Vector a, Vector b)
{
	return fabsf(Length(a - b));
}

inline float Vector::Length(Vector a)
{
	// √(x^2 + y^2 + z^2)
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline float Vector::InvLength(Vector a)
{
	return Q_rsqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline Vector Vector::Normalize(Vector a)
{
	float invLength = InvLength(a);
	__m128 vector = _mm_set_ps(0.f, a.z, a.y, a.x);
	__m128 length = _mm_set1_ps(invLength);
	return Vector(_mm_mul_ps(vector, length));
}

inline Vector Vector::cross(Vector a, Vector b)
{
	return Vector(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

inline const float* Vector::Array()
{
	return (const float*)this;
}

__inline Vector Vector::operator=(Vector b)
{
	x = b.x, y = b.y, z = b.z;
	return *this;
}

__inline Vector Vector::operator+(Vector b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps(0.f, b.z, b.y, b.x);
	return Vector(_mm_add_ps(vector1, vector2));
}

__inline Vector Vector::operator-(Vector b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps(0.f, b.z, b.y, b.x);
	return Vector(_mm_sub_ps(vector1, vector2));
}

inline Vector Vector::operator-()
{
	return Vector(-x, -y, -z);
}

__inline Vector Vector::operator*(Vector b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps(0.f, b.z, b.y, b.x);
	return Vector(_mm_mul_ps(vector1, vector2));
}

__inline Vector Vector::operator/(Vector b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps(0.f, b.z, b.y, b.x);
	return Vector(_mm_div_ps(vector1, vector2));
}

inline Vector Vector::operator*(float b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps1(b);
	return Vector(_mm_mul_ps(vector1, vector2));
}

inline Vector Vector::operator/(float b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps1(b);
	return Vector(_mm_div_ps(vector1, vector2));
}

inline void Vector::operator+=(Vector b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps(0.f, b.z, b.y, b.x);
	vector2 = _mm_add_ps(vector1, vector2);
	float nums[4] = {};
	_mm_store_ps(nums, vector2);
	x = nums[0], y = nums[1], z = nums[2];
}

inline void Vector::operator-=(Vector b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps(0.f, b.z, b.y, b.x);
	vector2 = _mm_sub_ps(vector1, vector2);
	float nums[4] = {};
	_mm_store_ps(nums, vector2);
	x = nums[0], y = nums[1], z = nums[2];
}

inline void Vector::operator*=(Vector b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps(0.f, b.z, b.y, b.x);
	vector2 = _mm_mul_ps(vector1, vector2);
	float nums[4] = {};
	_mm_store_ps(nums, vector2);
	x = nums[0], y = nums[1], z = nums[2];
}

inline void Vector::operator/=(Vector b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps(0.f, b.z, b.y, b.x);
	vector2 = _mm_div_ps(vector1, vector2);
	float nums[4] = {};
	_mm_store_ps(nums, vector2);
	x = nums[0], y = nums[1], z = nums[2];
}

inline void Vector::operator*=(float b)
{
	__m128 vector1 = _mm_set_ps(0.f, z, y, x);
	__m128 vector2 = _mm_set_ps1(b);
	vector2 = _mm_add_ps(vector1, vector2);
	float nums[4] = {};
	_mm_store_ps(nums, vector2);
	x = nums[0], y = nums[1], z = nums[2];
}

inline void Vector::operator/=(float b)
{
	x /= b, y /= b, z /= b;
}

inline bool Vector::operator==(Vector b)
{
	return x == b.x && y == b.y && z == b.z;
}

inline bool Vector::operator!=(Vector b)
{
	return !(*this == b);
}

//матрицы(4 порядок)
// порядок по столбцам!
class Matrix
{
public:
	Matrix();
	Matrix(float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p);

	Matrix(float *arr); // loads from an array
	Matrix(float a);

	// самые необходимые матрицы при рендеринге)
	
	/// <summary>
	/// Матрица перемещения
	/// </summary>
	/// <param name="pos">Позиция в пространстве</param>
	/// <returns>матрица</returns>
	static Matrix Translate(Vector pos);

	/// <summary>
	/// Матрица вида
	/// </summary>
	/// <param name="pos">Позиция камеры</param>
	/// <param name="look">Направление камеры</param>
	/// <param name="up">upvector</param>
	/// <returns>матрица</returns>
	static Matrix Camera(Vector pos, Vector look, Vector up = Vector(0.f, 1.f, 0.f)); // камера

	/// <summary>
	/// Матрица проекции
	/// </summary>
	/// <param name="ar">Отношение ширины экрана к её высоте</param>
	/// <param name="fov">Угол обзора</param>
	/// <param name="nearZ">Ближайшая точка глубины</param>
	/// <param name="farZ">Дальняя точка глубины</param>
	/// <returns>матрица</returns>
	static Matrix Projection(float ar, float fov, float nearZ, float farZ); // проекция

	/// <summary>
	/// Вращение вокруг оси
	/// </summary>
	/// <param name="axis">Нормализованный вектор оси</param>
	/// <param name="angle">Угол вращения в градусах</param>
	/// <returns>матрица</returns>
	static Matrix RotateByAxis(Vector axis, float angle);

	//returns an array
	const float *Array();

	Matrix operator=(Matrix b);
	Matrix operator+(Matrix b);
	Matrix operator-(Matrix b);
	Matrix operator*(Matrix b);
	Vector operator*(float *b);
	Matrix operator*(float b);

	float mat[4][4];
};

// row-order
// row 0 = a b c d
// row 1 = e f g h
// row 2 = i j k l
// row 3 = m n o p

//column-order
// column 0 = a e i m
// column 1 = b f j n
// column 2 = c g k o
// column 3 = d h l p

// just makes identity matrix
__inline Matrix::Matrix()
{
	_mm_store_ps(mat[0], _mm_set_ps(0.f, 0.f, 0.f, 1.f));
	_mm_store_ps(mat[1], _mm_set_ps(0.f, 0.f, 1.f, 0.f));
	_mm_store_ps(mat[2], _mm_set_ps(0.f, 1.f, 0.f, 0.f));
	_mm_store_ps(mat[3], _mm_set_ps(1.f, 0.f, 0.f, 0.f));
}

__inline Matrix::Matrix(float a, float b, float c, float d,
	float e, float f, float g, float h,
	float i, float j, float k, float l,
	float m, float n, float o, float p)
{
	_mm_store_ps(mat[0], _mm_set_ps(m, i, e, a));
	_mm_store_ps(mat[1], _mm_set_ps(n, j, f, b));
	_mm_store_ps(mat[2], _mm_set_ps(o, k, g, c));
	_mm_store_ps(mat[3], _mm_set_ps(p, l, h, d));
}

__inline Matrix::Matrix(float* arr)
{
	_mm_store_ps(mat[0], _mm_load_ps(arr));
	_mm_store_ps(mat[1], _mm_load_ps(arr + 4));
	_mm_store_ps(mat[2], _mm_load_ps(arr + 8));
	_mm_store_ps(mat[3], _mm_load_ps(arr + 12));
}

__inline Matrix::Matrix(float a)
{
	__m128 temp = _mm_set_ps1(a);
	_mm_store_ps(mat[0], temp);
	_mm_store_ps(mat[1], temp);
	_mm_store_ps(mat[2], temp);
	_mm_store_ps(mat[3], temp);
}

__inline Matrix Matrix::Translate(Vector pos)
{
	Matrix matrix;
	_mm_store_ps(matrix.mat[3], _mm_set_ps(1.f, pos.z, pos.y, pos.x));
	return matrix;
}

__inline Matrix Matrix::Camera(Vector pos, Vector look, Vector up)
{
	Vector forward = Vector::Normalize(look - pos);
	Vector side = Vector::Normalize(Vector::cross(forward, up));
	Vector u = Vector::cross(side, forward);

	return Matrix(side.x, side.y, side.z, -Vector::Dot(side, pos),
				u.x, u.y, u.z, -Vector::Dot(u, pos),
				-forward.x, -forward.y, -forward.z, Vector::Dot(forward, pos),
				0.f, 0.f, 0.f, 1.f);
}

__inline Matrix Matrix::Projection(float ar, float _fov, float nearZ, float farZ)
{
	Matrix matrix(0.f);
	float tan_halfFov = tanf(_fov * TO_RADIANS * 0.5f);
	matrix.mat[0][0] = 1.f / (ar * tan_halfFov);
	matrix.mat[1][1] = 1.f / tan_halfFov;
	matrix.mat[2][2] = -(farZ + nearZ) / (farZ - nearZ);
	matrix.mat[2][3] = -1.f;
	matrix.mat[3][2] = -(2.f * farZ * nearZ) / (farZ - nearZ);
	return matrix;
}

inline Matrix Matrix::RotateByAxis(Vector axis, float angle)
{
	Matrix mat;
	float c = cosf(angle * TO_RADIANS);
	float s = sinf(angle * TO_RADIANS);
	float t = 1 - c;
	float x = axis.x, y = axis.y, z = axis.z;

	_mm_store_ps(mat.mat[0], _mm_set_ps(0.f, t * x * z - s * y, t * x * y + s * z, t * powf(x, 2) + c));
	_mm_store_ps(mat.mat[0], _mm_set_ps(0.f, t * y * z + s * x, t * powf(y, 2) + c, t * x * y - s * z));
	_mm_store_ps(mat.mat[0], _mm_set_ps(0.f, t * powf(z, 2) + c, t * y * z - s * x, t * x * z + s * y));
	_mm_store_ps(mat.mat[0], _mm_set_ps(1.f, 0.f, 0.f, 0.f));
	return mat;
}

__inline const float *Matrix::Array()
{
	return (const float*)mat;
}

inline Matrix Matrix::operator=(Matrix b)
{
	__m128 vector = _mm_load_ps(b.mat[0]);
	_mm_store_ps(mat[0], vector);
	vector = _mm_load_ps(b.mat[1]);
	_mm_store_ps(mat[1], vector);
	vector = _mm_load_ps(b.mat[2]);
	_mm_store_ps(mat[2], vector);
	vector = _mm_load_ps(b.mat[3]);
	_mm_store_ps(mat[3], vector);
	return *this;
}

__inline Matrix Matrix::operator+(Matrix b)
{
	Matrix matrix(0.f);
	_mm_store_ps(matrix.mat[0], _mm_add_ps(_mm_load_ps(mat[0]), _mm_load_ps(b.mat[0])));
	_mm_store_ps(matrix.mat[1], _mm_add_ps(_mm_load_ps(mat[1]), _mm_load_ps(b.mat[1])));
	_mm_store_ps(matrix.mat[2], _mm_add_ps(_mm_load_ps(mat[2]), _mm_load_ps(b.mat[2])));
	_mm_store_ps(matrix.mat[3], _mm_add_ps(_mm_load_ps(mat[3]), _mm_load_ps(b.mat[3])));
	return matrix;
}

__inline Matrix Matrix::operator-(Matrix b)
{
	Matrix matrix(0.f);
	_mm_store_ps(matrix.mat[0], _mm_sub_ps(_mm_load_ps(mat[0]), _mm_load_ps(b.mat[0])));
	_mm_store_ps(matrix.mat[1], _mm_sub_ps(_mm_load_ps(mat[1]), _mm_load_ps(b.mat[1])));
	_mm_store_ps(matrix.mat[2], _mm_sub_ps(_mm_load_ps(mat[2]), _mm_load_ps(b.mat[2])));
	_mm_store_ps(matrix.mat[3], _mm_sub_ps(_mm_load_ps(mat[3]), _mm_load_ps(b.mat[3])));
	return matrix;
}

// простое скалярное произведение
__inline Vector Matrix::operator*(float *b)
{
	__m128 vector = _mm_mul_ps(_mm_load_ps(mat[0]), _mm_set_ps1(b[0]));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[1]), _mm_set_ps1(b[1])));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[2]), _mm_set_ps1(b[2])));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[3]), _mm_set_ps1(b[3])));

	return Vector(vector);
}

__inline Matrix Matrix::operator*(Matrix b)
{
	Matrix matrix(0.f);
	// умножаем и складываем)
	__m128 temp = _mm_load_ps(b.mat[0]);
	__m128 vector = _mm_mul_ps(_mm_load_ps(mat[0]), _mm_shuffle_ps(temp, temp, 0x00));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[1]), _mm_shuffle_ps(temp, temp, 0x55)));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[2]), _mm_shuffle_ps(temp, temp, 0xaa)));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[3]), _mm_shuffle_ps(temp, temp, 0xff)));
	_mm_store_ps(matrix.mat[0], vector);

	temp = _mm_load_ps(b.mat[1]);
	vector = _mm_mul_ps(_mm_load_ps(mat[0]), _mm_shuffle_ps(temp, temp, 0x00));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[1]), _mm_shuffle_ps(temp, temp, 0x55)));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[2]), _mm_shuffle_ps(temp, temp, 0xaa)));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[3]), _mm_shuffle_ps(temp, temp, 0xff)));
	_mm_store_ps(matrix.mat[1], vector);

	temp = _mm_load_ps(b.mat[2]);
	vector = _mm_mul_ps(_mm_load_ps(mat[0]), _mm_shuffle_ps(temp, temp, 0x00));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[1]), _mm_shuffle_ps(temp, temp, 0x55)));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[2]), _mm_shuffle_ps(temp, temp, 0xaa)));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[3]), _mm_shuffle_ps(temp, temp, 0xff)));
	_mm_store_ps(matrix.mat[2], vector);

	temp = _mm_load_ps(b.mat[3]);
	vector = _mm_mul_ps(_mm_load_ps(mat[0]), _mm_shuffle_ps(temp, temp, 0x00));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[1]), _mm_shuffle_ps(temp, temp, 0x55)));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[2]), _mm_shuffle_ps(temp, temp, 0xaa)));
	vector = _mm_add_ps(vector, _mm_mul_ps(_mm_load_ps(mat[3]), _mm_shuffle_ps(temp, temp, 0xff)));
	_mm_store_ps(matrix.mat[3], vector);

	return matrix;
}

__inline Matrix Matrix::operator*(float b)
{
	Matrix matrix(0.f);
	_mm_store_ps(mat[0], _mm_mul_ps(_mm_load_ps(mat[0]), _mm_set_ps1(b)));
	_mm_store_ps(mat[1], _mm_mul_ps(_mm_load_ps(mat[1]), _mm_set_ps1(b)));
	_mm_store_ps(mat[2], _mm_mul_ps(_mm_load_ps(mat[2]), _mm_set_ps1(b)));
	_mm_store_ps(mat[3], _mm_mul_ps(_mm_load_ps(mat[3]), _mm_set_ps1(b)));
	return matrix;
}


//quaternion(for rotation)
class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	~Quaternion();

	Matrix CreateMat();
	const float* Array();

	void operator=(Quaternion quat);

	float x, y, z, w;
};

__inline Quaternion::Quaternion()
{
	x = y = z = w = 0.f;
}

__inline Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x, y = _y, z = _z, w = _w;
}

__inline Quaternion::~Quaternion()
{
}

__inline Matrix Quaternion::CreateMat()
{
	Matrix matrix;
	float* mat = (float*)&matrix;
	// Первая строка
	mat[0] = 1.0f - 2.0f * (y * y + z * z);
	mat[1] = 2.0f * (x * y + z * w);
	mat[2] = 2.0f * (x * z - y * w);
	mat[3] = 0.0f;
	// Вторая сторока
	mat[4] = 2.0f * (x * y - z * w);
	mat[5] = 1.0f - 2.0f * (x * x + z * z);
	mat[6] = 2.0f * (z * y + x * w);
	mat[7] = 0.0f;
	// Третья строка
	mat[8] = 2.0f * (x * z + y * w);
	mat[9] = 2.0f * (y * z - x * w);
	mat[10] = 1.0f - 2.0f * (x * x + y * y);
	mat[11] = 0.0f;
	// Четвертая строка
	mat[12] = 0;
	mat[13] = 0;
	mat[14] = 0;
	mat[15] = 1.0f;
	return matrix;
}

inline const float* Quaternion::Array()
{
	return &x;
}

inline void Quaternion::operator=(Quaternion quat)
{
	__m128 a = _mm_load_ps(quat.Array());
	_mm_store_ps(&x, a);
}

#ifdef _WIN32
#define ToVector(vec) (Vector&)vec
#define ToPxVector(vec) (PxVec3&)vec
#define ToQuat(quat) (Quaternion&)quat
#define ToPxQuat(quat) (PxQuat&)quat
#else
#define ToVector(vec) *(Vector*)&vec
#define ToPxVector(vec) *(PxVec3*)&vec
#define ToQuat(quat) *(Quaternion*)&quat
#define ToPxQuat(quat) *(PxQuat*)&quat
#endif

#endif