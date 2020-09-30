#ifndef CUIHENGRIMOIRE_GRAPH_HPP
#define CUIHENGRIMOIRE_GRAPH_HPP

#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

namespace cuihengrimoire {

template<typename NodeT>
struct graph_t {
    using node_t = NodeT;
    using node_index_t = long long;
    std::vector<node_t> nodes;
    std::unordered_map<node_index_t, std::vector<node_index_t>> edges;

    explicit graph_t() {}

    void add_node(node_t&& n) {
        nodes.emplace_back(std::move(n));
        edges[nodes.size()-1] = {};
    }
    void add_edge(node_index_t src, node_index_t dst) {
        edges[src].push_back(dst);
    }

    using path_t = std::vector<node_index_t>;
    std::vector<path_t> search_shortest_path_from(node_index_t start) const {
        assert(0 <= start && start < static_cast<node_index_t>(nodes.size()));
        std::vector<long long> n_steps(nodes.size(), std::numeric_limits<long long>::max());
        std::vector<path_t> ret{nodes.size()};
        n_steps[start] = 0;

        std::queue<node_index_t> q;
        q.push(start);

        while (!q.empty()) {
            node_index_t node_index = q.front();
            q.pop();
            for (auto const& neighbor_node_id : edges.at(node_index)) {
                if (n_steps[neighbor_node_id] <= n_steps[node_index]+1)
                    continue;
                n_steps[neighbor_node_id] = n_steps[node_index]+1;
                ret[neighbor_node_id] = ret[node_index];
                ret[neighbor_node_id].push_back(node_index);
                q.push(neighbor_node_id);
            }
        }
        return ret;
    }
};

}

#endif
