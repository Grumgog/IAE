// Зачатки тестовой утилиты для IAE
#include <iostream> // Стандартные потоки ввода-вывода
#include "iaemath.h" // Ядро математической библиотеки
#include "iaesys.cpp"
using namespace std; // Стандартное пространство имен
using namespace IAE;
using namespace math; // Пространство имен ядра математической библиотеки
using namespace sys;
#include "utility.h"
using namespace utility;

#define SCALAR 3.0f

int main()
{
	setlocale(0, "");

        vect2_t point;
        clearVector2(point);
        cout << "Начало работы с вектором vect2_t point: " << "(" << point[0] << ", " << point[1] << ")" << endl;
        setVector2(point, 12.0, 7);
        real l = lenghtVector2(point);
        cout << "Длина вектора point: " << l;
        cout << "(" << point[0] << ", " << point[1] << ")" << endl;
        normalizeVector2(point);
        cout << "(" << point[0] << ", " << point[1] << ")" << endl;
        l = lenghtVector2(point);
        cout << "Длина вектора point: " << l << endl;

        vect2_t apoint;
        setVector2(apoint, 1.41, 0);
        real angle = DEG2RAD(45);
        rotateVector2(apoint, angle);
        cout << "now vector around is (" <<apoint[0] << ", " << apoint[1] << ");\n";
        vect3_t d3point;
        clearVector3(d3point);
        setVector3(d3point, 1, 1, 1);
        rotateVector3X(d3point, 3.1415926);
        cout << "(" << d3point[0] << ", " << d3point[1] << ", "  << d3point[2] << ")" << endl;

        vect3_t f;
        vect3_t d;
        vect3_t u;

        setVector3(f, 2, 5, 8);
        setVector3(d, 4, 2, -1);
        setVector3(u, 9, 0, 1);

        cout << "det is " << mixVector3(f, d, u) << endl;


        vect4_t d4VECTORIZE;
        clearVector4(d4VECTORIZE);

        matrix2_t matrix;
        clearMatrix2(matrix);
        #define pm2(m) for(int j = 0; j<2; j++){for(int i = 0; i<2; i++) cout << m[j][i] << " "; cout << endl;}
        pm2(matrix);

        setElement(matrix, 0, 0, 4);
        setElement(matrix, 0, 1, 5);
        setElement(matrix, 1, 0, 6);
        setElement(matrix, 1, 1, 7);

        matrix2_t dop;
        clearMatrix2(dop);
        setElement(dop, 0, 0, 6);
        setElement(dop, 0, 1, 9);
        setElement(dop, 1, 0, 1);
        setElement(dop, 1, 1, -3);

        matrix2_t res;

        clearMatrix2(res);
        mulMatrix2(matrix, dop, res);

        cout << "\nmul of matrix:\n";
        pm2(res);
        transponizeMatrix2(res);
        pm2(res);

        cout << "det of matrix is: " << detMatrix2(matrix);


        iaeFileID file;
        file = getFileID("test.cpp", read);
        char buff[1000];
        fread(file, buff, 500);
        buff[500] = '\0';
        cout << "File test.cpp" << buff << endl;
		cout << "File pos is " << getFilePos(file) << endl;
		setFilePos(file, 0, begin);
		cout << "File pos now is " << getFilePos(file) << endl << endl;

		cout << "utility library test..." << endl;

		vector<string> listPathes;
		listPathes = getPathes("C:\\hello\\lib\\outro.txt");

		for(int i = 0; i < listPathes.size(); i++)
            cout << listPathes[i] << endl;


        cout << "slice of string!" << endl;

        string tale = "live and was big man";

        cout << "slice from 1 to 4 is " << sliceString(tale, 1, 2000) << endl;

	return 0;
}
