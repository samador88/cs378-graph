// --------------------------------
// projects/g++/graph/TestGraph.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <iterator> // ostream_iterator
#include <sstream>  // ostringstream
#include <utility>  // pair

#include "boost/graph/adjacency_list.hpp"  // adjacency_list
#include "boost/graph/topological_sort.hpp"// topological_sort

#include "gtest/gtest.h"

#include "Graph.h"

using namespace std;

using testing::Test;
using testing::Types;

// ---------
// TestGraph
// ---------

template <typename G>
struct TestGraph : Test {
    // --------
    // typedefs
    // --------

    typedef          G                     graph_type;
    typedef typename G::vertex_descriptor  vertex_descriptor;
    typedef typename G::edge_descriptor    edge_descriptor;
    typedef typename G::vertex_iterator    vertex_iterator;
    typedef typename G::edge_iterator      edge_iterator;
    typedef typename G::adjacency_iterator adjacency_iterator;
    typedef typename G::vertices_size_type vertices_size_type;
    typedef typename G::edges_size_type    edges_size_type;};

// directed, sparse, unweighted
// possibly connected
// possibly cyclic
typedef Types<
            boost::adjacency_list<boost::setS, boost::vecS, boost::directedS>,
            Graph>
        graph_types;

TYPED_TEST_CASE(TestGraph, graph_types);

TYPED_TEST(TestGraph, test_vertex) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertices_size_type vertices_size_type;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);

    vertex_descriptor vd = vertex(0, g);
    ASSERT_EQ(vdA, vd);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(1, vs);}

TYPED_TEST(TestGraph, test_edge) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    typedef typename TestFixture::edges_size_type    edges_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    edges_size_type es = num_edges(g);
    ASSERT_EQ(1, es);

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = target(edAB, g);
    ASSERT_EQ(vdB, vd2);}

TYPED_TEST(TestGraph, test_vertices) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertex_iterator    vertex_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                        b = p.first;
    vertex_iterator                        e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, test_edges) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    typedef typename TestFixture::edge_iterator      edge_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edAC = add_edge(vdA, vdC, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                      b = p.first;
    edge_iterator                      e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(edAC, ed);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, test_adjacent_vertices) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::adjacency_iterator adjacency_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, add_edge1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(true, p1.second);


    pair<edge_descriptor, bool> p2 = add_edge(vdA, vdB, g);
    ASSERT_EQ(p2.first,  p1.first);
    ASSERT_EQ(false, p2.second);}

TYPED_TEST(TestGraph, add_edge2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdC, g);
    ASSERT_EQ(true, p1.second);


    pair<edge_descriptor, bool> p2 = add_edge(vdA, vdB, g);
    ASSERT_TRUE(p2.first != p1.first);
    ASSERT_EQ(true, p2.second);}

TYPED_TEST(TestGraph, add_edge3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdC, g);
    ASSERT_EQ(true, p1.second);


    pair<edge_descriptor, bool> p2 = add_edge(vdA, vdB, g);
    pair<edge_descriptor, bool> p3 = add_edge(vdB, vdA, g);
    ASSERT_EQ(true, p3.second);
    ASSERT_TRUE(p2.first != p3.first);

    ASSERT_EQ(true, p2.second);
    pair<edge_descriptor, bool> p4 = add_edge(vdE, vdE, g);
    ASSERT_EQ(true, p4.second);

    }

TYPED_TEST(TestGraph, add_edge4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;  

    pair<edge_descriptor, bool> p1 = add_edge(3, 6, g);
    ASSERT_EQ(true, p1.second);


    pair<edge_descriptor, bool> p2 = add_edge(3, 8, g);
    pair<edge_descriptor, bool> p3 = add_edge(3, 4, g);
    ASSERT_EQ(true, p3.second);
    ASSERT_TRUE(p2.first != p3.first);

    ASSERT_EQ(true, p2.second);

    }

TYPED_TEST(TestGraph, add_edge5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;  

    pair<edge_descriptor, bool> p1 = add_edge(3, 3, g);
    ASSERT_EQ(true, p1.second);

    }

    TYPED_TEST(TestGraph, add_vertex1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertices_size_type vertices_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    ASSERT_TRUE(vdA != vdB);

    ASSERT_EQ(vdB , 1);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(2, vs);}

    TYPED_TEST(TestGraph, add_vertex2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertices_size_type vertices_size_type;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    ASSERT_TRUE(vdA != vdF);

    ASSERT_EQ(vdF , 5);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(6, vs);}

    TYPED_TEST(TestGraph, add_vertex3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
   
    typedef typename TestFixture::vertices_size_type vertices_size_type;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    ASSERT_TRUE(vdA != vdC);

    ASSERT_EQ(vdC , 2);

    vertices_size_type vs = num_vertices(g);
    ASSERT_EQ(6, vs);}

TYPED_TEST(TestGraph, adjacent_vertices1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::adjacency_iterator adjacency_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdC, vdA, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;

    pair<adjacency_iterator, adjacency_iterator> p2 = adjacent_vertices(vdC, g);
    adjacency_iterator                           b2 = p2.first;
    adjacency_iterator                           e2 = p2.second;
    if (b2 != e2) {
        vertex_descriptor vd = *b2;
        ASSERT_EQ(vdA, vd);}
    ++b2;

    ASSERT_EQ(e, b);
    ASSERT_EQ(e2, b2);}

TYPED_TEST(TestGraph, adjacent_vertices2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::adjacency_iterator adjacency_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);
    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdC, vdA, g);
    add_edge(vdA, vdD, g);
    add_edge(vdA, vdE, g);
    add_edge(vdA, vdF, g);


    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdD, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdE, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdF, vd);}
    ++b;

    ASSERT_EQ(e, b);}


TYPED_TEST(TestGraph, adjacent_vertices3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::adjacency_iterator adjacency_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);
    add_edge(vdA, vdB, g);
    add_edge(vdA, vdC, g);
    add_edge(vdC, vdA, g);
    add_edge(vdC, vdB, g);
    add_edge(vdA, vdE, g);
    add_edge(vdA, vdF, g);


    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdE, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdF, vd);}
    ++b;

    pair<adjacency_iterator, adjacency_iterator> p2 = adjacent_vertices(vdC, g);
    adjacency_iterator                           b2 = p2.first;
    adjacency_iterator                           e2 = p2.second;
    if (b2 != e2) {
        vertex_descriptor vd = *b2;
        ASSERT_EQ(vdA, vd);}
    ++b2;
    if (b2 != e2) {
        vertex_descriptor vd = *b2;
        ASSERT_EQ(vdB, vd);}
    ++b2;

    pair<adjacency_iterator, adjacency_iterator> p3 = adjacent_vertices(vdB, g);
    adjacency_iterator                           b3 = p3.first;
    adjacency_iterator                           e3 = p3.second;

    ASSERT_EQ(e2, b2);
    ASSERT_EQ(e3, b3);
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, adjacent_vertices4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::adjacency_iterator adjacency_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    add_edge(vdA, vdC, g);
    add_edge(vdA, vdB, g);
    add_edge(vdC, vdA, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;

    pair<adjacency_iterator, adjacency_iterator> p2 = adjacent_vertices(vdC, g);
    adjacency_iterator                           b2 = p2.first;
    adjacency_iterator                           e2 = p2.second;
    if (b2 != e2) {
        vertex_descriptor vd = *b2;
        ASSERT_EQ(vdA, vd);}
    ++b2;

    ASSERT_EQ(e, b);
    ASSERT_EQ(e2, b2);}

TYPED_TEST(TestGraph, adjacent_vertices5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::adjacency_iterator adjacency_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    add_edge(vdA, vdC, g);
    add_edge(vdA, vdB, g);
    add_edge(vdC, vdB, g);
    add_edge(vdC, vdD, g);
    add_edge(vdC, vdA, g);

    pair<adjacency_iterator, adjacency_iterator> p = adjacent_vertices(vdA, g);
    adjacency_iterator                           b = p.first;
    adjacency_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;

    pair<adjacency_iterator, adjacency_iterator> p2 = adjacent_vertices(vdC, g);
    adjacency_iterator                           b2 = p2.first;
    adjacency_iterator                           e2 = p2.second;
    if (b2 != e2) {
        vertex_descriptor vd = *b2;
        ASSERT_EQ(vdA, vd);}
    ++b2;
    if (b2 != e2) {
        vertex_descriptor vd = *b2;
        ASSERT_EQ(vdB, vd);}
    ++b2;
    if (b2 != e2) {
        vertex_descriptor vd = *b2;
        ASSERT_EQ(vdD, vd);}
    ++b2;

    ASSERT_EQ(e, b);
    ASSERT_EQ(e2, b2);}

TYPED_TEST(TestGraph, source1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBA = add_edge(vdB, vdA, g).first;

    vertex_descriptor vd1 = source(edAB, g);
    ASSERT_EQ(vdA, vd1);

    vertex_descriptor vd2 = source(edBA, g);
    ASSERT_EQ(vdB, vd2);
    ASSERT_FALSE(vd2 == vdC);}


TYPED_TEST(TestGraph, source2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);
    
    edge_descriptor edFD = add_edge(vdF, vdD, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edFF = add_edge(vdF, vdF, g).first;

    vertex_descriptor vd1 = source(edFD, g);
    ASSERT_EQ(vdF, vd1);

    vertex_descriptor vd2 = source(edBC, g);
    ASSERT_EQ(vdB, vd2);
    ASSERT_FALSE(vd2 == vdC);

    vertex_descriptor vd3 = source(edAB, g);
    ASSERT_EQ(vd3, vdA);
    vertex_descriptor vd4 = source(edFF, g);
    ASSERT_EQ(vd4, vdF);}


TYPED_TEST(TestGraph, source3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);
    
    edge_descriptor edFD = add_edge(vdF, vdD, g).first;
    edge_descriptor edDF = add_edge(vdD, vdF, g).first;
    edge_descriptor edAB = add_edge(vdF, vdD, g).first;
    edge_descriptor edFF = add_edge(vdF, vdF, g).first;

    vertex_descriptor vd1 = source(edFD, g);
    ASSERT_EQ(vdF, vd1);

    vertex_descriptor vd2 = source(edDF, g);
    ASSERT_EQ(vdD, vd2);
    ASSERT_FALSE(vd2 == vdF);
    vertex_descriptor vd3 = source(edAB, g);
    ASSERT_EQ(vdF, vd3);}

TYPED_TEST(TestGraph, target1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edBA = add_edge(vdB, vdA, g).first;

    vertex_descriptor vd1 = target(edAB, g);
    ASSERT_EQ(vdB, vd1);

    vertex_descriptor vd2 = target(edBA, g);
    ASSERT_EQ(vdA, vd2);
    ASSERT_FALSE(vd2 == vdC);}


TYPED_TEST(TestGraph, target2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    edge_descriptor edFD = add_edge(vdF, vdD, g).first;
    edge_descriptor edBC = add_edge(vdB, vdC, g).first;
    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edFF = add_edge(vdF, vdF, g).first;

    vertex_descriptor vd1 = target(edFD, g);
    ASSERT_EQ(vdD, vd1);

    vertex_descriptor vd2 = target(edBC, g);
    ASSERT_EQ(vdC, vd2);
    ASSERT_FALSE(vd2 == vdB);

    vertex_descriptor vd3 = target(edAB, g);
    ASSERT_EQ(vd3, vdB);
    vertex_descriptor vd4 = target(edFF, g);
    ASSERT_EQ(vd4, vdF);}


TYPED_TEST(TestGraph, target3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    edge_descriptor edFD = add_edge(vdF, vdD, g).first;
    edge_descriptor edDF = add_edge(vdD, vdF, g).first;
    edge_descriptor edAB = add_edge(vdF, vdD, g).first;
    edge_descriptor edFF = add_edge(vdF, vdF, g).first;

    vertex_descriptor vd1 = target(edFD, g);
    ASSERT_EQ(vdD, vd1);

    vertex_descriptor vd2 = target(edDF, g);
    ASSERT_EQ(vdF, vd2);
    ASSERT_FALSE(vd2 == vdD);
    vertex_descriptor vd3 = target(edAB, g);
    ASSERT_EQ(vdD, vd3);}

TYPED_TEST(TestGraph, vertex1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    vertex_descriptor vd1 = vertex(5, g);
    ASSERT_EQ(vdF, vd1);
    vertex_descriptor vd2 = vertex(4, g);
    ASSERT_EQ(vdE, vd2);
    vertex_descriptor vd3 = vertex(3, g);
    ASSERT_EQ(vdD, vd3);
    vertex_descriptor vd4 = vertex(2, g);
    ASSERT_EQ(vdC, vd4);
    vertex_descriptor vd5 = vertex(1, g);
    ASSERT_EQ(vdB, vd5);
    vertex_descriptor vd6 = vertex(0, g);
    ASSERT_EQ(vdA, vd6);}

TYPED_TEST(TestGraph, vertex2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);

    vertex_descriptor vd1 = vertex(5, g);
    ASSERT_FALSE(vdE == vd1);
    vertex_descriptor vd2 = vertex(4, g);
    ASSERT_FALSE(vdD == vd2);
    vertex_descriptor vd3 = vertex(3, g);
    ASSERT_FALSE(vdC == vd3);
    vertex_descriptor vd4 = vertex(2, g);
    ASSERT_FALSE(vdB == vd4);
    vertex_descriptor vd5 = vertex(1, g);
    ASSERT_FALSE(vdA == vd5);
    vertex_descriptor vd6 = vertex(0, g);
    ASSERT_FALSE(vdF == vd6);}

TYPED_TEST(TestGraph, vertex3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);


    vertex_descriptor vd1 = vertex(2, g);
    ASSERT_FALSE(vdA == vd1);
    vertex_descriptor vd2 = vertex(1, g);
    ASSERT_FALSE(vdC == vd2);
    vertex_descriptor vd3 = vertex(0, g);
    ASSERT_FALSE(vdB == vd3);
    vertex_descriptor vd4 = vertex(2, g);
    ASSERT_EQ(vdC, vd4);
    vertex_descriptor vd5 = vertex(1, g);
    ASSERT_EQ(vdB, vd5);
    vertex_descriptor vd6 = vertex(0, g);
    ASSERT_EQ(vdA, vd6);}

TYPED_TEST(TestGraph, vertex4) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));

    vertex_descriptor v = vertex(0, g);

    ASSERT_EQ(0, v);
    ASSERT_EQ(0, num_vertices(g));

    v = vertex(4, g);

    ASSERT_EQ(4, v);
    add_vertex(g);
    ASSERT_EQ(1, num_vertices(g));}

TYPED_TEST(TestGraph, vertex5) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    ASSERT_EQ(0, num_vertices(g));

    vertex_descriptor v = vertex(0, g);

    ASSERT_EQ(0, v);
    ASSERT_EQ(0, num_vertices(g));

    v = vertex(17, g);

    ASSERT_EQ(17, v);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    ASSERT_EQ(4, num_vertices(g));}

TYPED_TEST(TestGraph, vertices1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertex_iterator    vertex_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                           b = p.first;
    vertex_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;

    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;

    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdD, vd);}
    ++b;
    ASSERT_EQ(e, b);}

TYPED_TEST(TestGraph, vertices2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertex_iterator    vertex_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);


    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                           b = p.first;
    vertex_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdC, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdD, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdE, vd);}
    ++b;
     if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdF, vd);}
    ++b;

    ASSERT_EQ(e, b);}


TYPED_TEST(TestGraph, vertices3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    typedef typename TestFixture::vertex_iterator    vertex_iterator;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);


    pair<vertex_iterator, vertex_iterator> p = vertices(g);
    vertex_iterator                           b = p.first;
    vertex_iterator                           e = p.second;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdA, vd);}
    ++b;
    if (b != e) {
        vertex_descriptor vd = *b;
        ASSERT_EQ(vdB, vd);}
    ++b;
    ASSERT_FALSE(b == e);
    ASSERT_EQ(*b, vdC);}

TYPED_TEST(TestGraph, edge1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    pair<edge_descriptor, bool> p3 = edge(vdB, vdA, g);
    ASSERT_TRUE(edAB != p3.first);
    ASSERT_EQ(false, p3.second);
}

TYPED_TEST(TestGraph, edge2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edCA = add_edge(vdC, vdA, g).first;

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    pair<edge_descriptor, bool> p3 = edge(vdC, vdA, g);
    ASSERT_EQ(edCA, p3.first);
    ASSERT_EQ(true, p3.second);
}

TYPED_TEST(TestGraph, edge3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD= add_vertex(g);

    edge_descriptor edAB = add_edge(vdA, vdB, g).first;
    edge_descriptor edCA = add_edge(vdC, vdA, g).first;

    pair<edge_descriptor, bool> p1 = add_edge(vdA, vdB, g);
    ASSERT_EQ(edAB,  p1.first);
    ASSERT_EQ(false, p1.second);

    pair<edge_descriptor, bool> p2 = edge(vdA, vdB, g);
    ASSERT_EQ(edAB, p2.first);
    ASSERT_EQ(true, p2.second);

    pair<edge_descriptor, bool> p3 = edge(vdC, vdD, g);
    ASSERT_TRUE(edCA != p3.first);
    ASSERT_EQ(false, p3.second);
}

TYPED_TEST(TestGraph, edges1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    typedef typename TestFixture::edge_iterator      edge_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    edge_descriptor eAB = add_edge(vdA, vdB, g).first;
    edge_descriptor eAC = add_edge(vdA, vdC, g).first;
    edge_descriptor eCA = add_edge(vdC, vdA, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eAC, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eCA, ed);}
    ++b;

    ASSERT_EQ(e, b);}

    TYPED_TEST(TestGraph, edges2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    typedef typename TestFixture::edge_iterator      edge_iterator;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);

    edge_descriptor eAB = add_edge(vdA, vdB, g).first;
    edge_descriptor eAC = add_edge(vdA, vdC, g).first;
    edge_descriptor eCA = add_edge(vdC, vdA, g).first;
    edge_descriptor eBD = add_edge(vdB, vdD, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eAC, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eBD, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eCA, ed);}
    ++b;

    ASSERT_EQ(e, b);}

    TYPED_TEST(TestGraph, edges3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    typedef typename TestFixture::edge_iterator      edge_iterator;
  

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);

    edge_descriptor eAB = add_edge(vdA, vdB, g).first;
    edge_descriptor eAC = add_edge(vdA, vdC, g).first;
    edge_descriptor eCA = add_edge(vdC, vdA, g).first;
    edge_descriptor eBD = add_edge(vdB, vdD, g).first;
    edge_descriptor eEA = add_edge(vdE, vdA, g).first;
    edge_descriptor eBA = add_edge(vdB, vdA, g).first;

    pair<edge_iterator, edge_iterator> p = edges(g);
    edge_iterator                           b = p.first;
    edge_iterator                           e = p.second;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eAB, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eAC, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eBA, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eBD, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eCA, ed);}
    ++b;
    if (b != e) {
        edge_descriptor ed = *b;
        ASSERT_EQ(eEA, ed);}
    ++b;

    ASSERT_EQ(e, b);}

    TYPED_TEST(TestGraph, num_edges1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);

    edge_descriptor eAB = add_edge(vdA, vdB, g).first;
    edge_descriptor eAC = add_edge(vdA, vdC, g).first;


    ASSERT_EQ(2, num_edges(g));}

    TYPED_TEST(TestGraph, num_edges2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;


    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);

    edge_descriptor eAB = add_edge(vdA, vdB, g).first;
    edge_descriptor eAC = add_edge(vdA, vdC, g).first;
    edge_descriptor eDB = add_edge(vdD, vdB, g).first;
    edge_descriptor eED = add_edge(vdE, vdD, g).first;


    ASSERT_EQ(4, num_edges(g));}

    TYPED_TEST(TestGraph, num_edges3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    typedef typename TestFixture::edge_descriptor    edge_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);

    edge_descriptor eAB = add_edge(vdA, vdB, g).first;
    edge_descriptor eAC = add_edge(vdA, vdC, g).first;
    edge_descriptor eDB = add_edge(vdD, vdB, g).first;
    edge_descriptor eED = add_edge(vdE, vdD, g).first;
    edge_descriptor eEE = add_edge(vdE, vdE, g).first;


    ASSERT_EQ(5, num_edges(g));}

    TYPED_TEST(TestGraph, num_vertices1) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    
    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);


    ASSERT_EQ(2, num_vertices(g));}

    TYPED_TEST(TestGraph, num_vertices2) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;
    

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);


    ASSERT_EQ(4, num_vertices(g));}

    TYPED_TEST(TestGraph, num_vertices3) {
    typedef typename TestFixture::graph_type         graph_type;
    typedef typename TestFixture::vertex_descriptor  vertex_descriptor;

    graph_type g;

    vertex_descriptor vdA = add_vertex(g);
    vertex_descriptor vdB = add_vertex(g);
    vertex_descriptor vdC = add_vertex(g);
    vertex_descriptor vdD = add_vertex(g);
    vertex_descriptor vdE = add_vertex(g);
    vertex_descriptor vdF = add_vertex(g);
    vertex_descriptor vdG = add_vertex(g);
    vertex_descriptor vdH = add_vertex(g);
    vertex_descriptor vdI = add_vertex(g);


    ASSERT_EQ(9, num_vertices(g));}