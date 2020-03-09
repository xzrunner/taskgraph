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
        return ParamType::File;
    }

    auto& GetFilepath() const { return m_filepath; }

private:
    std::string m_filepath;

}; // FileParam

class ImageParam : public Param
{
public:
    explicit ImageParam(const std::shared_ptr<prim::Bitmap<short>>& img)
        : m_img(img) {}

    virtual ParamType Type() const override {
        return ParamType::Image;
    }

    auto& GetImage() const { return m_img; }

private:
    std::shared_ptr<prim::Bitmap<short>> m_img;

}; // ImageParam

class ImageArrayParam : public Param
{
public:
    explicit ImageArrayParam(const std::vector<std::shared_ptr<prim::Bitmap<short>>>& imgs)
        : m_imgs(imgs) {}

    virtual ParamType Type() const override {
        return ParamType::ImageArray;
    }

    auto& GetAllImages() const { return m_imgs; }

private:
    std::vector<std::shared_ptr<prim::Bitmap<short>>> m_imgs;

}; // ImageArrayParam

}