cmd_Release/lz4_clib.node := c++ -bundle -undefined dynamic_lookup -Wl,-search_paths_first -mmacosx-version-min=10.5 -arch x86_64 -L./Release  -o Release/lz4_clib.node Release/obj.target/lz4_clib/src/source.o Release/obj.target/lz4_clib/lib/lz4.o Release/obj.target/lz4_clib/lib/lz4frame.o Release/obj.target/lz4_clib/lib/lz4hc.o Release/obj.target/lz4_clib/lib/xxhash.o 