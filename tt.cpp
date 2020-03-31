#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v = {1, 2, 3};
    v.push_back(4);
    for (int i = 0; i < 4; ++i)
        cout << v[i] << endl;

    return 0;
}
