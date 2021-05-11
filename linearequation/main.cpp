#include <fstream>
#include <forward_list>

inline int mod(int x, int n) {
    return (x < 0 ? x%n + n : x%n);
}

//Syntax: ./linearequation <a> <b> <n> <path for solution>
int main(int argc, char *argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int n = atoi(argv[3]);

    std::ofstream file(argv[4]);

    file << "\\documentclass{article}" << std::endl;
    file << "\\usepackage[T2A,T1]{fontenc}" << std::endl;
    file << "\\usepackage[utf8]{inputenc}" << std::endl;
    file << "\\usepackage[english,russian,ukrainian]{babel}" << std::endl;
    file << "\\usepackage[a6paper]{geometry}" << std::endl;
    file << "\\usepackage{lmodern}" << std::endl;
    file << "\\usepackage{textcomp}" << std::endl;
    file << "\\usepackage{lastpage}" << std::endl;
    file << "\\usepackage{amsmath}" << std::endl;
    file << "\\usepackage{amsfonts}" << std::endl;
    file << "\\usepackage{amssymb}" << std::endl;
    file << "\\usepackage{centernot}" << std::endl;
    file << "\\pagenumbering{gobble}" << std::endl;
    file << "\\begin{document}" << std::endl;
    file << "\\begin{math}" << std::endl;

    file << a << "x \\equiv " << b << " \\pmod{" << n << "} \\\\" << std::endl;
    int a_old = a, b_old = b;
    a = mod(a, n);
    b = mod(b, n);
    if (a_old != a || b_old != b) {
        file << a << "x \\equiv " << b << " \\pmod{" << n << "} \\\\" << std::endl;
    }
    file << "\\\\" << std::endl;

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
    file << "d = \\gcd(a, n) = \\gcd(" << a << ", " << n << ") = " << d << "\\\\" << std::endl;

    r_iter = r.begin();
    r_1 = *r_iter++;
    r_ = *r_iter++;
    q_iter = q.begin();
    while (r_iter != r.end()) {
        r_2 = r_1;
        r_1 = r_;
        r_ = *r_iter++;
        q_ = *q_iter++;
        file << r_2 << " = " << r_1 << " \\cdot " << q_ << " + " << r_ << " \\\\" << std::endl;
    }
    file << "\\\\" << std::endl;

    if (b%d == 0) {
        file << R"(b \;\vdots\; d \Rightarrow \\)" << std::endl;

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

        file << "\\begin{array}{c|c";
        for (auto i = q.begin(); i != q.end(); ++i) {
            file << "|c";
        }
        file << "|c c}" << std::endl;
        file << "q_i &";
        for (int t : q) {
            file << " & " << t;
        }
        file << " \\\\" << std::endl;
        file << "\\hline" << std::endl;
        file << "u_i";
        for (int t : u) {
            file << " & " << t;
        }
        file << " & = a^{-1} \\\\" << std::endl;
        file << "\\hline" << std::endl;
        file << "v_i";
        for (int t : v) {
            file << " & " << t;
        }
        file << " \\\\" << std::endl ;
        file << "\\hline" << std::endl;
        file << "\\end{array}" << std::endl;

        file << R"(\\ \\ \\)" << std::endl ;

        if (d == 1) {
            file << "d = 1 \\implies \\text{уравнение имеет 1 корень} \\\\" << std::endl;
            file << R"(x \equiv a^{-1} \cdot b \pmod n \\)" << std::endl;
            int x = a_1*b;
            file << "x \\equiv " << a_1 << " \\cdot " << b << " \\pmod{" << n << "} \\\\" << std::endl;
            file << "x \\equiv " << x << " \\pmod{" << n << "}" << std::endl;
            if (x < 0 || x >= n) {
                x %= n;
                if (x < 0)
                    x += n;
                file << "\\\\ " << "x \\equiv " << x << " \\pmod{" << n << "}" << std::endl;
            }
        }
        else {
            file << "d = " << d << " \\implies \\text{всего корней " << d << "} \\\\" << std::endl;
            int a_ = a/d, b_ = b/d, n_ = n/d;
            file << "a' = \\frac{a}{d} = " << a_ << " \\\\" << std::endl;
            file << "b' = \\frac{b}{d} = " << b_ << " \\\\" << std::endl;
            file << "n' = \\frac{n}{d} = " << n_ << " \\\\" << std::endl;
            file << R"(a' \cdot x' \equiv b' \pmod{n'} \\)" << std::endl;
            file << R"(x' \equiv a'^{-1} \cdot b' \pmod{n'} \\)" << std::endl;
            file << "a'^{-1} = a^{-1} = " << a_1 << " \\\\" << std::endl;
            int x_ = a_1 * b_;
            file << "x' \\equiv " << a_1 << " \\cdot " << b_ << " \\pmod{" << n_ << "} \\\\" << std::endl;
            file << "x' \\equiv " << x_ << " \\pmod{" << n_ << "} \\\\" << std::endl;
            int x_old = x_;
            x_ = mod(x_, n);
            if (x_old != x_) {
                file << "x' \\equiv " << x_ << " \\pmod{" << n_ << "} \\\\" << std::endl;
            }
            for (int i = 0; i < d; ++i) {
                file << "\\\\ x_" << i + 1 << " \\equiv " << x_ + i * n_ << " \\pmod{" << n << "}" << std::endl;
            }
        }
    }
    else {
        file << b << " \\centernot\\vdots " << d << " \\implies \\text{корней нет}" << std::endl;
    }

    file << "\\end{math}" << std::endl;
    file << "\\end{document}" << std::endl;

    file.close();

    return 0;
}
