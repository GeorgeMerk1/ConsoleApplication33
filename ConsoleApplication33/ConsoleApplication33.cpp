#include <iostream>
#include "string.h"

using namespace std;

#pragma region name

class Name
{
    char* firstName;
    char* secondName;

    void setCharArray(char*& dest, const char* source) {
        int strSize = strlen(source) + 1;
        dest = new char[strSize];
        strcpy_s(dest, strSize, source);
    }

    void remove() {
        if (firstName != nullptr) {
            delete[] firstName;
        }
        if (secondName != nullptr) {
            delete[] secondName;
        }
    }

public:
    Name(const char* _firstName, const char* _secondName) {
        setCharArray(firstName, _firstName);
        setCharArray(secondName, _secondName);
    }

    Name() {
        firstName = nullptr;
        secondName = nullptr;
    }

    Name(const Name& name) {
        setCharArray(firstName, name.firstName);
        setCharArray(secondName, name.secondName);
    }

    ~Name() {
        remove();
    }

    void print() {
        cout << firstName << " " << secondName << endl;
    }

    Name& operator= (const Name& name) {
        if (this == &name) {
            return *this;
        }

        remove();

        setCharArray(firstName, name.firstName);
        setCharArray(secondName, name.secondName);
        return *this;
    }

    friend ostream& operator<< (ostream& out, const Name& name);
};
#pragma endregion

#pragma region points

class Point2D {
    double x;
    double y;

public:
    Point2D(double _x, double _y) {
        x = _x;
        y = _y;
    }

    void print() const {
        cout << "(" << x << ", " << y << ")\n";
    }

    friend Point2D operator+ (const Point2D& p1, const Point2D& p2);

    friend Point2D operator* (const Point2D& p1, int a);

    friend bool operator== (const Point2D& p1, const Point2D& p2);

    friend bool operator!= (const Point2D& p1, const Point2D& p2);

    friend bool operator> (const Point2D& p1, const Point2D& p2);

    Point2D& operator++() {
        ++x; ++y; return *this;
    }

    Point2D& operator+= (const Point2D& p2) {
        x += p2.x;
        y += p2.y;
        return *this;
    }

    Point2D operator++(int) {
        Point2D p(x, y); // мы сохранили нашу точку
        ++(*this);
        return p;
    }

    friend ostream& operator<< (ostream& out, const Point2D& point);

    friend istream& operator>> (istream& in, Point2D& point);
};


ostream& operator<< (ostream& out, const Point2D& point) {
    out << "(" << point.x << ", " << point.y << ")";
    return out;
}

istream& operator>> (istream& in, Point2D& point) {
    cout << "Введите x: ";
    in >> point.x;
    in.ignore(1);
    cout << "\nВведите y: ";
    in >> point.y;
    return in;
}

Point2D operator+ (const Point2D& p1, const Point2D& p2) {
    return Point2D(p1.x + p2.x, p1.y + p2.y);
}

Point2D operator* (const Point2D& p1, int a) {
    return Point2D(p1.x * a, p1.y * a);
}

bool operator== (const Point2D& p1, const Point2D& p2) {
    return (p1.x == p2.x) and (p1.y == p2.y);
}

bool operator!= (const Point2D& p1, const Point2D& p2) {
    return (p1.x != p2.x) or (p1.y != p2.y);
}

bool operator> (const Point2D& p1, const Point2D& p2) {
    return (p1.x * p1.x + p1.y * p1.y) > (p2.x * p2.x + p2.y * p2.y);
}

bool operator>= (const Point2D& p1, const Point2D& p2) {
    return (p1 > p2) or (p1 == p2);
}

bool operator< (const Point2D& p1, const Point2D& p2) {
    return !(p1 >= p2);
}

bool operator<= (const Point2D& p1, const Point2D& p2) {
    return !(p1 > p2);
}

/// <summary>
/// перегрузить <, <= ...
/// </summary>
/// <returns></returns>

#pragma endregion

class Array {
private:
    int size;
    int* array;

    friend ostream& operator<< (ostream& output, const Array& arr);
    friend istream& operator>> (istream& input, Array& arr);

public:
    explicit Array(int size = 10);
    Array(const Array& arr);
    ~Array();
    int length() const;

    const Array& operator=(const Array& arr);
    bool operator== (const Array& arr) const;
    bool operator!= (const Array& arr) const {
        return !(*this == arr);
    }

    int& operator[](int);
    int operator[](int) const;
};

ostream& operator<< (ostream& output, const Array& arr)
{
    for (int i = 0; i < arr.size; i++)
    {
        output << arr[i] << ", ";
    }
    return output;
}


istream& operator>> (istream& input, Array& arr)
{
    for (int i = 0; i < arr.size; i++)
    {
        input >> arr[i];
    }
    return input;
}

Array::Array(int size) {
    this->size = size;
    array = new int[size];
}

Array::Array(const Array& arr) {
    size = arr.size;
    array = new int[arr.size];
    for (int i = 0; i < arr.size; i++)
    {
        array[i] = arr[i];
    }
}

Array::~Array() {
    delete[] array;
}

int Array::length() const {
    return size;
}

bool Array::operator== (const Array& arr) const {
    if (&*this == &arr) {
        return true;
    }

    if (size != arr.size) {
        return false;
    }

    for (int i = 0; i < size; i++)
    {
        if (array[i] != arr[i]) {
            return false;
        }
    }

    return true;
}

const Array& Array::operator= (const Array& arr) {
    if (*this == arr) {
        return *this;
    }

    if (size != arr.size) {
        delete[] array;
        size = arr.size;
        array = new int[size];
    }

    for (int i = 0; i < size; i++)
    {
        array[i] = arr[i]; // == arr.array[]
    }

    return *this;
}

int& Array::operator[](int index) {
    if (index < 0 or index >= size) {
        cout << "Индекс за пределами массива";
    }
    return array[index];
}

int Array::operator[](int index) const {
    if (index < 0 or index >= size) {
        cout << "Индекс за пределами массива";
    }
    return array[index];
}

int main()
{
    setlocale(LC_ALL, "rus");

    Array a1(5);
    Array a2;

    for (int i = 0; i < 5; i++)
    {
        a1[i] = i;
    }

    for (int i = 0; i < 10; i++)
    {
        a2[i] = i * 5;
    }
    cout << "Размер a1: " << a1.length() << endl;
    cout << "a1: " << a1 << endl;

    cout << "Размер a1: " << a2.length() << endl;
    cout << "a1: " << a2 << endl;



    cout << "a1 == a2: " << (a1 == a2) << endl;

    Array a3(a1);

    cout << "a3: " << a3 << endl;

    cout << "a1 == a3: " << (a1 == a3) << endl;

    Array a4(4);

    cin >> a4;
    cout << "a4: " << a4 << endl;

    Array a5;
    a5 = a4;
    cout << a5;

    const Array a6( a4 );
    a5[2] = 10;
    
    /*int c;

    Point2D p(1,1);
    cin >> p >> c;
    cout << p << endl << c << endl;

    char firstName[10] = "Иван";
    char secondName[10] = "Петров";

    {
        Name n1(firstName, secondName);
        cout << "Конструктор сработал: ";
        n1.print();
    }

    cout << "Сработал деструктор для n1\n";

    {
        Name n2(firstName, secondName);
        cout << "Конструктор сработал: ";
        n2.print();

        Name n3(n2);
        cout << "Конструктор копирования сработал: ";
        n3.print();
    }

    cout << "Сработал деструктор для n2, n3\n";

    Name name;

    {
        Name n4("эн четыре", secondName);
        cout << "Конструктор сработал: " << n4;

        name = n4;
        cout << "Присвоили name n4: ";
        name.print();
    }

    cout << "Сработал деструктор для n4\n";

    cout << "Обращаемся к name: ";
    name.print();

    Name n5("Пример", "Примеров");
    n5.print();

    Name n6("Прикол", "Приколов");
    n6.print();

    n5 = n6;

    n5 = n5;
    n5.print();*/
}
