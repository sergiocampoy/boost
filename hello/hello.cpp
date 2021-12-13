#include <boost/python.hpp>
#include <iostream>

/**
* Función para devolver el saludo
*/
char const*saluda()
{
   return "Hello World";
}

/**
* Macro para declarar el módulo y hacer la llamada a las funciones
*/
BOOST_PYTHON_MODULE(hello)
{
    using namespace boost::python;
    def("saluda", saluda);
}



