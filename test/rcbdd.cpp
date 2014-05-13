#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE rcbdd

#include <boost/test/unit_test.hpp>

#if ADDON_REVLIB

#include <boost/assign/std/vector.hpp>

#include <core/circuit.hpp>
#include <core/rcbdd.hpp>
#include <algorithms/synthesis/embed_pla.hpp>
#include <algorithms/synthesis/rcbdd_synthesis.hpp>

#include <core/utils/foreach_function.hpp>

using namespace boost::assign;

BOOST_AUTO_TEST_CASE(simple)
{
  using boost::unit_test::framework::master_test_suite;
  using namespace revkit;

  if ( master_test_suite().argc == 2u )
  {
    circuit circ;
    rcbdd cf;

    properties::ptr settings( new properties );
    settings->set( "verbose", true );
    settings->set( "truth_table", true );

    embed_pla( cf, master_test_suite().argv[1], settings );
    //rcbdd_synthesis( circ, cf, settings );
    return;
  }

  std::vector<std::string> whitelist;
  whitelist += "sym6_63","urf2_73","con1_136","hwb9_65","urf1_72","urf5_76","sym9_71","urf3_75","rd84_70","sym10_207","urf4_89","adr4_93","cycle_10_2_61","clip_124","dc2_143","misex1_178","co14_135","urf6_77","dk27_146","t481_208","5xp1_90","C7552_119","apla_107","bw_116";
  // extra alu1_94
  foreach_function_with_whitelist( whitelist, []( const boost::filesystem::path& path ) {
    circuit circ;
    rcbdd cf;

    properties::ptr settings( new properties );
    settings->set( "verbose", false );

    std::cout << "Parse: " << path.relative_path().string() << std::endl;
    embed_pla( cf, path.relative_path().string() );
    rcbdd_synthesis( circ, cf, settings );
  });
}

#else

BOOST_AUTO_TEST_CASE(simple) {}

#endif

// Local Variables:
// c-basic-offset: 2
// End: