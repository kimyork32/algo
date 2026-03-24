template <typename T>
T power(T a, long long b) {
    T res = 1;
    while (b > 0) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

template <typename U>
class Modular {
public:
    using Type = typename decay<decltype(U::value)>::type;
    Type value;
    Modular() : value() {}
    template <typename T>
    Modular(const T& x) {
        value = normalize(x);
    }

    template <typename T>
    Type normalize(const T& x) {
    Type v;
    if (-U::value <= x && x < U::value) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % U::value);
    if (v < 0) v += U::value;
    return v;
    }
    const Type& operator()() const { return value; }
    Modular& operator+=(const Modular& other) {
        if ((value += other.value) >= U::value) value -= U::value;
        return *this;
    }
    Modular& operator-=(const Modular& other) {
        if ((value -= other.value) < 0) value += U::value;
        return *this;
    }
    Modular& operator*=(const Modular& other) {
        value = static_cast<Type>((__int128_t)value * other.value % U::value);
        return *this;
    }

    friend Modular operator+(const Modular& a, const Modular& b) { return Modular(a) += b; }
    friend Modular operator-(const Modular& a, const Modular& b) { return Modular(a) -= b; }
    friend Modular operator*(const Modular& a, const Modular& b) { return Modular(a) *= b; }

    template <typename T> friend bool operator==(const Modular& a, const T& b) { return a.value == Modular(b).value; }
    template <typename T> friend bool operator!=(const Modular& a, const T& b) { return a.value != Modular(b).value; }
    friend bool operator==(const Modular& a, const Modular& b) { return a.value == b.value; }
    friend bool operator!=(const Modular& a, const Modular& b) { return a.value != b.value; }
};

