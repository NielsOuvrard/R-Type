#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "IDisplay.hpp"

namespace Haze
{
    template <typename T>
    class AssetManager {
        public:
            AssetManager() = default;
            ~AssetManager() = default;
            std::shared_ptr<T> loadAsset(std::string path)
            {
                if (_textures.find(path) == _textures.end()) {
                    _textures[path] = std::make_shared<T>(path);
                }
                return _textures[path];
            }
        protected:
        private:
            std::map<std::string, std::shared_ptr<T>> _textures;

    };
}
