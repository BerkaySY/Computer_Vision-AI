#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <ctime>

const int MATRIX_SIZE = 50;

int main()
{
    //Declare 2x3 float Matrix
    Eigen::Matrix<float, 2, 3> matrix_2x3;

    //Eigen::Matrix<double, 3, 1> == Eigen::Vector3d
    //v_3d and vd_3d are same
    Eigen::Vector3d v_3d;
    Eigen::Matrix<float, 3, 1> vd_3d;

    //Eigen::Matrix<double, 3, 3> == Eigen::Matrix3d
    Eigen::Matrix3d matrix_3x3 = Eigen::Matrix3d::Zero(); //initialized to zero

    //Dynamic Size Matrix
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;
    //Simple Version
    Eigen::MatrixXd matrix_x;

    //input data(initialization)
    matrix_2x3 << 1, 2, 3, 4, 5, 6;
    std::cout << "Matrix 2x3 from 1 to 6: \n" << matrix_2x3 << '\n';

    //Access Elements 
    std::cout << "Output of Matrix 2x3: " << '\n';
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
            std::cout << matrix_2x3(i, j) << '\t';
        std::cout << '\n';
    }

    v_3d << 1, 2, 3;
    vd_3d << 4, 5, 6;

    //Can't mix two different types of matrices
    // Wrong -> Eigen::Matrix<double, 2, 1> wrong = matrix_2x3 * v_3d;
    Eigen::Matrix<double, 2, 1> result = matrix_2x3.cast<double>() * v_3d;
    std::cout << "[1, 2, 3; 4, 5, 6] * [4, 5, 6]: " << result.transpose() << '\n';

    Eigen::Matrix<float, 2, 1> result2 = matrix_2x3 * vd_3d;
    std::cout << "[1, 2, 3; 4, 5, 6] * [4, 5, 6]: " << result2.transpose() << '\n';

    //Matrix Operations
    matrix_3x3 = Eigen::Matrix3d::Random(); //Random Number Matrix
    std::cout << "random number matrix: " << matrix_3x3 << '\n';
    std::cout << "Transpose: " << matrix_3x3.transpose() << '\n';
    std::cout << "Sum: " << matrix_3x3.sum() << '\n';
    std::cout << "Trace: " << matrix_3x3.trace() << '\n';
    std::cout << "times 10: " << matrix_3x3 * 10 << '\n';
    std::cout << "Inverse: " << matrix_3x3.inverse() << '\n';
    std::cout << "Determinant: " << matrix_3x3.determinant() << '\n';

    //EigenValues
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_3x3.transpose() * matrix_3x3);
    std::cout << "Eigen Values: " << eigen_solver.eigenvalues() << '\n';
    std::cout << "Eigen Vectors: " << eigen_solver.eigenvectors() << '\n';

    //Solving Equations
    //Equation -> matrix_NxN * x = v_Nd
    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NxN 
        = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_NxN *= matrix_NxN.transpose();
    Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_stt = clock();
    //Direct Inversion
    Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NxN.inverse() *v_Nd;
    std::cout << "Time Of Normal Inverse Is "
        << 1000 * (clock() - time_stt) / static_cast<double>CLOCKS_PER_SEC << "ms" << '\n';
    std::cout << "x = " << x.transpose() << '\n';

    //QR Decomposition
    time_stt = clock();
    x = matrix_NxN.colPivHouseholderQr().solve(v_Nd);
    std::cout << "Time Of QR Decomposition Is "
        << 1000 * (clock() - time_stt) / static_cast<double>CLOCKS_PER_SEC << "ms" << '\n';
    std::cout << "x = " << x.transpose() << '\n';


    //Cholesky Decomposition
    time_stt = clock();
    x = matrix_NxN .ldlt().solve(v_Nd);
    std::cout << "Time Of LDLT Decomposition Is "
        << 1000 * (clock() - time_stt) / static_cast<double>CLOCKS_PER_SEC << "ms" << '\n';
    std::cout << "x = " << x.transpose() << '\n';

    return 0;
}