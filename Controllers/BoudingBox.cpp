#include "Headers/BoundingBox.h"



// Helper to get center point
void BoundingBox::getCenter(float& x, float& y, float& z)  {
    x = (minX + maxX) / 2.0f;
    y = (minY + maxY) / 2.0f;
    z = (minZ + maxZ) / 2.0f;
}

float BoundingBox::getWidth()  { return maxX - minX; }
float BoundingBox::getHeight() { return maxY - minY; }
float BoundingBox::getDepth() { return maxZ - minZ; }

