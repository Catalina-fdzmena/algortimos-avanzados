class Punto {
    public:
        Punto();
        Punto(double x, double y);
        void swapXandY();

        double x;
        double y;
};

Punto::Punto() {
    this->x = 0;
    this->y = 0;
}

Punto::Punto(double x, double y) {
    this->x = x;
    this->y = y;
}

// Se implementó un swap para no tener que escribir otro quicksort basado en Y.
// Se cambian de coordenada, se manda a llamar quicksort y una vez ordenados, se regresan a
// su variable original
void Punto::swapXandY() {
    double temp = this->x;
    this->x = this->y;
    this->y = temp;
}