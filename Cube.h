#pragma once
#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public Shape {
public:
    Cube() {};

    ~Cube() {};

    OBJ_TYPE getType() {
        return SHAPE_CUBE;
    }

private:

    void compute_vertices() {
        vertexCount = 6 * (m_segmentsX + 1) * (m_segmentsY + 1);
        vertexList = new vertex[vertexCount];

        int c = 0;
        float p1, p2;
        for (int l = 0; l < 6; l++) {
            for (int i = 0; i <= m_segmentsX; i++) {
                p1 = (i / (float)m_segmentsX) - 0.5;
                for (int j = 0; j <= m_segmentsY; j++) {
                    p2 = (j / (float)m_segmentsY) - 0.5;
                    switch (l) {
                    case 0:
                        new_vertex(c, p1, p2, 0.5);
                        new_normal(c, 0, 0, 1);
                        break;
                    case 1:
                        new_vertex(c, p1, p2, -0.5);
                        new_normal(c, 0, 0, -1);
                        break;
                    case 2:
                        new_vertex(c, p1, -0.5, p2);
                        new_normal(c, 0, -1, 0);
                        break;
                    case 3:
                        new_vertex(c, p1, 0.5, p2);
                        new_normal(c, 0, 1, 0);
                        break;
                    case 4:
                        new_vertex(c, -0.5, p2, p1);
                        new_normal(c, -1, 0, 0);
                        break;
                    case 5:
                        new_vertex(c, 0.5, p2, p1);
                        new_normal(c, 1, 0, 0);
                        break;
                    }
                    c++;
                }
            }
        }
    };

    void compute_faces() {
        faceCount = 12 * (m_segmentsY) * (m_segmentsX);
        faceList = new face[faceCount];

        int c = 0;
        int v1, v2, v3;
        bool rev = false;
        for (int l = 0; l < 6; l++) {
            for (int i = 0; i < m_segmentsX; i++) {
                for (int j = 0; j < m_segmentsY; j++) {
                    v1 = (j + i * (m_segmentsY + 1)) + l * (vertexCount / 6);
                    v2 = v1 + m_segmentsY + 2;
                    v3 = v1 + 1;
                    if (l % 2 == 0) rev = false; else rev = true;
                    // top triangles
                    new_face(c, rev, v1, v2, v3);
                    c++;

                    // bottom triangles
                    v2 = v1 + m_segmentsY + 1;
                    v3 = v1 + m_segmentsY + 2;
                    new_face(c, rev, v1, v2, v3);
                    c++;
                }
            }
        }
    };

    void new_face(int ind, bool rev, int v1, int v2, int v3) {
        faceList[ind].v2 = v2;
        if (rev) {
            faceList[ind].v1 = v3;
            faceList[ind].v3 = v1;
        }
        else {
            faceList[ind].v1 = v1;
            faceList[ind].v3 = v3;
        }
    };
};

#endif