#include <iostream>
using namespace std;

class Fish {
public:
    virtual ~Fish(){};
    virtual void echo() {cout<<"I'm a fish"<<endl;};
};
class Beauty {
public:
    virtual ~Beauty(){};
    virtual void echo() {cout<<"I'm a beauty"<<endl;};
};
class FishBeauty: public Beauty, public Fish {
public:
    virtual ~FishBeauty(){};
    virtual void echo() {cout<<"I'm a fish-beauty"<<endl;};
};
void fish_echo(Fish* fish) {
    cout<<fish<<endl;
    fish->echo();
}
void beauty_echo(Beauty* beauty) {
    cout<<beauty<<endl;
    beauty->echo();
}

int main() {
    FishBeauty fb;
    Beauty b;
    Fish f;
    cout<<&fb<<endl;
    fish_echo(&fb);
    beauty_echo(&fb);
}
