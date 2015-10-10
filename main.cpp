#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double median(vector<double>::iterator &start, vector<double>::iterator &rstart) {
    --rstart;
    while(true){
        if ((start + 1) == rstart)
            return (*start + *rstart) / 2;
        else if (start == rstart)
            return *start;
        else {++start; --rstart;}
    }
}

void mean(vector<double>::iterator i, const vector<double>::iterator &ending, double &result) {
    int j = 0;
    for (;i != ending; i++) {
        result += *i;
        ++j;
    }
    result /= j;
}

inline double square(double i) {
    return i * i;
}

double variance(double mean, vector<double>::iterator &i, vector<double>::iterator eov) {
    double temp = 0;
    double temp2 = 0;
    unsigned short c = 0;
    for (;i != eov; i++) {
        temp2 = *i - mean;
        temp += square(temp2);
        c++;
    }
    return temp/c;
}

inline double standardDeviation (double vari) {
    return sqrt(vari);
}

inline double zee (double sd, double mean, double n) {
    return (n - mean)/sd;
}

int main() {
    cout << "This program processes a list of numbers to find mean, median, the first and third quartile, the IQR, outliers, and range.\n" << "To start, enter a range of numbers, separated by either a space or a return.\n" << "Once you are done inserting numbers, make a new line, hit CTRL + Z, and hit enter.\n" << "Feel free to message me any bugs you may find or just hunt me down." << endl;
    while (true) {
        cout << "____________________________________________________________________________" << endl;
        cout << "Enter in (another) list of numbers or hit the X button to exit the program." << endl;
        vector<double> cont;
        double j;
        while (cin >> j)
            cont.push_back(j);
        cin.clear();
        cout << endl << "This is the array of numbers sorted from least to greatest:" << endl;
        sort(cont.begin(), cont.end());
        for(vector<double>::iterator i = cont.begin(); i != cont.end(); i++)
            cout << *i << ", ";
        cout << endl;
        vector<double>::iterator start = cont.begin(), rstart = cont.end();
        double med = median(start, rstart);
        cout << "The median is " << med << endl;
        vector<double>::iterator qend = start, qstart = cont.begin();

        double q1;
        if ((start + 1) == rstart){
            ++qend;
            q1 = median(qstart, qend);
        }
        else if (start == rstart)
            q1 = median(qstart, qend);
        cout << "The first quartile is " << q1 << endl;

        qend = cont.end(); qstart = start;
        double q3;
        if ((start + 1) == rstart) {
            ++qstart;
            q3 = median(qstart, qend);
        }
        else if (start == rstart)
            q3 = median(qstart, ++qend);
        cout << "The third quartile is " << q3 << endl;

        double iqr = q3 - q1;
        cout << "The Quartile Range is " << iqr << endl;

        vector<double> outliers;
        for(vector<double>::iterator i = cont.begin(); i != cont.end(); i++) {
        if (*i < q1 - 1.5 * iqr)
            outliers.push_back(*i);
        else if (*i > q3 + 1.5*iqr)
            outliers.push_back(*i);
        else continue;
        }
        if (outliers.begin() != outliers.end()){
            cout << "The range contains the following outliers: ";
        for (vector<double>::iterator i = outliers.begin(); i != outliers.end(); i++)
            cout << *i << ", ";
            cout << endl;
        }
        else
        cout << "There are no outliers in the range" << endl;
        double meannum = 0;
        mean(cont.begin(), cont.end(), meannum);
        cout << "The mean is " << meannum << endl;
        double range = cont[cont.size() - 1] - cont[0];
        cout << "The range is " << range << endl << endl;

        vector<double>::iterator vt = cont.begin();
        double varianceN = variance(meannum, vt, cont.end());
        double standardDeviationN = standardDeviation(varianceN);

        cout << "The Standard Deviation is " << standardDeviationN << endl;

        for (vector<double>::iterator i = cont.begin(); i != cont.end(); i++) {
            cout << *i << "'s Z-Score is " << zee(standardDeviationN, meannum, *i) << endl;
        }
        cout << endl;

        double t = 0;
        for (double i = 0; i != cont.size(); i++) {
            if (t != cont[i]) {
                cout << cont[i] << " is in percentile " << static_cast<int>((i/cont.size())*100) << endl;
                t = cont[i];
            }
            else continue;
        }
        cout << endl;
    }
}
