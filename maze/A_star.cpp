

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//��������
int direc[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

//���,�����б���
enum Flag
{
    SEAL,
    OPEN,
    UNVISITED
};

//===========��С�ѽڵ���============
//�����ȼ�Ϊ:F=G+H
//GΪ��ǰ��·����
//HΪ���Ƶ�ǰλ�õ�Ŀ��λ�ÿ���̽��:��ǰ�ڵ�(x,y),Ŀ��ڵ�(x0,y0),���������پ�����ΪH,H=|x-x0|+|y-y0|

typedef struct node
{
    int _x, _y;       //�ڵ�����(x,y)
    int _G;           //ʵ���ѿ���G
    int _H;           //̽�⽫����H
    int _F;           //���ȼ�_F=_G+_H
    struct node *pre; //ǰ������
} Queue_Node;

//_seal[][]�ṹ��,������Ŀ���(���)���,���濪�Ž���ָ��
typedef struct
{
    Flag flag;
    Queue_Node *point;
} Seal;

//=============A*�㷨��=============
//���Ա�б�����:
//1.A*�㷨����
//2.���������پ���H����
//3.�Թ����뺯��
//4.���Ž�·���������
//5.����б�
//6.��С��ʵ�ֿ����б�
//7.�Թ���,��
//8.�Թ���ͼ
//9.���,Ŀ���
//10.��С��������
//11.����ֵ����
//12.�߽��ж�
//13.��ӡ·��
class A_Star
{
public:
    //���캯��,��ӡ��ӭ��Ϣ
    A_Star()
    {
        cout << "������ʹ�õ������ż�A*�㷨����Թ�" << endl;
        cout << "�㷨���ù����������,�Լ�̽�ⷽ������ѡ������С��״̬�ڵ������չ" << endl;
        cout << "����,��Ӧ�ø�����ʾ��������Թ�����Ϣ,���������A*�㷨���" << endl;
        input();
    }
    //��������
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
    //�Թ����뺯��
    void input()
    {
        cout << "����: �Թ���߳�,�ϱ߿�! ���磺5 3" << endl;
        cin >> _len >> _wid;
        _seal = new Seal *[_len + 1];
        _maze = new unsigned char *[_len + 1];
        for (int i = 0; i <= _len; ++i)
        {
            _seal[i] = new Seal[_wid + 1];
            _maze[i] = new unsigned char[_wid + 1];
        }
        cout << "����һ�п�ʼ�����Թ���Ϣ" << endl;
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
        cout << "�����������,Ŀ�������,����1 2 3 4" << endl;
        cin >> _sx >> _sy >> _ex >> _ey;
        if (_maze[_sx][_sy] == '1' || _maze[_ex][_ey] == '1' || bound(_sx, _sy) == false || bound(_ex, _ey) == false)
        {
            cout << "�����ܴ��������������" << endl;
            return;
        }
        cout << "����A*�㷨��ӡ������£�" << endl;
        A();
    }
    //A*�����㷨
    void A()
    {
        //Դ���뿪���б�
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
        //A*����
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
                if (bound(tx, ty) == false || _maze[tx][ty] == '1' || _seal[tx][ty].flag == SEAL) //�߽�,��·,���,�򲻿��������
                {
                    continue;
                }
                if (_seal[tx][ty].flag == UNVISITED)
                {
                    if (tx == _ex && ty == _ey)
                    {
                        print(p_node);
                        cout << "(" << tx << "," << ty << ")" << endl;
                        cout << "�ܹ�����:" << p_node->_F << "��" << endl;
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
        cout << "û�д�(" << _sx << "," << _sy << ")--->"
             << "(" << _ex << "," << _ey << ")��·��" << endl;
    }
    //��ӡ·��
    void print(Queue_Node *p)
    {
        if (p == NULL)
        {
            return;
        }
        print(p->pre);
        cout << "(" << p->_x << "," << p->_y << "),";
    }
    //�߽��ж�
    bool bound(int x, int y)
    {
        return (x <= _len) && (x >= 1) && (y <= _wid) && (y >= 1);
    }
    //���������پ���H����
    int get_H(int x, int y)
    {
        return ab(x - _ex) + ab(y - _ey);
    }
    //����ֵ����
    int ab(int i)
    {
        return i < 0 ? -i : i;
    }

private:
    //�±ȽϺ����ṹ��
    struct cmp
    {
        bool operator()(Queue_Node *n1, Queue_Node *n2)
        {
            return n1->_F > n2->_F;
        }
    };
    priority_queue<Queue_Node *, vector<Queue_Node *>, cmp> _open; //��С��(�����б�)
    int _len, _wid;                                                //�Թ���߳�,�ϱ߿�
    int _sx, _sy, _ex, _ey;
    Seal **_seal;          //��̬���ٷ���б�
    unsigned char **_maze; //�Թ���ͼ
};

int main()
{
    A_Star test;
    return 0;
}
