#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>

int main()
{
    //3D Rotation Matrix Directly Using Eigen::Matrix3d or Matrix3f
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    //The Rotation Vector uses AngleAxis but the operation can be treated as a Matrix
    //Rotate 45 degrees along the Z axis
    Eigen::AngleAxisd rotation_vector(M_PI / 4, Eigen::Vector3d(0, 0, 1));
    std::cout.precision(3);
    //Convert to Matrix with matrix()
    std::cout << "Rotation Matrix = \n" << rotation_vector.matrix() << '\n';
    //Assigned Directly
    rotation_matrix = rotation_vector.toRotationMatrix();

    //Coordinate Transformation with AngleAxis
    Eigen::Vector3d v(1, 0, 0);
    Eigen::Vector3d v_rotated = rotation_vector * v;
    std::cout << "(1, 0, 0) after rotation (by angle axis) = " << v_rotated.transpose() << '\n';

    //Coordinate Transformation with Rotation Matrix
    v_rotated = rotation_matrix * v;
    std::cout << "(1, 0, 0) after rotation (by rotation matrix) = " << v_rotated.transpose() << '\n';
    
    //Can convert the rotation matrix directly into Euler Angles
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
    //X -> roll Y -> pitch Z -> yaw
    std::cout << "yaw pitch roll = " << euler_angles.transpose() << '\n';

    //Euclidean transformation matrix using Eigen::Isometry
    Eigen::Isometry3d T= Eigen::Isometry3d::Identity(); //Used 3d for 4x4 matrix
    T.rotate(rotation_vector);
    T.pretranslate(Eigen::Vector3d(1, 3, 4)); // Set the translation vector to (1, 3, 4)
    std::cout << "Transform Matrix = \n" << T.matrix() << '\n';

    //Use the transformation matrix for coordinate transformation
    Eigen::Vector3d v_transformed = T * v;
    std::cout << "Transformed v = " << v_transformed.transpose() << '\n';

    //Affine Transformation -> Eigen::Affine3d | Projective Transformation -> Eigen::Projective3d
    //Gimbal Lock Explanation -> https://www.youtube.com/watch?v=zc8b2Jo7mno

    //Quaternions
    //Can assign AngleAxis directly to Quaternions, and vice versa
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);
    std::cout << "Quaternion from rotation vector = " << q.coeffs().transpose() << '\n';
    // coeffs -> (x, y, z, w), w is the real part,others are the imaginary part

    //Rotation matrix version
    q = Eigen::Quaterniond(rotation_matrix);
    std::cout << "Quaternion from rotation matrix = " << q.coeffs().transpose() << '\n';
    
    // Rotate a vector with a quaternion and use overloaded multiplication
    v_rotated = q * v; // qvq^{−1}
    std::cout << "(1, 0, 0) after rotation = " << v_rotated.transpose() << '\n';
    //expressed by regular vector multiplication, it should be calculated as follows
    std::cout << "Should be equal to " << (q * Eigen::Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose() << '\n';

    return 0;
}