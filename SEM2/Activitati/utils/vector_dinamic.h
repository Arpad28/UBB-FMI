#pragma once

template<typename T>
class VectorDinamic {
private:
    T* elems;
    int dim;
    int cap;

    void resize() {
        cap *= 2;
        T* nou = new T[cap];
        for (int i = 0; i < dim; i++)
            nou[i] = elems[i];
        delete[] elems;
        elems = nou;
    }

public:
    // 1. Constructor
    VectorDinamic(int c = 2) : dim(0), cap(c) {
        elems = new T[cap];
    }

    // 2. Copy Constructor
    VectorDinamic(const VectorDinamic& ot) : dim(ot.dim), cap(ot.cap) {
        elems = new T[cap];
        for (int i = 0; i < dim; i++) {
            elems[i] = ot.elems[i];
        }
    }

    // 3. Assignment Operator (Exception Safe)
    VectorDinamic& operator=(const VectorDinamic& ot) {
        if (this == &ot) {
            return *this;
        }
        T* nou = new T[ot.cap];
        for (int i = 0; i < ot.dim; i++) {
            nou[i] = ot.elems[i];
        }
        delete[] elems;
        elems = nou;
        dim = ot.dim;
        cap = ot.cap;
        return *this;
    }

    // 4. Move Constructor
    VectorDinamic(VectorDinamic&& ot) noexcept : elems(ot.elems), dim(ot.dim), cap(ot.cap) {
        ot.elems = nullptr;
        ot.dim = 0;
        ot.cap = 0;
    }

    // 5. Move Assignment
    VectorDinamic& operator=(VectorDinamic&& ot) noexcept {
        if (this == &ot) return *this;
        delete[] elems;
        elems = ot.elems;
        dim = ot.dim;
        cap = ot.cap;
        ot.elems = nullptr;
        ot.dim = 0;
        ot.cap = 0;
        return *this;
    }

    // 6. Destructor
    ~VectorDinamic() {
        delete[] elems;
    }

    void push_back(const T& el) {
        if (dim == cap) resize();
        elems[dim++] = el;
    }

    void erase(int poz) {
        for (int i = poz; i < dim - 1; i++)
            elems[i] = elems[i + 1];
        dim--;
    }

    int size() const { return dim; }

    T& operator[](int poz) { return elems[poz]; }
    const T& operator[](int poz) const { return elems[poz]; }

    // ITERATORI
    class iterator {
    private:
        T* ptr;
    public:
        iterator(T* p) : ptr(p) {}
        T& operator*() { return *ptr; }
        iterator& operator++() { ptr++; return *this; }
        iterator operator++(int) { iterator temp = *this; ptr++; return temp; }
        bool operator==(const iterator& ot) const { return ptr == ot.ptr; }
        bool operator!=(const iterator& ot) const { return ptr != ot.ptr; }
    };

    class const_iterator {
    private:
        const T* ptr;
    public:
        const_iterator(const T* p) : ptr(p) {}
        const T& operator*() const { return *ptr; }
        const_iterator& operator++() { ptr++; return *this; }
        const_iterator operator++(int) { const_iterator temp = *this; ptr++; return temp; }
        bool operator==(const const_iterator& ot) const { return ptr == ot.ptr; }
        bool operator!=(const const_iterator& ot) const { return ptr != ot.ptr; }
    };

    iterator begin() { return iterator(elems); }
    iterator end() { return iterator(elems + dim); }
    const_iterator begin() const { return const_iterator(elems); }
    const_iterator end() const { return const_iterator(elems + dim); }
};