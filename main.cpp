#include <iostream>
#include <string>
/*Mysql Automatically build grammar
Using:
 1.string exp:select username,amount from `xxx_201801` -r 201801 -s 201801 -e 202002
 2.using exp:select username,amount from `xxx_201801` to select username,amount from `xxx_202002`
 3.select username,amount from `xxx_201801` -r 201801 -s 201801 -e 202002
 4. -r replace text
    -s starttime
    -e endtime
 */
using namespace std;
int getDay(int y,int m) {
    int month[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (y % 4 == 0 && m == 2) {
        return 29;
    }
    for (int i = 0; i < (sizeof(month)); ++i) {
        if (month[i] == m) {
            return days[i];
        }
    }
    return 0;
}
string isZero(int j){
    if (j>=10){
        return to_string(j);
    } else{
        return "0"+to_string(j);
    }
}
string isZero(int m,int d){
    if (m>=10&&d>=10){
        return to_string(m)+to_string(d);
    } else if(m>=10&&d<10){
        return to_string(m)+"0"+to_string(d);
    }else if(m<10&&d>=10){
        return "0"+to_string(m)+to_string(d);
    }else{
        return "0"+to_string(m)+"0"+to_string(d);
    }
}
void _Time(string Statement,string retext,string Start,string End){
    string head = Statement.substr(0,Statement.find(retext));
    string tail = Statement.substr(Statement.find(retext)+retext.length(),Statement.length());
    int sy,sm,sd,ey,em,ed,y=0,m,d;
    switch (retext.length()) {
        case 6:
            sy = atoi(Start.substr(0,4).c_str());
            sm = atoi(Start.substr(4,2).c_str());
            ey = atoi(End.substr(0,4).c_str());
            em = atoi(End.substr(4,2).c_str());
            y = sy;
            ey==sy?m=em-sm+1:m=(ey-sy)*12+(em-sm)+1;
            for (int i = sm,j=sm; i <= m; ++i) {
                if (j == 13) {y = y+1;j = 1;}
                cout << head << (to_string(y) + isZero(j)) << tail;
                i==m? cout << endl:cout << "union all" << endl;
                j++;
            }
            break;
        case 8:
            sy = atoi(Start.substr(0,4).c_str());
            sm = atoi(Start.substr(4,2).c_str());
            sd = atoi(Start.substr(6,2).c_str());
            ey = atoi(End.substr(0,4).c_str());
            em = atoi(End.substr(4,2).c_str());
            ed = atoi(End.substr(6,2).c_str());
            y=sy;
            ey==sy?m=em-sm+1:m=(ey-sy)*12+(em-sm)+1;
            for(int k=sd;k<=getDay(y,sm);++k){
                cout << head << (to_string(y) + isZero(sm,k)) << tail;
                m==1&&k==ed? cout << endl:cout << "union all" << endl;
                if(m==1&&k==ed)break;
            }
            for (int i = sm+1,j=sm+1; i <= m; ++i) {
                if (j == 13) {y = y+1;j = 1;}
                for (int k = 1 ; k <= getDay(y,j); ++k) {
                    cout << head << (to_string(y) + isZero(j,k)) << tail;
                    i==m&&k==ed? cout << endl:cout << "union all" << endl;
                    if(m==i&&k==ed)break;
                }
                j++;
            }
            break;
        default:
            break;
    }
}
typedef std::uint64_t hash_t;

constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

hash_t hash_(char * str)
{
    hash_t ret{basis};
    while(*str){
        ret ^= *str;
        ret *= prime;
        str++;
    }
    return ret;
}
constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
    return *str ? hash_compile_time(str+1, (*str ^ last_value) * prime) : last_value;
}
int main(int argc,char ** argv) {
    string Statement,retext,Start,End;
    for(int i=1;i<argc;i++){
        switch (hash_(argv[i])) {
            case hash_compile_time("-r"):
                retext = argv[i+1];
                for (int j = 1; j < i; ++j) {Statement = Statement+argv[j]+' ';}
            case hash_compile_time("-s"):
                Start = argv[i+1];
            case hash_compile_time("-e"):
                End = argv[i+1];
            default:
                break;
        }
    }
    _Time(Statement,retext,Start,End);
    return 0;
}
