// Copyright (c) 2001, 2003  Martin-Luther-University Halle-Wittenberg (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Matthias Baesken

#include <CGAL/basic.h>

#ifndef CGAL_USE_LEDA
int main(){
  return 0;
}
#else

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/Window_stream.h>
#include <CGAL/range_search_delaunay_2.h>
#include <list>

typedef CGAL::Exact_predicates_inexact_constructions_kernel  Gt;
typedef Gt::FT                                             coord_type;
typedef CGAL::Delaunay_triangulation_2<Gt>                 Delaunay;
typedef CGAL::Delaunay_triangulation_2<Gt>::Edge_iterator  Edge_iterator;
typedef CGAL::Delaunay_triangulation_2<Gt>::Vertex_handle  Vertex_handle;

typedef Gt::Point_2     Point;
typedef Gt::Circle_2    Circle;
typedef Gt::Iso_rectangle_2  Rectangle;

Delaunay PS;

void output(CGAL::Window_stream& W, const Delaunay& PSet)
{
  W.clear();
  Edge_iterator eit = PSet.finite_edges_begin();
  
  for(;eit != PSet.finite_edges_end(); eit++) {
    CGAL::Segment_2<Gt> s= PSet.segment(*eit);
    W << s;
  }
}

void redraw(CGAL::Window_stream* wptr)
{ output(*wptr,PS); }


class check_empty_rectangle {
public:
  bool    result;
  Rectangle r;
  
  check_empty_rectangle(Rectangle ract) : result(false), r(ract) { }
  
  bool get_result() const  { return result; }
  void set_result(bool nr) { result=nr; }
  
  bool operator()(const Point& p)
  {
    return ! r.has_on_unbounded_side(p); 
  }
};

int main()
{
  CGAL::Window_stream W(600,500,"Range search operations on a point set checking emptiness of triangles");  

  W.init(-500,500,-400);
  W.set_redraw(redraw);
  W.display(100,100);
  
#if defined(CGAL_USE_CGAL_WINDOW)
  W.set_point_style(CGAL::disc_point);
#else
  W.set_point_style(leda_disc_point);
#endif   
  
  W.draw_text(-260,20, "Input some points; quit input with the right mouse button");

  CGAL::Point_2<Gt> pnew;

  while (W >> pnew) {
    PS.insert(pnew);
    output(W,PS);    
  }
  
  std::list<Vertex_handle> LV;  
  
  std::cout << "rectangular range search !\n";
  W << CGAL::BLACK;
  output(W,PS);
  W.draw_text(-450,-350, "Input a rectangle; we perform a range search (quit: right mouse button) ... ");
  
  CGAL::Iso_rectangle_2<Gt> rc;
   
  while (W >> rc) {
   W << CGAL::BLACK;
   output(W,PS);
   W.draw_text(-450,-350, "Input a rectangle; we perform an empty rectangle check (quit: right mouse button) ... ");
   W << CGAL::RED; W << rc; W << CGAL::BLACK;

   check_empty_rectangle checker(rc);

   CGAL::range_search(PS,rc.vertex(0),rc.vertex(1),rc.vertex(2),rc.vertex(3),std::back_inserter(LV),checker,true);
   
   if (checker.get_result()) std::cout << "rectangle not empty !\n";
   else std::cout << "rectangle was empty !\n";
   
   /*  
   W << CGAL::RED;
  
   for(vit=LV.begin(); vit!=LV.end(); vit++){
     W << (*vit)->point();
   }
   */
   
   LV.clear();
  }
 
  return 0;
}

#endif
