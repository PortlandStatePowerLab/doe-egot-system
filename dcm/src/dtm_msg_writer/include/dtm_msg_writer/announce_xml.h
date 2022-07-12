#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

//
// Created by Whitman on 3/25/2021.
//

#ifndef EGOT_DCS_CTA2045_ANNOUNCE_XML_H
#define EGOT_DCS_CTA2045_ANNOUNCE_XML_H



namespace dcm
{
namespace xml
{
/* -------------------------------------------------------------------
 * This class creates xml strings to be sent to the DTM
 * via an http POST. The xml strings are notifications
 * of the CTA-2045 commands that are being sent to the DER.
 * -------------------------------------------------------------------
 */
const std::string testing_file_name = "test_file.xml";
const std::string GENERIC = "unknown";
const std::string MSG_LOG_PATH = "../../msg_logs/dtm_messages_testing.xml";

class XMLCommandAdapter
{
    public:
        XMLCommandAdapter() : xml_notification_("NO DATA"), test_file_name_(testing_file_name), saved_("unknown")
        {}
        XMLCommandAdapter(boost::property_tree::ptree& t) : xml_notification_("NO DATA"), test_file_name_(testing_file_name), saved_("unknown"),
                                                            tree_(t)
        {}
        ~XMLCommandAdapter();
        void GenerateTestFile();
        void GenerateNamedTestFile(std::string src);
        void ReadTestFile();
        void AppendTreeToTestLog(std::string log_path);
        void OutputTreeToTerminal();
        void OutputTreeToTerminal(boost::property_tree::ptree & src_tree);
        void Load();
        void Shed();
        void MakeCommand(std::string type);
        std::string ReturnCustomCommand(const std::string& to, const std::string& from, const std::string& type, 
                                        const std::string& start, const std::string& duration, const std::string& content);
        std::string ReturnCustomGSPNotify(const std::string& to, const std::string& from, const std::string& type, const std::string& target,
                                        const std::string& body);
        std::string WriteMsg(const std::string& from, const std::string& to, const std::string& type, const std::string& target,
                                        const std::string& body);
        std::string ReturnCommandAsStr()
        {
            std::stringstream ss;
            boost::property_tree::write_xml(ss, tree_, boost::property_tree::xml_writer_make_settings<std::string>(' ', 4));
            return ss.str();
        }
        std::string ReturnCommandAsStr(boost::property_tree::ptree& prop)
        {
            std::stringstream ss;
            boost::property_tree::write_xml(ss, prop, boost::property_tree::xml_writer_make_settings<std::string>(' ', 4));
            return ss.str();
        }

    private:
        std::string xml_notification_;
        std::string test_file_name_;
        std::string saved_;
        boost::property_tree::ptree tree_;
};

}//namespace xml
}// namespace dcm

#endif //EGOT_DCS_CTA2045_ANNOUNCE_XML_H