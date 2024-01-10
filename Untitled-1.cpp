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
};

int main() {
    matrix m;
    m.alokuj(30).losuj(10);
    std::cout << "Macierz po losowaniu 10 cyfr:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << m.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    int diagonalData[30] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    m.diagonalna(diagonalData);
    std::cout << "Macierz diagonalna:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << m.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    int diagonalKData[30] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    m.diagonalna_k(5, diagonalKData);
    std::cout << "Macierz diagonalna przesunięta o 5:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << m.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    int columnData[30] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    m.kolumna(5, columnData);
    std::cout << "Macierz po wstawieniu kolumny:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << m.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    int rowData[30] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
    m.wiersz(5, rowData);
    std::cout << "Macierz po wstawieniu wiersza:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << m.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
