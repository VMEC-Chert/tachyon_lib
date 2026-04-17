// SECTION: Catch2 Includes
// Everything, but unity build
#include "external/catch2/extras/catch_amalgamated.hpp"
#include "external/catch2/extras/catch_amalgamated.cpp"

//  Everything, but library mode
// #include "../../external/catch2/src/catch2/catch_all.hpp"

// SECTION: Tachyon Library Includes
#include "../include_tachyon_lib_core.h"
// #include "../build_control/tachyon_lib_unity_core.cpp"

static tyon::library_context _library = {};

void test_init()
{
    // NOTE: No good working dir right now
    // tyon::file_set_working_directory( tyon::file_self_directory().string() + "/.." );
    // NOTE: Must make library context first because it holds global allocators
    // We can actually set up some defautl arguments here before calling init
    tyon::library_context_init( &_library );
    tyon::g_logger->console_output_enabled = true;
    // tyon::library_process_cmdline_args( argc, argv );

}

class catch2_main_hook : public Catch::EventListenerBase {
public:
    using EventListenerBase::EventListenerBase;

    void testRunStarting(Catch::TestRunInfo const&) override {
        test_init();
        // Your global setup code here (e.g., Init Engine)
    }

    void testRunEnded(Catch::TestRunStats const&) override {
        // Your global teardown code here
    }
};
CATCH_REGISTER_LISTENER( catch2_main_hook );

/* SECTION: Test Definitions */
using namespace tyon;

TEST_CASE( "Memory Alignment Helpers", "memory" )
{

    SECTION( "memory_padding" )
    {
        // pointer version
        REQUIRE( memory_padding( 4,  (void*)0xDEAD ) == 3 );
        REQUIRE( memory_padding( 16, (void*)0xF003 ) == 13 );
        REQUIRE( memory_padding( 2,  (void*)0x0ad3 ) == 1 );
        REQUIRE( memory_padding( 25, (void*)0x2afd ) == 20);
        REQUIRE( memory_padding( 4,  (void*)0x0021 ) == 3 );

        // int pointer version
        REQUIRE( memory_padding( 4,  (int*)0xDEAD ) == 3  );
        REQUIRE( memory_padding( 16, (int*)0xF003 ) == 13 );
        REQUIRE( memory_padding( 2,  (int*)0x0ad3 ) == 1  );
        REQUIRE( memory_padding( 25, (int*)0x2afd ) == 20 );
        REQUIRE( memory_padding( 4,  (int*)0x0021 ) == 3  );

        // User defined type version
        REQUIRE( memory_padding( 4,  (uid*)0xDEAD ) == 3  );
        REQUIRE( memory_padding( 16, (uid*)0xF003 ) == 13 );
        REQUIRE( memory_padding( 2,  (uid*)0x0ad3 ) == 1  );
        REQUIRE( memory_padding( 25, (uid*)0x2afd ) == 20 );
        REQUIRE( memory_padding( 4,  (uid*)0x0021 ) == 3  );

        // Integer version
        REQUIRE( memory_padding( 4,    0xDEAD ) == 3    );
        REQUIRE( memory_padding( 16,   0xF003 ) == 13   );
        REQUIRE( memory_padding( 2,    0x0ad3 ) == 1    );
        REQUIRE( memory_padding( 25,   0x2afd ) == 20   );
        REQUIRE( memory_padding( 4,    0x0021 ) == 3    );
    }

    SECTION( "memory_align" )
    {

        REQUIRE( memory_align( 0xDEAD,  4 ) == 0xDEB0  );
        REQUIRE( memory_align( 0xF003, 16 ) == 0xF010  );
        REQUIRE( memory_align( 0x0ad3,  2 ) == 0x00ad4 );
        REQUIRE( memory_align( 0x2afd, 25 ) == 0x2b11  );
        REQUIRE( memory_align( 0x0021,  4 ) == 0x0024  );
        REQUIRE( memory_align( 0x0021,  64 ) == 0x0040 );

        REQUIRE( memory_align_typed<i32>( 1, 64) == 64 );
    }
}

TEST_CASE( "uid/uuid Unique Identifiers" )
{
    uid valid = uuid_generate();
    REQUIRE( valid.valid() );

    uid invalid;
    REQUIRE( invalid.valid() == false );

    uid copy1 = uuid_generate();
    copy1.id = 25;
    uid copy2 = copy1;
    REQUIRE( memcmp( &copy1, &copy2, sizeof( uid) ) == 0 );

    uid equal1 = uuid_generate();
    equal1.id = 25;
    uid equal2 = equal1;
    REQUIRE( equal1 == equal2 );

    uid equal_different1 = uuid_generate();
    equal_different1.id = 25;
    uid equal_different2 = uuid_generate();
    REQUIRE( (equal_different1 == equal_different2) == false );

    // Unimplimented
    // uid inequal1 = uuid_generate();
    // inequal1.id = 25;
    // uid inequal2 = inequal1;
    // REQUIRE( inequal1 != inequal2 );

}

TEST_CASE( "Compile Time Library" )
{
    // constexpr uid v1;
    // // uid c1 = compile_expression( v1 );

    // constexpr uid v2;
    // // uid c2 = compile_expression( v2 );
    // uid c3 = compile_expression( 9 + 10 );
    // constexpr uid v3 = 0;

    // constexpr int c4 = compile_expression( 9 + 10 );

}

TEST_CASE( "Container Library" )
{
    SECTION( "String" )
    {
        cstring c_str = "hello world";
        fstring f_str = "hello world";
        string str_1 = c_str;
        string str_2 = f_str;
        // cstring copy
        REQUIRE( memory_same_raw( str_1.parts[0].data, c_str, sizeof(c_str)  ) );
        TYON_LOG( str_1.parts[0].data );
        // fstring copy
        REQUIRE( memory_same_raw( str_1.parts[0].data, f_str.data(), f_str.size()  ) );

    }
}
