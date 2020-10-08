#pragma once

#cmakedefine HAS_EXPERIMENTAL_FILESYSTEM

#ifdef HAS_EXPERIMENTAL_FILESYSTEM
#    include <experimental/filesystem>

namespace std_fs_impl = std::experimental::filesystem;
#else
#    include <filesystem>

namespace std_fs_impl = std::filesystem;
#endif
