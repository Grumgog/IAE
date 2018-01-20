#ifndef IAEMATH
#define IAEMATH
#include <math.h>
#include "iostream"
#include "iaetypes.h"
#include "iostream"
using namespace std;
/*--------- Модуль IAEMATH -------------
- Модуль содержит низкоуровневые операции с основными алгебраическими объектами
- (Матрицы, векторы). Основной код помещен пространство имен IAE_math.
- подробную информацию можно найти в файле iaemath.txt в катологе doc
- Автор: Никонов Василий (grumgog@gmail.com)
- 29.05.2017
*/

// Macros section
#define ANGLEMOD(angle) ((angle) - 360.0 * floor((angle)/360.0f))
#define DEG2RAD(angle) ((angle) * (M_PI/180.0f))
#define RAD2DEG(angle) ((angle) * (180.0f/M_PI))

namespace IAE
{
    namespace math {

    //Модуль объявляющий основные математические объекты и операции над ними
    typedef double real; // Вещественный двойной точности
    typedef real vect_t; // Вектор
    // Основные алгебраические объекты
    // Вектора
    typedef vect_t vect2_t[2];
    typedef vect_t vect3_t[3];
    typedef vect_t vect4_t[4];

    // Операции над векторами
    // 2d vectors
    real dot2Product(vect2_t first, vect2_t second);
    void setVector2(vect2_t vector, real x, real y);
    void clearVector2(vect2_t vector);
    void copyVector2(vect2_t dest, vect2_t src);
    void normalizeVector2(vect2_t vector);
    real lenghtVector2(vect2_t vector);
    void addVector2(vect2_t a, vect2_t b);
    void subVector2(vect2_t a, vect2_t b);
    bool equalVector2(vect2_t a, vect2_t b);
    void rotateVector2(vect2_t point, real angle);
    void scaleVector2(vect2_t vector, real scale);

    // 3d-vectors
    real dot3Product(vect3_t first, vect3_t second);
    void setVector3(vect3_t vector, real x, real y, real z);
    void clearVector3(vect3_t vector);
    void copyVector3(vect3_t dest, vect3_t src);
    void normalizeVector3(vect3_t vector);
    real lenghtVector3(vect3_t vector);
    void addVector3(vect3_t a, vect3_t b);
    void subVector3(vect3_t a, vect3_t b);
    bool equalVector3(vect3_t a, vect3_t b);
    void rotateVector3X(vect3_t point, real angle);
    void rotateVector3Y(vect3_t point, real angle);
    void rotateVector3Z(vect3_t point, real angle);
    void scaleVector3(vect3_t vector, real scale);
    void mulVector3(vect3_t a, vect3_t b, vect3_t dest);
    real mixVector3(vect3_t a, vect3_t b, vect3_t c);

    // 4d-vectors operations
    real dot4Product(vect4_t first, vect4_t second);
    void setVector4(vect4_t vector, real x, real y, real z, real t);
    void clearVector4(vect4_t vector);
    void copyVector4(vect4_t dest, vect4_t src);
    void normalizeVector4(vect4_t vector);
    real lenghtVector4(vect4_t vector);
    void addVector4(vect4_t a, vect4_t b);
    void subVector4(vect4_t a, vect4_t b);
    bool equalVector4(vect4_t a, vect4_t b);
    void scaleVector4(vect4_t vector, real scale);

    // Матрицы
    typedef real matrixElement;
    typedef matrixElement matrix2_t[2][2];
    typedef matrixElement matrix3_t[3][3];
    typedef matrixElement matrix4_t[4][4];

    // Операции над ними
    // Объявлен макрос заместо функции, так как шаблоны будут генерировать много мусора
    // В памяти программы...
    // Также этот макрос может быть использован для многих видов матриц
    // Однако он не является безопасным, так как не проверяет размеры матрицы
    /*Macros: setElement
      param:
      @m - matrix
      @j - row
      @i - column
      @el - element for assign
    */
    #define setElement(m, j, i, el) (m[j][i] = el)

    // Матрицы 2x2
    void clearMatrix2(matrix2_t m);
    void copyMatrix2(matrix2_t dest, matrix2_t src);
    void transponizeMatrix2(matrix2_t m);
    real detMatrix2(matrix2_t m);
    void productMatrix2(matrix2_t m, real n);
    void addMatrix2(matrix2_t a, matrix2_t b);
    void subMatrix2(matrix2_t a, matrix2_t b);
    void mulMatrix2(matrix2_t a, matrix2_t b, matrix2_t dest);
    void getRowMatrix2(matrix2_t m, int j, vect2_t dest);
    void getColMatrix2(matrix2_t m, int i, vect2_t dest);
    void setRowMatrix2(matrix2_t m, int j, vect2_t src);
    void setColMatrix2(matrix2_t m, int i, vect2_t src);

    // Матрицы 3x3
    void clearMatrix3(matrix3_t m);
    void copyMatrix3(matrix3_t dest, matrix3_t src);
    void transponizeMatrix3(matrix3_t m);
    real detMatrix3(matrix3_t m);
    void productMatrix3(matrix3_t m, real n);
    void addMatrix3(matrix3_t a, matrix3_t b);
    void subMatrix3(matrix3_t a, matrix3_t b);
    void mulMatrix3(matrix3_t a, matrix3_t b, matrix3_t dest);
    void getRowMatrix3(matrix3_t m, int j, vect3_t dest);
    void getColMatrix3(matrix3_t m, int i, vect3_t dest);
    void setRowMatrix3(matrix3_t m, int j, vect3_t src);
    void setColMatrix3(matrix3_t m, int i, vect3_t src);

    // Матрицы 4x4
    void clearMatrix4(matrix4_t m);
    void copyMatrix4(matrix4_t dest, matrix4_t src);
    void transponizeMatrix4(matrix4_t m);
    void productMatrix4(matrix4_t m, real n);
    void addMatrix4(matrix4_t a, matrix4_t b);
    void subMatrix4(matrix4_t a, matrix4_t b);
    void mulMatrix4(matrix4_t a, matrix4_t b, matrix4_t dest);
    void getRowMatrix4(matrix4_t m, int j, vect4_t dest);
    void getColMatrix4(matrix4_t, int i, vect4_t dest);
    void setRowMatrix4(matrix4_t m, int j, vect4_t src);
    void setColMatrix4(matrix4_t m, int i, vect4_t src);

    // Всякие вспомогательные функции
    // Табулирование функции
    std::vector<double> tabulateFunction(function_t f, real begin, real end, real step);
    std::vector<real> tabulateFunction(function_t f, std::vector<real> values);

    }
}
#endif // IAEMATH
