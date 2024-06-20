using namespace std;
#include <iostream>
#include <cstdlib>
#include <ctime>


//int Loptr(int HH, int mm){
//    if(HH >= 8 && HH < 15) return 0;
//    else if(HH >= 15 && HH < 22) return 1;
//    return 2;
//}


int main() {

    srand(time(NULL));

    int HH1,HH2,MM1,MM2;

    scanf("%d:%d",&HH1,&MM1);
    scanf("%d:%d",&HH2,&MM2);
//    cout << HH1 << ":" << MM1 << endl;
//    cout << HH2 << ":" << MM2 << endl;

    int HHStart = HH1;
    int MMStart = MM1;

    int epoka;
    scanf("%d",&epoka);
//    cout << epoka << endl;

    int ileMinut = HHStart * 60 + MMStart - HH2 * 60 - MM2;


//    cout << ileMinut << endl;

    int losujeMin = rand() % (ileMinut + 1);

//    cout << losujeMin << endl;



    int * counter = new int[6]();

    int czas = 100000;
    for(int i = 0; i < czas; i++){
        losujeMin = rand() % (ileMinut + 1);

        int HH3 = HHStart * 60 + MMStart + losujeMin;

        counter[Loptr(HH3/ 60,HH3 % 60)]++;
    }

    double prawd = counter[epoka] / (double) czas;
    //2 miejsca po przecinku
    cout.precision(2);
    cout << fixed;
    cout << prawd << endl;



    delete [] counter;
    return 0;
}
