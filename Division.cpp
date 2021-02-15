#include <iostream> 
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>
#include <fstream>
#include <iomanip>

using namespace std;

class Dec_to_Binary {
private:
    int num_x, num_y, bit;
    vector<int> binary_y, binary_x, x_dm, y_dt, minusDT, Z, smth;
public:
    Dec_to_Binary(int x, int y, int n) : num_x(x), num_y(y), bit(n) {}

    void decToBinary(int s) {
        for (int i = (s - 1); i >= 0; i--) {
            int k = num_x >> i;
            if (k & 1)   
                binary_x.push_back(1);
            else
                binary_x.push_back(0);
        }
        for (int i = (s - 1); i >= 0; i--) {
            int k = num_y >> i;
            if (k & 1)
                binary_y.push_back(1);
            else
                binary_y.push_back(0);
        }
    }
    
    int find(vector<int> binary) {
        int temp = binary.front();
        int antitemp;
        if (temp == 1)
            antitemp = 0;
        else
            antitemp = 1;

        if (binary.at(1) == temp) {
            for (auto it = binary.begin(); it != binary.end(); it++) {
                if ((*it) == antitemp) {
                    return (it - 1) - binary.begin();
                }
            }
        }
        else return 0;
    }

    void dM_plusdT() {
        x_dm.insert(x_dm.begin(), binary_x.begin() + find(binary_x), binary_x.end());
        x_dm.insert(x_dm.end(), find(binary_x), 0);

        y_dt.insert(y_dt.begin(), binary_y.begin() + find(binary_y), binary_y.end());
        y_dt.insert(y_dt.end(), find(binary_y), 0);
    }

    int calculate_N() { 
        int N;
        int X = find(binary_x);
        int Y = find(binary_y);
        if (Y > X) {
            N = Y - X + 1;
            return N;
        }
        else {
            N = X - Y + 1;
            return N;
        }
    }
    int calculate_KL() {
        int KL;
        int X = find(binary_x);
        int Y = find(binary_y);
        if (Y > X) {
            KL = Y - X;
            return KL;
        }
        else {
            KL = X - Y;
            return KL;
        }
    }

    bool oppositeSigns(int x, int y) {
        return ((x ^ y) < 0);
    }

    void findZ(int s) {
        for (int i = 0; i < (s - calculate_N()); i++) {
            if (oppositeSigns(num_x, num_y) == true)
                Z.push_back(1);
            else
                Z.push_back(0);
        }
    }

    vector<int> one(int s) {
        vector<int> plus_one;
        for (int i = 0; i < (s - 1); i++)
            plus_one.push_back(0);
        plus_one.push_back(1);
        return plus_one;
    }

    void find_minus_ydt(int s) {
        vector<int> minus_y_dt;
        for (auto it = y_dt.begin(); it != y_dt.end(); it++) {
            if ((*it) == 1)
                minus_y_dt.push_back(0);
            else
                minus_y_dt.push_back(1);
        }

        vector<int> plus = one(s);

        int* refArr = minus_y_dt.data();
        int* refArr2 = plus.data();

        minusDT = addition_binary(refArr, refArr2, s);
    }

    vector<int> addition_binary(int* array1, int* array2, int s) {
        vector<int> result;
        int temp[100];
        int carry = 0, p = s;
        for (int i = (s - 1); i >= 0; i--) {
            switch (array1[i] + array2[i] + carry) {
            case 0:
                p--;
                temp[p] = 0;
                carry = 0;
                break;
            case 1:
                p--;
                temp[p] = 1;
                carry = 0;
                break;
            case 2:
                p--;
                temp[p] = 0;
                carry = 1;
                break;
            case 3:
                p--;
                temp[p] = 1;
                carry = 1;
                break;
            default:
                throw std::invalid_argument("invalid input"); // should never be reached with inputs of 0 or 1
            }
        }   // temp[0] = carry;
        result.assign(temp, temp + s);
        return result;
    }

    void test_add(vector<int> vec) {
        if (y_dt.front() == vec.front()) {
            Z.push_back(1);
            cout << setw(25) << vec.front() << " =" << vec.front() << "      ";
        }
        else {
            Z.push_back(0);
            cout << setw(25) << y_dt.front() << "!=" << vec.front() << "      ";
        }
    }

    vector<int> back_one(vector<int> one) {
        vector<int> result;
        result.insert(result.begin(), one.begin() + 1, one.end());
        result.push_back(0);
        display(result);
        cout << endl;
        return result;
    }

    vector<int> mainTask(vector<int> v, int s, int num) {
        vector<int> temp, q;
        if (y_dt.front() == v.front()) {
            q = v;
            if (num != calculate_N() && num != 0) {
                q = back_one(v);                         
            }
            int* refArr1 = q.data();
            int* refArr2 = minusDT.data();
            cout << setw(34) << "+ "; display(minusDT); cout << "\n" << setw(44) << "===========\n";

            temp = addition_binary(refArr1, refArr2, s);

            cout << setw(35); display(temp); cout << " <-\n";
            return temp;
        }
        else {
            q = v;
            if (num != calculate_N() && num != 0) {
                q = back_one(v);                         
            }
            int* refAr1 = q.data();
            int* refAr2 = y_dt.data();
            cout << setw(34) << "+ "; display(y_dt); cout << "\n" << setw(44) << "===========\n";

            temp = addition_binary(refAr1, refAr2, s);

            cout << setw(35); display(temp); cout << " <-\n";
            return temp;
        }
    }

    void BIGtask(int s) {
        int n = calculate_N();
        smth = mainTask(x_dm, s, n);
        test_add(smth);
         
        for (int i = (n - 1); i > 0; i--) {   
            smth = mainTask(smth, s, i);
            test_add(smth);
        }
       
        cout << "- - - - -\n";
    }

    void vecZ() {
        cout << "  Z = ";
        copy(Z.begin(), Z.end(), ostream_iterator<int>(cout));
        cout << endl;
    }

    int VectorToInt(vector<int> v) {
        reverse(v.begin(), v.end());
        int decimal = 1;
        int total = 0;
        for (auto& it : v) {
            total += it * decimal;
            decimal *= 10;
        }
        return total;
    }

    int convertBinaryToDecimal(long long n) {
        int decimalNumber = 0, i = 0, remainder;
        while (n != 0) {
            remainder = n % 10;
            n /= 10;
            decimalNumber += remainder * pow(2, i);
            ++i;
        }
        return decimalNumber;
    }

    vector<int> zero(int s) {
        vector<int> plus_one;
        for (int i = 0; i < (s - 1); i++)
            plus_one.push_back(0);
        return plus_one;
    }

    void check_correction(int s) {
        vector<int> corrected, plus = one(s), zeroz = zero(s);

        int* refArr = Z.data();
        int* refArr2 = plus.data();
        int int_temp = VectorToInt(smth);
        int int_zero = VectorToInt(zeroz);
        int KL = calculate_KL();

        if (binary_x.at(0) == 0 && binary_y.at(0) == 1) {
            corrected = addition_binary(refArr, refArr2, s);
        }
        else if (binary_x.at(0) == 1 && binary_y.at(0) == 0)
        {
            if (int_temp != int_zero) {
                corrected = addition_binary(refArr, refArr2, s);
            }
            else corrected = Z;
        }
        else if (binary_x.at(0) == 1 && binary_y.at(0) == 1)
        {
            if (int_temp == int_zero) {
                corrected = addition_binary(refArr, refArr2, s);
            }
            else corrected = Z;
        }
        else corrected = Z;

        cout << setw(35); display(smth); cout << endl;
        if (corrected.back() == 0) {
            smth = mainTask(smth, s, 0);
        }
        else cout << "\n No operation needed. \n";

        smth.insert(smth.begin(), KL, smth.at(0));
        smth.erase(smth.end() - KL, smth.end());
        cout << setw(29) << KL << "b -> "; display(smth);

        int intCorrected = VectorToInt(corrected);
        int intSmth = VectorToInt(smth);

        cout << "\n ";
        cout << num_x << " = (" << num_y << ").(" << finito(corrected, intCorrected, s) << ")+(" << finito(smth, intSmth, s) << ")";
    }

    int finito(vector<int> v, long long n, int s) {  
        vector<int> p;
        vector<int> plus = one(s);
        int* refArr = v.data();
        int* refArr2 = plus.data();

        if (v.at(0) == 1) {
            for (int i = 1; i < v.size(); i++) {
                if (v[i] == 0) {
                    v[i] = 1;
                }
                else {
                    v[i] = 0;
                }
            }
            cout << " OK  = ";  display(v); cout << endl;
            v = addition_binary(refArr, refArr2, s); 
            cout << " OK+1 = "; display(v); 

            p.insert(p.begin(), v.begin() + 1, v.end());
            int intP = VectorToInt(p);
            int z = -convertBinaryToDecimal(intP);
            cout << " = " << z << "\n\n ";
            return z; 
        }
        else {
            return convertBinaryToDecimal(n);
        }
    }

    void display(vector<int> juicy) {
        vector<int> temp = juicy;
        copy(temp.begin(), temp.end(), ostream_iterator<int>(cout));
    }
    ostream& Output_x(ostream& out) const {
        cout << "\nDK of X: "; copy(binary_x.begin(), binary_x.end(), ostream_iterator<int>(out));
        cout << "\tDK of Y : "; copy(binary_y.begin(), binary_y.end(), ostream_iterator<int>(out));
        cout << "\n[X] dM = "; copy(x_dm.begin(), x_dm.end(), ostream_iterator<int>(out));
        cout << "\t[Y] +dT = ";  copy(y_dt.begin(), y_dt.end(), ostream_iterator<int>(out));
        cout << "\n\t\t\t[Y] -dT=  "; copy(minusDT.begin(), minusDT.end(), ostream_iterator<int>(out));
        cout << "\n\n\t\t\t[Y] +dT=  ";  copy(y_dt.begin(), y_dt.end(), ostream_iterator<int>(out));
        cout << "\n\t\t\t[X]  dM=  "; copy(x_dm.begin(), x_dm.end(), ostream_iterator<int>(out));
        cout << "\n";
        return out;
    }
    friend ostream& operator << (ostream& out, const  Dec_to_Binary& obj) {
        obj.Output_x(out);
        return out;
    }
};


int main() {
    int x, y, n;
    cout << "Enter X = "; cin >> x;
    cout << "Enter Y = "; cin >> y;
    cout << "Enter length [b] = "; cin >> n;

    Dec_to_Binary obj(x, y, n);
    obj.decToBinary(n);
    obj.dM_plusdT();
    obj.find_minus_ydt(n);
    obj.Output_x(cout);

    obj.findZ(n);
    obj.BIGtask(n); 
    obj.vecZ();
    obj.check_correction(n);
    cout << endl;
    return 0;
}