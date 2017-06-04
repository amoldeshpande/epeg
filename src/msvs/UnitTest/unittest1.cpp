#include "stdafx.h"
#include <vector>
#include <fstream>
#include "CppUnitTest.h"
#include <epeg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest
{		
    TEST_CLASS(UnitTest1)
    {
        std::vector<unsigned char> ReadAllBytes(char const* filename)
        {
            ifstream ifs(filename, ios::binary | ios::ate);
            ifstream::pos_type pos = ifs.tellg();

            std::vector<unsigned char>  result(pos);

            ifs.seekg(0, ios::beg);
            ifs.read((char*)&result[0], pos);

            return result;
        }
        void ReadAllBytes(char const* filename,std::vector<unsigned char>& data)
        {
            ofstream ofs(filename, ios::binary | ios::ate);

            ofs.write((char*)&data[0], data.size());

        }
    public:
        
        TEST_METHOD(TestMethod1)
        {
            auto filebuf = ReadAllBytes(R"(f:\photos\targets\WP_20170512_11_37_00_Rich_LI.jpg)");
            auto im = epeg_memory_open(&filebuf[0], filebuf.size());
            if (im != nullptr)
            {
                int w, h;
                epeg_size_get(im, &w, &h);
                epeg_decode_size_set(im, 1024, (int)(1024 * ((float)h / (float)w)));
                epeg_quality_set(im, 85);
                epeg_file_output_set(im, R"(f:\photos\targets\WP_20170512_11_37_00_Rich_LI_epeg.jpg)");
                epeg_encode(im);
                epeg_close(im);
            }
        }

    };
}