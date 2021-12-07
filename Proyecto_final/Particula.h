#ifndef PARTICULA_H
#define PARTICULA_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <iostream>
#include "Matrices.h"
using namespace std;

class Particula
{
public:
	vector<float> vertices;		//STAR
	vector<float> vertices_borders;	//STAR'S LINES

	vector<float> eje_x;
	vector<float> eje_y;
	vector<float> eje_z;
	
	int size_particula = 0;
	int points_size = 0;
	

	Particula(vector<float> temp_vertices, float R, float G, float B)
	{
		eje_x.reserve(2);
		eje_y.reserve(2);
		eje_z.reserve(2);
		eje_x.resize(2);
		eje_y.resize(2);
		eje_z.resize(2);
		vertices.reserve(temp_vertices.size() + ((temp_vertices.size() / 3) * 5));
		for (int j = 1; j <= temp_vertices.size(); ++j)
		{
			vertices.push_back(temp_vertices[j - 1]);
			//colores
			if (j % 3 == 0)
			{
				//colores
				vertices.push_back(R);
				vertices.push_back(G);
				vertices.push_back(B);

				vertices.push_back(0.0f);
				vertices.push_back(0.0f);
			}
		}
		points_size = vertices.size() / 8;
		vertices_borders = vertices;
		for (int i = 0; i < points_size; i++)
		{
			int pos = i * 8;
			vertices_borders[pos + 3] = 0;
			vertices_borders[pos + 4] = 0;
			vertices_borders[pos + 5] = 0;
		}
		
		
		size_particula = vertices.size() * sizeof(vertices);
		act_min_max_x();
		act_min_max_y();
		act_min_max_z();
	}
	///
	
	
	void draw(GLFWwindow *window, bool bordes = true)
	{
		glBufferData(GL_ARRAY_BUFFER, size_particula, vertices.data(), GL_STATIC_DRAW);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 8);
		//borders
		if(bordes ==true){
			glLineWidth(8);
			glBufferData(GL_ARRAY_BUFFER, size_particula, vertices_borders.data(), GL_STATIC_DRAW);
			glDrawArrays(GL_LINE_LOOP, 0, vertices_borders.size()/8);   
		}
		
		
	}
	
	void act_min_max_x()
	{
		vector<float> result;
		result.reserve(2);
		result.resize(2);
		result[0] = vertices[0]; //min
		result[1] = vertices[0]; //max
		for (int i = 1; i < points_size; i++)
		{
			int pos = i * 8;
			if (vertices[pos] < result[0])
				result[0] = vertices[pos];
			if (vertices[pos] > result[1])
				result[1] = vertices[pos];
		}
		eje_x = result;
	}
	///
	void act_min_max_y()
	{
		vector<float> result;
		result.reserve(2);
		result.resize(2);
		result[0] = vertices[1]; //min
		result[1] = vertices[1]; //max
		for (int i = 1; i < points_size; i++)
		{
			int pos = i * 8;
			if (vertices[pos + 1] < result[0])
				result[0] = vertices[pos + 1];
			if (vertices[pos + 1] > result[1])
				result[1] = vertices[pos + 1];
		}
		eje_y = result;
	}
	///
	void act_min_max_z()
	{
		vector<float> result;
		result.reserve(2);
		result.resize(2);
		result[0] = vertices[2]; //min
		result[1] = vertices[2]; //max
		for (int i = 1; i < points_size; i++)
		{
			int pos = i * 8;
			if (vertices[pos + 2] < result[0])
				result[0] = vertices[pos + 2];
			if (vertices[pos + 2] > result[1])
				result[1] = vertices[pos + 2];
		}
		eje_z = result;
	}
	
	///
	void translateF(float new_x,float new_y,float new_z){
		for(int i=0;i<points_size;i++){
			int pos=i*8;
			vertices[pos]+=new_x;
			vertices[pos+1]+=new_y;
			vertices[pos+2]+=new_z;
			vertices_borders[pos]+=new_x;
			vertices_borders[pos+1]+=new_y;
			vertices_borders[pos+2]+=new_z;
		}
	}
	void rotation_x(float angle)
	{
			Matrix m1(4, 4);
			Matrix m2(vertices);
			Matrix m3(4, vertices.size());
			m1.convert_matrix_rotation_x(angle);
			Multiply(m1, m2, m3);
			m3.copy_vert(vertices);
			m3.copy_vert(vertices_borders);
		}
		
		void rotation_z(float angle)
		{
			Matrix m1(4, 4);
			Matrix m2(vertices);
			Matrix m3(4, vertices.size());
			m1.convert_matrix_rotation_z(angle);
			Multiply(m1, m2, m3);
			m3.copy_vert(vertices);
			m3.copy_vert(vertices_borders);
		}
		
		
};
#endif