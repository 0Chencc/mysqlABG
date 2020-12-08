#include <iostream>
#include <string>
/*mysql Automatically build grammar
Using:
 1.string exp:select username,amount from `xxx_201801` -r 201801 -s 201801 -e 202002
 2.using exp:select username,amount from `xxx_201801` to select username,amount from `xxx_202002`
 3.select username,amount from `xxx_201801` -r 201801 -s 201801 -e 202002
 4. -r replace text
    -s starttime
    -e endtime
 */
using namespace std;
void _Time(string Statement,string retext,string Start,string End){
    string head = Statement.substr(0,Statement.find(retext));
    string tail = Statement.substr(Statement.find(retext)+retext.length(),Statement.length());
    int sy,sm,sd,ey,em,ed,y=0,m,d;
    switch (retext.length()) {
        case 6:
            sy = atoi(Start.substr(0,4).c_str());
            sm = atoi(Start.substr(4,5).c_str());
            ey = atoi(End.substr(0,4).c_str());
            em = atoi(End.substr(4,5).c_str());
            if(ey == sy){
                m = em-sm;
            }else{
                m = (ey-sy)*12+(em-sm);
            }
            for (int i = sm; i < m; ++i) {
                int j = i;
                int s = 1;
                while (s){
                    if(j>12){
                        j = j-12;
                    }else{
                        s=0;
                    }
                }
                if(j%12==0){
                    ++y;
                    j=1;
                }
                if(i+1==m){
                    if(j<10){
                        cout<<head;
                        cout<<(to_string(sy+y)+"0"+to_string(j));
                        cout<<tail<<endl;
                    }else{
                        cout<<head;
                        cout<<(to_string(sy+y)+to_string(j));
                        cout<<tail<<endl;
                    }
                }else{
                    if(j<10){
                        cout<<head;
                        cout<<(to_string(sy+y)+"0"+to_string(j));
                        cout<<tail<<"union all"<<endl;
                    }else{
                        cout<<head;
                        cout<<(to_string(sy+y)+to_string(j));
                        cout<<tail<<"union all"<<endl;
                    }
                }
            }
            break;
        case 8:
            sy = atoi(Start.substr(0,3).c_str());
            sm = atoi(Start.substr(3,5).c_str());
            sd = atoi(Start.substr(5,7).c_str());
            ey = atoi(End.substr(0,3).c_str());
            em = atoi(End.substr(3,5).c_str());
            ed = atoi(End.substr(5,7).c_str());
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
                for (int j = 1; j < i; ++j) {
                    Statement = Statement+argv[j]+' ';
                }
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
