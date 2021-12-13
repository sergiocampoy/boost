#include <boost/python/numpy.hpp>
#include <boost/scoped_array.hpp>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;
namespace p = boost::python;
namespace np = boost::python::numpy;

/**
* Función que multiplica todos los elementos del array por dos
*/
void multiplica(double* array, int n)
{

  for(int i=0 ; i<n ; i++) {
    array[i] *= 2;
  }

}

/**
* Función encargada de realizar el paso de datos de python a c++
*/
np::ndarray convertTypes(np::ndarray &array){

  static double output[2];

  multiplica(reinterpret_cast<double*>(array.get_data()), array.shape(0));

  np::dtype dt =np::dtype::get_builtin<double>();
  p::tuple shape =p::make_tuple(2);
  p::tuple stride =p::make_tuple(sizeof(double));

  np::ndarray result = np::from_data(output, dt, shape, stride, p::object());
 
  return result;
}

/**
* Macro para declarar el módulo y hacer la llamada a las funciones
*/
BOOST_PYTHON_MODULE(multiplica)
{
    using namespace boost::python;
    Py_Initialize();
    np::initialize();
    def("multiplica", convertTypes);

}
