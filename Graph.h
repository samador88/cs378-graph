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
        typedef std::vector<vertex_descriptor>::const_iterator adjacency_iterator; 
        typedef std::set<edge_descriptor>     set_type;
        typedef set_type::iterator            siterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor v1, vertex_descriptor v2, Graph& g) {
            // create edge descriptor
            edge_descriptor x = std::make_pair(v1, v2);
            std::pair<siterator, bool> p = g._e.insert(x);

            
            bool            b  = p.second;

            if(b)
                g._g[v1].push_back(v2);
            return std::make_pair(x, b);}

        // ----------
        // add_vertex
        // ----------

        /**
         * <your documentation>
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            std::vector<vertex_descriptor> x;
            g._g.push_back(x);
            vertex_descriptor v =(g._g.size()-1);
            g._vertices_list.push_back(v);
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation>
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& g) {
            adjacency_iterator b = g._g[v].begin();
            adjacency_iterator e = g._g[v].end();
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor v1, vertex_descriptor v2, const Graph& g) {
            // <your code>
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
         * <your documentation>
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& g) {
            // <your code>
            
            edge_iterator b = g._e.begin();
            edge_iterator e = g._e.end();
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation>
         */
        friend edges_size_type num_edges (const Graph& g) {
            // <your code>
            edges_size_type s = g._e.size(); 
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph& g) {
            // <your code>
            vertices_size_type s = g._vertices_list.size(); // fix
            return s;}

        // ------
        // source
        // ------

        /**
         * <your documentation>
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
         * <your documentation>
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
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type v, const Graph& g) {
            // <your code>




            vertex_descriptor vd = g._vertices_list[v]; // fix
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& g) {
            // <your code>
            
            vertex_iterator b = g._vertices_list.begin();
            vertex_iterator e = g._vertices_list.end();
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::vector< std::vector<vertex_descriptor> > _g; 
        std::set<edge_descriptor> _e;
        std::vector<vertex_descriptor> _vertices_list;

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>


            return _g.size() >=0 && _e.size() >= 0  && _vertices_list.size() >= 0 && _g.size() == _vertices_list.size();}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () {
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
