/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   Copyright (c) 2012 The plumed team
   (see the PEOPLE file at the root of the distribution for a list of names)

   See http://www.plumed-code.org for more information.

   This file is part of plumed, version 2.0.

   plumed is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   plumed is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with plumed.  If not, see <http://www.gnu.org/licenses/>.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#include <cmath>

#include "ColvarPathMSDBase.h"

#include "Colvar.h"
#include "ActionRegister.h"

#include <string>
#include <cstring>
#include <cassert>
#include <iostream>
#include "PDB.h"
#include "RMSD.h"
#include "Atoms.h"
#include "Tools.h"

using namespace std;

namespace PLMD{

//+PLUMEDOC COLVAR PATHMSD
/*
This Colvar calculates path collective variables. 

This is the Path Collective Variables implementation 
( see \cite brand07 ).
This variable computes the progress along a given set of frames that is provided  
in input ("s" component) and the distance from them ("z" component). 
(see below).

\par Examples

Here below is a case where you have defined three frames and you want to  
calculate the progress alng the path and the distance from it in p1

\verbatim
p1: PATHMSD REFERENCE=file.pdb  LAMBDA=500.0 NEIGH_STRIDE=1.0 NEIGH_SIZE=8 PROPERTY=X,Y 
PRINT ARG=p1.s,p1.z STRIDE=1 FILE=colvar FMT=%8.4f
\endverbatim

note that NEIGH_STRIDE=1.0 NEIGH_SIZE=8 control the neighborlist parameter (optional but
recommended for perfomance)
while PROPERTY=X,Y allows to do an "isomap" style kind of path (a-la Spiwok) 
where property is in the form of a REMARK line (note no spaces!!!) in the REFERENCE
e.g.
REMARK X=1 Y=2 
ATOM      1  CL  ALA     1      -3.171   0.295   2.045  1.00  1.00
ATOM      5  CLP ALA     1      -1.819  -0.143   1.679  1.00  1.00
.......
END
REMARK X=2 Y=3 
ATOM      1  CL  ALA     1      -3.175   0.365   2.024  1.00  1.00
ATOM      5  CLP ALA     1      -1.814  -0.106   1.685  1.00  1.00
....
END

*/
//+ENDPLUMEDOC
   
class ColvarPathMSD : public ColvarPathMSDBase {
public:
  ColvarPathMSD(const ActionOptions&);
  static void registerKeywords(Keywords& keys);
};

PLUMED_REGISTER_ACTION(ColvarPathMSD,"PATHMSD")

void ColvarPathMSD::registerKeywords(Keywords& keys){
  ColvarPathMSDBase::registerKeywords(keys);
}

ColvarPathMSD::ColvarPathMSD(const ActionOptions&ao):
Action(ao),ColvarPathMSDBase(ao)
{
  checkRead();
};

}

