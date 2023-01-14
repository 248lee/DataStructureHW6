#include <bits/stdc++.h>
#include "List.h"
using namespace std;

class Vertex
{
    friend class Graph;
    friend vector<Vertex>::iterator find(vector<Vertex>::iterator first, vector<Vertex>::iterator end, int id);

private:
    int data;
    List in, out; // adjecency list 的進化版，分為「入のlist」與「出のlist」，這樣比較好做 DeleteVertex
public:
    Vertex(int _data);
    void addIn(int id, int weight);
    void addOut(int id, int weight);
};

vector<Vertex>::iterator find(vector<Vertex>::iterator first, vector<Vertex>::iterator end, int id)
{
    auto itr = first;
    for (; itr < end; itr++)
        if (itr->data == id)
            break;
    return itr;
}

Vertex::Vertex(int _data) // Vertex 的建構式
{
    this->data = _data;
    this->in = List();
    this->out = List();
}

void Vertex::addIn(int id, int weight) // 新增編號為"id"的節點進入此節點
{
    this->in.push_front({id, weight});
}

void Vertex::addOut(int id, int weight) // 新增編號為"id"的節點自本節點出去
{
    this->out.push_front({id, weight});
}

class Graph
{
private:
    vector<Vertex> vs; // 保存此圖所有的節點們
    vector<bool> flag; // 用於顯示該節點是否存在，如果被刪掉了，就會變成false
    int n;             // 此圖內有幾個節點
public:
    Graph();
    ~Graph();
    void InsertVertex(int v);
    void InsertEdge(int u, int v, int weight);
    vector<pair<int, int> > ShortestPath(int v);
    vector<pair<pair<int, int>, int> > MinSpanTree();
};

Graph::Graph()
{
    this->vs = vector<Vertex>();
    this->flag = vector<bool>();
    this->n = 0;
}

Graph::~Graph()
{
}

void Graph::InsertVertex(int v)
{
    Vertex tmp = Vertex(v); // A "Vertex" includes 2 "Lists"
    this->vs.push_back(tmp); // A double-free error occurs at here!!!!!!
    this->flag.push_back(true);
    this->n++;
}

void Graph::InsertEdge(int u, int v, int weight) // insert an edge from u to v
{
    // 先找到u和v的節點編號
    auto utr = find(this->vs.begin(), this->vs.end(), u);
    auto vtr = find(this->vs.begin(), this->vs.end(), v);
    int u_id = utr - this->vs.begin();
    int v_id = vtr - this->vs.begin();
    if (!(utr != this->vs.end() && vtr != this->vs.end() && this->flag[utr - this->vs.begin()] && this->flag[vtr - this->vs.begin()]))
        throw "ERROR INSERT EDGE!! Such node does not exist!\n";

    // 再把v加進u的「出のlist」、把u加進v的「入のlist」
    utr->addOut(v_id, weight);
    vtr->addIn(u_id, weight);
}

vector<pair<int, int> > Graph::ShortestPath(int v) // Using the Dijkstra Algorithm to find the shortest path from v to all vertices.
{
    vector<int> result = vector<int>(this->vs.size(), -1);
    vector<bool> s_flag = vector<bool>(this->vs.size(), false); // 就是課本裡的那個「集合S」。以陣列表示，true代表屬於S；false代表不屬於S
    // initial state
    auto vtr = find(this->vs.begin(), this->vs.end(), v);
    int v_id = vtr - this->vs.begin();
    if (!(vtr != this->vs.end() && this->flag[vtr - this->vs.begin()]))
        throw "ERROR SHORTEST PATH!! Such node does not exist!\n";
    result[v_id] = 0;
    s_flag[v_id] = true;
    for (auto ltr = vtr->out.begin(); !ltr.is_end(); ltr++)
        result[(*ltr).first] = (*ltr).second;

    // iterating state
    for (int i = 1; i < this->n; i++)
    {
        // 以下為課本中所謂的 "Choose(n)"
        int min_id = -1, min_dist = -1;
        for (int j = 0; j < this->vs.size(); j++)
        {
            if (result[j] != -1 && !s_flag[j])
            {
                min_id = j;
                min_dist = result[j];
                break;
            }
        }
        if (min_id == -1) // 確認還有有機會但尚未被加入S的點
            break;

        for (int j = min_id + 1; j < this->vs.size(); j++)
        {
            if (result[j] != -1 && !s_flag[j] &&result[j] < min_dist)
            {
                min_id = j;
                min_dist = result[j];
            }
        }

        // Choose完了，加入S並更新result吧
        s_flag[min_id] = true;
        for (auto ltr = this->vs[min_id].out.begin(); !ltr.is_end(); ltr++)
        {
            int target_id = (*ltr).first;
            if (!s_flag[target_id] && (result[target_id] == -1 || result[min_id] + (*ltr).second < result[target_id]))
                result[target_id] = result[min_id] + (*ltr).second;
        }
    }
    vector<pair<int, int> > real_result;
    for (int i = 0; i < result.size(); i++)
        real_result.push_back({result[i], this->vs[i].data});
    
    return real_result;
}

vector<pair<pair<int, int>, int> > Graph::MinSpanTree() // Using the Prim's Algorithm to find the min spanning tree and return the result in the format "root leaf edge", return empty vector if there is no min spanning tree.
{
    vector<bool> visited(this->vs.size()); // 用來檢查哪些節點已經被放進spantree
    vector<int> spantree; // 裡面存著已經在spantree裡的節點們
    vector<pair<pair<int, int>, int> > result;

    visited[0] = true;
    spantree.push_back(0);
    for (int i = 0; i < this->n - 1; i++)
    {
        int min_edge = INT_MAX, min_root, min_leaf = -1;
        for (int j = 0; j < spantree.size(); j++) // 來找和spanning tree相鄰的「最小」邊吧
        {
            for (auto ltr = this->vs[spantree[j]].out.begin(); !ltr.is_end(); ltr++)
            {
                pair<int, int> tmp_end = (*ltr);
                if (!visited[tmp_end.first] && tmp_end.second < min_edge)
                {
                    min_edge = tmp_end.second;
                    min_root = spantree[j];
                    min_leaf = tmp_end.first;
                }
            }
        }
        if (min_leaf == -1) // 找不到最小的話，就代表這張圖沒有spanning tree
            return vector<pair<pair<int, int>, int> >();
        
        visited[min_leaf] = true;
        spantree.push_back(min_leaf);
        result.push_back({{this->vs[min_root].data, this->vs[min_leaf].data}, min_edge}); // 加進那條最小的邊
    }
    return result;
}
