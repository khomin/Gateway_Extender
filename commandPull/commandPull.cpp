#include "commandPull.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

namespace commandPull
{
    CommandPull::CommandPull() {
        this->commandHandler = std::make_shared<commandHandler::CommandHandler>();
    }
    
    CommandPull::~CommandPull() {}

    std::string CommandPull::getStatus() const {

    }

    std::string CommandPull::getStatisctics() const {

    }

    bool CommandPull::updateConfig(std::string & config) {

    }

    std::pair<bool, std::string> CommandPull::setData(std::string &data)
    {
        std::pair<bool, std::string> res = std::make_pair<bool, std::string>(false, " -error comamnd");
        Document document;
        try
        {
            document.Parse(data.c_str());
            if (document.GetParseError() == kParseErrorNone)
            {
                Value &commandDoc = document["type"];
                if (std::string("gatewayExtender").compare(commandDoc.GetString()) == 0)
                {
                    commandDoc = document["version"];
                    if (std::string("0.0").compare(commandDoc.GetString()) == 0)
                    {
                        commandDoc = document["operation"];
                        // operations
                        Document jsonExportDoc;
                        jsonExportDoc.SetObject();
                        Value t_value;
                        if (std::string("ping").compare(commandDoc.GetString()) == 0)
                        {
                            Document::AllocatorType &a = jsonExportDoc.GetAllocator();
                            jsonExportDoc.SetObject().AddMember("ping", "normal", a);
                            rapidjson::StringBuffer buffer;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                            jsonExportDoc.Accept(writer);
                            std::string json = buffer.GetString();
                            res.second = json;
                            res.first = true;
                        }
                        else if (std::string("setconfig").compare(commandDoc.GetString()) == 0)
                        {
                            Document::AllocatorType &a = jsonExportDoc.GetAllocator();
                            jsonExportDoc.SetObject().AddMember("setconfig", "normal", a);
                            rapidjson::StringBuffer buffer;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                            jsonExportDoc.Accept(writer);
                            std::string json = buffer.GetString();
                            res.second = json;
                            res.first = true;
                        }
                        else if (std::string("getStatus").compare(commandDoc.GetString()) == 0)
                        {
                            Document::AllocatorType &a = jsonExportDoc.GetAllocator();
                            jsonExportDoc.SetObject().AddMember("setconfig", "normal", a);
                            rapidjson::StringBuffer buffer;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                            jsonExportDoc.Accept(writer);
                            std::string json = buffer.GetString();
                            res.second = json;
                            res.first = true;
                        }
                        else if (std::string("getStatistics").compare(commandDoc.GetString()) == 0)
                        {
                            Document::AllocatorType &a = jsonExportDoc.GetAllocator();
                            jsonExportDoc.SetObject().AddMember("setconfig", "normal", a);
                            rapidjson::StringBuffer buffer;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                            jsonExportDoc.Accept(writer);
                            std::string json = buffer.GetString();
                            res.second = json;
                            res.first = true;
                        }
                    }
                }
            }
        }
        catch (std::exception ex) {
            std::cout << "ex: " << ex.what();
        }
        return res;
    }
    } // namespace commandPull

    // // d.Parse(json);

    // // 2. Modify it by DOM.

    // Value yy;
    // yy.SetString()
    // Value& s = d["stars"];
    // s.SetInt(s.GetInt() + 1);

    // // 3. Stringify the DOM
    // StringBuffer buffer;
    // Writer<StringBuffer> writer(buffer);
    // d.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    // std::cout << buffer.GetString() << std::endl;