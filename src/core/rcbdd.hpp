/* RevKit: A Toolkit for Reversible Circuit Design (www.revkit.org)
 * Copyright (C) 2009-2013  The RevKit Developers <revkit@informatik.uni-bremen.de>
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
 * @file rcbdd.hpp
 *
 * @brief Data structure for BDD of a characteristic function to a reversible function
 *
 * @author Mathias Soeken
 * @since  2.0
 */

#ifndef RCBDD_HPP
#define RCBDD_HPP

#include <boost/assign/std/vector.hpp>
#include <boost/optional.hpp>

#include <cuddObj.hh>

namespace revkit
{

  using namespace boost::assign;

  class rcbdd
  {
  public:
    rcbdd();

    void initialize_manager();
    void create_variables( unsigned n );
    BDD x( unsigned i ) const;
    BDD y( unsigned i ) const;
    BDD z( unsigned i ) const;

    const std::vector<BDD> xs() const;
    const std::vector<BDD> ys() const;
    const std::vector<BDD> zs() const;

    unsigned num_vars() const;
    const Cudd& manager() const;
    BDD chi() const;
    void set_chi( BDD f );

    BDD compose(const BDD& left, const BDD& right) const;
    BDD cofactor( BDD f, unsigned var, bool input_polarity, bool output_polarity ) const;
    BDD move_xs_to_tmp(const BDD& f) const;
    BDD move_ys_to_tmp(const BDD& f) const;
    BDD move_ys_to_xs(const BDD& f) const;
    BDD remove_xs( const BDD& f ) const;
    BDD remove_ys( const BDD& f ) const;

    BDD create_from_gate(unsigned target, const BDD& controlf) const;

  private:
    boost::optional<Cudd> _manager;
    BDD _chi;

    unsigned _n;
    std::vector<BDD> _xs;
    std::vector<BDD> _ys;
    std::vector<BDD> _zs;
  };

}

#endif

// Local Variables:
// c-basic-offset: 2
// End: