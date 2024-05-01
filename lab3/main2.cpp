#include <iostream>
#include "ABS.h"
#include "ABQ.h"
using namespace std;

int main() {
    /*
     int x;
     int y;
     ABS<int> abs1(10);
     x = abs1.getSize();
     y = abs1.getMaxCapacity();
     cout << x << " " << y << endl;


     for (int i = 0; i < 10; i++) {
         abs1.push(i);
         x = abs1.getSize();
         y = abs1.getMaxCapacity();
            cout << x << " " << y << endl;
     }


     for (int p = 0; p < 10; p++) {
         abs1.pop();
         x = abs1.getSize();
         y = abs1.getMaxCapacity();
         cout << x << " " << y << endl;
     }

     x = abs1.peek();
     cout << x;



     int x;
     int y;
     float z = 0.0f;
     ABS<float> abs1;
     x = abs1.getSize();
     y = abs1.getMaxCapacity();
     //cout << x << " " << y << endl;

     cout << "pushing elements" << endl;
     for (int i = 0; i < 10; i++) {
         z += 0.5f;
         abs1.push(z);
         x = abs1.getSize();
         y = abs1.getMaxCapacity();
         cout << x << " " << y << " " << z << endl;
     }

     cout << "popping elements" << endl;
     for (int p = 0; p < 10; p++) {
         z = abs1.pop();
         x = abs1.getSize();
         y = abs1.getMaxCapacity();
         cout << x << " " << y << " " << z << endl;
     }

     x = abs1.peek();
     cout << x;
     */
/*
    int x;
    int y;
    ABQ<int> abq1;
    x = abq1.getSize();
    y = abq1.getMaxCapacity();
    //cout << x << " " << y << endl;


    for (int i = 0; i < 10; i++) {
        abq1.enqueue(i);
        x = abq1.getSize();
        y = abq1.getMaxCapacity();
        cout << x << " " << y << endl;
    }

    for (int p = 0; p < 10; p++) {
        abq1.dequeue();
        x = abq1.getSize();
        y = abq1.getMaxCapacity();
        //cout << x << " " << y << endl;
    }

    x = abq1.peek();
    cout << x;
*/

    int x;
    int y;
    float z = 0.0f;
    ABQ<float> abq1;
    x = abq1.getSize();
    y = abq1.getMaxCapacity();
    //cout << x << " " << y << endl;

    //cout << "pushing elements" << endl;
    for (int i = 0; i < 10; i++) {
        z += 0.5f;
        abq1.enqueue(z);
        x = abq1.getSize();
        y = abq1.getMaxCapacity();
        //    cout << x << " " << y << " " << z << endl;
    }
    /*
    cout << "popping elements" << endl;
    for (int p = 0; p < 10; p++) {
        z = abq1.dequeue();
        x = abq1.getSize();
        y = abq1.getMaxCapacity();
        cout << x << " " << y << " " << z << endl;
    }
*/
    x = abq1.peek();
    cout << x;

        return 0;
    }

