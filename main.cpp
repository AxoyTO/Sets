#include <iostream>

using namespace std;

template<class T>
class Set {
private:
    T *group;
    int len;
public:
    Set() {
        len = 0;
        group = new T[len];
    }

    Set(const T *arg_group, int arg_len) {
        int count = 0;
        len = arg_len;
        int zeroFlag = 0;

        for (int i = 0; i < len; i++) {
            if (*(arg_group + i) == 0)
                zeroFlag++;
        }

        T *tmp = new T[len];

        for (int i = 0; i < len; i++)
            *(tmp + i) = *(arg_group + i);

        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j++) {
                if (*(tmp + i) == *(tmp + j))
                    *(tmp + j) = (T) NULL;
            }
        }
        for (int i = 0; i < len; i++) {
            //cout << *(tmp + i) << " ";
            if (*(tmp + i) == (T) NULL)
                count++;
        }
        len = arg_len - count;

        T k;
        for (int i = 0; i < arg_len; i++) {
            int j = i + 1;
            if (j == arg_len - count + 1)
                break;
            while (*(tmp + i) == (T) NULL) {
                k = (*(tmp + i));
                *(tmp + i) = *(tmp + j);
                *(tmp + j) = k;
                j++;
            }
        }

        //cout << zeroFlag << endl;
        if (zeroFlag == 0) {
            group = new T[len];
            for (int i = 0; i < len; i++) {
                for (int j = i; j < arg_len; j++) {
                    if (*(tmp + j) != (T) NULL) {
                        *(group + i) = *(tmp + j);
                        break;
                    }
                }
            }
        } else {
            group = new T[len + 1];
            for (int i = 0; i < len; i++) {
                for (int j = i; j < arg_len; j++) {
                    if (*(tmp + j) != (T) NULL) {
                        *(group + i) = *(tmp + j);
                        break;
                    }
                }
            }
            len++;
            *(group + len - 1) = 0;
        }

        delete[]tmp;
    }
/*
    Set(const Set &other) {
        len = other.len;
        group = new T[len];
        for (int i = 0; i < len; i++)
            *(group + i) = *(other.group + i);
    }
*/
    //операция добавления элемента в множество
    void add(T arg) {
        //len++;
        T tmp[len + 1];
        for (int i = 0; i < len; i++) {
            tmp[i] = *(group + i);
        }

        int flag = 0;
        for (int i = 0; i < len; i++) {
            if (arg == *(group + i))
                flag++;
        }

        if (!flag) {
            *(tmp + len) = arg;
            delete[]group;
            len++;
            group = new T[len];
            for (int i = 0; i < len; i++)
                *(group + i) = *(tmp + i);
        }
    }

    //операция добавления группы элементов в множество
    void add(T *arg_group, int amount) {
        int zeroFlag = 0;
        for (int i = 0; i < len; i++) {
            if (*(group + i) == 0)
                zeroFlag++;
        }

        for (int i = 0; i < amount; i++) {
            if (*(arg_group + i) == 0)
                zeroFlag++;
        }

        T *tmp = new T[len + amount];
        for (int i = 0; i < len; i++)
            *(tmp + i) = *(group + i);

        int t = 0;
        for (int i = len; i < len + amount; i++) {
            *(tmp + i) = *(arg_group + t);
            t++;
        }

        int count = 0;
        int maxLen = len + amount;

        for (int i = 0; i < maxLen; i++) {
            for (int j = i + 1; j < maxLen; j++) {
                if (*(tmp + i) == *(tmp + j))
                    *(tmp + j) = (T) NULL;
            }
        }
        for (int i = 0; i < maxLen; i++) {
            if (*(tmp + i) == (T) NULL)
                count++;
        }

        T k;
        for (int i = 0; i < maxLen; i++) {
            int j = i + 1;
            if (j == maxLen - count + 1)
                break;
            while (*(tmp + i) == (T) NULL) {
                k = (*(tmp + i));
                *(tmp + i) = *(tmp + j);
                *(tmp + j) = k;
                j++;
            }
        }

        len = maxLen - count;

        //cout <<"zeroFlag = " <<  zeroFlag << endl;
        delete[]group;
        if (zeroFlag == 0) {
            group = new T[len];
            for (int i = 0; i < len; i++) {
                *(group + i) = *(tmp + i);
            }
        } else {
            group = new T[len + 1];
            for (int i = 0; i < len; i++) {
                *(group + i) = *(tmp + i);
            }
            len++;
            *(group + len - 1) = 0;
        }

        delete[]tmp;
    }

    //операция удаления элемента
    void del(T arg) {
        int flag = 0, newFL = 0;
        if (len == 0)
            return;
        for (int i = 0; i < len; i++) {
            if (*(group + i) == arg)
                newFL++;
        }
        if (newFL == 0)
            return;

        T *tmp = new T[len - 1];
        for (int i = 0; i < len; i++) {
            if (*(group + i) != arg)
                *(tmp + i) = *(group + i);
            else {
                flag++;
                for (int j = i + 1; j < len; j++) {
                    *(tmp + i) = *(group + j);
                    i++;
                }
            }
            if (flag)
                break;
        }

        if (flag != 0) {
            delete[]group;
            len = len - 1;
            group = new T[len];
            for (int i = 0; i < len; i++) {
                *(group + i) = *(tmp + i);
            }
        }

        delete[]tmp;
        //return group;
    }

    //операция проверки вхождения элемента (in), элемент проверку, которого надо проверить передается в качестве аргумента.
    bool in(T arg) {
        int flag = 0;
        for (int i = 0; i < len; i++) {
            if (arg == *(group + i))
                flag++;
        }
        if (flag)
            return true;
        else
            return false;
    }

    //печать элементов множества по возрастанию
    void print() const {
        T tmp;
        if (len == 0) {
            cout << endl;
            return;
        }
        for (int i = 0; i < len; i++) {
            for (int j = i; j < len; j++) {
                if (*(group + j) < *(group + i)) {
                    tmp = *(group + i);
                    *(group + i) = *(group + j);
                    *(group + j) = tmp;
                }
            }
        }

        for (int i = 0; i < len; i++) {
            if (i == len - 1)
                cout << *(group + i) << endl;
            else
                cout << *(group + i) << " ";
        }
    }

    //union
    template<typename V>
    friend const Set<V> operator+(const Set<V> &op1, const Set<V> &op2);

    //equality
    const Set<T> &operator=(const Set<T> &other);

    //intersection
    template<typename V>
    friend const Set<V> operator*(const Set<V> &op1, const Set<V> &op2);

    ~Set() {
        //cout << "DELETED ";
        //print();
        delete[]group;
    }
};

template<typename V>
const Set<V> operator+(const Set<V> &op1, const Set<V> &op2) {
    Set<V> newUnion;
    int zeroFlag = 0;
    for (int i = 0; i < op1.len; i++) {
        if (*(op1.group + i) == 0)
            zeroFlag++;
    }

    for (int i = 0; i < op2.len; i++) {
        if (*(op2.group + i) == 0)
            zeroFlag++;
    }

    V tmp[op1.len + op2.len];
    for (int i = 0; i < op1.len; i++)
        *(tmp + i) = *(op1.group + i);

    int maxLen = op1.len + op2.len;
    int count = 0;
    int z = 0;
    for (int i = op1.len; i < maxLen; i++) {
        *(tmp + i) = *(op2.group + z);
        z++;
    }

    for (int i = 0; i < maxLen; i++) {
        for (int j = i + 1; j < maxLen; j++) {
            if (*(tmp + i) == *(tmp + j))
                *(tmp + j) = (V) NULL;
        }
    }

    for (int i = 0; i < maxLen; i++) {
        //cout << *(tmp + i) << " ";
        if (*(tmp + i) == (V) NULL)
            count++;
    }

    V k;
    for (int i = 0; i < maxLen; i++) {
        int j = i + 1;
        if (j == maxLen - count + 1)
            break;
        while (*(tmp + i) == (V) NULL) {
            k = (*(tmp + i));
            *(tmp + i) = *(tmp + j);
            *(tmp + j) = k;
            j++;
        }
    }

    int len = maxLen - count;
    newUnion.add(tmp, len);
    if (zeroFlag != 0) {
        newUnion.add(0);
        //len++;
    }
    return newUnion;
}

template<typename V>
const Set<V> &Set<V>::operator=(const Set<V> &other) {
    len = other.len;
    delete[]group;
    group = new V[len];
    for (int i = 0; i < len; i++) {
        *(group + i) = *(other.group + i);
    }
    return *this;
}

template<typename V>
const Set<V> operator*(const Set<V> &op1, const Set<V> &op2) {
    Set<V> newIntersect;
    int maxLen;
    if (op1.len > op2.len)
        maxLen = op1.len;
    else
        maxLen = op2.len;

    V *tmp = new V[maxLen];

    int z = 0;
    for (int i = 0; i < op1.len; i++) {
        for (int j = 0; j < op2.len; j++) {
            if (*(op1.group + i) == *(op2.group + j)) {
                *(tmp + z) = *(op1.group + i);
                z++;
            }
        }
    }

    newIntersect.add(tmp, z);
    delete[]tmp;
    return newIntersect;
}

/*
int main() {
    double a[] = {0, 2.1, 3.3, 4.4, 5.1, -1.3};
    double b[] = {6.2, 3, 2.9, 6.1};
    Set<double> seti1(a, 6), seti2(b, 4), seti3, seti4, seti5;
    if (seti2.in(0))
        cout << "yes." << endl;
    //seti2.add(b, 3);
    seti1.print();
    seti2.print();
    seti2.add(0);
    seti2.print();
    seti4 = seti3 + seti2;
    cout << "Union: ";
    seti4.print();
    seti5 = seti2 * seti1;
    cout << "Intersect: ";
    seti5.print();
    seti1.print();
    seti2.print();

    seti4 = seti1 + seti2;
    seti4.print();
    seti3.add(7);
    seti4.del(3);
    seti3.print();
    seti4.print();
    return 0;
}*/