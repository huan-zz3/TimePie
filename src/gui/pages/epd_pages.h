#ifndef EPD_PAGES_H
#define EPD_PAGES_H

// #include "iepd_driver.h"
#include "devicelayer.h"
#include "gui/components/epd_component.h"
// #include "predefine.h"
#include <memory>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <fstream>
#include <stdexcept>
#include <cstdint>

using ComponentRange = std::list<std::vector<PointCoordinates>>;
// 打印单个 PointCoordinates
void printPointCoordinates(const PointCoordinates& point);
// 打印整个 ComponentRange
void printComponentRange(const ComponentRange& range);
class EPD_Component;

class OrderedComponentList
{
private:
    std::vector<std::shared_ptr<EPD_Component>> components;
    // 辅助函数：查找元素索引
    int findIndex(const std::shared_ptr<EPD_Component> &component) const
    {
        auto it = std::find(components.begin(), components.end(), component);
        if (it == components.end())
        {
            return -1; // 未找到
        }
        return static_cast<int>(std::distance(components.begin(), it));
    }

public:
    // 新增元素到末尾
    void add(std::shared_ptr<EPD_Component> component)
    {
        if (components.size() >= 255)
        {
            throw std::out_of_range("Maximum capacity (255) reached");
        }
        int index = findIndex(component);
        if (index != -1)
        {
            // 如果元素已存在，更新索引到最大值
            updateIndex(component, static_cast<uint8_t>(components.size() - 1));
        }
        else
        {
            // 如果元素不存在，新增到末尾
            components.push_back(component);
        }
    }
    // 删除指定元素
    void remove(const std::shared_ptr<EPD_Component> &component)
    {
        int index = findIndex(component);
        if (index == -1)
        {
            // 不抛出异常，找不到组件是正常逻辑
            // throw std::invalid_argument("Component not found in the list");
            std::cout << "Component not found in the list: " << component.get() << std::endl;
            return;
        }
        components.erase(components.begin() + index);
    }
    // 获取元素
    std::shared_ptr<EPD_Component> get(uint8_t index) const
    {
        if (index >= components.size())
        {
            throw std::out_of_range("Index out of range");
        }
        return components[index];
    }
    // 更新元素索引
    void updateIndex(const std::shared_ptr<EPD_Component> &component, uint8_t newIndex)
    {
        int oldIndex = findIndex(component);
        if (oldIndex == -1)
        {
            // 如果元素不存在，当做新增处理
            add(component);
            return;
        }
        if (newIndex >= components.size())
        {
            throw std::out_of_range("New index out of range");
        }
        if (static_cast<uint8_t>(oldIndex) == newIndex)
            return;
        auto element = components[oldIndex];
        components.erase(components.begin() + oldIndex);
        components.insert(components.begin() + newIndex, element);
    }
    // 查询元素索引
    uint8_t find(const std::shared_ptr<EPD_Component> &component) const
    {
        int index = findIndex(component);
        if (index == -1)
        {
            throw std::invalid_argument("Component not found in the list");
        }
        return static_cast<uint8_t>(index);
    }
    // 其他辅助函数
    size_t size() const { return components.size(); }
    bool empty() const { return components.empty(); }
    const std::shared_ptr<EPD_Component>& operator[](int index) const { return components[index]; }
    // 提供迭代器接口
    using Iterator = typename std::vector<std::shared_ptr<EPD_Component>>::iterator;
    using ConstIterator = typename std::vector<std::shared_ptr<EPD_Component>>::const_iterator;
    Iterator begin() { return components.begin(); }
    Iterator end() { return components.end(); }
    ConstIterator begin() const { return components.begin(); }
    ConstIterator end() const { return components.end(); }
    ConstIterator cbegin() const { return components.cbegin(); }
    ConstIterator cend() const { return components.cend(); }
};

/*
 * 第一层list代表围岛，list数代表围岛数。
 * 第二层vector代表围岛中的坐标点，各点连线所围成的图形定义了该围岛，vector数代表围岛中的坐标点数。
 */
class EPD_Page : public std::enable_shared_from_this<EPD_Page>
{
public:
    explicit EPD_Page(std::shared_ptr<DeviceLayer> _epdd);
    ~EPD_Page();

    virtual Result<void> draw() = 0;
    virtual Result<void> show() = 0;

    Result<void> loadbmp(std::string _picpath);
    Result<void> addcomponent(std::shared_ptr<EPD_Component> component);
    Result<void> removecomponent(std::shared_ptr<EPD_Component> component);
    Result<void> setcomponentvisable(std::shared_ptr<EPD_Component> component, bool visable);

    Result<ImageBuffer_ptr> getimagebuffer();

    Result<void> updatecomponentzindex(uint8_t z, std::shared_ptr<EPD_Component> comp);
    Result<void> updatecomponentrange(std::shared_ptr<EPD_Component> comp, ComponentRange range);

protected:
    OrderedComponentList componentList_;
    std::shared_ptr<DeviceLayer> epd_driver_;
    ImageBuffer_ptr imageBuffer_;

    std::unordered_map<std::shared_ptr<EPD_Component>, bool> componentVisable_ = {};
    std::unordered_map<std::shared_ptr<EPD_Component>, ComponentRange> componentToRange_ = {};

public:
    Signal_coordinate signal_Clicked_;

private:
    virtual Result<void> delete_remove();
    void slot_Clicked_(PointCoordinates point);
};

#endif // EPD_PAGES_H