#include "Collision.h"
#include "Box.h"

using namespace std;
using namespace MATH;

    float Collision::distancePointBox(Vec3 point_, Box theBox_) {
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
        return distance;
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
