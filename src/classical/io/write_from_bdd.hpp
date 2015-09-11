/* CirKit: A circuit toolkit
 * Copyright (C) 2009-2015  University of Bremen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file write_from_bdd.hpp
 *
 * @brief Writes files from BDDs based on suffix
 *
 * @author Mathias Soeken
 * @since  2.3
 */

#ifndef WRITE_FROM_BDD_HPP
#define WRITE_FROM_BDD_HPP

#include <string>
#include <vector>

#include <core/properties.hpp>
#include <classical/dd/bdd.hpp>

namespace cirkit
{

void write_from_bdd( const std::vector<bdd>& fs, const std::string& filename,
                     const properties::ptr& settings = properties::ptr(),
                     const properties::ptr& statistics = properties::ptr() );

}

#endif

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
