#pragma once
#include "Vector.h"
#include "VMath.h"
#include "Box.h"
using namespace std;
using namespace MATH;


struct Collision
{
    static int boxBoxCollision(Box& a, Box& b);
    static float distancePointBox(Vec3 point_, Box theBox_);
};