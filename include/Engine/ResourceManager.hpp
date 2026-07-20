#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

template <typename Resource>
class ResourceManager
{
public:
    Resource& load(const std::string& id, const std::string& filename)
    {
        if(auto existing = m_resources.find(id); existing != m_resources.end())
            return *existing->second;

        auto resource = std::make_unique<Resource>();

        bool loaded = false;
        if constexpr (std::is_same_v<Resource, sf::Font>)
            loaded = resource->openFromFile(filename);
        else
            loaded = resource->loadFromFile(filename);

        if(!loaded)
            throw std::runtime_error("Failed to load resource: " + filename);

        auto* raw = resource.get();
        m_resources.emplace(id, std::move(resource));
        return *raw;
    }

    Resource& get(const std::string& id)
    {
        return *m_resources.at(id);
    }

    const Resource& get(const std::string& id) const
    {
        return *m_resources.at(id);
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Resource>> m_resources;
};
