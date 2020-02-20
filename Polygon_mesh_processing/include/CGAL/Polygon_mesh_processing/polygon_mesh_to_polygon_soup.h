// Copyright (c) 2020 GeometryFactory (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
//
// $URL$
// $Id$
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Mael Rouxel-Labbé

#ifndef CGAL_POLYGON_MESH_PROCESSING_POLYGON_MESH_TO_POLYGON_SOUP_H
#define CGAL_POLYGON_MESH_PROCESSING_POLYGON_MESH_TO_POLYGON_SOUP_H

#include <CGAL/license/Polygon_mesh_processing/repair.h>

#include <CGAL/algorithm.h>
#include <CGAL/boost/graph/iterator.h>
#include <CGAL/boost/graph/named_params_helper.h>
#include <CGAL/Dynamic_property_map.h>
#include <CGAL/property_map.h>
#include <CGAL/Container_helper.h>

#include <boost/range/value_type.hpp>
#include <boost/range/reference.hpp>

namespace CGAL {
namespace Polygon_mesh_processing {

/// \ingroup PMP_repairing_grp
///
/// Adds the vertices and faces of a mesh into a (possibly non-empty) polygon soup.
///
/// \tparam PolygonMesh a model of `FaceListGraph`
/// \tparam PointRange a model of the concepts `RandomAccessContainer` and
///                    `BackInsertionSequence` whose value type can be constructed from
///                    the point type of the polygon mesh
/// \tparam PolygonRange a model of the concepts `RandomAccessContainer` and `BackInsertionSequence` whose
///                      `value_type` is itself a model of the concepts `RandomAccessContainer` and
///                      `BackInsertionSequence` whose `value_type` is `std::size_t`
/// \tparam NamedParameters a sequence of \ref pmp_namedparameters
///
/// \param mesh the mesh whose faces are being put in the polygon soup
/// \param points points making the polygons of the soup
/// \param polygons each element in the vector describes a polygon using the index of the points in `points`
/// \param np optional sequence of \ref pmp_namedparameters among the ones listed below
///
/// \cgalNamedParamsBegin
///   \cgalParamBegin{vertex_point_map}
///     a model of `WritablePropertyMap`, the property map with the points associated to the vertices of `out`.
///     If this parameter is omitted, an internal property map for
///     `CGAL::vertex_point_t` must be available in `TriangleMesh`
///   \cgalParamEnd
/// \cgalNamedParamsEnd
///
/// \sa `CGAL::Polygon_mesh_processing::orient_polygon_soup()`
/// \sa `CGAL::Polygon_mesh_processing::is_polygon_soup_a_polygon_mesh()`
/// \sa `CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh()`
///
template<typename PolygonMesh,
         typename PointRange, typename PolygonRange,
         typename NamedParameters>
void polygon_mesh_to_polygon_soup(const PolygonMesh& mesh,
                                  PointRange& points,
                                  PolygonRange& polygons,
                                  const NamedParameters& np)
{
  typedef typename boost::graph_traits<PolygonMesh>::vertex_descriptor              vertex_descriptor;
  typedef typename boost::graph_traits<PolygonMesh>::halfedge_descriptor            halfedge_descriptor;
  typedef typename boost::graph_traits<PolygonMesh>::face_descriptor                face_descriptor;

  using parameters::choose_parameter;
  using parameters::get_parameter;

  typedef typename GetVertexPointMap<PolygonMesh, NamedParameters>::const_type      VPM;
  VPM vpm = choose_parameter(get_parameter(np, internal_np::vertex_point),
                             get_const_property_map(vertex_point, mesh));

  typedef CGAL::dynamic_vertex_property_t<std::size_t>                              Vertex_index;
  typedef typename boost::property_map<PolygonMesh, Vertex_index>::const_type       VIM;
  VIM vim = get(Vertex_index(), mesh);

  typedef typename boost::range_value<PolygonRange>::type                           Polygon;

  std::size_t index = points.size(); // so that multiple meshes can be put into the same soup
  CGAL::internal::reserve(points, points.size() + vertices(mesh).size());
  CGAL::internal::reserve(polygons, polygons.size() + faces(mesh).size());

  for(const vertex_descriptor v : vertices(mesh))
  {
    points.emplace_back(get(vpm, v));
    put(vim, v, index++);
  }

  for(const face_descriptor f : faces(mesh))
  {
    Polygon polygon;
    for(halfedge_descriptor h : CGAL::halfedges_around_face(halfedge(f, mesh), mesh))
      polygon.push_back(get(vim, target(h, mesh)));

    polygons.push_back(polygon);
  }
}

template<typename PolygonMesh, typename PointRange, typename PolygonRange>
void polygon_mesh_to_polygon_soup(const PolygonMesh& mesh,
                                  PointRange& points,
                                  PolygonRange& polygons)
{
  return polygon_mesh_to_polygon_soup(mesh, points, polygons, CGAL::parameters::all_default());
}

} // namespace Polygon_mesh_processing
} // namespace CGAL

#endif // CGAL_POLYGON_MESH_PROCESSING_POLYGON_MESH_TO_POLYGON_SOUP_H
