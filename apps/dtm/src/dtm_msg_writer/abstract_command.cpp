#include <iostream>
#include "include/dtm_msg_writer/abstract_command.h"

//namespacing for this file

using std::cout;
using std::endl;
using std::string;
namespace pt = boost::property_tree;

namespace dcm_src
{
namespace xml
{
/* --------------------------------------------------------------------
 *            Implementation of InterfaceCommand
 * --------------------------------------------------------------------
 */
InterfaceCommand::InterfaceCommand()
{}
InterfaceCommand::InterfaceCommand(const InterfaceCommand & src)
{

}
InterfaceCommand::InterfaceCommand(const boost::property_tree::ptree  & tree)
{

}
InterfaceCommand::~InterfaceCommand()
{
    cout<<"InterfaceCommand DESTRUCTOR"<<endl;
}
InterfaceCommand & InterfaceCommand::operator = (const InterfaceCommand & src)
{

}
}//namespace xml
}//namespace dcm_src

