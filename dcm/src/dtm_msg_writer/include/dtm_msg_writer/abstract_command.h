#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#ifndef EGOT_DCS_CTA2045_ABSTRACT_COMMAND_H
#define EGOT_DCS_CTA2045_ABSTRACT_COMMAND_H

#endif //EGOT_DCS_CTA2045_ABSTRACT_COMMAND_H

namespace dcm_src
{
namespace xml
{
/* -------------------------------------------------------------------
 * This is an individual command for a DER. It is represented
 * as a class because these commands are used as an abstracted
 * representation of instructions for the DER at multiple points
 * throughout the DCM architecture.
 * -------------------------------------------------------------------
 */
class InterfaceCommand {
    public:
        InterfaceCommand();
        InterfaceCommand(const InterfaceCommand &);
        InterfaceCommand(const boost::property_tree::ptree  & tree);
        InterfaceCommand & operator = (const InterfaceCommand &);
        InterfaceCommand & operator = (const boost::property_tree::ptree & tree);
        ~InterfaceCommand();
        std::string Str()
        {
            return ss_command_.str();
        }

    private:
        std::stringstream ss_command_;
        boost::property_tree::ptree tree_;
};


}//namespace xml
}//namespace dcm_src