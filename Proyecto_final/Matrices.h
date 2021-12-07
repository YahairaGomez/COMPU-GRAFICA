#ifndef MATRICES_H
#define MATRICES_H
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define PI 3.14159265

typedef vector<vector<float>> matrix_type;
struct Matrix{
	matrix_type *data;
	Matrix(int x_size=4,int y_size=4){
		data=new vector<vector<float>> (x_size,vector<float>(y_size,0));
	}
		///
		Matrix(vector<float> &data_tempo){
			data=new vector<vector<float>> (4,vector<float>(data_tempo.size()/6));
			for(int i=0;i<data_tempo.size()/8;i++){
				int pos=i*8;
				(*data)[0][i]=data_tempo[pos];
				(*data)[1][i]=data_tempo[pos+1];
				(*data)[2][i]=data_tempo[pos+2];
				(*data)[3][i]=1;
			}
		}
			///MATRIZ IDENTIDAD
			void indentityM(int size){
				for(int i=0;i<size;++i){
					(*data)[i][i]=1;
				}
			}
			
			void convert_matrix_rotation_x(float angle){
				indentityM(4);
				(*data)[1][1]=cos(angle* PI / 180.0 );  
				(*data)[1][2]=-sin(angle* PI / 180.0 );
				(*data)[2][1]=sin(angle* PI / 180.0 ); 
				(*data)[2][2]=cos(angle* PI / 180.0 );
			}
							
								
			void convert_matrix_rotation_z(float angle){
			indentityM(4);
			(*data)[0][0]=cos(angle* PI / 180.0 );           
			(*data)[0][1]=-sin(angle* PI / 180.0 );
			(*data)[1][0]=sin(angle* PI / 180.0 );            
			(*data)[1][1]=cos(angle* PI / 180.0 );
								
			}
						
						//PASO EL RESULTADO AL VECTOR DE FLOAT CORRESPONDIENTE
			void copy_vert(vector<float> &vertices){
				for(int i=0;i<vertices.size()/8;i++){
					int pos=i*8;
					vertices[pos]=(*data)[0][i];
					vertices[pos+1]=(*data)[1][i];
					vertices[pos+2]=(*data)[2][i];
				}
			}
														
};
void Multiply(Matrix &a, Matrix &b,Matrix &c){
	const int n = (*a.data).size();     // a rows
	const int m = (*a.data)[0].size();  // a cols
	const int p = (*b.data)[0].size();  // b cols
	
	for (auto j = 0; j < p; ++j){
		for (auto k = 0; k < m; ++k){
			for (auto i = 0; i < n; ++i){
				(*c.data)[i][j] += ((*a.data)[i][k] * (*b.data)[k][j]);
			}
		}
	}
}
#endif	
