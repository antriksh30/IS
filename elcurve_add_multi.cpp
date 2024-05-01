// addition and multiplication of elliptic curve points over finite field GF(p)
#include<bits/stdc++.h>
using namespace std;

class Point{
    public:
    int x, y;
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
};

class EllipticCurve{
    public:
    int a, b, p;
    EllipticCurve(int a, int b, int p){
        this->a = a;
        this->b = b;
        this->p = p;
    }
    int mod(int a, int m){
        return (a % m + m) % m;
    }
    bool isPointOnCurve(Point pt){
        return mod((pt.y * pt.y),p) == mod((pt.x * pt.x * pt.x + a * pt.x + b),p);
    }
    Point add(Point p1, Point p2){
        if(p1.x == p2.x && p1.y == p2.y){
            int m = mod(((3 * p1.x * p1.x + a) * multi_inverse(2 * p1.y, p)),p);
            int x = mod((m * m - 2 * p1.x),p);
            int y = mod((m * (p1.x - x) - p1.y),p);
            return Point(x, y);
        }
        else{
            int m = mod(((p2.y - p1.y) * multi_inverse(p2.x - p1.x, p)) , p);
            int x = mod((m * m - p1.x - p2.x),p);
            int y = mod((m * (p1.x - x) - p1.y) , p);
            return Point(x, y);
        }
    }
    Point multiply(Point p, int n){
        Point result = p;
        for(int i = 1; i < n; i++){
            result = add(result, p);
        }
        return result;
    }
    Point inverse(Point pt){
        return Point(pt.x, mod(-pt.y,p));
    }
    int multi_inverse(int a, int m){
        a = mod(a,m);
        for(int i = 1; i < m; i++){
            if(mod((a * i),m) == 1){
                return i;
            }
        }
        return 1;
    }
};

int main(){
    int a, b, p;
    cout << "Enter a b p: ";
    cin >> a >> b >> p;
    EllipticCurve ec(a, b, p);

    //Addition of two points
    cout << "\nAddition of two points->\n";
    int x1,y1,x2,y2;
    cout << "Enter point 1 (x1 y1): ";
    cin >> x1 >> y1;
    cout << "Enter point 2 (x2 y2): ";
    cin >> x2 >> y2;
    Point p1(x1, y1);
    Point p2(x2, y2);
    Point p3 = ec.add(p1, p2);
    cout << "Addition: " << p3.x << " " << p3.y << endl;

    //Multiplication of a point by a scalar
    cout << "\nMultiplication of a point by a constant -> \n";
    int x,y,n;
    cout << "Enter point (x y): ";
    cin >> x >> y;
    cout << "Enter constant (k): ";
    cin >> n;
    Point pt(x, y);
    Point p4 = ec.multiply(pt, n);
    cout << "Multiplication: " << p4.x << " " << p4.y << endl;

    //Inverse of a point
    cout << "\nInverse of a point -> \n";
    int x3,y3;
    cout << "Enter point (x y): ";
    cin >> x3 >> y3;
    Point p5(x3, y3);
    Point p6 = ec.inverse(p5);
    cout << "Inverse: " << p6.x << " " << p6.y << endl;
    return 0;

}
