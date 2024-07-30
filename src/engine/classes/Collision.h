//
// Created by Brandon Friend on 7/29/24.
//

#ifndef COLLISION_H
#define COLLISION_H


#include "../PhantomEngine.h"

    typedef struct {
        Vector3 *transformedPoints;// Array of points definig the transofrmed collider
        Vector3 *notTransformed;// Array of points defining the collider
        int numPoints;      // Number of points in the array
        Vector3 *normals; //Normal array, helps with detection
        int numNormals; //Number of normals
    } Collider;



    inline void GetNormals(Mesh mesh,Vector3 * normals)
    {
        for (int i = 0; i < mesh.vertexCount; i+=3)
        {//Loop trough the normals and add them to the array
            normals[i/3] = (Vector3){mesh.normals[i],mesh.normals[i+1],mesh.normals[i+2]};
        }
    }

    inline void SetupColliderMesh(Collider *c, Mesh mesh)
{
    // Allocate memory for vertices
    c->numPoints = mesh.vertexCount;
    c->notTransformed = (Vector3 *)malloc(c->numPoints * sizeof(Vector3));
    c->transformedPoints = (Vector3 *)malloc(c->numPoints * sizeof(Vector3));

    // Copy vertices to notTransformed
    for (int i = 0; i < c->numPoints; i++)
    {
        c->notTransformed[i] = (Vector3){mesh.vertices[i * 3], mesh.vertices[i * 3 + 1], mesh.vertices[i * 3 + 2]};
    }

    // If indices are NULL, handle as non-indexed mesh
    if (mesh.indices == NULL)
    {
        // Every 3 vertices form a triangle
        int numTriangles = mesh.vertexCount / 3;
        c->numNormals = numTriangles;
        c->normals = (Vector3 *)malloc(c->numNormals * sizeof(Vector3));

        // Compute normals based on vertices
        for (int i = 0; i < numTriangles; i++)
        {
            int index0 = i * 3;
            int index1 = i * 3 + 1;
            int index2 = i * 3 + 2;

            Vector3 v0 = c->notTransformed[index0];
            Vector3 v1 = c->notTransformed[index1];
            Vector3 v2 = c->notTransformed[index2];

            // Calculate normal for the current triangle
            Vector3 edge1 = Vector3Subtract(v1, v0);
            Vector3 edge2 = Vector3Subtract(v2, v0);

            Vector3 normal = Vector3CrossProduct(edge1, edge2);
            normal = Vector3Normalize(normal);

            c->normals[i] = normal;
        }
    }
    else
    {
        // Handle indexed mesh (as previously)
        int numTriangles = mesh.triangleCount;
        c->numNormals = numTriangles;
        c->normals = (Vector3 *)malloc(c->numNormals * sizeof(Vector3));

        // Compute normals based on indices
        for (int i = 0; i < numTriangles; i++)
        {
            int index0 = mesh.indices[i * 3];
            int index1 = mesh.indices[i * 3 + 1];
            int index2 = mesh.indices[i * 3 + 2];

            Vector3 v0 = c->notTransformed[index0];
            Vector3 v1 = c->notTransformed[index1];
            Vector3 v2 = c->notTransformed[index2];

            // Calculate normal for the current triangle
            Vector3 edge1 = Vector3Subtract(v1, v0);
            Vector3 edge2 = Vector3Subtract(v2, v0);

            Vector3 normal = Vector3CrossProduct(edge1, edge2);
            normal = Vector3Normalize(normal);

            c->normals[i] = normal;
        }
    }
}



    inline void GetMinMax(Collider b, Vector3 axis, float *min, float *max)
    {
    *min = Vector3DotProduct(b.transformedPoints[0], axis); //Initialize min as the first vertex
    *max = *min;  // Initialize max with the same value as min

    for (int i = 1; i < b.numPoints; i++)
        { //Loop trough the vertices
            //Find the dot product between the vertex and the axis
            float dot = Vector3DotProduct(b.transformedPoints[i], axis);
            //Check if the dot is smaller then min, if it is set the new min
            if (dot < *min)
            {
                *min = dot;
            }
            //Check if the dot is bigger then max, if it is set the new max
            if (dot > *max)
            {
                *max = dot;
            }
        }
    }

    inline Vector3 GetMiddlePoint(Vector3 *vertices,int numVertices)
    {
	    float x=0,y=0,z=0;//Init variables
	    for(int i = 0; i < numVertices;i++)
	    {//Iterate trought the vertices and get the sum
           //Add all the vertex values togerher
           x+= vertices[i].x;
           y+= vertices[i].y;
           z+= vertices[i].z;
	    }
	    return(Vector3){x/numVertices,y/numVertices,z/numVertices}; //Divide the values to get the average(Middle)
    }

    inline bool CheckCollision(Collider a, Collider b, Vector3 *normal)
    {
        *normal = (Vector3){0, 0, 0}; //Init normal vector
        float depth = FLT_MAX; //Init depth as the max value it can be

        for (int i = 0; i < a.numNormals; i++)
        {
            float min1, max1, min2, max2;
           GetMinMax(a, a.normals[i], &min2, &max2);
           GetMinMax(b, a.normals[i], &min1, &max1);

            if (max1 < min2 || max2 < min1)
            {
                return false;  // No collision on this axis
            }
            else
            {
                float axisDepth = fminf(max2 - min1, max1 - min2);
                if (axisDepth < depth)
                {
                    depth = axisDepth;
                    *normal = a.normals[i];
                }
            }
        }

        for (int i = 0; i < b.numNormals; i++)
        {
            float min1, max1, min2, max2;
            GetMinMax(a, b.normals[i], &min2, &max2);
            GetMinMax(b, b.normals[i], &min1, &max1);

            if (max1 < min2 || max2 < min1)
            {
                return false;  // No collision on this axis
            }
            else
            {
                float axisDepth = fminf(max2 - min1, max1 - min2);
                if (axisDepth < depth)
                {
                    depth = axisDepth;
                    *normal = b.normals[i];
                }
            }
        }

        // Simplify direction calculation
        Vector3 direction = Vector3Subtract(GetMiddlePoint(a.transformedPoints, a.numPoints), GetMiddlePoint(b.transformedPoints,b.numPoints));

        if (Vector3DotProduct(direction, *normal) < 0.0f)
        {
            *normal = Vector3Negate(*normal);
        }
        *normal = Vector3Scale(*normal, depth);
        return true;
    }

    //Not optimal, doesn't include rotation and scaling, it's a simple demo
    inline void UpdateCollider(Vector3 parent,Collider *c)
    {
        //Loop trough the points and add them to the
        for(int i = 0; i < c->numPoints;i++)
        {
            c->transformedPoints[i] = Vector3Add( c->notTransformed[i],parent);
        }
    }

    inline void UnloadCollider(Collider *collider)
    {
        free(collider->normals);
        free(collider->transformedPoints);
        free(collider->notTransformed);
    }

inline Vector3 GetClosestPointOnCollider(const Collider& collider, const Vector3& point, const Mesh mesh) {
        Vector3 closestPoint = {0.0f, 0.0f, 0.0f};
        float minDistance = FLT_MAX;

        // Iterate over the vertices of the collider's mesh to find the closest point
        for (int i = 0; i < mesh.vertexCount; i++) {
            Vector3 vertex = {
                mesh.vertices[i * 3],
                mesh.vertices[i * 3 + 1],
                mesh.vertices[i * 3 + 2]
            };

            float distance = Vector3Distance(point, vertex);
            if (distance < minDistance) {
                minDistance = distance;
                closestPoint = vertex;
            }
        }

        return closestPoint;
    }


#endif //COLLISION_H
