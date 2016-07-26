#ifndef CONFIGURATION_HPP_INCLUDED
#define CONFIGURATION_HPP_INCLUDED

#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/parse/jsd.h"
#   include "SimpleJSON/parse/jsd_convenience.h"
#   include "SimpleJSON/stringify/jss.h"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.h"
#   include "SimpleJSON/utility/base64.h"
#endif

#include <string>

namespace WikiMarkup
{
    class Configuration;

    struct Config : public JSON::Stringifiable <Config>
                  , public JSON::Parsable <Config>
    {
        /**
         *  Default constructor.
         */
        Config() = default;
        Config(Config const&) = default;
        Config& operator=(Config const&) = default;

        /**
         *  Reads the config contents from a string.
         */
        Config(std::string const& json);

        /**
         *  Program wide unified line endings. These are only used for producing markup, not for parsing.
         *  The parser accepts all possible line ending combinations as valid. (CRLF, CR, LF)
         **/
		JSON::Base64Binary <char> lineEndings = "\n";

        /**
         *  A list of protocols to accept for implicit external links.
         *  Similar to $wgUrlProtocols, but // is a breaking parameter.
         *
         *  Example: ["bitcoin:", "ftp://", "http://", "https://", "urn:"]
         */
		std::vector <std::string> urlProtocols = {
            "bitcoin:",
            "ftp://",
            "ftps://",
            "geo:",
            "git://",
            "gopher://",
            "http://",
            "https://",
            "irc://",
            "ircs://",
            "magnet:",
            "mailto:",
            "mms://",
            "news:",
            "nntp://",
            "redis://",
            "sftp://",
            "sip:",
            "sips:",
            "sms:",
            "ssh://",
            "svn://",
            "tel:",
            "telnet://",
            "urn:",
            "worldwind://",
            "xmpp:"
        };
    };

    struct ConfigWriteable : public Config
    {
        friend Configuration;

    public:
        // no copy
        ConfigWriteable(ConfigWriteable const&) = delete;
        ConfigWriteable& operator=(ConfigWriteable const&) = delete;

        ~ConfigWriteable();

    private: // a user of this class shall not be able to copy it.
        ConfigWriteable(Config cfg, std::string fileName);
        std::string fileName_;
    };

    /**
     *  The configuration object is a program-wide config holder.
     *  It would be toxic to have multiple copies of it lying around which
     *  could cause inconsistencies. This is why this class is a Singleton.
     */
    class Configuration
    {
    public:
        ~Configuration();
        Configuration(Configuration const&) = delete;
        Configuration& operator=(Configuration const&) = delete;

        static Configuration& getInstance();

        /**
         *  All changes made to the config are NOT stored to the filesystem.
         */
        Config getReadOnly() const;

        /**
         *  All changes made to the ConfigWriteable instance are written to the filesystem
         *  after it runs out of scope.
         */
        ConfigWriteable getWriteable() const;

        /**
         *  Reloads the configuration file from the hard drive.
         */
        void reload();

    private:
        std::string getFileName() const;

    private:
        Configuration();
        Config cfg_;
    };
}

BOOST_FUSION_ADAPT_STRUCT(
	WikiMarkup::Config,
	(JSON::Base64Binary <char>, lineEndings)
	(std::vector <std::string>, urlProtocols)
)

BOOST_FUSION_ADAPT_STRUCT(
	WikiMarkup::ConfigWriteable,
	(JSON::Base64Binary <char>, lineEndings)
	(std::vector <std::string>, urlProtocols)
)

#endif // CONFIGURATION_HPP_INCLUDED
