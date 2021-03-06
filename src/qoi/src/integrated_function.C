//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// GRINS - General Reacting Incompressible Navier-Stokes
//
// Copyright (C) 2014-2016 Paul T. Bauman, Roy H. Stogner
// Copyright (C) 2010-2013 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-


// This class
#include "grins/integrated_function.h"

// GRINS
#include "grins/multiphysics_sys.h"
#include "grins/assembly_context.h"
#include "grins/materials_parsing.h"
#include "grins/rayfire_mesh.h"

// libMesh
#include "libmesh/getpot.h"
#include "libmesh/fem_system.h"
#include "libmesh/quadrature_gauss.h"
#include "libmesh/elem.h"
#include "libmesh/fe.h"
#include "libmesh/fe_type.h"
#include "libmesh/function_base.h"
#include "libmesh/fem_function_base.h"

namespace GRINS
{
  template<typename Function>
  IntegratedFunction<Function>::IntegratedFunction(unsigned int p_level, SharedPtr<Function> f, SharedPtr<RayfireMesh> rayfire, const std::string& qoi_name) :
    QoIBase(qoi_name),
    _p_level(p_level),
    _f(f),
    _rayfire(rayfire)
  {
    // use Gauss Quadrature
    _qbase.reset(new libMesh::QGauss(1,libMesh::Order(_p_level)));
  }

  template<typename Function>
  QoIBase* IntegratedFunction<Function>::clone() const
  {
    return new IntegratedFunction<Function>( *this );
  }

  template<typename Function>
  void IntegratedFunction<Function>::init
    (const GetPot& /*input*/,
     const MultiphysicsSystem& system,
     unsigned int /*qoi_num*/ )
  {
    _rayfire->init(system.get_mesh());
  }

  template<typename Function>
  void IntegratedFunction<Function>::element_qoi( AssemblyContext& context,
                                       const unsigned int qoi_index )
  {
    const libMesh::Elem& original_elem = context.get_elem();
    const libMesh::Elem* rayfire_elem = _rayfire->map_to_rayfire_elem(original_elem.id());

    // rayfire_elem will be NULL if the main_elem
    // is not in the rayfire
    if (rayfire_elem)
      {
        // init the quadrature base on the rayfire elem
        _qbase->init(rayfire_elem->type(),_p_level);

        // need the QP coordinates and JxW
        libMesh::UniquePtr< libMesh::FEBase > fe = libMesh::FEBase::build(rayfire_elem->dim(), libMesh::FEType(libMesh::FIRST, libMesh::LAGRANGE) );

        fe->attach_quadrature_rule( _qbase.get() );
        fe->get_xyz();
        fe->get_JxW();

        fe->reinit(rayfire_elem);

        const std::vector<libMesh::Real>& JxW = fe->get_JxW();
        const std::vector<libMesh::Point>& xyz = fe->get_xyz();

        const unsigned int n_qpoints = fe->n_quadrature_points();

        libMesh::Number& qoi = context.get_qois()[qoi_index];

        for (unsigned int qp = 0; qp != n_qpoints; ++qp)
            qoi += this->qoi_value((*_f),context,xyz[qp])*JxW[qp];

      }
  }

  template<typename Function>
  void IntegratedFunction<Function>::element_qoi_derivative( AssemblyContext& /*context*/,
                                       const unsigned int /*qoi_index*/ )
  {
    //TODO
    libmesh_not_implemented();
  }

  // speciaizations of the qoi_value() function
  template<>
  libMesh::Real IntegratedFunction<libMesh::FEMFunctionBase<libMesh::Real> >::qoi_value(libMesh::FEMFunctionBase<libMesh::Real>& f,AssemblyContext& context,const libMesh::Point& xyz)
  {
    return f(context,xyz);
  }

  template<>
  libMesh::Real IntegratedFunction<libMesh::FunctionBase<libMesh::Real> >::qoi_value(libMesh::FunctionBase<libMesh::Real>& f,AssemblyContext& /*context*/,const libMesh::Point& xyz)
  {
    return f(xyz);
  }

template class IntegratedFunction<libMesh::FunctionBase<libMesh::Real> >;
template class IntegratedFunction<libMesh::FEMFunctionBase<libMesh::Real> >;

} //namespace GRINS
