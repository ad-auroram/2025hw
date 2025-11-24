#include "MsgSystem.hpp"
#include <getopt.h>   
#include <cstdlib>
#include <iostream>
#include <string>

static void print_usage(const char* prog) 
{
    std::cout <<
    R"(Message System (Assignment 7)

    USAGE:
    )" << prog << R"( [OPTIONS]

    OPTIONS:
    -i, --io <mode>     I/O mode: file | stdin (default: file)
    -f, --file <path>   Path to input file (required for --io file; default: messages.txt)
    -h, --help          Show this help and exit

    EXAMPLES:
    )" << prog << R"( -i file -f messages.txt
    )" << prog << R"( --io stdin
    )";
}

int main(int argc, char** argv) 
{
    IOType ioType = IOType::File;
    std::string filePath = "messages.txt";

    // Long options
    static option longopts[] = {
        {"io",     required_argument, nullptr, 'i'},
        {"file",   required_argument, nullptr, 'f'},
        {"help",   no_argument,       nullptr, 'h'},
        {nullptr,  0,                 nullptr,  0 }
    };

    int opt, longidx = 0;
    while ((opt = ::getopt_long(argc, argv, "i:f:vh", longopts, &longidx)) != -1) {
        switch (opt) {
        case 'i': {
            std::string mode = optarg ? std::string(optarg) : "";
            if (mode == "file")       ioType = IOType::File;
            else if (mode == "stdin") ioType = IOType::Stdin;
            else if (mode == "socket")
                return (std::cerr << "socket mode is reserved for a later assignment.\n", 2);
            else
                return (std::cerr << "unknown --io mode: " << mode << "\n", 2);
            break;
        }
        case 'f':
            filePath = optarg ? std::string(optarg) : "";
            break;
        case 'h':
            print_usage(argv[0]);
            return 0;
        case '?': // unknown option or missing arg
        default:
            print_usage(argv[0]);
            return 2;
        }
    }

    // Validate combinations
    if (ioType == IOType::File && filePath.empty()) {
        std::cerr << "--io file requires --file <path>\n\n";
        print_usage(argv[0]);
        return 2;
    }

    try {
        MsgSystem sys(ioType, filePath);
        sys.start();
        sys.end();
    } 
    catch (const std::exception& e) {
        std::cerr << "fatal: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
