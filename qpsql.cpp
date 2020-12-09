
/*
注意事项:
每一条语句以单独的';'结束!!!
不能与变量连起来.
*/

#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using ll = long long;

ifstream oldfile;
ofstream mycout, mylog;

const int maxn = 10; // 最大表数
const int maxm = 10; // 最大列数

set<int>st; //表集

map<string, int>Type; //数据类型映射
map<string, int>Opr; //操作映射

map<string, int>mp; //表名 -> id
map<int, string>_mp; //id -> 表名

//map<int, string> mp1;
//map<int, int> g; //记录数量

int cnt; //表数

int FLAG; //文件处理标志变量
int tmp_cnt;
string tmp_str[100]; //转存

template<class T>
T Input(T& x) {
    if (FLAG) {
        oldfile >> x;
        //string s = to_string(x);
        //tmp_str[tmp_cnt++] = s;
    }
    else {
        cin >> x;
        //mycout << x << '\n';
    }
    //cout << x << '\n';
    return x;
}
/*
int cnt_int;
int cnt_string;
int cnt_double;
int cnt_ll;
*/

int len[maxn]; //列数

int vis[maxn];
string s[maxn];

int num[maxn]; //行数

void It() {
    Type["double"] = 1;
    Type["ll"] = 2;
    Type["int"] = 3;
    Type["string"] = 4;

    Opr["quit"] = 1;
    Opr["create"] = 2;
    Opr["insert"] = 3;
    Opr["select"] = 4;
    Opr["drop"] = 5;
    Opr["update"] = 6;
    Opr["show"] = 7;
}

void Error(int id) {
    switch (id) {
    case 1:
        puts("ERROR(00002): Access denied for user 'root'@'localhost' (using password: Yes)"); break;
    case 2:
        puts("ERROR(00002): There is no such type."); break;
    case 3:
        puts("ERROR(00003): There is no such string."); break;
    case 4:
        puts("ERROR(00004): The number of tables has reached the upper limit!"); break;
    case 5:
        puts("ERROR(00005): None of the members had that name."); break;
    case 6:
        puts("ERROR(00006): You have an error in your SQL syntax."); break;
    case 7:
        puts("ERROR(00007): There is no such table."); break;
    }
}

struct table {
    string s; //数据类型
    int len; //个数
    int cnt[10];

    vector<double> data1; //支持最多10个表
    vector<ll> data2;
    vector<int> data3;
    vector<string> data4;

    //    vector<bool> vis;

    table() {
        for (auto i : cnt) {
            cnt[i] = 0;
            len = 0;
            s = "";
        }
        data1.clear();
        data2.clear();
        data3.clear();
        data4.clear();
        //        vis.clear();
    }
}ab[maxn][maxm];

/*
double
ll
int
string
*/

/*
vector<double> data1[10]; //支持最多10个表
vector<ll> date2[10];
vector<int> date3[10];
vector<string> date4[10];
*/

string ss[maxn][maxm][2]; // 一维:名称, 二维:数据类型

int cnt_1; //select 记录选择列
string tp[maxm];
int vis_1[maxm]; //select 标记选择那些列

inline void init(int x = 0) {
    cout << (!x ? "    -> " : "qpsql> ");
}

inline void quit() {
    init(1);
    cout << "Bye!\n";
}

inline string Tolower(string s) {
    transform(s.begin(), s.end(), s.begin(), tolower);
    return s;
}

int Find_Unlocked_Id() {
    for (int i = 1; i <= maxn; i++) {
        if (st.find(i) == st.end()) {
            st.insert(i);
            cnt++;
            return i;
        }
    }
    return -1;
}

void create_Table(string name) {
    int tmp = Find_Unlocked_Id();
    if (tmp == -1) {
        Error(4);
        return;
    }
    mp[name] = tmp;
    tmp_cnt = 0;
    tmp_str[tmp_cnt++] = "create";
    tmp_str[tmp_cnt++] = "table";
    tmp_str[tmp_cnt++] = name;
    //cout << tmp << '\n';
    _mp[tmp] = name;
    string S;
    int id = 0;
    while (1) {
        if(FLAG == 0)
            init();
        if (FLAG)
            oldfile >> S;
        else {
            cin >> S;
            tmp_str[tmp_cnt++] = S;
        }
        if (S == ";") {
            if (FLAG == 0) {
                init(1);
                cout << "CREATE COMPLETE\n";
                init(1);
            }
            break;
        }
        id++;
        ss[tmp][id][0] = Tolower(S);
        if (FLAG)
            oldfile >> S;
        else {
            cin >> S;
            tmp_str[tmp_cnt++] = S;
        }
        if (Type[S] == 0) {
            if(FLAG == 0)
                Error(2);
            break;
        }
        ss[tmp][id][1] = Tolower(S);
        //cout << S << "sadf\n";
    }
    if (FLAG == 0) {
        mycout << tmp_str[0] << ' ' << tmp_str[1] << ' ' << tmp_str[2] << '\n';
        for (int i = 3; i < tmp_cnt - 1; i += 2) {
            mycout << tmp_str[i] << ' ' << tmp_str[i + 1] << '\n';
        }
        mycout << ';' << '\n';
    }
    //cout << "af\n";
    len[tmp] = id; //列数记录
    num[tmp] = 0; //行数
}

int Find(string s, int id) {
    int l = len[id];
    for (int i = 1; i <= l; i++) {
        if (ss[id][i][0] == s)
            return i;
    }
    return 0;
}

void st_insert(int n, int m, int x) {
    ab[n][m].len++;
    //cout << "asdf" << ab[n][m].len << '\n';
    //ab[n][m].len = x;
    switch (Type[ss[n][m][1]]) {
    case 1:
        double s1;
        ab[n][m].data1.push_back(Input(s1));
        tmp_str[tmp_cnt++] = to_string(s1);
        break;
    case 2:
        ll s2;
        ab[n][m].data2.push_back(Input(s2));
        tmp_str[tmp_cnt++] = to_string(s2);
        break;
    case 3:
        int s3;
        ab[n][m].data3.push_back(Input(s3));
        tmp_str[tmp_cnt++] = to_string(s3);
        break;
    case 4:
        string s4;
        ab[n][m].data4.push_back(Input(s4));
        tmp_str[tmp_cnt++] = s4;
    }
}

void avg(int id) {
    for (int i = 1; i <= len[id]; i++) {
        if (num[id] != ab[id][i].len) {
            ab[id][i].len = num[id]; //not
        }
    }
}

void insert() {
    tmp_cnt = 0;
    tmp_str[tmp_cnt++] = "insert";
    string S;
    if (FLAG)
        oldfile >> S;
    else {
        cin >> S; //"into"
        tmp_str[tmp_cnt++] = S;
    }
    if (FLAG)
        oldfile >> S;
    else {
        cin >> S;
        tmp_str[tmp_cnt++] = S;
        mylog << S << '\n';
    }
    int id = mp[S];
    num[id] ++;
    //cout << num[id] << '\n';
    while (1) {
        if(FLAG == 0)
            init();
        //cin >> S;
        if (FLAG)
            oldfile >> S;
        else {
            cin >> S;
            tmp_str[tmp_cnt++] = S;
        }
        if (S == ";") {
            if (FLAG == 0) {
                init(1);
                cout << "INSERT COMPLETE\n";
            }
            break;
        }
        S = Tolower(S);
        int new_id = Find(S, id); //寻找位置
        //cin >> S;
        //S = Tolower(S);
        if (new_id == 0) {
            if (FLAG == 0) {
                init(1);
                Error(3);
            }
            break;
        }
        st_insert(id, new_id, num[id]);
    }
    if (FLAG == 0) {
        //cout << tmp_cnt << '\n';
        for(int i = 0 ; i < 2 ; i++)
            mycout << tmp_str[i] << ' ';
        mycout << tmp_str[2] << '\n';
        for (int i = 3; i < tmp_cnt - 1 ; i += 2) {
            mycout << tmp_str[i] << ' ' << tmp_str[i + 1] << '\n';
        }
        mycout << ';' << '\n';
    }
    //cout << num[id] << '\n';
    //cout << len[id] << '\n';
    if(FLAG == 0)
        init(1);
    //avg(id);
}

void debug() {
    for (int i = 1; i <= cnt; i++) {
        init();
        for (int j = 1; j <= len[i]; j++) {
            cout << ss[i][j][0] << ' ';
        }
        cout << '\n';
    }
}

void Login_in() {
    //system("color 04");
    string s;
    while (1) {
        cout << "Enter password: ";
        cin >> s;
        if (s == "quit") {
            quit();
            break;
        }

        if (s == "******") { //假装像mysql一样可以隐藏输入密码
            system("cls");
            //system("color 04");
            puts("Welcome to the QpSQL monitor!");
            puts("Commands end with ';'!");
            puts("Server version: 0.0.0.1 Alpha");
            puts("Qpwlkq is licensed under the Apache License Version 2.0");
            //system("color 03");
            break;
        }
        else {
            Error(1);
        }
    }
}

//输出单表, 所有列
void Print_1(int id) {
    //cout << num[id] << "asdf" << len[id] << '\n';
    init(1);
    for (int j = 1; j <= len[id]; j++) {
        cout << ss[id][j][0] << ' ';
    }
    cout << '\n';
    init(1);
    for (int j = 1; j <= len[id]; j++) {
        cout << ss[id][j][1] << ' ';
    }
    cout << '\n';
    for (int i = 0; i < num[id]; i++) {
        init();
        for (int j = 1; j <= len[id]; j++) {
            //cout << Type[ss[id][j][1]] << '\n';
            switch (Type[ss[id][j][1]]) {
            case 1: //double
                cout << ab[id][j].data1[i] << ' '; break;
            case 2:
                cout << ab[id][j].data2[i] << ' '; break;
            case 3:
                cout << ab[id][j].data3[i] << ' '; break;
            case 4:
                cout << ab[id][j].data4[i] << ' '; break;
            }
        }
        cout << '\n';
    }
}

//输出单表, 部分列
void Print_2(int id) {
    //cout << num[id] << ' ' << len[id] << '\n';
    init(1);
    for (int j = 1; j <= len[id]; j++) {
        if (vis_1[j] == 0)
            continue;
        cout << ss[id][j][0] << ' ';
    }
    cout << '\n';
    init(1);
    for (int j = 1; j <= len[id]; j++) {
        if (vis_1[j] == 0)
            continue;
        cout << ss[id][j][1]<< ' ';
    }
    cout << '\n';
    for (int i = 0; i < num[id]; i++) {
        init();
        for (int j = 1; j <= len[id]; j++) {
            //cout << "vz\n";
            if (vis_1[j] == 0)
                continue;
            switch (Type[ss[id][j][1]]) {
            case 1: //double
                cout << ab[id][j].data1[i] << ' '; break;
            case 2:
                cout << ab[id][j].data2[i] << ' '; break;
            case 3:
                cout << ab[id][j].data3[i] << ' '; break;
            case 4:
                cout << ab[id][j].data4[i] << ' '; break;
            }
        }
        cout << '\n';
    }
}


void Print_Table_All(string sz, string sx) {
    string s;
    string s2;
    //cin >> s;
    s = sz;
    //s = "*";
    //cout << mp[s] << '\n';
    //cin >> s2;
    s2 = sx;
    if (s2 != ";") {
        Error(6);
        init(1);
        return;
    }
    if (s == "*") {
        set<int>::iterator iter = st.begin();
        init();
        cout << "--------------------\n";
        for (iter; iter != st.end(); iter++) {
            init();
            cout << "Table " << _mp[*iter] << '\n';

            Print_1(*iter);
            init();
            cout << "--------------------\n";
            //cout << '\n';
        }
    }
    else {
        if (mp[s] == 0) {
            Error(7);
        }
        else {
            init();
            cout << "--------------------\n";
            init();
            cout << "Table " << _mp[mp[s]] << '\n';
            Print_1(mp[s]);
            init();
            cout << "--------------------\n";
        }
    }
    init(1);
    return;
}

int Visit(int id) {
    memset(vis_1, 0, sizeof vis_1);
    for (int i = 1; i <= cnt_1; i++) {
        int flag1 = 0;
        for (int j = 1; j <= len[id]; j++) {
            if (ss[id][j][0] == tp[i]) {
                vis_1[j] = 1;
                flag1 = 1;
                break;
            }
        }
        if (flag1 == 0) {
            init(1);
            Error(5);
            return 0;
            break;
        }
    }
    return 1;
}

void select() {
    string s, ss;
    cin >> s;
    s = Tolower(s);
    mylog << s << '\n';
    int flag = 1;
    if (s == "*" || s == "all") {
        flag = 0;
        cin >> s; // from 
        if (s == ";") {
            Print_Table_All("*", ";");
            //init();
            return;
        }
        cin >> s; // table_name
        cin >> ss; // ";"
        //init();
        //cout << "--------------------\n";
        //cout << "Table " << _mp[s] << '\n';
        

        Print_1(mp[s]);
        //init();
        //cout << "--------------------\n";
    }
    else {
        //"some"
        cnt_1 = 1;
        tp[cnt_1] = s;
        while (1) {
            cin >> s;
            s = Tolower(s);
            if (s == "from") {
                break;
            }
            cnt_1 += 1;
            tp[cnt_1] = s;
            //cout << s << '\n';
        }
        //cout << cnt_1 << '\n';
        cin >> s; // table_name
        //cout << mp[s] << '\n';
        int flag = Visit(mp[s]);
        //for (int i = 1; i <= cnt_1; i++) {
            //cout << vis_1[i] << ' ';
        //}
        //cout << '\n';
        if(flag == 1)
            Print_2(mp[s]);
        cin >> s; // ';'
    }
    init(1);
}

bool judge(string s) { //删表/删行
    return 0;
}

void Drop() {
    string s;
    if (FLAG)
        oldfile >> s;
    else {
        cin >> s;
        mycout << "drop table ";
    }
    s = Tolower(s);
    if (s == "table") {
        if (FLAG)
            oldfile >> s;
        else {
            cin >> s;
            mylog << s;
            mycout << s;
        }
        st.erase(mp[s]);
        len[mp[s]] = 0;
        num[mp[s]] = 0;
        _mp[mp[s]] = "";
        mp[s] = 0;
        if (FLAG)
            oldfile >> s;
        else {
            cin >> s; // ';'
            mycout << " ;" << '\n';
        }
        if(FLAG == 0)
            init();
        if(FLAG == 0)
            cout << "DROP COMPLETE\n";
    }
    else if (s == "data") {
        cin >> s; //from
        mycout << s << ' ';
        cin >> s; //table_name
        mycout << s << ' ';
        cin >> s; // ';'
        mycout << s;
    }
    else {
        if(FLAG == 0)
            Error(6);
        return;
    }
    if(FLAG == 0)
        init(1);
}

void Update() {
    string s, s2, sss;
    if (FLAG) {
        oldfile >> s >> s >> s2 >> sss;
    }
    else {
        mycout << "update ";
        cin >> s; //table
        mycout << s << ' ';
        cin >> s; //table_name
        mycout << s << ' ';

        cin >> s2; //data / set
        mycout << s2 << ' ';
        cin >> sss;
        mycout << sss << ' ';
        mylog << s << '\n';
    }
    //cnt_1 = 1;
    //cin >> tp[cnt_1]; //data_name
    int id = mp[s];
    //Visit(id);
    for (int i = 0; i < num[id]; i++) {
        //init();
        for (int j = 1; j <= len[id]; j++) {
            if (ss[id][j][0] != sss)
                continue;
            
            switch (Type[ss[id][j][1]]) {
            case 1:
                double s1;
                s1 = Input(s1);
                for (auto it = ab[id][j].data1.begin(); it != ab[id][j].data1.end(); ++it) {
                    if (*it == s1) {
                        if (FLAG)
                            oldfile >> s;
                        else {
                            cin >> s;
                            mycout << s1 << " to " << ' ';
                        }
                        *it = Input(s1);
                        mycout << s1 << '\n';
                    }
                }
                break;
            case 2:
                ll s2;
                s2 = Input(s2);
                for (auto it = ab[id][j].data2.begin(); it != ab[id][j].data2.end(); ++it) {
                    if (*it == s2) {
                        if (FLAG)
                            oldfile >> s;
                        else {
                            cin >> s;
                            mycout << s2 << " to" << ' ';
                        }
                        *it = Input(s2);
                        mycout << s2 << '\n';
                    }
                }
                //int x = ab[id][j].data2.push_back(Input(s2));
                break;
            case 3:
                int s3;
                s3 = Input(s3);
                for (auto it = ab[id][j].data3.begin(); it != ab[id][j].data3.end(); ++it) {
                    if (*it == s3) {
                        if (FLAG)
                            oldfile >> s;
                        else {
                            cin >> s;
                            mycout << s3 << " to" << ' ';
                        }
                        *it = Input(s3);
                        mycout << s3 << '\n';
                    }
                }
                //int x = ab[id][j].data3.push_back(Input(s3));
                break;
            case 4:
                string s4;
                s4 = Input(s4);
                for (auto it = ab[id][j].data4.begin(); it != ab[id][j].data4.end(); ++it) {
                    if (*it == s4) {
                        if (FLAG)
                            oldfile >> s;
                        else {
                            cin >> s;
                            mycout << s4 << " to" << ' ';
                        }
                        *it = Input(s4);
                        mycout << s4 << '\n';
                    }
                }
                //ab[id][j].data4.push_back(Input(s4));
            }
           
        }
    }
    if(FLAG == 0)
        init(1);
    if (FLAG)
        oldfile >> s;
    else {
        cin >> s;
        mycout << ';' << '\n';
    }
    //cout <<"???" << '\n';
}

void File() {
    //FILE* f = fopen("C:/Users/DELL/Desktop/test.qp", "r+");
    //while()
    FLAG = 1;

    oldfile.open("C:/Users/DELL/Desktop/test.qp", ios::in);
    while (oldfile >> s[0]) {
        s[0] = Tolower(s[0]);
        //cout << s[0] << '\n';
        switch (Opr[s[0]]) {
        //case 1:
            //quit(); break;
        case 2:
            if (FLAG) {
                oldfile >> s[1];
                oldfile >> s[2];
            }
            else
                cin >> s[1] >> s[2];
            create_Table(s[2]); break;
        case 3:
            insert(); break;
        //case 4:
            //select(); break;
        case 5:
            Drop(); break;
        case 6:
            Update(); break;
        //case 7:
            //Print_Table_All(); break;
        //default: {
            //Error(6);
            //init(1);
        //}
        }
    }
    oldfile.close();
    FLAG = 0;
    //system("color 05");
    //init(1);
}

int main() {
    It();

    //Login_in();
    File();

    init(1);
    //cout << 'x';
    mycout.open("C:/Users/DELL/Desktop/test.qp", std::ios::app);
    mylog.open("C:/Users/DELL/Desktop/log.qp", std::ios::app);
    
    auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
    //mycout << std::put_time(std::localtime(&t), "%Y-%m-%d %H-%M-%S") << '\n';
    mylog << std::put_time(std::localtime(&t), "%Y-%m-%d %H-%M-%S") << '\n';


    int fg1 = 1;
    while (cin >> s[0]) {
        s[0] = Tolower(s[0]);
        switch (Opr[s[0]]) {
        case 1: {
            quit();
            mylog << "quit" << '\n';
            fg1 = 0;
            break;
        }
        case 2: {
            cin >> s[1] >> s[2];
            create_Table(s[2]);
            mylog << "create" << " " << s[2] << '\n';
            break;
        }
        case 3: {
            insert();
            mylog << "insert" << ' ';
            break;
        }
        case 4: {
            select();
            mylog << "select" << ' ';
            break;
        }
        case 5: {
            Drop();
            mylog << "drop" << ' ';
            break;
        }
        case 6: {
            Update();
            mylog << "update" << ' ';
            fg1 = 1;
            break;
        }
        case 7: {
            string xx;
            cin >> xx >> xx;
            Print_Table_All("*", ";");
            mylog << "show" << '\n';
            break;
        }
        default: {
            Error(6);
            init(1);
        }
        }
        if (fg1 == 0)
            break;
        //debug();
    }
    mycout.close();
    mylog.close();
    return 0;
}

/*

create table name1
    int

update
insert name1, name2 from name2 where ???

drop name1

alert


空格分隔符
每个语句以单独';'结束
1. create语句
create table asdf
a int
b string
c ll
d double
;

2. insert语句
insert new
Sname asdfasdf
Sgrade 100
;

3. select * from name1
4. select name1 name2 from name3

5. drop name1


*/

/*


/*
.log日志文件: 记录所有输出字符串,不管正误
.qp 数据文件: 存储数据
*/


/*
文件输入输出测试
#include <bits/stdc++.h>
#include <chrono>
using namespace std;
#define FILE_NAME "test.txt" // 文件名称

int main() {
    FILE* f = fopen("C:/Users/DELL/Desktop/test.qp", "r+");


    //cout << std::put_time(std::localtime(&t), "%Y/%m/%d %H:%M:%S") << '\n';
    
    ofstream mycout, mylog;
    mycout.open("C:/Users/DELL/Desktop/test.qp", std::ios::app);
    mylog.open("C:/Users/DELL/Desktop/ts.log", std::ios::app);
    auto t = chrono::system_clock::to_time_t(chrono::system_clock::now());
    mycout << std::put_time(std::localtime(&t), "%Y-%m-%d %H-%M-%S") << '\n';
    mylog << std::put_time(std::localtime(&t), "%Y-%m-%d %H-%M-%S") << '\n';
    string a;
    cin >> a;
    //mycout << a;
    while (cin >> a) {
        mycout << a << '\n';
        mylog << a << '\n';
    }
    //fclose();
    //mycout.clear();
    mycout.close();
    //mylog.clear();
    mylog.close();
    //cout << a;

    清空文件

    ofstream qpclose("C:/Users/DELL/Desktop/test.qp");
    ofstream logclose("C:/Users/DELL/Desktop/test.qp");
    qpclose.close();
    logclose.close();
    

    char str[100];
    while (fgets(str, 199, f)) {
        cout << str << '\n';
    }

    //fclose(f);
    //f = fopen("C:/Users/DELL/Desktop/test.qp", "a+");

    gets_s(str);
    fprintf(f, "%s\n", str);
    fclose(f);
    return 0;
}
*/


/*

create table t1
a int
b double
c string
;
create table t2
a int
b int
;
create table t3
c string
d double
;
insert into t1
a 100000
b 2.2
c database
;
insert into t1
a 200000
b 3.3
c dbms
;
insert into t2
a 123
b 321
;
select * ;
select * from t1 ;
select a b from t1 ;
select a b c from t1 ;

show databases ;

drop table t1 ;

update table t1 data a 100 to 200 ;




*/
