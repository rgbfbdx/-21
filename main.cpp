#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Matrix {
    int rows, cols;
    int** data;
public:
    Matrix(int r=0, int c=0) {
        rows=r; cols=c;
        if(rows>0 && cols>0){
            data=new int*[rows];
            for(int i=0;i<rows;i++){
                data[i]=new int[cols];
                for(int j=0;j<cols;j++) data[i][j]=rand()%10; 
            }
        } else data=nullptr;
    }

    ~Matrix() {
        if(data){
            for(int i=0;i<rows;i++) delete[] data[i];
            delete[] data;
        }
    }

    friend istream& operator>>(istream& in, Matrix& m) {
        cout<<"rows="; in>>m.rows;
        cout<<"cols="; in>>m.cols;
        if(m.data){
            for(int i=0;i<m.rows;i++) delete[] m.data[i];
            delete[] m.data;
        }
        m.data=new int*[m.rows];
        for(int i=0;i<m.rows;i++){
            m.data[i]=new int[m.cols];
            for(int j=0;j<m.cols;j++) m.data[i][j]=rand()%10;
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Matrix& m) {
        out<<"cols: "<<m.cols<<" rows: "<<m.rows<<"\n";
        for(int i=0;i<m.rows;i++){
            for(int j=0;j<m.cols;j++) out<<m.data[i][j]<<" ";
            out<<"\n";
        }
        return out;
    }

    void saveToFile(string fname){
        ofstream f(fname);
        f<<*this;
        f.close();
    }

    void loadFromFile(string fname){
        ifstream f(fname);
        string tmp;
        f>>tmp>>cols>>tmp>>rows;
        if(data){
            for(int i=0;i<rows;i++) delete[] data[i];
            delete[] data;
        }
        data=new int*[rows];
        for(int i=0;i<rows;i++){
            data[i]=new int[cols];
            for(int j=0;j<cols;j++) f>>data[i][j];
        }
        f.close();
    }
};

int main(){
    srand(time(0));
    Matrix m;
    cin>>m;
    cout<<m;
    m.saveToFile("matrix.txt");

    Matrix m2;
    m2.loadFromFile("matrix.txt");
    cout<<"Завантажена матриця:\n"<<m2;
}
