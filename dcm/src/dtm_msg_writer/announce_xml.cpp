#include "include/dtm_msg_writer/announce_xml.h"
//
// Created by Whitman on 3/25/2021.
//
using std::cout;
using std::endl;
using std::string;
namespace pt = boost::property_tree;

namespace dcm //in dcm_src namespace, covering code meant to run on dcm
{
namespace xml
{
//----------------------------------------------------------------------------------------------------------
//                         Implementation of XMLCommandAdapter Class
//----------------------------------------------------------------------------------------------------------
XMLCommandAdapter::~XMLCommandAdapter()
{}

void XMLCommandAdapter::GenerateTestFile()
{
    cout << "Generate Test File" << endl;
    cout << "Test file name: " << test_file_name_ << endl;

    tree_.put("debug.filename", test_file_name_);
    tree_.put("debug.level", 3);
    tree_.add("debug.modules.module", "there");

    pt::write_xml(test_file_name_, tree_);
}
void XMLCommandAdapter::GenerateNamedTestFile(string src)
{
    cout << "Generate Named Testfile" << endl;
    cout << "Test file name: " << src << endl;

    tree_.put("CREATED.date", "4/1/2021");
    pt::write_xml(src, tree_);
}

void XMLCommandAdapter::ReadTestFile()
{
    cout<<"read"<<endl;
    std::stringstream string_xml; //stringstream
    pt::read_xml(test_file_name_, tree_); //read

    pt::write_xml(string_xml, tree_); //write to stream
    cout << string_xml.str() <<endl; //output string version of stream
     /*
    std::ifstream f("test_file.xml");
    std::stringstream buffer;
    buffer << f.rdbuf();
    cout << "string: " << buffer.str() <<endl;
     */
}
void XMLCommandAdapter::AppendTreeToTestLog(std::string log_path)
{
    cout << "Append Tree" << endl;
    std::stringstream ss;
    pt::ptree file_tree;

    pt::read_xml(log_path, file_tree, pt::xml_parser::trim_whitespace); //read in from xml file
    OutputTreeToTerminal(file_tree); //print file
    file_tree.push_back( std::make_pair("message_log", tree_ ) );
   // file_tree.put_child("message_log", tree_ ); //add tree_ to read-in tree

    cout << "Now Re-display" << endl;
    OutputTreeToTerminal(file_tree); //redisplay in terminal
    //pt::write_xml(log_path, file_tree); //write modified tree to file
    pt::write_xml(log_path, file_tree, std::locale(), pt::xml_writer_make_settings<std::string>(' ', 4)); //<- this works to format the tree nicely
    //the ^ std::locale() is necessary when writing to a file rather then a stream object, for reasons I don't understand

    /*
    std::stringstream ss; //string stream
    std::ofstream file(log_path, std::ios::app); //open file stream in append mode
    pt::write_xml(ss, tree_); //write xml tree to string stream
    file << endl << endl; //add line breaks after prev entry
    file << ss.str(); //write stringstream (containing xml tree) to file
    file.close(); //close file
     */

}
void XMLCommandAdapter::OutputTreeToTerminal()
{
    std::stringstream ss;
    //pt::write_xml(ss, tree_); //write tree to stringstream
    pt::write_xml(ss, tree_, pt::xml_writer_make_settings<std::string>(' ', 4)); //<- this works to format the tree nicely
    cout << "TREE: " << endl << endl << ss.str() << endl << endl; //output string created by stringstream
}
void XMLCommandAdapter::OutputTreeToTerminal(pt::ptree & src_tree)
{
    std::stringstream ss;
    //pt::write_xml(ss, tree_); //write tree to stringstream
    pt::write_xml(ss, src_tree, pt::xml_writer_make_settings<std::string>(' ', 4)); //<- this works to format the tree nicely
    cout << "TREE: " << endl << endl << ss.str() << endl << endl; //output string created by stringstream
}
void XMLCommandAdapter::Load()
{
    MakeCommand("LOAD");
}
void XMLCommandAdapter::Shed()
{
    MakeCommand("SHED");
}
void XMLCommandAdapter::MakeCommand(string type)
{
    std::time_t start_time = std::time(0);
    string str_time = ctime(&start_time);
    //std::tm* gmtm = gmtime(&t);
    //std::string str_time = std::asctime(gmtm);
    tree_.put("message.from", "DCM");
    tree_.put("message.to", "DER");
    tree_.put("message.content.command.type", type);
    tree_.put("message.content.command.start", start_time);
    //tree_.put("message.content.command.duration", dur);
    tree_.put("message.content.expect_response", 1);
    tree_.put("message.logged", std::time(0));
}
std::string XMLCommandAdapter::ReturnCustomCommand(const std::string& to, const std::string& from, const std::string& type, 
                                                    const std::string& start, const std::string& duration, const std::string& content)
{
    boost::property_tree::ptree t;

    std::time_t start_time = std::time(0);
    string str_time = ctime(&start_time);
    //std::tm* gmtm = gmtime(&t);
    //std::string str_time = std::asctime(gmtm);
    std::string content_path = "message.content." + content; 
    std::string type_path = content_path + ".type";
    std::string start_path = content_path + ".start";
    std::string duration_path = content_path + ".duration";
    
    t.put("message.from", from);
    t.put("message.to", to);
    t.put(type_path, type);
    if (start != "na")
    {
        t.put(start_path, start);
    }
    //t.put("message.content.command.start", start_time);
    if (duration != "na")
    {
        t.put(duration_path, duration);
    }
    //t.put("message.content.command.duration", duration);
    //t.put("message.content.expect_response", 1);
    t.put("message.DCM_timestamp", std::time(0));
    return ReturnCommandAsStr(t);
}

std::string XMLCommandAdapter::ReturnCustomGSPNotify(const std::string& to, const std::string& from, const std::string& type, const std::string& target,
                                                    const std::string& body)
{
    boost::property_tree::ptree t, st;
    std::stringstream ss;
    ss << body;
    boost::property_tree::xml_parser::read_xml(ss, st, boost::property_tree::xml_parser::trim_whitespace);

    std::time_t start_time = std::time(0);
    string str_time = ctime(&start_time);
    //std::tm* gmtm = gmtime(&t);
    //std::string str_time = std::asctime(gmtm);
    std::string type_path = "message.content." + type; 
    std::string target_path = type_path + ".target";
    std::string body_path = type_path + ".body";
    
    
    t.put("message.from", from);
    t.put("message.to", to);
    
    if (target != "na")
        t.put(target_path, target);
    t.add_child(body_path, st);
    
    //t.put("message.content.command.duration", duration);
    //t.put("message.content.expect_response", 1);
    t.put("message.DCM_timestamp", std::time(0));

    std::cout << "Now outputing custom msg tree to terminal: " << std::endl;
    OutputTreeToTerminal(t);
    std::cout << "----------------Done outputting msg tree----------- " << std::endl;
    return ReturnCommandAsStr(t);
}

std::string XMLCommandAdapter::WriteMsg(const std::string& from, const std::string& to, const std::string& type, 
                                        const std::string& target, const std::string& body)
{
    boost::property_tree::ptree t, st;
    std::stringstream ss;

    std::time_t start_time = std::time(0);
    string str_time = ctime(&start_time);
    //std::tm* gmtm = gmtime(&t);
    //std::string str_time = std::asctime(gmtm);
    std::string type_path = "message.content." + type; 
    std::string target_path = type_path + ".target";
    std::string body_path = type_path + ".body";
    
    t.put("message.from", from);
    t.put("message.to", to);
    
    if (target != "na")
        t.put(target_path, target);
    if (body != "na")
    {
        std::string xml_syntax = "</";
        std::size_t check_for_xml = body.find(xml_syntax); //check for present of xml syntax as substring
        if (check_for_xml != std::string::npos) //if body is xml encoded as str
        {
            ss << body; //save body as string stream for xml encoding
            boost::property_tree::xml_parser::read_xml(ss, st, boost::property_tree::xml_parser::trim_whitespace); //convert body to xml tree
            t.add_child(body_path, st); //add body as xml subtree
        }
        else
        {
            t.put(body_path, body); //add body as plain text
        }
    }
    
    //t.put("message.content.command.duration", duration);
    //t.put("message.content.expect_response", 1);
    t.put("message.DCM_timestamp", std::time(0));

    std::cout << "Now outputing custom msg tree to terminal: " << std::endl;
    OutputTreeToTerminal(t);
    std::cout << "----------------Done outputting msg tree----------- " << std::endl;
    return ReturnCommandAsStr(t);
}

}//namespace xml
}//namespace dcm

