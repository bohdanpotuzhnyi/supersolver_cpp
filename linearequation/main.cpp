#include <iostream>
#include <iomanip>
#include <forward_list>

inline int mod(int x, int n) {
    return (x < 0 ? x%n + n : x%n);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int a, b, n;
    std::cout << "Enter a, b, n for the equation ax=b(mod n)" << std::endl;
    std::cin >> a >> b >> n;

    std::cout << a << "*x = " << b << "(mod " << n << ')' << std::endl;
    int a_old = a, b_old = b;
    a = mod(a, n);
    b = mod(b, n);
    if (a_old != a || b_old != b) {
        std::cout << a << "*x = " << b << "(mod " << n << ')' << std::endl;
    }
    std::cout << std::endl;

    int r_ = n, r_1 = a, r_2, q_;
    std::forward_list<int> r{r_1, r_}, q; //result of euclidean algorithm: r, q
    auto r_iter = ++r.begin(), q_iter = q.before_begin();
    while (r_ != 0) {
        r_2 = r_1;
        r_1 = r_;
        q_ = (int) r_2 / r_1;
        q.insert_after(q_iter, q_);
        ++q_iter;
        r_ = r_2 - r_1 * q_;
        r.insert_after(r_iter, r_);
        ++r_iter;
    }
    int d = r_1;

    //gcd(a, n) = gcd(<a>, <n>) = <d>
    std::cout << "d = gcd(a, n) = gcd(" << a << ", " << n << ") = " << d << std::endl;

    r_iter = r.begin();
    r_1 = *r_iter++;
    r_ = *r_iter++;
    q_iter = q.begin();
    while (r_iter != r.end()) {
        r_2 = r_1;
        r_1 = r_;
        r_ = *r_iter++;
        q_ = *q_iter++;
        //<r_2> = <r_1>*<q_> + <r_>
        std::cout << r_2 << " = " << r_1 << '*' << q_ << " + " << r_ << std::endl;
    }
    std::cout << std::endl;

    if (b%d == 0) {
        std::cout << "b : d =>" << std::endl;

        //delete last element
        auto prev = q.before_begin(), it = ++q.begin();
        while (it != q.end()) {
            ++prev;
            ++it;
        }
        q.erase_after(prev);

        //calculate u and v
        int u_ = 0, u_1 = 1, u_2;
        int v_ = 1, v_1 = 0, v_2;
        std::forward_list<int> u{u_1, u_}, v{v_1, v_};
        auto u_iter = ++u.begin(), v_iter = ++v.begin();
        q_iter = q.begin();
        while (q_iter != q.end()) {
            q_ = *q_iter++;

            u_2 = u_1;
            u_1 = u_;
            u_ = u_2 - u_1*q_;
            u.insert_after(u_iter, u_);
            ++u_iter;

            v_2 = v_1;
            v_1 = v_;
            v_ = v_2 - v_1*q_;
            v.insert_after(v_iter, v_);
            ++v_iter;
        }
        int a_1 = *u_iter; //a^-1 (mod n)

        const int width = 5;
        std::cout << std::left << std::setw(width) << "";
        for (int t : q) {
            std::cout << std::left << std::setw(width) << t;
        }
        std::cout << std::endl;
        for (int t : u) {
            std::cout << std::left << std::setw(width) << t;
        }
        std::cout << " = a^-1(mod n)" << std::endl;
        for (int t : v) {
            std::cout << std::left << std::setw(width) << t;
        }
        std::cout << std::endl << std::endl;

        if (d == 1) {
            std::cout << "d == 1 => there is 1 root" << std::endl;
            std::cout << "x = a^-1*b(mod n)" << std::endl;
            int x = a_1*b;
            std::cout << "x = " << a_1 << '*' << b << "(mod " << n << ")" << std::endl;
            std::cout << "x = " << x << "(mod " << n << ")" << std::endl;
            if (x < 0 || x >= n) {
                x %= n;
                if (x < 0)
                    x += n;
                std::cout << "x = " << x << "(mod " << n << ")" << std::endl;
            }
        }
        else {
            std::cout << "d == " << d << " => there is " << d << " roots" << std::endl;
            int a_ = a/d, b_ = b/d, n_ = n/d;
            std::cout << "a' = a/d = " << a_ << std::endl;
            std::cout << "b' = b/d = " << b_ << std::endl;
            std::cout << "n' = n/d = " << n_ << std::endl;
            std::cout << "a'*x' = b'(mod n')" << std::endl;
            std::cout << "x' = a'^-1*b'(mod n')" << std::endl;
            std::cout << "a'^-1 = a^-1 = " << a_1 << std::endl;
            int x_ = a_1 * b_;
            std::cout << "x' = " << a_1 << '*' << b_ << "(mod " << n_ << ")" << std::endl;
            std::cout << "x' = " << x_ << "(mod " << n_ << ")" << std::endl;
            int x_old = x_;
            x_ = mod(x_, n);
            if (x_old != x_) {
                std::cout << "x' = " << x_ << "(mod " << n_ << ")" << std::endl;
            }
            for (int i = 0; i < d; ++i) {
                std::cout << "x_" << i + 1 << " = " << x_ + i * n_ << "(mod " << n << ')' << std::endl;
            }
        }
    }
    else {
        //<b> !: <d> => no roots
        std::cout << b << " !: " << d << " => no roots" << std::endl;
    }

    return 0;
}
