/*
    �Ǹ�:41043210 
    �m�W:������ 
    ���O:Ackermann , Powerset
    ��k:�D���j , ���j
*/

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class powerset{
    public:
        powerset(string str){
            int len = str.length() - 2 , j = 0;
            char *arr = new char[len];              //�إ߰ʺA�}�C
            for (int i = 1 ; i <= len ; i+=2){      //���r�����}�C
                arr[j] = str[i];
                j++; 
            }
            int len1 = str.length() / 2;
            pset((pow(2,len1) - 1) , arr , len1);
        }
        void pset(int i, char arr[], int len);
};

class Ackermann{
    public:
        void acknonrecursive(int m, int n);
        int ackrecursive(int m, int n);
};

int Ackermann::ackrecursive(int m, int n){
    if (m == 0){
        return (n + 1);
    }else if(n == 0){
        return ackrecursive((m - 1),1);
    }else{
        return ackrecursive((m - 1), (int)(ackrecursive(m, (n - 1))));
    }
}

void Ackermann::acknonrecursive(int m, int n){
    
    
    int **data; //�t�m�G���}�C
    data = new int*[m + 1];
    for(int i = 0; i < m + 1; i++)
        data[i] = new int[n + 1];

    for (int rows = 0 ; rows < m + 1 ; rows++){
        for (int cols = 0 ; cols < n + 1 ; cols++){
            if(rows == 0){                                      //m = 0
                data[rows][cols] = cols + 1;
            }else if(cols == 0){                                //n = 0
                data[rows][cols] =data[rows - 1][1];
            }else{
                int r = rows - 1;                               //a(m-1.a(m.n-1))�� m-1 ����
                int c = data[rows][cols-1];                     //��������a(m.n-1)
                int sum;
                 
                if (r == 0){                                    //m = 0
                    sum = c + 1;
                }else if (c <= n){                              //�٨S����
                    sum = data[rows-1][data[rows][cols-1]];
                }else{                                          //�ݭn������
                    sum = (c-n)*(r) + data[r][n];
                }
 
                data[rows][cols] = sum;
            }
        }
    }
    
    cout << data[m][n] << endl;

    //�R���G���}�C
    for(int i = 0; i < m; i++)
        delete [] data[i];
    delete [] data;

}

void powerset::pset (int i, char arr[], int len){
    if (i < 0){
        return;
    }else{
        string num; 
        int m = i , j = 0;
        while (m != 0){ //�̶i����G�i��
            num +=  ( m % 2 == 0 ? 0 : 1 );
            m /= 2;
            j++;
        }
        cout << "(";
        int numlen = num.length(); //�G�i����
        for (int k = 0 ; k < len ; k++){
            if (num[k] % 10 == 1 && (numlen - 1) == k){ //�G�i�� = 1 �ɦL�X�r��
                cout << arr[k];
            }else if (num[k] % 10 == 1){
               cout << arr[k] << ",";
            }
        }
        cout << ")" << endl;
        pset(i - 1,arr,len);
    }
}
     
int main(){
    
    Ackermann test;
    int m,n;
    cout << "��Jm,n:";
    cin >> m >> n;
    cout << "Ackermann(nonrecursive):";
    test.acknonrecursive(m,n);
    cout << "Ackermann(recursive):";
    cout << test.ackrecursive(m,n) << endl;

    string str;
    cout << "��J�榡��(a,b,c):";
    getline(cin,str);
    getline(cin,str);
    powerset block(str);
}
