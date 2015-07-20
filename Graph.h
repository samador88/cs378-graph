// --------------------------
// projects/c++/graph/Graph.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;  
        typedef std::pair<vertex_descriptor, vertex_descriptor> edge_descriptor;    

        typedef std::vector<vertex_descriptor>::const_iterator vertex_iterator;    
        typedef std::set<edge_descriptor>::const_iterator edge_iterator;      
        typedef std::set<vertex_descriptor>::const_iterator adjacency_iterator; 
        typedef std::set<edge_descriptor>     set_type;
        typedef set_type::iterator            siterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * @param 2 vertex_descriptors
         * @param Graph&
         * make an edge between the two vertices given, first is source, second is target
         * @return pair with edge descriptor and bool stating whether add was successful
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor v1, vertex_descriptor v2, Graph& g) {
            edge_descriptor x = std::make_pair(v1, v2);
            std::pair<siterator, bool> p = g._e.insert(x);

            
            bool            b  = p.second;

            if(b){
                while(std::max(v1, v2) >= (int) g._g.size()){
                    add_vertex(g);
                }
                
                g._g[v1].insert(v2);
            }
                
            return std::make_pair(x, b);}

        // ----------
        // add_vertex
        // ----------

        /**
         * @param Graph&
         * add vertex to graph
         * @return vertex descriptor
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            std::set<vertex_descriptor> x;
            g._g.push_back(x);
            vertex_descriptor v =(g._g.size()-1);
            g._vertices_list.push_back(v);
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * @param vertex descriptor
         * @param const Graph&
         * @return pair of iterators to beginning and end list of adjacent vertices
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& g) {
            adjacency_iterator b = g._g[v].begin();
            adjacency_iterator e = g._g[v].end();
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * @param 2 vertex descriptors
         * @param const Graph&
         * checks  if there is an edge between the two given vertices
         * @return pair with edge descriptor and bool indicating if found
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor v1, vertex_descriptor v2, const Graph& g) {
            edge_descriptor x = std::make_pair(v1, v2);
            bool            b  = true;

            if(g._e.find(x) == g._e.end()){
                b = false;
            }
            
            return std::make_pair(x, b);}

        // -----
        // edges
        // -----

        /**
         * @param const Graph&
         * @return pair of iterators to beginning and end of set of edges
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
                      
            edge_iterator b = g._e.begin();
            edge_iterator e = g._e.end();
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * @param const Graph&
         * @return number of edges in graph
         */
        friend edges_size_type num_edges (const Graph& g) {

            edges_size_type s = g._e.size(); 
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * @param const Graph&
         * @return number of vertices in graph
         */
        friend vertices_size_type num_vertices (const Graph& g) {

            vertices_size_type s = g._vertices_list.size();
            return s;}

        // ------
        // source
        // ------

        /**
         * @param edge_descriptor
         * @param Graph&
         * @return source vertex(where the edge starts)
         */
        friend vertex_descriptor source (edge_descriptor x, const Graph& g) {
            if(g._e.find(x) != g._e.end()){
                return x.first;
            }


            
            return -1;}

        // ------
        // target
        // ------

        /**
         * @param edge_descriptor
         * @param Graph&
         * @return target vertex(where the edge ends)
         */
        friend vertex_descriptor target (edge_descriptor x, const Graph& g) {
            if(g._e.find(x) != g._e.end()){
                return x.second;
            }


            
            return -1;}

        // ------
        // vertex
        // ------

        /**
         * @param vertices_size_type
         * @param const Graph&
         * @return given value as vertex descriptor
         */
        friend vertex_descriptor vertex (vertices_size_type v, const Graph& g) {

            vertex_descriptor vd = v;
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * @param const Graph&
         * @return iterators to beginning and end of list of vertices
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            
            vertex_iterator b = g._vertices_list.begin();
            vertex_iterator e = g._vertices_list.end();
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::vector< std::set<vertex_descriptor> > _g; 
        std::set<edge_descriptor> _e;
        std::vector<vertex_descriptor> _vertices_list;

        // -----
        // valid
        // -----

        /**
         * @return true if a valid graph
         */
        bool valid () const {


            return _g.size() >=0 && _e.size() >= 0  && _vertices_list.size() >= 0 && _g.size() == _vertices_list.size();}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * default constructor
         * creates empty graph
         */
        Graph () {
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
