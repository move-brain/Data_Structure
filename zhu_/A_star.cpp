

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//方向向量
int direc[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

//封闭,开放列表标记
enum Flag
{
    SEAL,
    OPEN,
    UNVISITED
};

//===========最小堆节点类============
//堆优先级为:F=G+H
//G为当前的路径长
//H为估计当前位置到目标位置开销探测:当前节点(x,y),目标节点(x0,y0),则以曼哈顿距离作为H,H=|x-x0|+|y-y0|

typedef struct node
{
    int _x, _y;       //节点坐标(x,y)
    int _G;           //实际已开销G
    int _H;           //探测将开销H
    int _F;           //优先级_F=_G+_H
    struct node *pre; //前驱顶点
} Queue_Node;

//_seal[][]结构体,保存结点的开放(封闭)标记,保存开放结点的指针
typedef struct
{
    Flag flag;
    Queue_Node *point;
} Seal;

//=============A*算法类=============
//类成员列表如下:
//1.A*算法核心
//2.计算曼哈顿距离H函数
//3.迷宫输入函数
//4.最优解路径输出函数
//5.封闭列表
//6.最小堆实现开放列表
//7.迷宫长,宽
//8.迷宫地图
//9.起点,目标点
//10.最小堆排序函数
//11.绝对值函数
//12.边界判断
//13.打印路径
class A_Star
{
public:
    //构造函数,打印欢迎信息
    A_Star()
    {
        cout << "您正在使用的是入门级A*算法求解迷宫" << endl;
        cout << "算法采用广度优先搜索,以及探测方法优先选择开销最小的状态节点进行拓展" << endl;
        cout << "下面,您应该根据提示输入各种迷宫的信息,并请求调用A*算法求解" << endl;
        input();
    }
    //析构函数
    // ~A_Star()
    // {
    //     for (int i = 1; i <= _len; ++i)
    //     {
    //         for (int j = 1; j <= _wid; ++j)
    //         {
    //             if (_seal[i][j].point != NULL)
    //             {
    //                 delete _seal[i][j].point;
    //             }
    //         }
    //     }
    //     for (int i = 0; i <= _len; ++i)
    //     {
    //         delete[] _seal[i];
    //         delete[] _maze[i];
    //     }
    //     delete[] _seal;
    //     delete[] _maze;
    // }
    //迷宫输入函数
    void input()
    {
        cout << "输入: 迷宫左边长,上边宽! 例如：5 3" << endl;
        cin >> _len >> _wid;
        _seal = new Seal *[_len + 1];
        _maze = new unsigned char *[_len + 1];
        for (int i = 0; i <= _len; ++i)
        {
            _seal[i] = new Seal[_wid + 1];
            _maze[i] = new unsigned char[_wid + 1];
        }
        cout << "从下一行开始输入迷宫信息" << endl;
        for (int i = 1; i <= _len; ++i)
        {
            for (int j = 1; j <= _wid; ++j)
            {
                cin >> _maze[i][j];
                cout << _maze[i][j] << ' ';
                _seal[i][j].flag = UNVISITED;
                _seal[i][j].point = NULL;
            }
            cout<< endl;
        }
        cout << "输入起点坐标,目标点坐标,例如1 2 3 4" << endl;
        cin >> _sx >> _sy >> _ex >> _ey;
        if (_maze[_sx][_sy] == '1' || _maze[_ex][_ey] == '1' || bound(_sx, _sy) == false || bound(_ex, _ey) == false)
        {
            cout << "不可能存在这样的情况！" << endl;
            return;
        }
        cout << "调用A*算法打印结果如下：" << endl;
        A();
    }
    //A*核心算法
    void A()
    {
        //源点入开放列表
        Queue_Node *p_node = new Queue_Node;
        p_node->pre = NULL;
        p_node->_H = get_H(_sx, _sy);
        p_node->_G = 0;
        p_node->_x = _sx;
        p_node->_y = _sy;
        p_node->_F = p_node->_H + p_node->_G;
        _open.push(p_node);
        _seal[_sx][_sy].flag = OPEN;
        _seal[_sx][_sy].point = p_node;
        //A*搜索
        while (!_open.empty())
        {
            p_node = _open.top();
            _open.pop();
            int x = p_node->_x;
            int y = p_node->_y;
            _seal[x][y].flag = SEAL;

            for (int i = 0; i < 4; ++i)
            {
                int tx = x + direc[i][0];
                int ty = y + direc[i][1];
                if (bound(tx, ty) == false || _maze[tx][ty] == '1' || _seal[tx][ty].flag == SEAL) //边界,无路,封闭,则不考虑这个格
                {
                    continue;
                }
                if (_seal[tx][ty].flag == UNVISITED)
                {
                    if (tx == _ex && ty == _ey)
                    {
                        print(p_node);
                        cout << "(" << tx << "," << ty << ")" << endl;
                        cout << "总共走了:" << p_node->_F << "步" << endl;
                        return;
                    }
                    Queue_Node *temp = new Queue_Node;
                    _seal[tx][ty].flag = OPEN;
                    _seal[tx][ty].point = temp;
                    temp->pre = p_node;
                    temp->_G = p_node->_G + 1;
                    temp->_x = tx;
                    temp->_y = ty;
                    temp->_H = get_H(tx, ty);
                    temp->_F = temp->_G + temp->_H;
                    _open.push(temp);
                }
                // else
                // {
                //     Queue_Node *temp = _seal[tx][ty].point;
                //     if (p_node->_G + 1 < temp->_G)
                //     {
                //         temp->_G = p_node->_G + 1;
                //         temp->pre = p_node;
                //         temp->_F = temp->_G + temp->_H;
                //     }
                // }
            }
        }
        cout << "没有从(" << _sx << "," << _sy << ")--->"
             << "(" << _ex << "," << _ey << ")的路径" << endl;
    }
    //打印路径
    void print(Queue_Node *p)
    {
        if (p == NULL)
        {
            return;
        }
        print(p->pre);
        cout << "(" << p->_x << "," << p->_y << "),";
    }
    //边界判断
    bool bound(int x, int y)
    {
        return (x <= _len) && (x >= 1) && (y <= _wid) && (y >= 1);
    }
    //计算曼哈顿距离H函数
    int get_H(int x, int y)
    {
        return ab(x - _ex) + ab(y - _ey);
    }
    //绝对值函数
    int ab(int i)
    {
        return i < 0 ? -i : i;
    }

private:
    //仿比较函数结构体
    struct cmp
    {
        bool operator()(Queue_Node *n1, Queue_Node *n2)
        {
            return n1->_F > n2->_F;
        }
    };
    priority_queue<Queue_Node *, vector<Queue_Node *>, cmp> _open; //最小堆(开放列表)
    int _len, _wid;                                                //迷宫左边长,上边宽
    int _sx, _sy, _ex, _ey;
    Seal **_seal;          //动态开辟封闭列表
    unsigned char **_maze; //迷宫地图
};

int main()
{
    A_Star test;
    return 0;
}
