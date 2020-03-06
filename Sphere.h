#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
public:
    Sphere() {};

    ~Sphere() {};

    OBJ_TYPE getType() {
        return SHAPE_SPHERE;
    }

private:
    void compute_vertices() {
        vertexCount = (m_segmentsX * (m_segmentsY - 1)) + 2;
        vertexList = new vertex[vertexCount];

        float r = 0.5;
        float x, y, z, phi, theta;

        int c = 0;
        new_vertex(c, 0, r, 0);
        new_normal(c, 0, r, 0);
        c++;
        for (int i = 0; i < m_segmentsY - 1; i++) {
            phi = (i + 1) * PI / (float)m_segmentsY;
            for (int j = 0; j < m_segmentsX; j++) {
                theta = j * 2 * PI / (float)m_segmentsX;

                x = r * sin(phi) * cos(theta);
                y = r * cos(phi);
                z = r * sin(phi) * sin(theta);
                new_vertex(c, x, y, z);
                new_normal(c, x, y, z);
                c++;
            }
        }
        r = -0.5;
        new_vertex(c, 0, r, 0);
        new_normal(c, 0, r, 0);
    };

    void compute_faces() {
        faceCount = (2 * m_segmentsX) * (m_segmentsY - 1);
        faceList = new face[faceCount];

        int c = 0;
        int v1, v2, v3;
        // bottom faces
        for (int i = 0; i < m_segmentsY - 1; i++) {
            for (int j = 0; j < m_segmentsX; j++) {
                if (i == 0) v1 = 0;
                else v1 = (j + 1) + (i - 1) * m_segmentsX;

                v2 = (j + 1) + (i * m_segmentsX);

                if (j == 0) v3 = (i + 1) * m_segmentsX;
                else v3 = j + (i * m_segmentsX);

                new_face(c, v1, v2, v3);
                c++;
            }
        }
        // top faces
        for (int i = 1; i < m_segmentsY; i++) {
            for (int j = 0; j < m_segmentsX; j++) {
                v1 = (j + 1) + (i - 1) * m_segmentsX;

                if (j == m_segmentsX - 1) v2 = 1 + (i - 1) * m_segmentsX;
                else v2 = (j + 2) + (i - 1) * m_segmentsX;

                if (i == m_segmentsY - 1) v3 = vertexCount - 1;
                else v3 = (j + 1) + (i * m_segmentsX);

                new_face(c, v1, v2, v3);
                c++;
            }
        }
    };
};

#endif