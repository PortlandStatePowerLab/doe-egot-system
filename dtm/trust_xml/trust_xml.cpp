#include "include/trust_xml/trust_xml.hpp"
#include <boost/property_tree/xml_parser.hpp>

namespace pt = boost::property_tree;

namespace dtm
{
    boost::property_tree::ptree Treeify(const Message& message)
    {
        pt::ptree tree;
        tree.put("message.to", message.to);
        tree.put("message.from", message.from);
        tree.put("message.command", message.command);
        tree.put("message.timestamp", message.timestamp);

        for (const auto& arg : message.args)
        {
            tree.put("message.args.key", arg.first);
            tree.put("message.args.value", arg.second);
        }

        return tree;
    };

    std::string Stringify(const boost::property_tree::ptree &pt)
    {
        // utility function to help translate strings to/from objects
        std::stringstream ss;
        boost::property_tree::xml_parser::write_xml(ss, pt);
        return ss.str();
    };
}