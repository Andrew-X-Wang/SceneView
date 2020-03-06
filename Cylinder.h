#pragma once
#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

class Cylinder : public Shape {
public:
    Cylinder() {};
    ~Cylinder() {};

    OBJ_TYPE getType() {
        return SHAPE_CYLINDER;
    }

private:
    void compute_vertices() {
        vertexCount = m_segmentsX * (m_segmentsY + 3) + 2;
        vertexList = new vertex[vertexCount];

        float r = 0.5;
        float x, y, z, theta;

        int c = 0;
        new_vertex(c, 0, r, 0);
        new_normal(c, 0, r, 0);
        c++;
        for (int i = 1; i <= m_segmentsX; i++) {
            theta = 2 * PI * (float)i / (float)m_segmentsX;
            x = r * cos(theta);
            z = r * sin(theta);
            new_vertex(c, x, r, z);
            new_normal(c, 0, r, 0);
            c++;
        }
        for (int i = 0; i <= m_segmentsY; i++) {
            for (int j = 0; j < m_segmentsX; j++) {
                theta = 2 * PI * (float)j / (float)m_segmentsX;
                x = r * cos(theta);
                z = r * sin(theta);
                y = 0.5 - (i / (float)m_segmentsY);
                new_vertex(c, x, y, z);
                new_normal(c, cos(theta), 0.5, sin(theta));
                c++;
            }
        }
        r = -0.5;
        for (int i = 1; i <= m_segmentsX; i++) {
            theta = 2 * PI * (float)i / (float)m_segmentsX;
            x = r * cos(theta);
            z = r * sin(theta);
            new_vertex(c, x, r, z);
            new_normal(c, 0, r, 0);
            c++;
        }
        new_vertex(c, 0, r, 0);
        new_normal(c, 0, r, 0);
    };

    void compute_faces() {
        faceCount = 2 * m_segmentsX * (m_segmentsY + 1);
        faceList = new face[faceCount];

        int c = 0;
        int v1, v2, v3;
        int shift = 0;
        // top base
        for (int i = 0; i < m_segmentsX; i++) {
            v1 = 0;

            if (i == m_segmentsX - 1) v2 = 1;
            else v2 = (i + 2);

            v3 = (i + 1);

            new_face(c, v1, v2, v3);
            c++;
        }
        shift = m_segmentsX + 1;
        // bottom triangles
        for (int i = 0; i < m_segmentsY; i++) {
            for (int j = 0; j < m_segmentsX; j++) {
                v1 = j + i * m_segmentsX + shift;

                v2 = j + (i + 1) * m_segmentsX + shift;

                v3 = (j - 1) + (i + 1) * m_segmentsX + shift;
                if (j == 0) v3 += m_segmentsX;

                new_face(c, v1, v2, v3);
                c++;
            }
        }
        // top triangles
        for (int i = 0; i < m_segmentsY; i++) {
            for (int j = 0; j < m_segmentsX; j++) {
                v1 = j + i * m_segmentsX + shift;

                if (j == m_segmentsX - 1) v2 = (j + 1) + (i - 1) * m_segmentsX + shift;
                else v2 = (j + 1) + i * m_segmentsX + shift;

                v3 = j + (i + 1) * m_segmentsX + shift;

                new_face(c, v1, v2, v3);
                c++;
            }
        }
        shift = m_segmentsX * (m_segmentsY + 1) + 1;
        // bottom base
        for (int i = 0; i < m_segmentsX; i++) {

            v1 = i + shift;

            if (i == m_segmentsX - 1) v2 = shift;
            else v2 = (i + 1) + shift;

            v3 = vertexCount - 1;

            new_face(c, v1, v2, v3);
            c++;
        }
    };
};

#endif