#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll calc_pow(ll a, ll n, ll p){
    ll ans = 1;
    for (int i = 0; i < 20; i++)
    {
        int bit = 1 << i;
        if (n & bit) ans = (ans * a) % p;
        a = (a * a) % p;
    }
    return ans;
}
int gcd(int a, int p, int &t1, int t2)
{
    if (a == 0) return p;
    if (p == 0) return a;

    if (a < p){
        int q = p / a;
        int r = p % a;
        int t = t1 - t2 * q;
        t1 = t2;
        return gcd(a, r, t1, t);
    }
    else{
        int q = a / p;
        int r = a % p;
        int t = t1 - t2 * q;
        t1 = t2;
        return gcd(r, p, t1, t);
    }
}
int findInverse(int a, int p){
    a = (p + a % p) % p;
    int t1 = 0;
    gcd(a, p, t1, 1);
    t1 = (p + t1 % p) % p;
    return t1;
}

int main(){
    int p, q, e;
    cout << "Enter two prime numbers p and q:"; 
    cin >> p >> q; // 101 113
    cout << "Enter the value of e:"; 
    cin >> e; // 51

    int n = p * q; // 11413
    int phi_n = (p - 1) * (q - 1);  // 11200
    int d = findInverse(e, phi_n);  // 5051
    cout << "Private Key:-(" << d << "," << n << ")" << endl;
    cout << "Public Key:-(" << e << "," << n << ")" << endl;

    int m;
    cout << "Enter the message:";
    cin >> m; //1234 (should be less than n)
    int Sig = calc_pow(m, d, n);
    cout << "Signature=" << Sig << endl; //5072
    int ver = calc_pow(Sig, e, n);
    cout << "V=" << ver << endl; //1234
    if (m == ver)
    {
        cout << "Signature Verified" << endl;
    }
    else
        cout << "Signature not verified" << endl;
}