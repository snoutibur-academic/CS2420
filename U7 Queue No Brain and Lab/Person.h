#include <iostream>
#include <string>
using namespace std;


class Person {
public:
    Person(string name, int amount) : name(name), amount(amount) {}
    bool operator >(const Person &g)const;

    bool operator<(const Person &g) const;

    bool operator!=(const Person &g) const;

    bool operator<=(const Person &g) const;

    bool operator>=(const Person &g) const;

    int getAmount() const;
    friend ostream& operator <<(ostream &out, const Person &g);
private:
    string name;
    int amount;
};

int Person::getAmount() const {
    return amount;
}

bool Person::operator >(const Person &g)const  {
    return amount > g.amount;
}
bool Person::operator >=(const Person &g)const  {
    return amount >= g.amount;
}

bool Person::operator <(const Person &g)const  {
    return amount < g.amount;
}
bool Person::operator <=(const Person &g)const {
    return amount <= g.amount;
}

bool Person::operator !=(const Person &g)const {
    return amount != g.amount;
}

ostream& operator <<(ostream &out, const Person &g) {
    out << g.name << ": " << g.amount;
    return out;
}