#include "taskgraph/task/FileCompress.h"
#include "taskgraph/TaskHelper.h"
#include "taskgraph/ParamImpl.h"

#include <LzmaEnc.h>
#include <Alloc.h>

#include <boost/filesystem.hpp>

namespace
{

static void *SzAlloc(void *p, size_t size) { p = p; return MyAlloc(size); }
static void SzFree(void *p, void *address) { p = p; MyFree(address); }
static ISzAlloc g_Alloc = { SzAlloc, SzFree };

static const unsigned PropHeaderSize = 5;
static const unsigned HeaderSize = 9;

}

namespace taskgraph
{
namespace task
{

void FileCompress::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    if (m_output_filepath.empty()) {
        return;
    }

    std::string filepath;
    auto prev_param = TaskHelper::GetInputParam(*this, 0);
    if (prev_param)
    {
        assert(prev_param->Type() == PT_FILE);
        filepath = std::static_pointer_cast<FileParam>(prev_param)->GetFilepath();
    }
    else
    {
        filepath = m_input_filepath;
    }

    if (!boost::filesystem::exists(filepath)) {
        return;
    }

    std::ifstream fin(filepath.c_str(), std::ios::binary | std::ios::ate);
    std::streamsize size = fin.tellg();
    fin.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (fin.read(buffer.data(), size))
    {
        char* dst = nullptr;
        size_t dst_sz;
        Compress(&dst, &dst_sz, buffer.data(), buffer.size());

        std::ofstream fout(m_output_filepath.c_str(), std::ios::binary);
        fout.write(reinterpret_cast<const char*>(dst), dst_sz);
        fout.close();

        m_vals.resize(1);
        m_vals[0] = std::make_shared<FileParam>(m_output_filepath);
    }

    fin.close();
}

void FileCompress::Compress(char** dst, size_t* dst_len, const char* src, size_t src_len)
{
    CLzmaEncProps props;
    LzmaEncProps_Init(&props);
    props.level = -1;
    props.dictSize = 0;
    props.lc = -1;
    props.lp = -1;
    props.pb = -1;
    props.fb = -1;
    props.numThreads = -1;

    size_t buf_sz = src_len * 2;
    uint8_t* buf = new uint8_t[buf_sz];

    memcpy(buf + PropHeaderSize, &src_len, 4);

    size_t out_sz = buf_sz;
    size_t prop_sz = PropHeaderSize;
    int result = LzmaEncode(buf + HeaderSize, &out_sz, reinterpret_cast<const unsigned char*>(src), src_len, &props, buf + 4, &prop_sz,
        0, NULL, &g_Alloc, &g_Alloc);
    if (SZ_OK != result) {
        *dst_len = 0;
        *dst = NULL;
        return;
    }

    *dst_len = out_sz + HeaderSize;

    *dst = new char[*dst_len];
    memcpy(*dst, buf, *dst_len);

    (*dst)[0] = (src_len >> 24) & 0xff;
    (*dst)[1] = (src_len >> 16) & 0xff;
    (*dst)[2] = (src_len >> 8) & 0xff;
    (*dst)[3] = (src_len) & 0xff;

    delete[] buf;
}

}
}