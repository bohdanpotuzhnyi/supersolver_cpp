#include <iostream>
#include <forward_list>

inline int mod(int x, int n) {
    return (x < 0 ? x%n + n : x%n);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int a, b, n;
    std::cout << "Enter a, b, n for the equation ax=b(mod n)" << std::endl;
    std::cin >> a >> b >> n;

    std::cout << "\\documentclass{article}" << std::endl;
    std::cout << "\\usepackage[T2A,T1]{fontenc}" << std::endl;
    std::cout << "\\usepackage[utf8]{inputenc}" << std::endl;
    std::cout << "\\usepackage[english,russian,ukrainian]{babel}" << std::endl;
    std::cout << "\\usepackage[a6paper]{geometry}" << std::endl;
    std::cout << "\\usepackage{lmodern}" << std::endl;
    std::cout << "\\usepackage{textcomp}" << std::endl;
    std::cout << "\\usepackage{lastpage}" << std::endl;
    std::cout << "\\usepackage{amsmath}" << std::endl;
    std::cout << "\\usepackage{amsfonts}" << std::endl;
    std::cout << "\\usepackage{amssymb}" << std::endl;
    std::cout << "\\usepackage{centernot}" << std::endl;
    std::cout << "\\pagenumbering{gobble}" << std::endl;
    std::cout << "\\begin{document}" << std::endl;
    std::cout << "\\begin{math}" << std::endl;

    std::cout << a << "x \\equiv " << b << " \\pmod{" << n << "} \\\\" << std::endl;
    int a_old = a, b_old = b;
    a = mod(a, n);
    b = mod(b, n);
    if (a_old != a || b_old != b) {
        std::cout << a << "x \\equiv " << b << " \\pmod{" << n << "} \\\\" << std::endl;
    }
    std::cout << "\\\\" << std::endl;

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
    std::cout << "d = \\gcd(a, n) = \\gcd(" << a << ", " << n << ") = " << d << "\\\\" << std::endl;

    r_iter = r.begin();
    r_1 = *r_iter++;
    r_ = *r_iter++;
    q_iter = q.begin();
    while (r_iter != r.end()) {
        r_2 = r_1;
        r_1 = r_;
        r_ = *r_iter++;
        q_ = *q_iter++;
        std::cout << r_2 << " = " << r_1 << " \\cdot " << q_ << " + " << r_ << " \\\\" << std::endl;
    }
    std::cout << "\\\\" << std::endl;

    if (b%d == 0) {
        std::cout << R"(b \;\vdots\; d \Rightarrow \\)" << std::endl;

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

        std::cout << "\\begin{array}{c|c";
        for (auto i = q.begin(); i != q.end(); ++i) {
            std::cout << "|c";
        }
        std::cout << "|c c}" << std::endl;
        std::cout << "q_i &";
        for (int t : q) {
            std::cout << " & " << t;
        }
        std::cout << " \\\\" << std::endl;
        std::cout << "\\hline" << std::endl;
        std::cout << "u_i";
        for (int t : u) {
            std::cout << " & " << t;
        }
        std::cout << " & = a^{-1} \\\\" << std::endl;
        std::cout << "\\hline" << std::endl;
        std::cout << "v_i";
        for (int t : v) {
            std::cout << " & " << t;
        }
        std::cout << " \\\\" << std::endl ;
        std::cout << "\\hline" << std::endl;
        std::cout << "\\end{array}" << std::endl;

        std::cout << R"(\\ \\ \\)" << std::endl ;

        if (d == 1) {
            std::cout << "d = 1 \\implies \\text{уравнение имеет 1 корень} \\\\" << std::endl;
            std::cout << R"(x \equiv a^{-1} \cdot b \pmod n \\)" << std::endl;
            int x = a_1*b;
            std::cout << "x \\equiv " << a_1 << " \\cdot " << b << " \\pmod{" << n << "} \\\\" << std::endl;
            std::cout << "x \\equiv " << x << " \\pmod{" << n << "}" << std::endl;
            if (x < 0 || x >= n) {
                x %= n;
                if (x < 0)
                    x += n;
                std::cout << "\\\\ " << "x \\equiv " << x << " \\pmod{" << n << "}" << std::endl;
            }
        }
        else {
            std::cout << "d = " << d << " \\implies \\text{всего корней " << d << "} \\\\" << std::endl;
            int a_ = a/d, b_ = b/d, n_ = n/d;
            std::cout << "a' = \\frac{a}{d} = " << a_ << " \\\\" << std::endl;
            std::cout << "b' = \\frac{b}{d} = " << b_ << " \\\\" << std::endl;
            std::cout << "n' = \\frac{n}{d} = " << n_ << " \\\\" << std::endl;
            std::cout << R"(a' \cdot x' \equiv b' \pmod{n'} \\)" << std::endl;
            std::cout << R"(x' \equiv a'^{-1} \cdot b' \pmod{n'} \\)" << std::endl;
            std::cout << "a'^{-1} = a^{-1} = " << a_1 << " \\\\" << std::endl;
            int x_ = a_1 * b_;
            std::cout << "x' \\equiv " << a_1 << " \\cdot " << b_ << " \\pmod{" << n_ << "} \\\\" << std::endl;
            std::cout << "x' \\equiv " << x_ << " \\pmod{" << n_ << "} \\\\" << std::endl;
            int x_old = x_;
            x_ = mod(x_, n);
            if (x_old != x_) {
                std::cout << "x' \\equiv " << x_ << " \\pmod{" << n_ << "} \\\\" << std::endl;
            }
            for (int i = 0; i < d; ++i) {
                std::cout << "\\\\ x_" << i + 1 << " \\equiv " << x_ + i * n_ << " \\pmod{" << n << "}" << std::endl;
            }
        }
    }
    else {
        std::cout << b << " \\centernot\\vdots " << d << " \\implies \\text{корней нет}" << std::endl;
    }

    std::cout << "\\end{math}" << std::endl;
    std::cout << "\\end{document}" << std::endl;

    return 0;
}
