#include "commandPull.h"
#include "interfaces/interfaceAbstract.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

namespace commandPull
{
    CommandPull::CommandPull() {
    }
    
    CommandPull::~CommandPull() {}

    std::string CommandPull::getStatus() const {

    }

    std::string CommandPull::getStatisctics() const {

    }

    std::pair<bool, std::string> CommandPull::setData(std::string &data)
    {
        std::pair<bool, std::string> res = std::make_pair<bool, std::string>(false, " -error comamnd");
        Document document;
        try {
            document.Parse(data.c_str());
            if (document.GetParseError() == kParseErrorNone) {
                Value &commandDoc = document["type"];
                if (std::string("gatewayExtender").compare(commandDoc.GetString()) == 0) {
                    Document jsonExportDoc;
                    Document::AllocatorType &a = jsonExportDoc.GetAllocator();
                    commandDoc = document["version"];
                    if (std::string("0.0").compare(commandDoc.GetString()) == 0) {
                        commandDoc = document["operation"];
                        // operations
                        if (std::string("ping").compare(commandDoc.GetString()) == 0) {
                            jsonExportDoc.SetObject().AddMember("ping", "normal", a);
                            rapidjson::StringBuffer buffer;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                            jsonExportDoc.Accept(writer);
                            std::string json = buffer.GetString();
                            res.second = json;
                            res.first = true;
                        } else if (std::string("setconfig").compare(commandDoc.GetString()) == 0) {
                            Value portArray = document["port"].GetArray();
                            bool isSetConfigNormal = false;
                            for(auto portIter = portArray.Begin(); portIter != portArray.End(); portIter++) {
                                InterfaceAbstract::sInterfaceProperty tIoProperty;
                                Value obj = portIter->GetObject();
                                Value tPortObj = obj["port_1"].GetObject();
                                Value tProperty = tPortObj["property"].GetObject();
                                tIoProperty.portName = tProperty["name"].GetString();
                                tIoProperty.portType = tProperty["type"].GetString();
                                tIoProperty.portBaudrate = tProperty["baudrate"].GetString();
                                isSetConfigNormal = true;
                                // create command hander and interface
                                commandHandler.reset();
                                commandHandler = std::make_shared<commandHandler::CommandHandler>(tIoProperty);
                            }
                            if(isSetConfigNormal) {
                                jsonExportDoc.SetObject().AddMember("setconfig", "normal", a);
                                rapidjson::StringBuffer buffer;
                                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                                jsonExportDoc.Accept(writer);
                                std::string json = buffer.GetString();
                                res.second = json;
                                res.first = true;
                            }
                        } else if (std::string("transmitData").compare(commandDoc.GetString()) == 0) {
                            Value portArray = document["port"].GetArray();
                            if(commandHandler.get() != nullptr) {
                                bool isSetConfigNormal = false;
                                for(auto portIter = portArray.Begin(); portIter != portArray.End(); portIter++) {
                                    std::vector<uint8_t>packetData;
                                    Value obj = portIter->GetObject();
                                    Value tPortObj = obj["port_1"].GetObject();
                                    Value packetObj = tPortObj["packet"].GetObject();
                                    std::string packetHeader = packetObj["header"].GetString();
                                    Value tRawDataArray = packetObj["data"].GetArray();
                                    for(auto rawBytesPacketIter = tRawDataArray.Begin(); rawBytesPacketIter != tRawDataArray.End(); rawBytesPacketIter++) {
                                        std::string hexByte = rawBytesPacketIter->GetString();
                                        packetData.push_back((uint8_t)std::stoul(hexByte, 0, 16));
                                        isSetConfigNormal = true;
                                    }
                                    commandHandler->addTranssmitedBytes(packetData);
                                }
                                if(isSetConfigNormal) {
                                    jsonExportDoc.SetObject().AddMember("transmitData", "normal", a);
                                    rapidjson::StringBuffer buffer;
                                    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                                    jsonExportDoc.Accept(writer);
                                    std::string json = buffer.GetString();
                                    res.second = json;
                                    res.first = true;
                                }
                            } else {
                                jsonExportDoc.SetObject().AddMember("transmitData", "conenction is closed", a);
                                rapidjson::StringBuffer buffer;
                                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                                jsonExportDoc.Accept(writer);
                                std::string json = buffer.GetString();
                                res.second = json;
                                res.first = true;
                            }
                        } else if (std::string("getStatus").compare(commandDoc.GetString()) == 0) {
                            Value messageReply;
                            if(commandHandler.get() == nullptr) {
                                messageReply.SetString("no configured");
                            } else {
                                messageReply.SetString(commandHandler->getStatusIo().c_str(), commandHandler->getStatusIo().length());
                            }
                            jsonExportDoc.SetObject().AddMember("getStatus", messageReply, a);
                            rapidjson::StringBuffer buffer;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                            jsonExportDoc.Accept(writer);
                            std::string json = buffer.GetString();
                            res.second = json;
                            res.first = true;
                        } else if (std::string("getStatistics").compare(commandDoc.GetString()) == 0) {
                            Value messageReply;
                            if(commandHandler.get() == nullptr) {
                                messageReply.SetString("no configured");
                            } else {
                                const std::string stats = commandHandler->getStatistics();
                                messageReply.SetString(stats.c_str(), stats.length());
                            }
                            jsonExportDoc.SetObject().AddMember("getStatistics", messageReply, a);
                            rapidjson::StringBuffer buffer;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                            jsonExportDoc.Accept(writer);
                            std::string json = buffer.GetString();
                            res.second = json;
                            res.first = true;
                        } else {
                            res.second = " -error";
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
    }