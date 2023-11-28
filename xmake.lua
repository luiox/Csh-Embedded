add_rules("mode.debug", "mode.release")

target("csh")
    set_kind("binary")
    add_includedirs("inc")
    add_files("src/**.c")
