#pragma once
#ifndef CONE_H
#define CONE_H

#include "Shape.h"

class Cone : public Shape {
public:
    Cone() {};

    ~Cone() {};

    OBJ_TYPE getType() {
        return SHAPE_CONE;
    }

private:
    void compute_vertices() {
        vertexCount = m_segmentsX * (m_segmentsY + 1) + 2;
        vertexList = new vertex[vertexCount];

        float r = 0.5;
        float x, y, z, theta;

        int c = 0;
        new_vertex(c, 0, r, 0);
        new_normal(c, 0, r, 0);
        c++;

        for (int i = 1; i <= m_segmentsY; i++) {
            r = 0.5 * (float)i / (float)m_segmentsY;
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
        faceCount = 2 * m_segmentsX * m_segmentsY;
        faceList = new face[faceCount];

        int c = 0;
        int v1, v2, v3;
        // bottom triangles
        for (int i = 0; i < m_segmentsY; i++) {
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
        // top triangles
        for (int i = 1; i < m_segmentsY; i++) {
            for (int j = 0; j < m_segmentsX; j++) {
                int shift = (i - 1) * m_segmentsX;

                v1 = (j + 1) + shift;

                if (j == m_segmentsX - 1) v2 = 1 + shift;
                else v2 = (j + 2) + shift;

                v3 = (j + 1) + (i * m_segmentsX);

                new_face(c, v1, v2, v3);
                c++;
            }
        }
        // base
        for (int i = 0; i < m_segmentsX; i++) {
            int shift = (m_segmentsY - 1) * m_segmentsX;

            v1 = (i + 1) + shift;

            if (i == m_segmentsX - 1) v2 = 1 + shift;
            else v2 = (i + 2) + shift;

            v3 = vertexCount - 1;

            new_face(c, v1, v2, v3);
            c++;
        }
    };
};

#endif