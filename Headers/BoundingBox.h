#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

class BoundingBox {
public:
    float minX, minY, minZ;
    float maxX, maxY, maxZ;

    // Helper functions to get dimensions
    float getWidth();
    float getHeight();
    float getDepth();

    // Helper to get center point
    void getCenter(float& x, float& y, float& z);
};

#endif // !BOUNDINGBOX_H


