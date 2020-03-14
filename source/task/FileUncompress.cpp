#include "taskgraph/task/FileUncompress.h"
#include "taskgraph/TaskHelper.h"
#include "taskgraph/ParamImpl.h"

#include <Alloc.h>
#include <LzmaDec.h>

#include <boost/filesystem.hpp>

namespace
{

static void *SzAlloc(void *p, size_t size) { p = p; return MyAlloc(size); }
static void SzFree(void *p, void *address) { p = p; MyFree(address); }
static ISzAlloc g_Alloc = { SzAlloc, SzFree };

#define LZMA_PROPS_SIZE 5

struct block {
    uint8_t size[4];
    uint8_t prop[LZMA_PROPS_SIZE];
    uint8_t data[119];
};

}

namespace taskgraph
{
namespace task
{

void FileUncompress::Execute(const std::shared_ptr<dag::Context>& ctx)
{
    std::string filepath;
    auto prev_param = TaskHelper::GetInputParam(*this, 0);
    if (prev_param)
    {
        assert(prev_param->Type() == PT_FILE);
        filepath = std::static_pointer_cast<FileParam>(prev_param)->GetFilepath();
    }
    else
    {
        filepath = m_filepath;
    }

    if (!boost::filesystem::exists(filepath)) {
        return;
    }

    std::ifstream fin(filepath.c_str(), std::ios::binary | std::ios::ate);
    if (fin.fail()) {
        return;
    }

    size_t size = static_cast<uint8_t>(fin.tellg());
    fin.seekg(0, std::ios::beg);

    uint8_t* c_buf = new uint8_t[size];
    struct block* block = (struct block*)c_buf;
    fin.read(reinterpret_cast<char*>(block), size);
    fin.close();

    size_t uc_sz = size * 10;		// FIXME
    size_t guess_sz = uc_sz;
    uint8_t* uc_buf = new uint8_t[uc_sz];
    size_t c_sz = size - sizeof(block->size) - LZMA_PROPS_SIZE;
    Uncompress(uc_buf, &uc_sz, block->data, &c_sz, block->prop, LZMA_PROPS_SIZE);
    if (guess_sz == uc_sz) {
        return;
    }
    delete[] c_buf;

    m_vals.resize(1);
    m_vals[0] = std::make_shared<BufferParam>(uc_buf);
}

int FileUncompress::Uncompress(unsigned char* dst, size_t* dst_len, const unsigned char* src, size_t* src_len, 
                               const unsigned char* props, size_t props_sz)
{
    ELzmaStatus status;
    return LzmaDecode(dst, dst_len, src, src_len, props, (unsigned)props_sz, LZMA_FINISH_ANY, &status, &g_Alloc);
}

}
}