#pragma once
#include "Vector.h"
#include "VMath.h"
#include "Box.h"
using namespace std;
using namespace MATH;


struct Collision
{
    static int boxBoxCollision( Box& a,  Box& b);
    static int distancePointBox(Vec3 point_, const Box theBox_);
    static int TestSphereSphere(Box& a_, Box& b_);
};