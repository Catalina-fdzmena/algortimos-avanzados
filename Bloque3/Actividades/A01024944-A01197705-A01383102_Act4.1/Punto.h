class Punto {
    private:
        int x;
        int y;

    public:
        Punto();
        Punto(int x, int y);
};

Punto::Punto() {
    this->x = 0;
    this->y = 0;
}

Punto::Punto(int x, int y) {
    this->x = x;
    this->y = y;
}