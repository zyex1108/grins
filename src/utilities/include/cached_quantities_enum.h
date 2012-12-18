//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
// 
// GRINS - General Reacting Incompressible Navier-Stokes 
//
// Copyright (C) 2010-2012 The PECOS Development Team
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the Version 2 GNU General
// Public License as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA
// 02110-1301 USA
//
//-----------------------------------------------------------------------el-
//
// $Id$
//
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

#ifndef GRINS_CACHED_QUANTITIES_ENUM_H
#define GRINS_CACHED_QUANTITIES_ENUM_H

namespace GRINS
{

  enum CachedQuantities{ X_VELOCITY = 0,
			 Y_VELOCITY,
			 Z_VELOCITY,
			 X_VELOCITY_GRAD,
			 Y_VELOCITY_GRAD,
			 Z_VELOCITY_GRAD,
			 PRESSURE,
			 THERMO_PRESSURE,
			 TEMPERATURE,
			 TEMPERATURE_GRAD,
			 PERFECT_GAS_DENSITY,
			 MIXTURE_DENSITY,
			 PERFECT_GAS_VISCOSITY,
			 SPECIES_VISCOSITY,
			 MIXTURE_VISCOSITY,
			 PERFECT_GAS_THERMAL_CONDUCTIVITY,
			 SPECIES_THERMAL_CONDUCTIVITY,
			 MIXTURE_THERMAL_CONDUCTIVITY,
			 PERFECT_GAS_SPECIFIC_HEAT_P,
			 SPECIES_SPECIFIC_HEAT_P,
			 MIXTURE_SPECIFIC_HEAT_P,
			 PERFECT_GAS_SPECIFIC_HEAT_V,
			 SPECIES_SPECIFIC_HEAT_V,
			 MIXTURE_SPECIFIC_HEAT_V,
			 MASS_FRACTIONS,
			 MASS_FRACTION_GRADIENTS,
			 MOLE_FRACTIONS,
			 MOLAR_MASS,
			 SPECIES_GAS_CONSTANTS,
			 MIXTURE_GAS_CONSTANT,
			 DIFFUSION_COEFFS,
			 SPECIES_ENTHALPY,
			 OMEGA_DOT };
  

} // namespace GRINS

#endif // GRINS_CACHED_QUANTITIES_ENUM_H
