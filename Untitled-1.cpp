#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

class matrix {
private:
    int n;
    int** data;

public:
    // Konstruktory
    matrix(void) : n(0), data(nullptr) {}
    matrix(int size) : n(0), data(nullptr) { alokuj(size); }
    matrix(int size, int* arr) : n(0), data(nullptr) { alokuj(size); std::memcpy(data[0], arr, n * n * sizeof(int)); }
    matrix(const matrix& m) : n(0), data(nullptr) { alokuj(m.n); std::memcpy(data[0], m.data[0], n * n * sizeof(int)); }
    
    // Destruktor
    ~matrix(void) {
        for (int i = 0; i < n; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Przeciążony operator przypisania
    matrix& operator=(const matrix& m) {
        if (this != &m) {
            alokuj(m.n);
            std::memcpy(data[0], m.data[0], n * n * sizeof(int));
        }
        return *this;
    }

    // Funkcje dodatkowe
    matrix& alokuj(int size) {
        if (data == nullptr || n != size) {
            for (int i = 0; i < n; ++i) {
                delete[] data[i];
            }
            delete[] data;

            n = size;
            data = new int*[n];
            data[0] = new int[n * n];
            for (int i = 1; i < n; ++i) {
                data[i] = data[i - 1] + n;
            }
        }
        return *this;
    }

    matrix& wstaw(int row, int col, int value) {
        if (row >= 0 && row < n && col >= 0 && col < n) {
            data[row][col] = value;
        }
        return *this;
    }

    int pokaz(int row, int col) {
        if (row >= 0 && row < n && col >= 0 && col < n) {
            return data[row][col];
        }
        return -1;
    }

    matrix& dowroc() {
        int** transposed = new int*[n];
        for (int i = 0; i < n; ++i) {
            transposed[i] = new int[n];
            for (int j = 0; j < n; ++j) {
                transposed[i][j] = data[j][i];
            }
        }

        for (int i = 0; i < n; ++i) {
            delete[] data[i];
        }
        delete[] data;

        data = transposed;

        return *this;
    }

    matrix& losuj() {
        srand(time(nullptr));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i][j] = rand() % 10;
            }
        }
        return *this;
    }

    matrix& losuj(int x) {
        srand(time(nullptr));
        for (int k = 0; k < x; ++k) {
            int row = rand() % n;
            int col = rand() % n;
            data[row][col] = rand() % 10;
        }
        return *this;
    }

    matrix& diagonalna(int* t) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    data[i][j] = t[i];
                } else {
                    data[i][j] = 0;
                }
            }
        }
        return *this;
    }

    matrix& diagonalna_k(int k, int* t) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - j == k) {
                    data[i][j] = t[i];
                } else {
                    data[i][j] = 0;
                }
            }
        }
        return *this;
    }

    matrix& kolumna(int x, int* t) {
        if (x >= 0 && x < n) {
            for (int i = 0; i < n; ++i) {
                data[i][x] = t[i];
            }
        }
        return *this;
    }

    matrix& wiersz(int y, int* t) {
        if (y >= 0 && y < n) {
            for (int j = 0; j < n; ++j) {
                data[y][j] = t[j];
            }
        }
        return *this;
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

    matrix& operator*(matrix& m) {
        matrix* result = new matrix(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int sum = 0;
                for (int k = 0; k < n; ++k) {
                    sum += data[i][k] * m.data[k][j];
                }
                result->data[i][j] = sum;
            }
        }
        return *result;
    }

    matrix& operator+(int a) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i][j] += a;
            }
        }
        return *this;
    }

    matrix& operator*(int a) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i][j] *= a;
            }
        }
        return *this;
    }

    matrix& operator-(int a) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i][j] -= a;
            }
        }
        return *this;
    }

    friend matrix operator+(int a, matrix& m) {
        matrix result = m;
        result + a;
        return result;
    }

    friend matrix operator*(int a, matrix& m) {
        matrix result = m;
        result * a;
        return result;
    }

    friend matrix operator-(int a, matrix& m) {
        matrix result = m;
        result - a;
        return result;
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

    std::cout << "\nMacierz B:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << m2.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    matrix result_add = m1 + m2;
    std::cout << "\nSuma macierzy A i B:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << result_add.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    matrix result_multiply = m1 * m2;
    std::cout << "\nIloczyn macierzy A i B:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << result_multiply.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    matrix result_scalar_multiply = m1 * 5;
    std::cout << "\nMacierz A pomnożona przez 5:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << result_scalar_multiply.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    matrix result_scalar_add = m1 + 3;
    std::cout << "\nMacierz A powiększona o 3:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << result_scalar_add.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    matrix result_scalar_subtract = 2 - m1;
    std::cout << "\n2 odjęte od macierzy A:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << result_scalar_subtract.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    return 0;
}