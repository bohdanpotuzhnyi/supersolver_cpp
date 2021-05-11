//
// Created by Bohdan Potuzhnyi on 5/11/2021.
//
#include "fstream"
using namespace std;

void prefix(int s, int f,int arr[], ofstream &file){
    for(int i = s; i<f; i++){
        file << arr[i] << "\\cdot";
    }
}

void prefix2(int s, int f, int arr[], int pow2, ofstream &file){
    for(int i = s; i<f; i++){
        file << arr[i] << "\\cdot";
    }
    file << "2^{" << pow2 << "}";
}

int get_mod2(int a, int pow, int pow2, int mod, ofstream &file){
    int k = 0, f = 0;
    int arr[1200];
    int res = 0;
    while(pow >= 2){
        if(pow % 2 != 0){
            pow --;
            arr[f] = a;
            f++;
            prefix2(k, f, arr, pow2, file);
            file << a <<"^{" << pow <<"}(\\mod"<< mod << ") = ";
        }else{
            if(pow > 2) {
                pow /= 2;
                prefix2(k, f, arr, pow2, file);
                file << "(" << a << "^{2}" << ")^{" << pow << "}(\\mod" << mod << ") = ";
                prefix2(k, f, arr, pow2, file);
                if ((a * a) % mod < mod / 2) {
                    file << "(" << (a * a) % mod << ")^{" << pow << "}(\\mod" << mod << ") = ";
                    a = (a * a) % mod;
                } else {
                    file << "(" << ((a * a) % mod) - mod << ")^{" << pow << "}(\\mod" << mod << ") = ";
                    a = (a * a % mod) - mod;
                }
            }else{
                prefix2(k, f, arr, pow2, file);
                pow -= 2;
                file << (a * a) % mod << "(\\mod" << mod << ") = ";
                a = (a * a) % mod;
            }
        }
    }
    for(int i = f-1; i >= 0; i--){
        if(i > 0){
            if(((arr[i]*a)%mod<mod/2)) {
                prefix2(0, i, arr, pow2, file);
                file <<  (arr[i]*a) % mod << "(\\mod"<< mod << ") = ";
                a = (arr[i]*a) % mod;
            }else{
                prefix2(0, i, arr, pow2, file);
                file <<  ((arr[i]*a) % mod)-mod << "(\\mod"<< mod << ") = ";
                a = (arr[i]*a % mod)-mod;
            }
        }else {
            int s = (arr[i]*a)%mod;
            if((s<mod/2)) {
                file << "2^{" << pow2 << "}";
                file << (arr[i]*a) % mod << "(\\mod" << mod << ") = ";
                a = (arr[i] * a) % mod;
            }else{
                file << "2^{" << pow2 << "}";
                file <<  ((arr[i]*a) % mod)-mod << "(\\mod"<< mod << ") = ";
                a = (arr[i]*a % mod)-mod;
            }
        }
    }
    f = 0;
    int a1 = 2;
    while(pow2 >= 2){
        if(pow2 % 2 != 0){
            pow2--;
            arr[f] = a1;
            f++;
            if(f>0) prefix(k, f, arr, file);
            file << a <<"\\cdot"<< a1 << "^{" << pow2 <<"}(\\mod"<< mod << ") = ";
        }else{
            if(pow2 > 2) {
                pow2 /= 2;
                if (f > 0) prefix(k, f, arr, file);
                file << a << "(\\cdot" << a1 << "^{2}" << ")^{" << pow2 << "}(\\mod" << mod << ") = ";
                if (f > 0) prefix(k, f, arr, file);
                if ((4) % mod < mod / 2) {
                    file << a <<"(" << (a1 * a1) % mod << ")^{" << pow2 << "}(\\mod" << mod << ") = ";
                    a1 = (a1 * a1) % mod;
                } else {
                    file << a << "(" << ((a1 * a1) % mod) - mod << ")^{" << pow2 << "}(\\mod" << mod << ") = ";
                    a1 = (a1 * a1 % mod) - mod;
                }
            }else{
                if (f > 0) prefix(k, f, arr, file);
                pow2 -= 2;
                file << a << "\\cdot" <<  (a1 * a1) % mod << "(\\mod" << mod << ") = ";
                a1 = (a1 * a1) % mod;
            }
        }
    }

    for(int i = f-1; i >= 0; i--){
        if(i > 0){
            if(((arr[i]*a1)%mod<mod/2)) {
                prefix(0, i, arr, file);
                file << a << "\\cdot" <<  (arr[i]*a1) % mod << "(\\mod"<< mod << ") = ";
                a1 = (arr[i]*a1) % mod;
            }else{
                prefix(0, i, arr, file);
                file << a << "\\cdot"<<  ((arr[i]*a1) % mod)-mod << "(\\mod"<< mod << ") = ";
                a1 = (arr[i]*a1 % mod)-mod;
            }
        }else {
            int s = (arr[i]*a1)%mod;
            if((s<mod/2)) {
                file << a << "\\cdot" << (arr[i]*a) % mod << "(\\mod" << mod << ") = ";
                a1 = (arr[i] * a1) % mod;
            }else{
                file << a << "\\cdot" << ((arr[i]*a) % mod)-mod << "(\\mod"<< mod << ") = ";
                a1 = (arr[i]*a1 % mod)-mod;
            }
        }
    }
    file << a << "\\cdot" << a1 << "(\\mod " << mod << ") = ";
    a = (a*a1) % mod;
    if(a<0){a += mod;}
    file << a << "\\\\\\\\";
    return a;
}
int get_mod(int a,int pow, int mod, ofstream &file){
    int k = 0, f = 0;
    int arr[1200];
    int p = pow;
    int res = 0;
    while(pow >= 2){
        if(pow % 2 != 0){
            pow --;
            arr[f] = a;
            f++;
            if(f>0) prefix(k, f, arr, file);
            file << a <<"^{" << pow <<"}(\\mod"<< mod << ") = ";
        }else{
            if(pow > 2) {
                pow /= 2;
                if (f > 0) prefix(k, f, arr, file);
                file << "(" << a << "^{2}" << ")^{" << pow << "}(\\mod" << mod << ") = ";
                if (f > 0) prefix(k, f, arr, file);
                if ((a * a) % mod < mod / 2) {
                    file << "(" << (a * a) % mod << ")^{" << pow << "}(\\mod" << mod << ") = ";
                    res = (a * a) % mod;
                    a = (a * a) % mod;
                } else {
                    file << "(" << ((a * a) % mod) - mod << ")^{" << pow << "}(\\mod" << mod << ") = ";
                    res = (a * a % mod) - mod;
                    a = (a * a % mod) - mod;
                }
            }else{

                if (f > 0) prefix(k, f, arr, file);
                pow -= 2;
                file << (a * a) % mod << "(\\mod" << mod << ") = ";
                res = (a * a) % mod;
                a = (a * a) % mod;
            }
        }
    }
    for(int i = f-1; i >= 0; i--){
        if(i > 0){
            if(((arr[i]*a)%mod<mod/2)) {
                prefix(0, i, arr, file);
                file <<  (arr[i]*a) % mod << "(\\mod"<< mod << ") = ";
                res = (arr[i]*a) % mod;
                a = (arr[i]*a) % mod;
            }else{
                prefix(0, i, arr, file);
                file <<  ((arr[i]*a) % mod)-mod << "(\\mod"<< mod << ") = ";
                res = (arr[i]*a % mod)-mod;
                a = (arr[i]*a % mod)-mod;
            }
        }else {
            int s = (arr[i]*a)%mod;
            if((s<mod/2)) {
                file << (arr[i]*a) % mod << "(\\mod" << mod << ") = ";
                res = (arr[i] * a) % mod;
                a = (arr[i] * a) % mod;
            }else{
                file <<  ((arr[i]*a) % mod)-mod << "(\\mod"<< mod << ") = ";
                res = (arr[i]*a % mod)-mod;
                a = (arr[i]*a % mod)-mod;
            }
        }
    }
    if(res<0){res += mod;}
    file << res << "\\\\\\\\";
    return res;
}

int main(int argc, char *argv[]){
//int main(){
    //syntax <res> <a> <p> <path>

    int res = atoi(argv[1]);
    int a = atoi(argv[2]);
    int p = atoi(argv[3]);

    std::ofstream file(argv[4]);
    /*
    std::ofstream file;
    file.open(argv[4], std::ios_base::app);
    */
    //path id res a p



    if(res == 1){
        if(p % 4 == 3){
            int p1 = p/4;
            file << "\\\\\\\\";
            file << "p = 4*"<<p1<<" + 3\\\\\\\\";
            p1++;
            file << "x = \\pm "<< a << "^{"<< p1 << "}(\\mod "<< p << " )\\\\";
            int l = 0;
            l = get_mod(a, p1, p, file);
            file << "x = \\pm " << l << "(\\mod "<< p <<")$";
        }else{
            if(p % 8 == 5){
                int p1 = p/8;
                p1 = p1*2 + 1;
                file << "\\\\\\\\p = 8*"<<p1<<" + 5\\\\\\\\";
                file << a << "^{" << p1 << "}" << "(\\mod" << p << ") = ";
                int l = 0;
                l = get_mod(a, p1, p, file);
                p1 -= 1;
                p1 /= 2;
                if(l == 1){
                    file << "x = \\pm "<< a << "^{"<< p1+1 << "}(\\mod "<< p << " ) = ";
                    l = get_mod(a, p1+1, p, file);
                    file << "x = \\pm " << l << "(\\mod "<< p <<")$";
                }else{
                    file << "x = \\pm "<< a << "^{" << p1+1 <<"} 2^{" << 2*p1+1 << "}(\\mod " << p << " ) = ";
                    l = get_mod2(a, p1+1, (p1*2 + 1), p, file);
                    file << "x = \\pm " << l << "(\\mod "<< p <<")$";
                }
            }else{
                file << "\\\\$Форма $p = 8k + 1$ на жаль, на даний момент не підтримується, але розробники працюють, чесно-чесно" << endl;
            }
        }
    }else{
        file << "\\\\$На жаль, у цього рівняння немає квадратичних лишків...";
    }
    file << "\\end{document}";
    file.close();
    return 0;
}

