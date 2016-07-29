#include "configuration.hpp"
#include "SimpleJSON/utility/beauty_stream.hpp"

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include <fstream>

namespace WikiMarkup {
//####################################################################################
    Config::Config(std::string const& json)
    {
        auto tree = JSON::parse_json("{\"config\":" + json + "}");
        JSON::parse(*this, "config", tree);
    }
//####################################################################################
    ConfigWriteable::ConfigWriteable(Config cfg, std::string fileName)
        : Config(std::move(cfg))
        , fileName_(std::move(fileName))
    {
    }
//-----------------------------------------------------------------------------------
    ConfigWriteable::~ConfigWriteable()
    {
        std::ofstream writer (fileName_, std::ios_base::binary);
        if (!writer.good())
            return;
        writer.close();

        boost::iostreams::filtering_ostream filter;
        filter.push(JSON::BeautifiedStreamWrapper{});
        filter.push(boost::iostreams::file_sink(fileName_));

        JSON::try_stringify(filter, "", *this);
    }
//####################################################################################
    Configuration::~Configuration()
    {
        getWriteable();
    }
//-----------------------------------------------------------------------------------
    Configuration& Configuration::getInstance()
    {
        static Configuration config;
        return config;
    }
//-----------------------------------------------------------------------------------
    std::string Configuration::getFileName() const
    {
        return "./config.json";
    }
//-----------------------------------------------------------------------------------
    ConfigWriteable Configuration::getWriteable() const
    {
        return {cfg_, getFileName()};
    }
//-----------------------------------------------------------------------------------
    Configuration::Configuration()
    {
        reload();
    }
//-----------------------------------------------------------------------------------
    void Configuration::reload()
    {
        std::ifstream reader(getFileName(), std::ios_base::binary);
        if (reader.good())
        {
            reader.seekg(0, std::ios::end);
            size_t size = reader.tellg();
            std::string buffer(size, ' ');
            reader.seekg(0);
            reader.read(&buffer[0], size);

            cfg_ = {buffer};
        }
    }
//-----------------------------------------------------------------------------------
    Config Configuration::getReadOnly() const
    {
        return cfg_;
    }
//####################################################################################
}
