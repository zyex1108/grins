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


#include "grins_config.h"

#ifdef GRINS_HAVE_ANTIOCH

// This class
#include "grins/antioch_mixture_averaged_transport_evaluator.h"

// GRINS
#include "grins/cached_values.h"

namespace GRINS
{
  template<typename Thermo, typename Viscosity, typename Conductivity, typename Diffusivity>
  AntiochMixtureAveragedTransportEvaluator<Thermo,Viscosity,Conductivity,Diffusivity>::AntiochMixtureAveragedTransportEvaluator( const AntiochMixtureAveragedTransportMixture<Thermo,Viscosity,Conductivity,Diffusivity>& mixture )
    : AntiochEvaluator<Thermo>( mixture ),
    _wilke_evaluator( new Antioch::MixtureAveragedTransportEvaluator<Diffusivity,Viscosity,Conductivity,libMesh::Real>( mixture.wilke_mixture(), mixture.diffusivity(), mixture.viscosity(), mixture.conductivity() ) ),
    _diffusivity( mixture.diffusivity() )
  {}

  template<typename Th, typename V, typename C, typename D>
  libMesh::Real AntiochMixtureAveragedTransportEvaluator<Th,V,C,D>::mu( const libMesh::Real T,
                                                                        const libMesh::Real /*P*/,
                                                                        const std::vector<libMesh::Real>& Y )
  {
    return _wilke_evaluator->mu( T, Y );
  }

  template<typename Th, typename V, typename C, typename D>
  libMesh::Real AntiochMixtureAveragedTransportEvaluator<Th,V,C,D>::k( const libMesh::Real /*T*/,
                                                                       const libMesh::Real /*P*/,
                                                                       const std::vector<libMesh::Real>& /*Y*/ )
  {
    libmesh_error();
    return 0.0;//_wilke_evaluator->k( T, Y );
  }

  template<typename Th, typename V, typename C, typename Diff>
  void AntiochMixtureAveragedTransportEvaluator<Th,V,C,Diff>::mu_and_k_and_D( const libMesh::Real T,
                                                                              const libMesh::Real rho,
                                                                              const libMesh::Real cp,
                                                                              const std::vector<libMesh::Real>& Y,
                                                                              libMesh::Real& mu, libMesh::Real& k,
                                                                              std::vector<libMesh::Real>& D )
  {
    typename Antioch::MixtureAveragedTransportEvaluator<Diff,V,C,libMesh::Real>::DiffusivityType
      diff_type = Antioch::MixtureAveragedTransportEvaluator<Diff,V,C,libMesh::Real>::DiffusivityType::MASS_FLUX_MASS_FRACTION;

    _wilke_evaluator->mu_and_k_and_D( T, rho, cp, Y, mu, k, D, diff_type );
  }

} // end namespace GRINS

#endif // GRINS_HAVE_ANTIOCH
