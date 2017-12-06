#include <tmd/bin.hpp>
#include <tmd/hook.inc>

namespace nob {
	tmd::bin _main_mdu_mem = tmd::bin::from_this_process_main_module();
}
