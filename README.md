
[toc]

### 一, 基本声明

#### table类 
```c++
struct table {
    string s; //数据类型
    int len; //个数
    int cnt[10];

    vector<double> data1; //支持最多N个表
    vector<ll> data2;
    vector<int> data3;
    vector<string> data4;

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
    }
}ab[maxn][maxm];
```

#### 初始化映射
```C++
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
```

#### 其他变量

```C++
ifstream oldfile; //文件输入流
ofstream mycout, mylog; //文件输出流, 目标文件不存在则自动创建

const int maxn = 10; // 最大表数
const int maxm = 10; // 最大列数

set<int>st; //表集
map<string, int>Type; //数据类型映射
map<string, int>Opr; //操作映射

map<string, int>mp; //表名 -> id
map<int, string>_mp; //id -> 表名

int cnt; //表数

int FLAG; //文件处理标志变量
int tmp_cnt;
string tmp_str[100]; //转存

int len[maxn]; //列数

int vis[maxn];
string s[maxn];

int num[maxn]; //行数

string ss[maxn][maxm][2]; // 一维:名称, 二维:数据类型

int cnt_1; //select 记录选择列
string tp[maxm];
int vis_1[maxm]; //select 标记选择那些列

```

### 二, 业务逻辑

将输入分成两部分

首先处理第一部分, **File**() 函数读取文件中的语句, 然后通过主函数再去处理当前输入. 部分函数中包含**FLAG**变量, 如果FLAG为真, 则意味着正在处理输入, 不会有任何输出内容, 文件处理完成, FLAG赋值0.

```C++
    mycout.open("C:/Users/DELL/Desktop/test.qp", std::ios::app);
    mylog.open("C:/Users/DELL/Desktop/ts.log", std::ios::app);
```
打开文件

根据输入第一个关键词, 进行映射, map<X, int>的属性之一如果没有设置过映射, 则映射为0, 根据这个特性可以判断是否正确输入.

每次输入都逐个关键词判断输出语句是否正确, 然后最终正确则处理输入, 否则报错.

输入数据值:

```C++
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
```
写了一个模板函数, 后面每个地方根据不同的映射, 定义不同的变量, 然后均赋值x = Input(x); 即可, 类中作为举例, 定义了4个变量(long long int, int, double, string), 可以简单修改后, 支持所有变量类型.


### 三, 测试语句
```C++
create table t1
a int
b double
c string
;
create table t2
a int
b int ;

create table t3
c string
d double ;

insert into t1
a 1000
b 2.2
c database ;

insert into t1
a 2000
b 3.3
c dbms ;

insert into t2
a 123
b 321 ;

select * ;
select * from t1 ;
select a b from t1 ;
select a b c from t1 ;

show databases ;

drop table t1 ;

update table t1 data a 1000 to 299 ;
```
