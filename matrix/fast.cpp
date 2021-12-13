#include <iostream>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace p = boost::python;
namespace np = boost::python::numpy;

/**
 * @brief Función que multiplica dos matrices en forma de array
 *
 * @param a Matriz primera en forma de array
 * @param ax Número de filas de la primera matriz
 * @param ay Número de columnas de la primera matriz
 *
 * @param b Matriz segunda en forma de array
 * @param bx Número de filas de la segunda matriz
 * @param by Número de columnas de la segunda matriz
 *
 * @return r Matriz resultado en forma de array
 * @return rx Número de filas de la matriz resultado
 * @return ry Número de columnas de la matriz resultado
 */
void cmatmul(double*  a, int  ax, int  ay,
             double*  b, int  bx, int  by,
             double*& r, int& rx, int& ry) {
    // Inicia la matriz resultado a la matriz nula
    r = nullptr;
    rx = -1;
    ry = -1;

    if (ay == bx) {
        // Se puede realizar la multiplicación
        // Crea la matriz resultado
        rx = ax;
        ry = by;
        r = new double[rx*ry];

        // Realiza la multiplicación
        for (int i = 0; i < rx; i++) {
            for (int j = 0; j < ry; j++) {
                r[rx*i + j] = 0;
                for (int k = 0; k < ay; k++) {
                    r[rx*i + j] += a[ax*i + k] * b[bx*k + j];
                }
            }
        }
    }
}

/**
 * @brief Función que multiplica dos matrices de python
 * @param a Matriz primera
 * @param b Matriz segunda
 * @return Matriz resultado de multiplicar la primera por la segunda
 */
np::ndarray matmul(np::ndarray& a, np::ndarray b) {
    // Inicializa la matriz resultado como matriz nula
    double* r = nullptr;
    int rx = -1;
    int ry = -1;

    // Convierte las matrices de python a array de c++
    double* aa = reinterpret_cast<double*>(a.get_data());
    int ax = a.shape(0);
    int ay = a.shape(1);
    double* bb = reinterpret_cast<double*>(b.get_data());
    int bx = b.shape(0);
    int by = b.shape(1);

    // Realiza la multiplicación
    cmatmul(aa, ax, ay,
            bb, bx, by,
            r,  rx, ry);

    // Convierte la matriz resultado a python
    np::dtype dt = np::dtype::get_builtin<double>();
    p::tuple shape = p::make_tuple(rx, ry);
    p::tuple stride = p::make_tuple(rx*sizeof(double), sizeof(double));
    p::object own;
    np::ndarray res = np::from_data(r, dt, shape, stride, own);

    return res;
}

// Exporta la función matmul para que se pueda usar desde Python
BOOST_PYTHON_MODULE(fast) {
    // Inicializa python y numpy
    Py_Initialize();
    np::initialize();
    // Exporta matmul
    def("matmul", matmul);
}
