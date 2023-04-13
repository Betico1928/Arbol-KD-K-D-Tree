#include <iostream>
#include <vector>
using namespace std;

struct Nodo {
    vector<int> punto;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(const vector<int>& punto) : punto(punto), izquierdo(nullptr), derecho(nullptr) {}
};

class KDTree{
private:
    Nodo* raiz;
    int k;

    Nodo* insertarRec(Nodo*, const vector<int>&, int);
    Nodo* eliminarRec(Nodo*, const vector<int>&, int);
    Nodo* minimoRec(Nodo*, int, int);
    Nodo* buscarRec(Nodo*, const vector<int>&, int);
    void preordenRec(Nodo*);
    void inordenRec(Nodo*, int);
    void postordenRec(Nodo*);

public:
    KDTree(int k) : raiz(nullptr), k(k) {}
    void insertar(const vector<int>&);
    void eliminar(const vector<int>&);
    bool buscar(const vector<int>&);
    void preorden();
    void inorden();
    void postorden();
};

Nodo* KDTree::insertarRec(Nodo* nodo, const vector<int>& punto, int profundidad) {
    if (nodo == nullptr) {
        return new Nodo(punto);
    }

    int ejeActual = profundidad % k;
    if (punto[ejeActual] < nodo->punto[ejeActual]) {
        nodo->izquierdo = insertarRec(nodo->izquierdo, punto, profundidad + 1);
    } else {
        nodo->derecho = insertarRec(nodo->derecho, punto, profundidad + 1);
    }

    return nodo;
}

void KDTree::insertar(const vector<int>& punto) {
    raiz = insertarRec(raiz, punto, 0);
}

Nodo* KDTree::eliminarRec(Nodo* nodo, const vector<int>& punto, int profundidad) {
    if (nodo == nullptr) {
        return nullptr;
    }

    int ejeActual = profundidad % k;
    if (nodo->punto == punto) {
        if (nodo->derecho != nullptr) {
            nodo->punto = minimoRec(nodo->derecho, ejeActual, profundidad + 1)->punto;
            nodo->derecho = eliminarRec(nodo->derecho, nodo->punto, profundidad + 1);
        } else if (nodo->izquierdo != nullptr) {
            nodo->punto = minimoRec(nodo->izquierdo, ejeActual, profundidad + 1)->punto;
            nodo->derecho = eliminarRec(nodo->izquierdo, nodo->punto, profundidad + 1);
            nodo->izquierdo = nullptr;
        } else {
            delete nodo;
            return nullptr;
        }
    } else if (punto[ejeActual] < nodo->punto[ejeActual]) {
        nodo->izquierdo = eliminarRec(nodo->izquierdo, punto, profundidad + 1);
    } else {
        nodo->derecho = eliminarRec(nodo->derecho, punto, profundidad + 1);
    }

    return nodo;
}

void KDTree::eliminar(const vector<int>& punto) {
    raiz = eliminarRec(raiz, punto, 0);
}

Nodo* KDTree::buscarRec(Nodo* nodo, const vector<int>& punto, int profundidad) {
    if (nodo == nullptr || nodo->punto == punto) {
        return nodo;
    }

    int ejeActual = profundidad % k;
    if (punto[ejeActual] < nodo->punto[ejeActual]) {
        return buscarRec(nodo->izquierdo, punto, profundidad + 1);
    } else {
        return buscarRec(nodo->derecho, punto, profundidad + 1);
    }
}

bool KDTree::buscar(const vector<int>& punto) {
    return buscarRec(raiz, punto, 0) != nullptr;
}

void KDTree::preordenRec(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    for (int i : nodo->punto) {
        cout << i << " ";
    }
    cout << endl;

    preordenRec(nodo->izquierdo);
    preordenRec(nodo->derecho);
}

void KDTree::preorden() {
    preordenRec(raiz);
}

void KDTree::inordenRec(Nodo* nodo, int ejeActual) {
    if (nodo == nullptr) {
        return;
    }

    inordenRec(nodo->izquierdo, (ejeActual + 1) % k);

    for (int i : nodo->punto) {
        cout << i << " ";
    }
    cout << endl;

    inordenRec(nodo->derecho, (ejeActual + 1) % k);
}

void KDTree::inorden() {
    inordenRec(raiz, 0);
}

void KDTree::postordenRec(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    postordenRec(nodo->izquierdo);
    postordenRec(nodo->derecho);

    for (int i : nodo->punto) {
        cout << i << " ";
    }
    cout << endl;
}

void KDTree::postorden() {
    postordenRec(raiz);
}

int main()
{
    // Insertar datos:
    
}