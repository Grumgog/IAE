#include "iaemath.h"

namespace IAE
{
    namespace math {

    real dot2Product(vect2_t first, vect2_t second)
    {
        return first[0]*second[0] + first[1]*second[1];
    }

    void setVector2(vect2_t vector, real x, real y)
    {
        vector[0] = x;
        vector[1] = y;
    }

    void clearVector2(vect2_t vector)
    {
        vector[0] = 0;
        vector[1] = 0;
    }

    void copyVector2(vect2_t dest, vect2_t src)
    {
        dest[0] = src[0];
        dest[1] = src[1];
    }

    void normalizeVector2(vect2_t vector)
    {
        real lenght = lenghtVector2(vector);
        if(lenght)
        {
            lenght = 1/lenght;
            vector[0]*= lenght;
            vector[1]*= lenght;
        }
    }

    real lenghtVector2(vect2_t vector)
    {
        return sqrt(dot2Product(vector, vector));
    }

    void addVector2(vect2_t a, vect2_t b)
    {
        a[0]+=b[0];
        a[1]+=b[1];
    }

    void subVector2(vect2_t a, vect2_t b)
    {
        a[0]-=b[0];
        a[1]-=b[1];
    }

    bool equalVector2(vect2_t a, vect2_t b)
    {
        return (a[0]==b[0]) && (a[1]==b[1]);
    }

    void rotateVector2(vect2_t point, real angle)
    {
        real xn = point[0] * cos(angle) - point[1] * sin(angle);
        real yn = point[0] * sin(angle) + point[1] * cos(angle);
        setVector2(point, xn, yn);
    }

    void scaleVector2(vect2_t vector, real scale)
    {
        vector[0]*=scale;
        vector[1]*=scale;
    }

    // 3d-vectors
    real dot3Product(vect3_t first, vect3_t second)
    {
        return first[0]*second[0] + first[1]*second[1] + first[2]*second[2];
    }

    void setVector3(vect3_t vector, real x, real y, real z)
    {
        vector[0] = x;
        vector[1] = y;
        vector[2] = z;
    }

    void clearVector3(vect3_t vector)
    {
        vector[0] = vector[1] = vector[2] = 0;
    }

    void copyVector3(vect3_t dest, vect3_t src)
    {
        dest[0] = src[0];
        dest[1] = src[1];
        dest[2] = src[2];
    }

    void normalizeVector3(vect3_t vector)
    {
        real lenght = lenghtVector3(vector);
        if(lenght)
        {
            lenght = 1.0 / lenght;
            vector[0] *= lenght;
            vector[1] *= lenght;
            vector[2] *= lenght;
        }
    }

    real lenghtVector3(vect3_t vector)
    {
        return sqrt(dot3Product(vector, vector));
    }

    void addVector3(vect3_t a, vect3_t b)
    {
        a[0]+=b[0];
        a[1]+=b[1];
        a[2]+=b[2];
    }

    void subVector3(vect3_t a, vect3_t b)
    {
        a[0]-=b[0];
        a[1]-=b[1];
        a[2]-=b[2];
    }

    bool equalVector3(vect3_t a, vect3_t b)
    {
        return (a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]);
    }

    void rotateVector3X(vect3_t point, real angle)
    {
        real yn = point[1] * cos(angle) - point[2] * sin(angle);
        real zn = point[1] * sin(angle) + point[2] * cos(angle);
        setVector3(point, point[0], yn, zn);
    }

    void rotateVector3Y(vect3_t point, real angle)
    {
        real xn = point[0] * cos(angle) - point[2] * sin(angle);
        real zn = point[0] * sin(angle) + point[2] * cos(angle);
        setVector3(point, xn, point[1], zn);
    }

    void rotateVector3Z(vect3_t point, real angle)
    {
        real xn = point[0] * cos(angle) - point[1] * sin(angle);
        real yn = point[0] * sin(angle) + point[1] * cos(angle);
        setVector3(point, xn, yn, point[2]);
    }

    void scaleVector3(vect3_t vector, real scale)
    {
        vector[0]*=scale;
        vector[1]*=scale;
        vector[2]*=scale;
    }

    void mulVector3(vect3_t a, vect3_t b, vect3_t dest)
    {
        dest[0] = a[1]*b[2] - a[2]*b[2];
        dest[1] = a[2]*b[0] - a[0]*b[2];
        dest[2] = a[0]*b[1] - a[1]*b[0];
    }

    real mixVector3(vect3_t a, vect3_t b, vect3_t c)
    {
        // this is det of matrix 3x3
        real answer = 0;
        answer = a[0]*b[1]*c[2] + a[1]*b[2]*c[0] + a[2]*b[0]*c[1];
        answer+= -(a[2]*b[1]*c[0]) - (a[0]*b[2]*c[1]) - (a[1]*b[0]*c[2]);
        return answer;
    }

    real dot4Product(vect4_t first, vect4_t second)
    {
        return first[0]*second[0] + first[1]*second[1] +
               first[2]*second[2] + first[3]*second[3];
    }

    void setVector4(vect4_t vector, real x, real y, real z, real t)
    {
        vector[0] = x;
        vector[1] = y;
        vector[2] = z;
        vector[3] = t;
    }

    void clearVector4(vect4_t vector)
    {
        vector[0] = vector[1] = vector[2] = vector[3] = 0;
    }

    void copyVector4(vect4_t dest, vect4_t src)
    {
        dest[0] = src[0];
        dest[1] = src[1];
        dest[2] = src[2];
        dest[3] = src[3];
    }

    void normalizeVector4(vect4_t vector)
    {
        real lenght = lenghtVector4(vector);
        if(lenght)
        {
            lenght = 1/lenght;
            vector[0] *= lenght;
            vector[1] *= lenght;
            vector[2] *= lenght;
            vector[3] *= lenght;
        }
    }

    real lenghtVector4(vect4_t vector)
    {
        return sqrt(dot4Product(vector, vector));
    }

    void addVector4(vect4_t a, vect4_t b)
    {
        a[0] += b[0];
        a[1] += b[1];
        a[2] += b[2];
        a[3] += b[3];
    }

    void subVector4(vect4_t a, vect4_t b)
    {
        a[0] -= b[0];
        a[1] -= b[1];
        a[2] -= b[2];
        a[3] -= b[3];
    }

    bool equalVector4(vect4_t a, vect4_t b)
    {
        return (a[0] == b[0]) && (a[1] == b[1]) &&
               (a[2] == b[2]) && (a[3] == b[3]);
    }

    void scaleVector4(vect4_t vector, real scale)
    {
        vector[0] *= scale;
        vector[1] *= scale;
        vector[2] *= scale;
        vector[3] *= scale;
    }

    // Матрицы 2x2
    void clearMatrix2(matrix2_t m)
    {
         for(int j = 0; j<2; j++)
             for(int i = 0; i<2; i++)
                 m[j][i] = 0;
    }

    void copyMatrix2(matrix2_t dest, matrix2_t src)
    {
         for(int j = 0; j<2; j++)
             for(int i = 0; i<2; i++)
                 dest[j][i] = src[j][i];
    }

    void transponizeMatrix2(matrix2_t m)
    {
         matrix2_t res;
         for(int j = 0; j<2; j++)
             for(int i = 0; i<2; i++)
                 res[i][j] = m[j][i];
         copyMatrix2(m, res);
    }

    real detMatrix2(matrix2_t m)
    {
         return m[0][0]*m[1][1] - m[0][1]*m[1][0];
    }

    void productMatrix2(matrix2_t m, real n)
    {
         for(int j = 0; j<2; j++)
             for(int i = 0; i<2; i++)
                 m[j][i] *= n;
    }

    void addMatrix2(matrix2_t a, matrix2_t b)
    {
         for(int j = 0; j<2; j++)
             for(int i = 0; i<2; i++)
                 a[j][i] += b[j][i];
    }

    void subMatrix2(matrix2_t a, matrix2_t b)
    {
        for(int j = 0; j<2; j++)
            for(int i = 0; i<2; i++)
                a[j][i] -= b[j][i];
    }

    void mulMatrix2(matrix2_t a, matrix2_t b, matrix2_t dest)
    {
        clearMatrix2(dest);

        for(int m = 0; m<2; m++)
        for(int j = 0; j<2; j++)
            for(int i = 0; i<2; i++)
                dest[i][j] += a[i][m]*b[m][j];
    }

    void getRowMatrix2(matrix2_t m, int j, vect2_t dest)
    {
         for(int i = 0; i<2; i++)
             dest[i] = m[j][i];
    }
    void getColMatrix2(matrix2_t m, int i, vect2_t dest)
    {
         for(int j = 0; j<2; j++)
             dest[j] = m[j][i];
    }

    void setRowMatrix2(matrix2_t m, int j, vect2_t src)
    {
         for(int i = 0; i < 2; i++)
            m[j][i] = src[i];
    }

    void setColMatrix2(matrix2_t m, int i, vect2_t src)
    {
         for(int j = 0; j < 2; j++)
            m[j][i] = src[j];
    }

    // Матрицы 3x3
    void clearMatrix3(matrix3_t m)
    {
         for(int j = 0; j<3; j++)
            for(int i = 0; i<3; i++)
                m[j][i] = 0;
    }

    void copyMatrix3(matrix3_t dest, matrix3_t src)
    {
        for(int j = 0; j<3; j++)
           for(int i = 0; i<3; i++)
               dest[j][i] = src[j][i];
    }

    void transponizeMatrix3(matrix3_t m)
    {
         matrix3_t res;
         for(int j = 0; j<3; j++)
            for(int i = 0; i<3; i++)
                res[j][i] = m[i][j];
         copyMatrix3(m, res);
    }

    real detMatrix3(matrix3_t m)
    {
        // Правило Саррюса
        return m[0][0]*m[1][1]*m[2][2]
             + m[0][1]*m[1][2]*m[2][0]
             + m[0][2]*m[1][0]*m[2][1]
             - m[0][2]*m[1][1]*m[2][1]
             - m[0][0]*m[1][2]*m[2][1]
             - m[0][1]*m[1][0]*m[2][2];
    }

    void productMatrix3(matrix3_t m, real n)
    {
        for(int j = 0; j<3; j++)
           for(int i = 0; i<3; i++)
               m[j][i] *= n;
    }

    void addMatrix3(matrix3_t a, matrix3_t b)
    {
        for(int j = 0; j<3; j++)
           for(int i = 0; i<3; i++)
               a[j][i] += b[j][i];
    }
    void subMatrix3(matrix3_t a, matrix3_t b)
    {
        for(int j = 0; j<3; j++)
           for(int i = 0; i<3; i++)
               a[j][i] -= b[j][i];
    }

    void mulMatrix3(matrix3_t a, matrix3_t b, matrix3_t dest)
    {
        clearMatrix3(dest);

        for(int m = 0; m<3; m++)
        for(int j = 0; j<3; j++)
            for(int i = 0; i<3; i++)
                dest[i][j] += a[i][m]*b[m][j];
    }

    void getRowMatrix3(matrix3_t m, int j, vect3_t dest)
    {
         for(int i = 0; i<3; i++)
            dest[i] -= m[j][i];
    }

    void getColMatrix3(matrix3_t m, int i, vect3_t dest)
    {
        for(int j = 0; j<3; j++)
           dest[j] -= m[j][i];
    }

    void setRowMatrix3(matrix3_t m, int j, vect3_t src)
    {
        for(int i = 0; i < 3; i++)
           m[j][i] = src[i];
    }

    void setColMatrix3(matrix3_t m, int i, vect3_t src)
    {
        for(int j = 0; j < 3; j++)
           m[j][i] = src[j];
    }

    // Матрицы 4x4
    void clearMatrix4(matrix4_t m)
    {
        for(int j = 0; j<4; j++)
           for(int i = 0; i<4; i++)
               m[j][i] = 0;
    }

    void copyMatrix4(matrix4_t dest, matrix4_t src)
    {
        for(int j = 0; j<4; j++)
           for(int i = 0; i<4; i++)
               dest[j][i] = src[j][i];
    }

    void transponizeMatrix4(matrix4_t m)
    {
        matrix4_t res;

        for(int j = 0; j<4; j++)
           for(int i = 0; i<4; i++)
               res[j][i] = m[i][j];
        copyMatrix4(m, res);
    }

    void productMatrix4(matrix4_t m, real n)
    {
        for(int j = 0; j<4; j++)
            for(int i = 0; i<4; i++)
                m[i][j] *= n;
    }

    void addMatrix4(matrix4_t a, matrix4_t b)
    {
        for(int j = 0; j<4; j++)
            for(int i = 0; i<4; i++)
                a[i][j] += b[i][j];
    }

    void subMatrix4(matrix4_t a, matrix4_t b)
    {
        for(int j = 0; j<4; j++)
            for(int i = 0; i<4; i++)
                a[i][j] -= b[i][j];
    }

    void mulMatrix4(matrix4_t a, matrix4_t b, matrix4_t dest)
    {
        clearMatrix4(dest);

        for(int m = 0; m<4; m++)
        for(int j = 0; j<4; j++)
            for(int i = 0; i<4; i++)
                dest[i][j] += a[i][m]*b[m][j];
    }

    void getRowMatrix4(matrix4_t m, int j, vect4_t dest)
    {
        for(int i = 0; i<4; i++)
           dest[i] -= m[j][i];
    }

    void getColMatrix4(matrix4_t m, int i, vect4_t dest)
    {
        for(int j = 0; j<4; j++)
           dest[j] -= m[j][i];
    }

    void setRowMatrix4(matrix4_t m, int j, vect4_t src)
    {
        for(int i = 0; i < 4; i++)
           m[j][i] = src[i];
    }

    void setColMatrix4(matrix4_t m, int i, vect4_t src)
    {
        for(int j = 0; j < 4; j++)
           m[j][i] = src[j];
    }

    std::vector<real> tabulateFunction(function_t f, real begin, real end, real step)
    {
        std::vector<real> res;

        if(end>begin && step<0) step*=-1;
        if(end<begin && step>0) step*=-1;
        if(step == 0)           return res;

        for(real var = begin; var <= end; var+= step)
        {
            res.push_back(f(var));
        }
        return res;
    }

    std::vector<real> tabulateFunction(function_t f, std::vector<real> values)
    {
        std::vector<real> res;
        for(std::vector<real>::iterator i = values.begin(); i != values.end(); i++)
        {
            res.push_back(f(*i));
        }
        return res;
    }

    }
}
