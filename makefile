##
# Boost
#
# @file
# @version 0.1

PYTHON_INC = /usr/include/python2.7
PYTHON_LIB = /usr/lib/python2.7/config

BOOST_INC = /usr/include/boost/
BOOST_LIB = /usr/lib/

# compile mesh classes
TARGET = fast

all: $(TARGET).so

run: all
	python2 matrix.py

$(TARGET).so: $(TARGET).o
#	g++ -shared -Wl,--export-dynamic $(TARGET).o -L$(BOOST_LIB) -lboost_python39 -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -o $(TARGET).so
	g++ -shared $(TARGET).o -L$(PYTHON_LIB) -L$(BOOST_LIB) -lboost_python27 -lboost_numpy27 -o $(TARGET).so

$(TARGET).o: $(TARGET).cpp
	g++ -I$(PYTHON_INC) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp
# g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp

clean:
	rm -f $(TARGET).o $(TARGET).so

.PHONY: clean


# end
# g++ -o my_test.so -fPIC -shared my_test.cpp \
# -I/usr/include/python3.5  `# for pyconfig.h` \
# -L/usr/lib/python3.5/config-3.5m-x86_64-linux-gnu  `# for libpython3.5 or libpython3.5m` \
# -lpython3.5  \
# -I/usr/local/boost_1_71_0/include  `# for Boost header files` \
# -L/usr/local/boost_1_71_0/lib  `# for Boost binary files` \
# -lboost_python35 -lboost_numpy35
