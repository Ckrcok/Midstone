#include "Collision.h"
#include "Box.h"

using namespace std;
using namespace MATH;

    int Collision::distancePointBox(Vec3 point_, Box theBox_) {
        float distance = 0;
        for (int i = 0; i < 3; i++) {
            float coord = point_[i];
            if (coord < theBox_.minCoords[i]) {
                distance += theBox_.minCoords[i] - coord;
            }
            if (coord > theBox_.maxCoords[i]) {
                distance += coord - theBox_.maxCoords[i];
            }
        }
        if(distance < 1.0f) {
            return 1;
        }else {
            return 0;
        }
    }

    int Collision::boxBoxCollision(Box& a_, Box& b_)
    {
        // Exit with no intersection if separated along an axis
        if (a_.maxCoords[0] < b_.minCoords[0] || a_.minCoords[0] > b_.maxCoords[0]) return 0;
        if (a_.maxCoords[1] < b_.minCoords[1] || a_.minCoords[1] > b_.maxCoords[1]) return 0;
        if (a_.maxCoords[2] < b_.minCoords[2] || a_.minCoords[2] > b_.maxCoords[2]) return 0;
        // Overlapping on all axes means AABBs are intersecting
        return 1;
    }

    int Collision::TestSphereSphere(Box& a_, Box& b_)
    {
        // Calculate squared distance between centers
        Vec3 d = a_.pos - b_.pos;
        float dist2 =  VMath::dot(d, d); 
        // Spheres intersect if squared distance is less than squared sum of radii
        float radiusSum = a_.radius + b_.radius;
        return dist2 <= radiusSum * radiusSum;
    }
