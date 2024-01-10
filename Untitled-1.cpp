#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

class matrix {
private:
    int n;
    int** data;

public:
    matrix() : n(0), data(nullptr) {}

    matrix(int size) : n(0), data(nullptr) {
        alokuj(size);
    }

    matrix(int size, int* arr) : n(0), data(nullptr) {
        alokuj(size);
        memcpy(data[0], arr, n * n * sizeof(int));
    }

    matrix(const matrix& m) : n(0), data(nullptr) {
        alokuj(m.n);
        memcpy(data[0], m.data[0], n * n * sizeof(int));
    }

    ~matrix() {
        for (int i = 0; i < n; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    matrix& alokuj(int size) {
        if (n > 0) {
            for (int i = 0; i < n; ++i) {
                delete[] data[i];
            }
            delete[] data;
        }
        n = size;
        data = new int*[n];
        data[0] = new int[n * n];
        for (int i = 1; i < n; ++i) {
            data[i] = data[i - 1] + n;
        }
        return *this;
    }

    matrix& losuj(int x) {
        srand(static_cast<unsigned>(time(nullptr)));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i][j] = rand() % (x + 1);
            }
        }
        return *this;
    }

    int pokaz(int x, int y) {
        return data[x][y];
    }

    matrix& przekatna() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i][j] = (i == j) ? 1 : 0;
            }
        }
        return *this;
    }

    matrix& pod_przekatna() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i][j] = (i > j) ? 1 : 0;
            }
        }
        return *this;
    }

    matrix& nad_przekatna() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i][j] = (i < j) ? 1 : 0;
            }
        }
        return *this;
    }

    matrix& szachownica() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i][j] = (i + j) % 2;
            }
        }
        return *this;
    }

    matrix& operator+(matrix& m) {
        matrix* result = new matrix(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result->data[i][j] = data[i][j] + m.data[i][j];
            }
        }
        return *result;
    }
};

int main() {
    matrix m1, m2;
    m1.alokuj(30).losuj(10);
    m2.alokuj(30).losuj(10);

    std::cout << "Macierz A:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << m1.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Macierz B:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << m2.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    matrix m3 = m1 + m2;

    std::cout << "Macierz A + B:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << m3.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
