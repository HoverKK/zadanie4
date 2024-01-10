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
};

int main() {
    matrix m;
    m.alokuj(30).losuj();
    std::cout << "Losowa macierz 30x30:\n";
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            std::cout << m.pokaz(i, j) << " ";
        }
        std::cout << "\n";
    }

    return 0;
}