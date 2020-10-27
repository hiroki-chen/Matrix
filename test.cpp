#include "matrix.hpp"
#include <random>

int main(int argc, const char** argv) {

    std::random_device e;
    std::uniform_int_distribution<unsigned> ls(1, 999);

    LowerTriangularMatrix<int> matrix(5);
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= i; j++) {
            matrix.set(i, j, ls(e));
        }
    }
    UpperTriangularMatrix<int> a = matrix.transpose();
    std::cout << matrix << std::endl;
    std::cout << a;

    /*SparseMatrix<int> m1, m2;
    std::cin >> m1;
    std::cin >> m2;
    SparseMatrix<int> m = m1 * m2;
    std::cout << m1;
    std::cout << m2;
    std::cout << m;
*/

    LinkedMatrix<int> m1, m2;
    std::cout << m1 << m2;
    LinkedMatrix<int> m = m1 + m2;
    std::cout << m;

    return 0;

}