#pragma once

#include "taskgraph/Param.h"

#include <primitive/Bitmap.h>

#include <memory>

namespace taskgraph
{

class FileParam : public Param
{
public:
    explicit FileParam(const std::string& filepath)
        : m_filepath(filepath) {}

    virtual ParamType Type() const override {
        return PT_FILE;
    }

    auto& GetFilepath() const { return m_filepath; }

private:
    std::string m_filepath;

}; // FileParam

class BufferParam : public Param
{
public:
    explicit BufferParam(const uint8_t* buf)
        : m_buf(buf) {}
    ~BufferParam() { delete[] m_buf; }

    virtual ParamType Type() const override {
        return PT_BUFFER;
    }

    auto& GetBuffer() const { return m_buf; }

private:
    const uint8_t* m_buf;

}; // BufferParam

struct Image
{
    Image(size_t width, size_t height, size_t channels)
        : bmp(width, height, channels) {}

    std::string name;
    prim::Bitmap<short> bmp;
};

class ImageParam : public Param
{
public:
    explicit ImageParam(const std::shared_ptr<Image>& img)
        : m_img(img) {}

    virtual ParamType Type() const override {
        return PT_IMAGE;
    }

    auto& GetImage() const { return m_img; }

private:
    std::shared_ptr<Image> m_img = nullptr;

}; // ImageParam

class ImageArrayParam : public Param
{
public:
    explicit ImageArrayParam(const std::vector<std::shared_ptr<Image>>& imgs)
        : m_imgs(imgs) {}

    virtual ParamType Type() const override {
        return PT_IMAGE_ARRAY;
    }

    auto& GetAllImages() const { return m_imgs; }

private:
    std::vector<std::shared_ptr<Image>> m_imgs;

}; // ImageArrayParam

}