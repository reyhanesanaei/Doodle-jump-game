#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

// Generic, type-safe resource cache.
//
// Works for any SFML asset type exposing loadFromFile(const std::string&) —
// sf::Texture, sf::Font, sf::SoundBuffer, etc. Each asset is loaded from disk
// at most once and reused (cached) by file path for the rest of the
// program's lifetime, which avoids redundant disk I/O for assets shared by
// many objects (e.g. every "normal platform" sprite uses the same texture).
//
// Header-only by necessity: a class template's member definitions must be
// visible at every instantiation point, so splitting this into a .cpp file
// would require explicit instantiation for every type we ever use — that
// defeats the purpose of a *generic* manager reusable in later phases.
//
// Ownership is managed with std::unique_ptr, so every loaded resource is
// automatically destroyed (no manual "delete", no leaks) when the manager
// itself goes out of scope.
template <typename T>
class ResourceManager
{
public:
    ResourceManager() = default;

    // Non-copyable: copying would either duplicate GPU resources or require
    // deep-copying sf::Texture/sf::Font, neither of which we want.
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // Returns a reference to the cached resource at filePath, loading it
    // from disk on first request.
    T& get(const std::string& filePath)
    {
        auto it = m_resources.find(filePath);
        if (it != m_resources.end())
            return *(it->second);

        auto resource = std::make_unique<T>();
        if (!resource->loadFromFile(filePath))
            throw std::runtime_error("ResourceManager: failed to load resource \"" + filePath + "\"");

        T& reference = *resource;
        m_resources.emplace(filePath, std::move(resource));
        return reference;
    }

    bool isLoaded(const std::string& filePath) const
    {
        return m_resources.find(filePath) != m_resources.end();
    }

    void clear()
    {
        m_resources.clear();
    }

private:
    std::unordered_map<std::string, std::unique_ptr<T>> m_resources;
};

// Convenience aliases for the asset types this project needs.
// Phase 2 can reuse the same template for new asset kinds (e.g. sf::SoundBuffer
// for sound effects) without touching this file.
using TextureManager     = ResourceManager<sf::Texture>;
using FontManager         = ResourceManager<sf::Font>;
using SoundBufferManager = ResourceManager<sf::SoundBuffer>;