#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <geode/CacheFactory.hpp>
#include <geode/CqAttributesFactory.hpp>
#include <geode/PoolManager.hpp>
#include <geode/RegionFactory.hpp>
#include <geode/RegionShortcut.hpp>
#include <geode/Region.hpp>
#include <geode/CacheListener.hpp>
#include <geode/EntryEvent.hpp>
using namespace apache::geode::client;

int main(int argc, char *argv[]) {

    auto cache = CacheFactory()
            .set("cache-xml-file","client-cache.xml")
            .create();
    auto region = cache.getRegion("regionA");
    if (!region) {
        std::cerr << "region is not found.";
        exit(1);
    }

    std::cout << "start: " << region->getFullPath() << " Name: " << region->getName() << " size: " << region->size() << std::endl;

    auto now = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(now);

    region->put("foo", std::ctime(&end_time));
    auto val = region->get("foo");
    if (!val) {
        std::cerr << "val is not found.";
        exit(1);
    }
    std::cout << "key: foo  value: " << std::dynamic_pointer_cast<CacheableString>(val)->value() << std::endl;  
}
