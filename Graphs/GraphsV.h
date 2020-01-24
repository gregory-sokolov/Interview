#pragma once

#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <map>
#include <unordered_set>
#include <algorithm>

// Graph vertex
template<typename T, typename C>
struct GraphVertex
{
	std::list<std::pair<GraphVertex<T, C>*, C>> neighbors;
	T key;

	GraphVertex() {}
	GraphVertex(const T& k) : key(k) {}
};

///
/// Graph as vertex list
///
template<typename T, typename C>
class Graph
{
public:
	Graph()
	{
	}

	Graph(const Graph& graph)
	{
		for (auto&& gv : graph.GetVertices())
		{
			if (gv->neighbors.empty())
			{
				AddVertex(gv->key);
			}
			else
			{
				for (auto&& nb : gv->neighbors)
				{
					AddEdge(gv->key, nb.first->key, nb.second);
				}
			}
		}
	}

	Graph& operator=(const Graph& graph)
	{
		// Self-check
		if (this != &graph)
		{
			// Cleanup
			for (auto&& vx : vertices)
			{
				delete vx;
			}

			// Copying
			for (auto&& gv : graph.GetVertices())
			{
				if (gv->neighbors.empty())
				{
					AddVertex(gv->key);
				}
				else
				{
					for (auto&& nb : gv->neighbors)
					{
						AddEdge(gv->key, nb.first->key, nb.second);
					}
				}
			}
		}

		// Linking
		return *this;
	}

	~Graph()
	{
		for (auto&& vx : vertices)
		{
			delete vx;
		}
	}

	const std::vector<GraphVertex<T, C>*> GetVertices() const
	{
		return vertices;
	}

	void AddVertex(const T& key)
	{
		add(key);
	}

	void AddEdge(const T& from, const T& to, C cost = 0)
	{
		auto vi = std::find_if(vertices.begin(), vertices.end(), [&from](GraphVertex<T, C>* v) { return v->key == from; });
		auto vf = vi != vertices.cend() ? *vi : add(from);
		vi = std::find_if(vertices.begin(), vertices.end(), [&to](GraphVertex<T, C>* v) { return v->key == to; });
		auto vt = vi != vertices.cend() ? *vi : add(to);

		auto duplicate = find_if(vf->neighbors.begin(), vf->neighbors.end(),
			[&vt](std::pair<GraphVertex<T, C>*, C> nb) { return nb.first->key == vt->key; });
		if (duplicate == vf->neighbors.cend() || duplicate->second != cost)
		{
			vf->neighbors.push_back(std::make_pair(vt, cost));
		}
	}

	template<typename V>
	T* Dfs(V& visit) const
	{
		return search(true, visit);
	}

	template<typename V>
	T* Bfs(V& visit) const
	{
		return search(false, visit);
	}

private:
	std::vector<GraphVertex<T, C>*> vertices;

	GraphVertex<T, C>* add(const T& key)
	{
		auto vx = new(std::nothrow) GraphVertex<T, C>(key);
		vertices.push_back(vx);

		return vx;
	}

	/// Generalized search function for both DFS and BFS
	template<typename V>
	T* search(bool df, V& visit) const
	{
		T* result = NULL;
		std::unordered_set<char> visited;
		for (auto&& vx : vertices)
		{
			if (visited.find(vx->key) == visited.cend())
			{
				result = df ? dfs(vx, 0, visited, visit) : bfs(vx, 0, visited, visit);
				if (result != NULL)
				{
					break;
				}
			}
		}

		return result;
	}

	/// EPI 16.0.1. BFS: breadth-first search
	/// Uses queue to scan in breadth.
	template<typename V>
	T* bfs(GraphVertex<T, C>* vx, C cost, std::unordered_set<char>& visited, V& visit) const
	{
		T* result = NULL;
		std::queue<std::pair<GraphVertex<T, C>*, C>> qgv;
		qgv.push(std::make_pair(vx, cost));

		while (!qgv.empty())
		{
			auto vx = qgv.front();
			qgv.pop();

			if (visited.find(vx.first->key) == visited.cend())
			{
				auto found = visit(vx.first->key, vx.second);
				visited.insert(vx.first->key);
				if (found)
				{
					result = &(vx.first->key);
					break;
				}
				else
				{
					for (auto&& nb : vx.first->neighbors)
					{
						qgv.push(nb);
					}
				}
			}
		}

		return result;
	}

	/// EPI 16.0.2. DFS: depth-first search
	/// Uses stack to move into depth.
	template<typename V>
	T* dfs(GraphVertex<T, C>* vx, C cost, std::unordered_set<char>& visited, V& visit) const
	{
		T* result = NULL;
		std::stack<std::pair<GraphVertex<T, C>*, C>> sgv;
		sgv.push(std::make_pair(vx, cost));

		while (!sgv.empty())
		{
			auto vx = sgv.top();
			sgv.pop();

			if (visited.find(vx.first->key) == visited.end())
			{
				auto found = visit(vx.first->key, vx.second);
				visited.insert(vx.first->key);
				if (found)
				{
					result = &(vx.first->key);
					break;
				}
				else
				{
					for (auto&& nb : vx.first->neighbors)
					{
						sgv.push(nb);
					}
				}
			}
		}

		return result;
	}
};
