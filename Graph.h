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

        typedef int vertex_descriptor;  // fix!
        typedef std::pair<vertex_descriptor, vertex_descriptor> edge_descriptor;    // fix!

        typedef std::vector<vertex_descriptor>::iterator vertex_iterator;    // fix!
        typedef std::set<edge_descriptor>::iterator edge_iterator;      // fix!
        typedef std::vector<vertex_descriptor>::iterator adjacency_iterator; // fix!
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
            pair<siterator, bool> p = e.insert(x);

            
            bool            b  = p.second;

            if(b)
                g[v1].push_back(v2);
            return std::make_pair(x, b);}

        // ----------
        // add_vertex
        // ----------

        /**
         * <your documentation>
         */
        friend vertex_descriptor add_vertex (Graph& g) {
            std::vector<vertex_descriptor> x;
            g.push_back(x);
            vertex_descriptor v =(g.size()-1);
            vertices_list.push_back(v);
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * <your documentation>
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v, const Graph& g) {
            adjacency_iterator b = g[v].begin();
            adjacency_iterator e = g[v].end();
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor, vertex_descriptor, const Graph&) {
            // <your code>
            edge_descriptor ed = 0;
            bool            b  = true;
            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         * <your documentation>
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph&) {
            // <your code>
            static int a [] = {0, 0};     // dummy data
            edge_iterator b = a;
            edge_iterator e = a + 2;
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * <your documentation>
         */
        friend edges_size_type num_edges (const Graph&) {
            // <your code>
            edges_size_type s = 1; // fix
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         * <your documentation>
         */
        friend vertices_size_type num_vertices (const Graph&) {
            // <your code>
            vertices_size_type s = 1; // fix
            return s;}

        // ------
        // source
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor source (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor target (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v = 0; // fix
            return v;}

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type, const Graph&) {
            // <your code>
            vertex_descriptor vd = 0; // fix
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph&) {
            // <your code>
            static int a [] = {0, 0};     // dummy data
            vertex_iterator b = a;
            vertex_iterator e = a + 2;
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::vector< std::vector<vertex_descriptor> > g; // something like this
        set<edge_descriptor> e;
        vector<vertex_descriptor> vertcies_list;

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () {
            // <your code>
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

#endif // Graph_h
