// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision: $
// release_date  : $CGAL_Date: $
//
// file          : print_inventor.h
// chapter       : $CGAL_Chapter: Support Library ... $
// package       : $CGAL_Package: Polyhedron_IO 2.11 (04 Feb 2000) $
// source        : polyhedron_io.fw
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Lutz Kettner  <kettner@inf.ethz.ch>
//
// coordinator   : Herve Bronnimann  <Herve.Bronnimann@sophia.inria.fr>
//
// Print a Polyhedron_3 in Inventor file format (.iv)
// ============================================================================

#ifndef CGAL_IO_PRINT_INVENTOR_H
#define CGAL_IO_PRINT_INVENTOR_H 1
#ifndef CGAL_IO_POLYHEDRON_INVENTOR_OSTREAM_H
#include <CGAL/IO/Polyhedron_inventor_ostream.h>
#endif // CGAL_IO_POLYHEDRON_INVENTOR_OSTREAM_H

CGAL_BEGIN_NAMESPACE

#ifdef CGAL_USE_POLYHEDRON_DESIGN_ONE
template <class Traits, class HDS>
void
print_inventor( std::ostream& out, const Polyhedron_3<Traits,HDS>& P) {
#else // CGAL_USE_POLYHEDRON_DESIGN_ONE //
template < class Traits,
           class Items,
#ifndef CGAL_CFG_NO_TMPL_IN_TMPL_PARAM
           template < class T, class I>
#endif
           class HDS>
void
print_inventor( std::ostream& out, const Polyhedron_3<Traits,Items,HDS>& P) {
#endif // CGAL_USE_POLYHEDRON_DESIGN_ONE //
    Inventor_ostream os( out);
    os << P;
}

CGAL_END_NAMESPACE
#endif // CGAL_IO_PRINT_INVENTOR_H //
// EOF //
