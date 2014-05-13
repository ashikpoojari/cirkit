#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE approximate_additional_lines

#include <initializer_list>
#include <iomanip>
#include <future>
#include <fstream>
#include <vector>

#include <boost/assign/std/vector.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/optional.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/irange.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/tuple/tuple.hpp>

#include <core/functions/approximate_additional_lines.hpp>
#include <core/utils/foreach_function.hpp>

#include "caching.h"
#include "benchmark_table.hpp"

unsigned call_extern( const std::string& filename, unsigned num_inputs, const std::string& program )
{
  using boost::format;
  using boost::str;

  system( str( format( "./test/test_%s %s" ) % program % filename ).c_str() );
  std::ifstream is( str( format( "/tmp/lines_%s" ) % program ) );
  int lines;
  is >> lines;
  is.close();
  return num_inputs + lines;
}

BOOST_AUTO_TEST_CASE(simple)
{
  using namespace boost::assign;
  using namespace revkit;
  using namespace revkit::test;

  /* store results */
  benchmark_table<std::string, unsigned, unsigned, unsigned, unsigned, boost::optional<unsigned>, boost::optional<unsigned> >
    table( { "Benchmark", "n", "m", "Bennett", "Heurist.", "Exact", "ExactBDD" } );

  enable_caching( "tcad_embedding" );

  /* run algorithms */
  std::vector<std::string> blacklist, whitelist;
  blacklist += "misex3c_181","5xp1_90","bw_116","sao2_199","f2_158","cps_140";
  whitelist += "xor5_195";
  foreach_function_with_blacklist( blacklist, [&table]( const boost::filesystem::path& path ) {
    std::string function = path.stem().string();

    /* output */
    std::cout << "Processing " << function << "..." << std::endl;

    /* filename */
    std::string filename = path.relative_path().string();

    /* cube based heuristic */
    unsigned num_inputs = 0u, num_outputs = 0u;

//unsigned heuristic = compute_and_cache<unsigned>([&filename, &num_inputs, &num_outputs]() {
      properties::ptr statistics( new properties() );
      unsigned lines = approximate_additional_lines( filename, statistics );
      num_inputs = statistics->get<unsigned>( "num_inputs" );
      num_outputs = statistics->get<unsigned>( "num_outputs" );
      unsigned heuristic = num_inputs + lines;
//}, "tcad_embedding", function + "-heuristic" );

    /* exact after extending */     // unfortunately CUDD is not thread-safe, hence this work around
    boost::optional<unsigned> exact = compute_and_cache<unsigned>([&filename, &num_inputs]() {
      return call_extern( filename, num_inputs, "extend_truth_table" );
    }, std::chrono::seconds(5), "tcad_embedding", function + "-exact", true );

    /* exact with characteristic BDD */
    boost::optional<unsigned> exact_bdd = compute_and_cache<unsigned>([&filename, &num_inputs]() {
      return call_extern( filename, num_inputs, "characteristic_bdd" );
    }, std::chrono::seconds(10), "tcad_embedding", function + "-exact-bdd", true );

    /* add to results */
    table.add( function, num_inputs, num_outputs, num_inputs + num_outputs, heuristic, exact, exact_bdd );
  });

  /* generate table */
  table.print();
}