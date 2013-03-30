/****************************************************************************
FileName     [ Matrix.h ]
PackageName  [ HW1.2.P2 ]
Synopsis     [ Class definitions for matrix in HW1.2 of DSnP class ]
Author       [ Chung-Yang (Ric) Huang ]
Copyright    [ Copyleft(c) 2010 LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;
class Vector
{
public:
   Vector(unsigned size = 0) { 
	_data=new float[size];
	_size=size;
   } // TODO
   
   void VchangeSize(unsigned size){
	delete []_data;
	_data=new float[size];
	_size=size;
   }

   ~Vector() { 
	   
   delete []_data;
   } // TODO: need to release all the memory

   unsigned size() const { 
	   return _size; }

   // cerr an error message if i >= _size; return garbage
  float& operator[] (unsigned i) { 
	if (i <0 || i> _size){
		cout<<"Illegal row index";
		return *(_data);
		}
	else return *(_data+i);
  } // TODO
   
   const float& operator[] (unsigned i) const { 
   	if (i <0 || i> _size){
		cout<<"Illegal row index";
		return *(_data);
		}
	else return *(_data+i);
   
   } // TODO

private:
   unsigned     _size;  // number of elements
   float    *_data;  // dynamic array
};



class Matrix
{
public:
   Matrix(unsigned numRows = 0, unsigned numColumns = 0) {
	   _data=new Vector[numRows];
	   for(unsigned i =0 ; i <numRows;i++)
			(*(_data+i)).VchangeSize(numColumns);
	   _nRows=numRows;
  }

  Matrix(const Matrix& m) { 
	_data=new Vector[m.rows()];
	   for(unsigned i =0 ; i <m.rows();i++)
			(*(_data+i)).VchangeSize(m.columns());
	   _nRows=m.rows();

		 for (unsigned i = 0; i < _nRows; i++)
         for (unsigned j = 0; j <  m.columns(); j++)
         _data[i][j]=m[i][j];

  } // TODO: copy constructor
   ~Matrix() { 
		delete []_data;
   } 
   // TODO: need to release all the memory
   unsigned rows() const { 
	   return _nRows; }
   unsigned columns() const { 
	   return (_nRows? _data[0].size(): 0); }

   // cerr an error message if i >= _nRows; return garbage
   Vector& operator[] (unsigned i) { 
	if (i <0 || i> _nRows){
		cout<<"Illegal row index";
		return *(_data);
		}
	else return *(_data+i);
   } // TODO
   const Vector& operator[] (unsigned i) const { 
	if (i <0 || i> _nRows){
		cout<<"Illegal row index";
		return *(_data);
		}
	else return *(_data+i);
   } // TODO
   // TODO
   float maxElm() const {
      float d = 0;
      for (unsigned i = 0; i < _nRows; ++i)
         for (unsigned j = 0, n = columns(); j < n; ++j)
            if (d < _data[i][j]) d = _data[i][j];
      return d;
	}

   // If matrix sizes do not match, cerr a message return a copy of (*this)
 Matrix operator + (const Matrix& m) const {
     if((_nRows!=m.rows())||(columns()!=m.columns()))
	 {
		 cout<<"matrix sizes do not match"<<endl;
	 return *this;
	 }
     else 
	 {
	 Matrix n(*this);
	   for (unsigned i = 0; i < _nRows; i++)
         for (unsigned j = 0; j < columns(); j++)
			n[i][j]=n[i][j]+m[i][j];
	 return n;
	 }
  } // TODO

   // If matrix sizes do not match, cerr a message return (*this)
  Matrix& operator += (const Matrix& m) { 
     if((_nRows!=m.rows())||(columns()!=m.columns()))
	 {
		 cout<<"matrix sizes do not match"<<endl;
	 return *this;
	 }
     else 
	 {
	   for (unsigned i = 0; i < _nRows; i++)
         for (unsigned j = 0; j < columns(); j++)
			_data[i][j]=_data[i][j]+m[i][j];
	 return *this;
	 }
  } // TODO
   Matrix operator * (const Matrix& m) const { 
	 if(columns()!=m.rows())
	 {
		 cout<<"matrix sizes do not match"<<endl;
		return *this;
	 }
     else 
	 {
	   Matrix M3(_nRows,m.columns());
	   for (unsigned i = 0; i < _nRows; i++)
         for (unsigned j = 0; j < m.columns(); j++)
			M3[i][j]=0;
	   for (unsigned i = 0; i < _nRows; i++)
         for (unsigned j = 0; j < m.columns(); j++)
			for (unsigned k = 0; k < m.rows(); k++)
			 M3[i][j]= M3[i][j]+(_data[i][k]*(m[k][j]));

	   return M3;
   } // TODO

   }
   // If matrix sizes do not match, cerr a message return (*this)
  
  Matrix& operator *= (const Matrix& m) 
  { 
   	 if(this->columns()!=m.rows())
	 {
		 cout<<"matrix sizes do not match"<<endl;
		return *this;
	 }
     else 
	 {
	   Matrix M3(_nRows,m.columns());
	   for (unsigned i = 0; i < _nRows; i++)
         for (unsigned j = 0; j < m.columns(); j++)
			M3[i][j]=0;
	   for (unsigned i = 0; i < _nRows; i++)
         for (unsigned j = 0; j < m.columns(); j++)
			for (unsigned k = 0; k < m.rows(); k++)
			 M3[i][j]= M3[i][j]+(_data[i][k]*(m[k][j]));
      
	   delete []_data;

	   _data=new Vector[M3.rows()];
	   for(unsigned i =0 ; i <M3.rows();i++)
			(*(_data+i)).VchangeSize(M3.columns());
	   _nRows=M3.rows();


	   for (unsigned i = 0; i < M3.rows(); i++)
         for (unsigned j = 0; j < M3.columns(); j++)
	   _data[i][j]=M3[i][j];
	   
	   return  *this;
	 }

  }// TODO

    Matrix operator = (const Matrix& m) { 
	   Matrix m2(m);
   return m2;
   } 

   // If matrix sizes do not match, cerr a message return a copy of (*this)


  friend ostream& operator << (ostream&, const Matrix&);
 
private:
   unsigned     _nRows;
   Vector      *_data;
   // auxilary functions
   };

#endif // MATRIX_H


