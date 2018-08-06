/*
 * Author: Damir Cavar (http://damir.cavar.me/)
 * Date: 11/05/2015 - 08/06/2018
 * Purpose:
 * Testing Foma integration in C++.
 * See for more details on Foma nad fomalib:
 * https://fomafst.github.io
 *
 * Copyright 2015 by Damir Cavar
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



typedef bool _Bool; // Foma uses C99 _Bool, Mac clang has trouble with that

#include <iostream>
#include <vector>
#include <stdbool.h> // Foma uses _Bool from C99, this is necessary
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <fomalib.h>



using namespace std;

namespace {
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_XML = 2;
    const size_t ERROR_UNHANDLED_EXCEPTION = 3;
    const size_t ERROR_MISSING_FILE = 4;
} // namespace

namespace fs = boost::filesystem;
namespace po = boost::program_options;


int main(int argc, char *argv[]) {

    bool quiet = false;

    try {

        po::options_description desc("fomatest options");
        desc.add_options()
                ("quiet,q", "Quiet operations")
                ("input-files", po::value<vector<string>>()->required(), "Word list input files");

        po::positional_options_description p;
        p.add("input-files", -1);
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);

        if (vm.count("help")) {
            cout << "Usage: fomatest [OPTION]... [words]..." << endl << endl
            << "Process words " << endl
            << endl
            << "(C) 2015 by Damir Cavar <damir@linguistlist.org>" << endl
            << "            Lwin Moe <lwing@linguistlist.org>" << endl << endl
            << desc << endl;
            return SUCCESS;
        }
        po::notify(vm);
        if (vm.count("quiet")) {
            quiet = true;
        }
        if (vm.count("input-files")) {
            // read tokens from file
            struct fsm *net;
            struct apply_handle *ah;
            char *result;

            char binaryfst[] = "english.fst";
            net = fsm_read_binary_file(binaryfst);
            cout << "Loaded binary fst: " << binaryfst << endl;
            ah = apply_init(net);

            vector<string> files = vm["input-files"].as<vector<string>>();
            for (auto file : files) {
                ifstream infile(file);
                string line;
                while (infile >> line) {
                    cout << line;
                    result = apply_up(ah, (char *) line.c_str());
                    while (result != NULL) {
                        cout << "\t" << result << endl;
                        result = apply_up(ah, NULL);
                    }
                }
            }
            apply_clear(ah);
            fsm_destroy(net);
        }
    }
        // Catch command line error
    catch (exception &e) {
        cerr << "Error: " << e.what() << endl;
        return ERROR_IN_COMMAND_LINE;
    }
        // catch any other error
    catch (...) {
        cerr << "Unknown error!" << endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }

    return SUCCESS;
} // main
