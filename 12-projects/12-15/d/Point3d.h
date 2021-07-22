// Header file that defines the Point3d class
 
#ifndef POINT3D_H
#define POINT3D_H
 
class Vector3d; // forward declaration for class Vector3d for function moveByVector()
 
class Point3d
{
    private:
    	double m_x{};
        double m_y{};
        double m_z{};
        
    public:
        Point3d(double x = 0.0, double y = 0.0, double z = 0.0);
 
        void print() const;
        void moveByVector(const Vector3d& v); // forward declaration above needed for this line
};
 
#endif