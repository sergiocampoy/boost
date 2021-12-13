//obtenemos las librerias de boost
#include <boost/python/numpy.hpp>
#include <boost/scoped_array.hpp>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
//indico el espacio de nombres para usar python y numpy
namespace p = boost::python;
namespace np = boost::python::numpy;


/**
 * función que suma todos los elementos del array y como salida devuelve dicha suma y 
 * el numero de elementos del array.
 **/
void contador_sumador(double* array, int n, double output[]){
	double sum = 0.0;

	//aplica la suma
	for(int i=0; i<n; ++i){
		sum += array[i];
	}

	//indico los valores de salida
	output[0] = sum;
	output[1] = n;
}

/**
 * contiene algunos traductores para garantizar que la mayoria de los tipos de datos 
 * se conviertan en punteros y los que no.
 * Esta función contenedora transforma la información que recibe de python, en el tipo 
 * equivalente en C++, procesa dichos datos llamando a las funciones creadas por nosotros
 * en C++ y transforma dicho resultado en el tipo equivalente en Python.
 **/
np::ndarray wrap_contador_sumador(np::ndarray const & array){
	//nos aseguramos que son de tipo double los valores, si no coinciden genero una excepción
	if(array.get_dtype() != np::dtype::get_builtin<double>()){
		PyErr_SetString(
			PyExc_TypeError, 
			"El array tiene un tipo de dato incorrecto, solo acepta el tipo double"
			);
		p::throw_error_already_set();
	}

	//creamos el objeto estatico double de tamaño 2, que contendrá el resultado de la función
	static double output[2];

	//llamamos a la función para que calculo con los datos que recibe de python
	//con reinterpret_cast<double*> hacemos un casting al tipo (double *)	
	contador_sumador(reinterpret_cast<double*>(array.get_data()), array.shape(0), output);

	//convertimos la salida en un array de tamaño 2
	np::dtype dt = np::dtype::get_builtin<double>();//tipo de datos a almacenar
	p::tuple shape = p::make_tuple(2);//tamaño a tener el array
	p::tuple stride = p::make_tuple(sizeof(double));//indicamos el tamaño del tipo double

	//creo el array con los datos
	np::ndarray result = np::from_data(output, dt, shape, stride, p::object());

	return result;
}

/**
 * creamos la nueva libreria para usarse en python, el nombre de la librería tiene que
 * llamarse igual que como lo hemos llamado en el archivo cpp.
 * Esta función sirve para inicializar los componentes Python y NumPy, y declarar la función
 * wrap_contador_sumador bajo el nombre contador_sumador
 **/
BOOST_PYTHON_MODULE(contador_suma){
	Py_Initialize();
	np::initialize();
	p::def("contador_sumador", wrap_contador_sumador);
}