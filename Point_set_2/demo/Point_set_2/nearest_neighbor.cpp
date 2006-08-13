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
#include <list>
#include <CGAL/Point_set_2.h>
#include <CGAL/IO/Window_stream.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;

typedef CGAL::Point_set_2<K>::Edge_iterator  Edge_iterator;
typedef CGAL::Point_set_2<K>::Vertex_handle  Vertex_handle;

CGAL::Point_set_2<K> PSet;

void output(CGAL::Window_stream& W, const CGAL::Point_set_2<K>& PS)
{
  W.clear();
  Edge_iterator eit = PS.finite_edges_begin();
  
  for(;eit != PS.finite_edges_end(); eit++) {
    CGAL::Segment_2<K> s= PS.segment(*eit);
    W << s;
  }
}


void redraw(CGAL::Window_stream* wptr)
{
  output(*wptr,PSet);
}

int main()
{
  CGAL::Window_stream W(600,500, "Finding nearest neighbor / k nearest neighbors");  

  W.init(-500,500,-400);
  W.set_redraw(redraw);
  W.display(100,100);
  
#if defined(CGAL_USE_CGAL_WINDOW)
  W.set_point_style(CGAL::disc_point);
#else
  W.set_point_style(leda_disc_point);
#endif  
  
  W.draw_text(-260,20, "Input some points; quit input with the right mouse button");
  
  CGAL::Point_2<K> actual;
  /*std::cout << sizeof(actual) << "\n";*/
  
  int i=0;
  
  while (W >> actual){
   PSet.insert(actual);
   output(W,PSet);
   i++;
  }  
  
  std::cout << i << " points were inserted !\n";

  // nearest neighbor ...  
  W.draw_text(-450,-350, "Input a point; we display the nearest neighbor ... ");
  
  for (i=0; i<5; i++){
    W >> actual;
    Vertex_handle v = PSet.nearest_neighbor(actual);
    
    if (v != NULL) {
    
     CGAL::Segment_2<K> my_seg(actual,v->point());
    
     W << CGAL::RED << v->point() << CGAL::BLACK;
     W << CGAL::BLUE << my_seg << CGAL::BLACK;
    }
  }
  
  // k nearest neighbors ...
  std::list<Vertex_handle> L;
  std::list<Vertex_handle>::const_iterator it;
 
  output(W,PSet);
  W.draw_text(-450,-350, "Input a point; we display the 5 nearest neighbors ... "); 
  
  for (i=0; i<5; i++){
    L.clear();
    W >> actual;
    PSet.nearest_neighbors(actual,5, std::back_inserter(L));
    std::cout << "actual point: " << actual << "\n";
    
    W.clear();
    W.draw_text(-450,-350, "Input a point; we display the 5 nearest neighbors ... "); 
    output(W,PSet);
    W << CGAL::RED << actual << CGAL::BLACK;
    
    for (it=L.begin();it != L.end(); it++){
      W << CGAL::GREEN << (*it)->point() << CGAL::BLACK;      
      std::cout << (*it)->point() << "\n";
    }
    std::cout << "\n";
  }  

  W.read_mouse();

  return 1;
}

#endif
