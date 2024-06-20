using namespace std;

#include <iostream>
#include <list>
#include <valarray>
#include <stack>

struct Point {
    float x, y;
};

double det(Point a, Point b, Point c) {
    return a.x * b.y + a.y * c.x + b.x * c.y - c.x * b.y - c.y * a.x - b.x * a.y;
}

Point returnSecondElement(stack<Point> &stack) {
    Point top = stack.top();
    stack.pop();
    Point secTop = stack.top();
    stack.push(top);
    return secTop;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;
    list <Point> points;

    Point p0{};
    for (int i = 0; i < n; i++) {

        Point temp{};
        cin >> temp.x >> temp.y;
        if (i == 0) {
            p0 = temp;
        } else {
            if (temp.y < p0.y || (temp.y == p0.y && temp.x < p0.x)) {
                p0 = temp;
            }
        }
        points.push_back(temp);
    }

    points.sort([p0](Point a, Point b) -> bool {
        double angleA = atan2(a.y - p0.y, a.x - p0.x);
        double angleB = atan2(b.y - p0.y, b.x - p0.x);
        if (angleA == angleB) {
            return pow(a.x - p0.x, 2) + pow(a.y - p0.y, 2) < pow(b.x - p0.x, 2) + pow(b.y - p0.y, 2);
        }
        return angleA < angleB;
    });

    stack<Point> stack;
    stack.push(p0);
    stack.push(*points.begin());
    stack.push(*next(points.begin()));

    for(auto it = next(next(points.begin())); it != points.end(); it++){
        while(stack.size() > 1 && det(returnSecondElement(stack), stack.top(), *it) <= 0){
            stack.pop();
        }
        stack.push(*it);
    }

    double area = 0;
    Point first = stack.top();
    stack.pop();
    Point second = stack.top();
    while(!stack.empty()){
        Point third = stack.top();
        stack.pop();
        double a = sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
        double b = sqrt(pow(second.x - third.x, 2) + pow(second.y - third.y, 2));
        double c = sqrt(pow(third.x - first.x, 2) + pow(third.y - first.y, 2));
        double s = (a + b + c) / 2;
        area += sqrt(s * (s - a) * (s - b) * (s - c));
        second = third;
    }
    cout.precision(3);
    cout << fixed << area;

    return 0;
}
