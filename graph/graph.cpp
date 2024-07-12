#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <unordered_map>
#include <algorithm>

/// @brief Graph类
/// @tparam Vertex 需支持各种比较运算符, 预计<<运算符
/// @tparam Hash   对Vertex哈希的方法, 用来存边
/// 
template<typename Vertex, typename Hash>
class Graph
{
public:
    
    // 点数
    size_t _M_vertex_num = 0;

    // 边数
    size_t _M_edge_num = 0;

    // 邻接表
    std::vector<std::list<Vertex>> _M_adj;

    // 逆邻接表
    std::vector<std::list<Vertex>> _M_invs_adj;

    // 图的点集, Key为Vertex, Value为Vertex在图中点的编号(从0开始)
    std::unordered_map<Vertex, size_t, Hash> _M_hash_table;

public:
    
    /// @brief 初始化一个图
    Graph() { }


    /// @brief 获取点数和边数
    /// @return 点数和边数
    size_t get_vertex_num() { return _M_vertex_num; }
    size_t get_edge_num()   { return _M_edge_num; }


    /// @brief 从图中加入一个点
    /// @param v 点
    /// @return true-加边成功, 反之-false
    bool add_vertex(Vertex& v) 
    {
        // 判断v是否已经在图中, 若已经在图中, 则加点失败
        if(_M_hash_table.count(v)) {
            return false;
        }

        _M_adj.emplace_back();
        _M_invs_adj.emplace_back();
        _M_hash_table[v] = _M_vertex_num++;

        return true;
    }


    /// @brief 往图中加入一条边
    /// @param u 边的出度
    /// @param v 边的入度
    /// @return 同上
    bool add_edge(Vertex& u, Vertex& v)
    {
        // 判断两个点是否在图中, 若有一者不在, 则加边失败
        if(!_M_hash_table.count(u) || !_M_hash_table.count(v)) {
            return false;
        }

        _M_adj[_M_hash_table[u]].emplace_back(v);
        _M_invs_adj[_M_hash_table[v]].emplace_back(u);
        _M_edge_num++;

        return true;
    }


    /// @brief 删除顶点, 只有该点不与任何点有关系才能删除
    /// @param u 待删点
    /// @return -1-该点无法删除, 0-该点不存在, 1-删除成功
    int del_vertex(Vertex& u) 
    {
        if(!_M_hash_table.count(u)) {
            return -1;
        }

        size_t idx = _M_hash_table[u];

        // 若该点有出边或者入边, 无法删除
        if(!(_M_adj[idx].empty() && _M_invs_adj[idx].empty())) {
            return -1;
        }

        // 删除该点
        std::cout << "idx = " << idx << std::endl;
        _M_hash_table.erase(u);
        // _M_adj.erase(_M_adj.begin() + idx);
        // _M_invs_adj.erase(_M_invs_adj.begin() + idx);

        return 1;
    }


    /// @brief 删边
    /// @param u 出度
    /// @param v 入度
    /// @return true-删除成功, false-删除失败
    bool del_edge(Vertex& u, Vertex& v)
    {
        // 判断两个点是否在图中, 若有一者不在, 则加边失败
        if(!_M_hash_table.count(u) || !_M_hash_table.count(v)) {
            return false;
        }

        // 获取点u, v的编号
        size_t x = _M_hash_table[u], y = _M_hash_table[v];
        _M_adj[x].remove(v);
        _M_invs_adj[y].remove(u);
        _M_edge_num--;
        
        return true;
    }


    /// @brief 获取某点的所有出边
    /// @param x 
    /// @return 
    std::list<Vertex> get_out(Vertex& x)
    {

    }


    /// @brief 获取某点的所有入边
    /// @param x 
    /// @return 
    std::list<Vertex> get_in(Vertex& x)
    {

    }


    /// @brief 按照邻接表的形式打印该图, 打印结果为点的编号
    void print_adj()
    {
        for(auto it = _M_hash_table.begin(); it != _M_hash_table.end(); it++) {
            std::cout << it->first;
            for(auto& v : _M_adj[it->second]) {
                std::cout << " --> " << _M_hash_table[v];
            }
            std::cout << "\n";
        }
    }

    /// @brief 按照逆邻接表的形式打印该图, 打印结果为点的编号
    void print_invs_adj()
    {
        for(auto it = _M_hash_table.begin(); it != _M_hash_table.end(); it++) {
            std::cout << it->first;
            for(auto& v : _M_invs_adj[it->second]) {
                std::cout << " --> " << _M_hash_table[v];
            }
            std::cout << "\n";
        }
    }

    ~Graph() { }

};


struct Vertex {
    int id;

    // 哈希方法
    struct Hash {
        size_t operator()(const Vertex& v) const {
            return std::hash<int>()(v.id);
        }
    };

    Vertex() : id(-1) { }

    Vertex(int id) : id(id) { }

    friend std::istream& operator>>(std::istream& in, Vertex& v) {
        in >> v.id;
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Vertex& v) {
        out << v.id;
        return out;
    }

    friend bool operator==(const Vertex& l, const Vertex& r) {
        return l.id == r.id;
    }

    friend bool operator!=(const Vertex& l, const Vertex& r) {
        return l.id != r.id;
    } 

    friend bool operator<(const Vertex& l, const Vertex& r) {
        return l.id < r.id;
    }

    friend bool operator>(const Vertex& l, const Vertex& r) {
        return l.id > r.id;
    }

    friend bool operator<=(const Vertex& l, const Vertex& r) {
        return !(l.id > r.id);
    }

    friend bool operator>=(const Vertex& l, const Vertex& r) {
        return !(l.id > r.id);
    }

    ~Vertex() { }
};


int main()
{
    Vertex v0(0);
    Vertex v1(1);
    Vertex v2(2);

    Graph<Vertex, typename Vertex::Hash> g;
    g.add_vertex(v0);
    g.add_vertex(v1);
    g.add_vertex(v2);
    g.add_edge(v0, v1);
    g.add_edge(v0, v2);
    g.add_edge(v1, v2);

    {
        g.print_adj();
        std::cout << std::endl;
    }

    g.del_edge(v0, v1);

    {
        g.print_adj();
        std::cout << std::endl;
    }

    g.del_edge(v0, v2);
    
    {
        g.print_adj();
        std::cout << std::endl;
    }

    g.del_vertex(v0);

    {
        g.print_adj();
        std::cout << std::endl;
        g.print_invs_adj();
    }

    using namespace std;
    cout << endl;

    int i = 0;
    for(auto& v : g._M_adj) 
    {
        cout << i++ << ' ' << v.size() << endl;
        for(auto& l : v) {
            cout << l << ' ';
        }
        cout << '\n' << endl;
    }
}