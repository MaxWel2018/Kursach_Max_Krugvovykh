#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <math.h>
// Все ограничение вынес в define что бы проще было регулировать.
#define  ALPHA_RESTRICTION_START  0
#define  ALPHA_RESTRICTION_END M_PI/2

#define  E_RESTRICTION_START 1E-9
#define  E_RESTRICTION_END 3E-9

#define  V_RESTRICTION_START 1000
#define  V_RESTRICTION_END 2000

#define  B_RESTRICTION_START 0.01
#define  B_RESTRICTION_END 0.025

using namespace std;

class ComputeObject{
protected:
    double F;

    virtual void input()=0;
    virtual void output()=0;
    virtual void parameterCalculation()=0;
};

class Charge:public ComputeObject{
    double temp,temp1,temp2,temp3; // временные переменные
    bool flag;
    bool flag1;
    bool flag2;
    bool flag3;
    bool flag4;
protected:
    double e,V,B,alpha;
    void rangeCheck(double alpha, double e, double V, double B){
        // проверка на ввод , если хоть  1 данное ведено не верно выводиться сообщение об ошибке ,
        // и поле которое не правильно введено.Если всё верно данные с
        // временной переменной(к которой нету доступа у пользователь так как она private)
        // переносяться в нужные
        flag = false;   // устанавливаем все флаги как false
        flag1 = false;
        flag2 = false;
        flag3 = false;
        flag4 = false;
        if (alpha>= ALPHA_RESTRICTION_START && alpha <= ALPHA_RESTRICTION_END) {
            this->alpha= alpha;
        } else {
            flag = true;
            flag1 = true;
        }
        if (e>= E_RESTRICTION_START && e<= E_RESTRICTION_END) {
            this->e = e;
        } else {
            flag = true;
            flag2 = true;
        }
        if (V >= V_RESTRICTION_START && V <= V_RESTRICTION_END) {
            this->V = V;
        } else {
            flag = true;
            flag3 = true;
        }


        if (B >= B_RESTRICTION_START && B<= B_RESTRICTION_END) {
            this->B = B;
        } else {
            flag = true;
            flag4 = true;
        }

        if (flag) {
            errorMessege();
            exit(1); // что бы после ошибки программа завершалась

        }
    }
    void errorMessege() {
        cout << "Ошибка! Данные не соответсвуют заданым диапазонам:" << endl;
        if (flag1) {
            cout << "\tПоле \"alpha\" Введено не верно.Введите данные в диапазоне от " << ALPHA_RESTRICTION_START << " до "  << ALPHA_RESTRICTION_END << endl;

        }
        if (flag2) {
            cout << "\tПоле \"e\" Введено не верно.Введите данные в диапазоне от  "<< E_RESTRICTION_START <<" до " << E_RESTRICTION_END << endl;

        }
        if (flag3) {
            cout << "\tПоле \"V\" Введено не верно.Введите данные в диапазоне от  "<< V_RESTRICTION_START << " до " << V_RESTRICTION_END << endl;

        }
        if (flag4) {
            cout << "\tПоле \"B\" Введено не верно.Введите данные в диапазоне от  "<< B_RESTRICTION_START <<" до " << B_RESTRICTION_END << endl;
        }

    };
public:
    friend bool operator==(const Charge &th, const Charge &other);
    friend bool operator!=(const Charge &th, const Charge &other);
    friend bool operator>=(const Charge &th, const Charge &other);
    friend bool operator<=(const Charge &th, const Charge &other);
    friend bool operator>(const Charge &th, const Charge &other);
    friend bool operator<(const Charge &th, const Charge &other);




    void output()override{
        ofstream fout("./../result.txt",ios_base::app);
        if (!fout.is_open()) {
            cout << "Файл не может быть открыт для записи!\n";
            exit(1); // если файл не открился закрываем программу.

        }else{
            /* fout.setf(ios_base::fixed);   Эксопненциальную в обычную форму
             fout.precision(10);*/
            fout << "Начальные данные: "<<endl;
            fout << "Alpha = " <<alpha <<endl;
            fout << "e = " << e <<endl;
            fout << "V = " << V <<endl;
            fout << "B = " << B <<endl;
            fout << "Результат: " << endl;
            fout  << "F = " << F << endl;
            fout << "----------------------------------------------------------------------------------------------"<<endl;
            fout.close();
        }
    }
    void parameterCalculation()override{
        F= alpha*e*V*B;

    }
    void input ()override{
        ifstream fin(R"(C:\Users\User\CLionProjects\Kursach_Max_Krugvovykh\hello.txt)",ios_base::in);
        if (!fin.is_open()) {
            cout << "Файл не может быть открыт!\n";
            exit(1); // если файл не открился закрываем программу.
        } else{
            fin >> temp;
            fin >> temp1;
            fin >> temp2;
            fin >> temp3;
            rangeCheck(temp, temp1, temp2, temp3);
        }

    }
    Charge(double e, double V, double B, double alpha);
    Charge() {};
    Charge(const Charge &other){ // конструктор копирования
        this->e = other.e;
        this->B = other.B;
        this->V = other.V;
        this->alpha = other.alpha;
    }



};

bool operator ==(const Charge &th , const Charge &other) {
    return th.alpha == other.alpha && th.V == other.V && th.e == other.e && th.B == other.B;
}

bool operator!=(const Charge &th, const Charge &other) {
    return !(th.alpha == other.alpha && th.V == other.V && th.e == other.e && th.B == other.B);
}

bool operator>=(const Charge &th, const Charge &other) {
    return th.V>=other.V;
}

bool operator<=(const Charge &th, const Charge &other) {
    return th.V<=other.V;
}

bool operator>(const Charge &th, const Charge &other) {
    return th.F>other.F;
}

bool operator<(const Charge &th, const Charge &other) {
    return th.F<other.F;
}

Charge::Charge(double alpha, double e, double V, double B) {
    rangeCheck(alpha, e, V, B);
};

void equal(Charge i, Charge j) {
    if (i == j) {
        cout << "Обьекты равны  " << endl;
    } else if(i!=j){
        cout << "Обьекты НЕ равны  " << endl;
    }else{ cout << "ERROR"<<endl; }
}
void equalF(Charge i, Charge j) {
    if (i > j) {
        cout << "F первого обьекта больше " << endl;
    } else if (i < j) {
        cout << "F второго обьекта больше " << endl;
    } else { cout << "F Обьектов равны" << endl; }
}
void equalV(Charge i, Charge j){
    if (i <= j) {
        cout << "Скорость второго заряда  не меньше скорости первого"<< endl;
    } else if (i >= j) {
        cout << "Скорость первого заряда  не меньше скорости второго"<< endl;

    }else{
        cout << "Упс... что-то пошло не так , этого не должны было показать"<<endl;
    }
}
int main(){


    Charge charge;
    charge.input();
    charge.parameterCalculation();
    charge.output();
    Charge chargeCopy(charge);

    Charge ch(1.1, 1.1E-09, 1500, 0.016);
    Charge ch1(1.2, 2.3E-09, 1500, 0.020);
    ch.parameterCalculation();
    ch.output();

    equal(ch, ch1);
    equalF(charge, chargeCopy);
    equalV(charge, ch);








    cin.get();


    return 0;
}