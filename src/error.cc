/*
 *  This file is part of MUSIC.
 *  Copyright (C) 2007, 2008, 2009 INCF
 *
 *  MUSIC is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MUSIC is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <mpi.h>

#include <music/error.hh>

#include <iostream>
#include <stdlib.h>

namespace MUSIC {

  void
  error ()
  {
    MPI::COMM_WORLD.Abort (1);
  }


  void
  hang ()
  {
    while (true)
      ;
  }
  
  
  void
  error (std::string msg)
  {
    std::cerr << "Error in MUSIC library: " << msg << std::endl;
    error ();
  }


  void
  error0 (std::string msg)
  {
    if (MPI::COMM_WORLD.Get_rank () == 0)
      error (msg);
    else
      // Give process #0 a chance to report the error
      hang ();
  }

}