#include <iostream>
#include <string>
#include <utility>
#include <cmath>
using namespace std;






//BADFIGURE.H  *************BEGINS//


class BadFigureException{


private:
    std::string _figureName;

public:
    BadFigureException(std::string name);
    void print();
};

//BADFIGURE.H  *************  ENDS//




//SHAPES.H  *************BEGINS//

struct Point {
    double x;
    double y;

    Point(): x(0.0), y(0.0) {}
    Point(double x_, double y_): x(x_), y(y_) {}
    void RotatePoint(Point around, double degAngle);

};

class Shape {
public:
    Shape();
    virtual void move(const double, const double) = 0;
    virtual void turn(double angle) = 0;
    virtual void scale(double factor) = 0;
    void setColor(string);
    string getColor();
    int getId();

protected:
    static int _id;
    int id;
    string color;
};


//SHAPES.H  *************ENDS//







//RECTANGLE.H  *************BEGINS//


class Rectangle : public Shape {
public:

    Rectangle(const Point a, const Point c);
    ~Rectangle();


    void move(const double, const double) override;
    void turn(double angle) override;
    void scale(double factor) override;
    friend ostream& operator<<(ostream& os, const Rectangle& rect);

private:
    Point positionCentre();


private:
    Point _a;
    Point _b;
    Point _c;
    Point _d;
};


//RECTANGLE.H  *************   ENDS//








//PENTAGON.H  *************  BEGINS//

class Pentagon : public Shape {
public:
    Pentagon(const Point , const Point );
    ~Pentagon();

    void move(const double, const double) override;
    void turn(double angle) override;
    void scale(double factor) override;
    friend ostream& operator<<(ostream& os, const Pentagon& pent);

private:
    void positionCentre();
    void generatePoints();



private:
    Point centre;
    Point _a;
    Point _b;
    Point _c;
    Point _d;
    Point _e;
};

//PENTAGON.H  *************  ENDS//


//STAR.H  *************  BEGINS//

class Star : public Shape {
public:
    Star(const Point , const Point );
    ~Star();

    void move(const double, const double) override;
    void turn(double angle) override;
    void scale(double factor) override;
    friend ostream& operator<<(ostream& os, const Star& pent);

private:
    void positionCentre();
    void generatePoints();




private:
    Point centre;
    Point _aB;
    Point _bB;
    Point _cB;
    Point _dB;
    Point _eB;


    Point _aS;
    Point _bS;
    Point _cS;
    Point _dS;
    Point _eS;

};

//STAR.H  *************  ENDS//





//BADFIGURE.C  *************  BEGINS//


BadFigureException::BadFigureException(std::string name) : _figureName(name) {}

void BadFigureException::print(){
    cout<<"bad "+_figureName+" exception"<<endl;
    exit(1);
}

//BADFIGURE.C  *************  ENDS//






//SHAPES.C  *************  BEGINS//

int Shape::_id = 0;

int Shape::getId() {
    return id;
}

void Shape::setColor(string Ncolor){
    color = Ncolor;
};

string Shape::getColor(){
    return color;
}

Shape::Shape(){
    id = ++_id;
};


void Point::RotatePoint(Point around, double degAngle)
{
    if ((int)degAngle % 360 != 0 && (degAngle - (int)degAngle == 0.0))
    {
        double rad = degAngle * (M_PI / 180);
        Point rotpoint(0, 0);
        rotpoint.x = around.x + (this->x - around.x)*cos(rad) - (this->y - around.y)*sin(rad);
        rotpoint.y = around.y + (this->x - around.x)*sin(rad) + (this->y - around.y)*cos(rad);
        this->x = rotpoint.x;
        this->y = rotpoint.y;
    }
}


//SHAPES.C  *************ENDS//





//RECTANGLE.C  *************BEGINS//



Rectangle::Rectangle(const Point a, const Point c) : _a(a), _c(c){
    if(_c.x <= a.x || _c.y >= a.y) {
        BadFigureException a("Rectangle");
        a.print();
    }
    _b.x = _c.x; _b.y = _a.y;
    _d.x = _a.x; _d.y = _c.y;
    }


Rectangle::~Rectangle() {
}



Point Rectangle::positionCentre(){
    Point centre;
    centre.x = (_a.x + _c.x)/2;
    centre.y = (_c.y + _a.y)/2;
    return centre;
}

void Rectangle::move(const double x, const double y) {


    _a.x += x; _a.y += y;
    _b.x += x; _b.y += y;
    _c.x += x; _c.y += y;
    _d.x += x; _d.y += y;
}


void Rectangle::turn(double angle){
    Point centre = positionCentre();

    _a.RotatePoint(centre, angle);
    _b.RotatePoint(centre, angle);
    _c.RotatePoint(centre, angle);
    _d.RotatePoint(centre, angle);
}


void Rectangle::scale(double factor){
    if(factor < 0.0) {
        BadFigureException a("negative factor");
        a.print();
    }
    //Point cen = positionCentre();
    double Nlen;
    double Nwid;
    Nlen = abs(_b.x-_a.x)*factor;
    Nwid = abs(_b.y-_c.y)*factor;

    _b.x = _a.x + Nlen;
    _c.x = _b.x; _c.y = _b.y - Nwid;
    _d.x = _d.x; _d.y = _c.y;
}


ostream& operator<<(ostream& os, const Rectangle& rect){
    os << '(' << rect._a.x << ':' << rect._a.y << ')' << endl
       << '(' << rect._b.x << ':' << rect._b.y << ')' << endl
       << '(' << rect._c.x << ':' << rect._c.y << ')' << endl
       << '(' << rect._d.x << ':' << rect._d.y << ')' << endl << "\n\n\n";

    return os;

}
//RECTANGLE.C  *************BEGINS//




//PENTAGON.C  *************  BEGINS//


Pentagon::Pentagon(const Point cen, const Point a) : _a(a), centre(cen) {
    if(centre.x == a.x && centre.y == a.y) {
            BadFigureException a("Pentagon");
            a.print();
    }
    else{
        generatePoints();
        cout << "The new Regular Pentagon has been created!" << endl;
    }
}


Pentagon::~Pentagon() {
}


void Pentagon::generatePoints() {
    _b = _a;
    _b.RotatePoint(centre,72);
    _c = _b;
    _c.RotatePoint(centre,72);
    _d = _c;
    _d.RotatePoint(centre,72);
    _e = _d;
    _e.RotatePoint(centre,72);
}

 void Pentagon::positionCentre(){

    centre = _b;
    centre.RotatePoint(_a,54);
}


void Pentagon::move(const double x, const double y){

    _a.x += x; _a.y += y;
    _b.x += x; _b.y += y;
    _c.x += x; _c.y += y;
    _d.x += x; _d.y += y;
    _e.x += x; _e.y += y;
    centre.x += x; centre.y += y;

}


void Pentagon::turn(double angle){
    _a.RotatePoint(centre, angle);
    _b.RotatePoint(centre, angle);
    _c.RotatePoint(centre, angle);
    _d.RotatePoint(centre, angle);
    _e.RotatePoint(centre, angle);

}


void Pentagon::scale(double factor){
    if(factor < 0.0) {
        BadFigureException a("negative factor");
        a.print();
    }
    double NewLen = abs(centre.x - _a.x)*factor;
    double NewWid = abs(centre.y - _a.y)*factor;
    if(_a.x >= centre.x)
        _a.x = centre.x + NewLen;
    else
        _a.x = centre.x - NewLen;
    if(_a.y >= centre.y)
        _a.y = centre.y + NewWid;
    else
        _a.y = centre.y - NewWid;
    generatePoints();
}



ostream& operator<<(ostream& os, const Pentagon& pent){
    os << '(' << pent._a.x << ':' << pent._a.y << ')' << endl
       << '(' << pent._b.x << ':' << pent._b.y << ')' << endl
       << '(' << pent._c.x << ':' << pent._c.y << ')' << endl
       << '(' << pent._d.x << ':' << pent._d.y << ')' << endl
       << '(' << pent._e.x << ':' << pent._e.y << ')' << endl << "\n\n\n";
    return os;

}

//PENTAGON.C  *************  ENDS//



//STAR.C  *************  BEGINS//


Star::Star(const Point cen, const Point aB) : _aB(aB), centre(cen) {
    if(centre.x == aB.x && centre.y == aB.y) {
        BadFigureException a("Pentagon");
        a.print();
    }
    else{
        _aS = _aB;
        _aS.RotatePoint(centre,36);
        if(_aS.x >= centre.x)
            _aS.x = centre.x + abs(centre.x -_aS.x)/2;
        else
            _aS.x = centre.x - abs(centre.x -_aS.x)/2;
        if(_aS.y >= centre.y)
            _aS.y = centre.y + abs(centre.y -_aS.y)/2;
        else
            _aS.y = centre.y - abs(centre.x -_aS.y)/2;
        generatePoints();
        cout << "The new Star Pentagon has been created!" << endl;
    }
}


Star::~Star() {
}


void Star::generatePoints() {
    _bB = _aB;
    _bB.RotatePoint(centre,72);
    _cB = _bB;
    _cB.RotatePoint(centre,72);
    _dB = _cB;
    _dB.RotatePoint(centre,72);
    _eB = _dB;
    _eB.RotatePoint(centre,72);

    _bS = _aS;
    _bS.RotatePoint(centre,72);
    _cS = _bS;
    _cS.RotatePoint(centre,72);
    _dS = _cS;
    _dS.RotatePoint(centre,72);
    _eS = _dS;
    _eS.RotatePoint(centre,72);
}

void Star::positionCentre(){

    centre = _bB;
    centre.RotatePoint(_aB,54);
}


void Star::move(const double x, const double y){

    _aB.x += x; _aB.y += y;
    _bB.x += x; _bB.y += y;
    _cB.x += x; _cB.y += y;
    _dB.x += x; _dB.y += y;
    _eB.x += x; _eB.y += y;

    _aS.x += x; _aS.y += y;
    _bS.x += x; _bS.y += y;
    _cS.x += x; _cS.y += y;
    _dS.x += x; _dS.y += y;
    _eS.x += x; _eS.y += y;

    centre.x += x; centre.y += y;
}


void Star::turn(double angle){
    _aB.RotatePoint(centre, angle);
    _bB.RotatePoint(centre, angle);
    _cB.RotatePoint(centre, angle);
    _dB.RotatePoint(centre, angle);
    _eB.RotatePoint(centre, angle);


    _aS.RotatePoint(centre, angle);
    _bS.RotatePoint(centre, angle);
    _cS.RotatePoint(centre, angle);
    _dS.RotatePoint(centre, angle);
    _eS.RotatePoint(centre, angle);

}


void Star::scale(double factor){
    if(factor < 0.0) {
        BadFigureException a("negative factor");
        a.print();
    }
    double NewLen = abs(centre.x - _aB.x)*factor;
    double NewWid = abs(centre.y - _aB.y)*factor;
    if(_aB.x >= centre.x){
        _aB.x = centre.x + NewLen;
        _aS.x = centre.x + NewLen/2;
    }
    else{
        _aB.x = centre.x - NewLen;
        _aS.x = centre.x - NewLen/2;
    }

    if(_aB.y >= centre.y){
        _aB.y = centre.y + NewWid;
        _aS.y = centre.y + NewWid/2;
    }
    else{
        _aB.y = centre.y - NewWid;
        _aS.y = centre.y - NewWid/2;

    }
    generatePoints();
}



ostream& operator<<(ostream& os, const Star& pent){
    os << "aB = (" << pent._aB.x << ":" << pent._aB.y << ")" << endl
       << "aS = (" << pent._aS.x << ":" << pent._aS.y << ")" << endl
       << "bB = (" << pent._bB.x << ":" << pent._bB.y << ")" << endl
       << "bS = (" << pent._bS.x << ":" << pent._bS.y << ")" << endl
       << "cB = (" << pent._cB.x << ":" << pent._cB.y << ")" << endl
       << "cS = (" << pent._cS.x << ":" << pent._cS.y << ")" << endl
       << "dB = (" << pent._dB.x << ":" << pent._dB.y << ")" << endl
       << "dS = (" << pent._dS.x << ":" << pent._dS.y << ")" << endl
       << "eB = (" << pent._eB.x << ":" << pent._eB.y << ")" << endl
       << "eS = (" << pent._eS.x << ":" << pent._eS.y << ")" << endl << "\n\n\n";
    return os;

}

//STAR.C  *************  ENDS//







int main() {

    return 0;
}


