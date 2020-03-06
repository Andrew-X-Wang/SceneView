#pragma once
#ifndef SHAPE_H
#define SHAPE_H

#include <FL/gl.h>
#include <FL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include <math.h>

using namespace std;

#define PI glm::pi<float>()  //PI is now a constant for 3.14159....

enum OBJ_TYPE {
    SHAPE_CUBE = 0,
    SHAPE_CYLINDER = 1,
    SHAPE_CONE = 2,
    SHAPE_SPHERE = 3,
    SHAPE_SPECIAL1 = 4,
    SHAPE_SPECIAL2 = 5,
    SHAPE_SPECIAL3 = 6,
    SHAPE_MESH = 7
};

struct vertex {
    float x, y, z;
    float nx, ny, nz;
    vertex() {
        x = y = z = 0;
        nx = ny = nz = 0;
    }
};

struct face {
    int v1, v2, v3;
    face() {
        v1 = v2 = v3 = 0;
    }
};

class Shape {
public:
    static int m_segmentsX;
    static int m_segmentsY;

    Shape() {
        faceCount = 0;
        vertexCount = 0;

        vertexList = NULL;
        faceList = NULL;
        setSegments(10, 10);
    };

    ~Shape() {
        if (vertexList != NULL)
            delete[] vertexList;
        if (faceList != NULL)
            delete[] faceList;
        vertexList = NULL;
        faceList = NULL;
    };

    void setSegments(int segX, int segY) {
        m_segmentsX = segX;
        m_segmentsY = segY;
        reload();
    }

    virtual OBJ_TYPE getType() = 0;

    virtual void draw() {
        for (int i = 0; i < faceCount; i++) {
            glBegin(GL_TRIANGLES);
            draw_vertex(faceList[i].v1);
            draw_vertex(faceList[i].v2);
            draw_vertex(faceList[i].v3);
            glEnd();
        }
    };

    virtual void drawNormal() {
        for (int i = 0; i < vertexCount; i++) {
            float x = vertexList[i].x;
            float y = vertexList[i].y;
            float z = vertexList[i].z;
            float nx = vertexList[i].nx;
            float ny = vertexList[i].ny;
            float nz = vertexList[i].nz;
            glBegin(GL_LINES);
            glVertex3f(x, y, z);
            glVertex3f(n_end(x, nx), n_end(y, ny), n_end(z, nz));
            glEnd();
        }
    };

    virtual void reload() {
        if (vertexList != NULL)
            delete[] vertexList;
        if (faceList != NULL)
            delete[] faceList;
        vertexList = NULL;
        faceList = NULL;

        faceCount = 0;
        vertexCount = 0;

        compute_vertices();
        compute_faces();
    };

protected:
    virtual void compute_vertices() {};
    virtual void compute_faces() {};

    virtual void new_vertex(int ind, float x, float y, float z) {
        vertexList[ind].x = x;
        vertexList[ind].y = y;
        vertexList[ind].z = z;
    };

    virtual void new_normal(int ind, float x, float y, float z) {
        glm::vec3 tmpV = glm::normalize(glm::vec3(x, y, z));
        vertexList[ind].nx = tmpV.x;
        vertexList[ind].ny = tmpV.y;
        vertexList[ind].nz = tmpV.z;
    };

    virtual void new_face(int ind, int v1, int v2, int v3) {
        faceList[ind].v1 = v1;
        faceList[ind].v2 = v2;
        faceList[ind].v3 = v3;
    };

    virtual float n_end(float p, float v) {
        return p + 0.05 * v;
    };

    virtual void draw_vertex(int v) {
        glNormal3f(
            vertexList[v].nx,
            vertexList[v].ny,
            vertexList[v].nz
        );
        glVertex3f(
            vertexList[v].x,
            vertexList[v].y,
            vertexList[v].z
        );
    }

    int vertexCount;
    int faceCount;

    vertex* vertexList;
    face* faceList;
};

#endif