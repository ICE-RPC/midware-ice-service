
#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

class JSON {
public:

    static bool Parse(rapidjson::Document& doc, const std::string& data) {
        if(doc.Parse((char*)data.c_str()).HasParseError())
            return false;
        return true;
    }
    static bool Parse(rapidjson::Document& doc, const char* val, size_t vlen) {
        if(doc.Parse(val, vlen).HasParseError())
            return false;
        return true;
    }
    static bool ParseInsitu(rapidjson::Document& doc, const std::string& data) {
        if(doc.ParseInsitu((char*)data.c_str()).HasParseError())
            return false;
        return true;
    }
     
    static bool Exist(rapidjson::Document& doc, const std::string& key) {
        return doc.HasMember(key.c_str());
    }

    static bool Exist(rapidjson::Value& doc, const std::string& key) {
        return doc.HasMember(key.c_str());
    }

    static std::string GetString(rapidjson::Value& doc, const std::string& def) {
        if(doc.IsString())
            return doc.GetString();
        return def;
    }

    static std::string GetString(const rapidjson::Document& doc, const std::string& key, const std::string& def) {
        if(!doc.IsObject() || !doc.HasMember(key.c_str()))
            return def;
        if(doc[key.c_str()].IsString())
            return doc[key.c_str()].GetString();
        return def;
    }
    static std::string GetString(const rapidjson::Value& doc, const std::string& key, const std::string& def) {
        if(!doc.HasMember(key.c_str())) 
            return def;
        if(doc[key.c_str()].IsString())
            return doc[key.c_str()].GetString();
        return def;
    }
   
    static int GetInt(const rapidjson::Document& doc, const std::string& key, const int& def=0) {
        if(!doc.HasMember(key.c_str()))
            return def;
        if(doc[key.c_str()].IsInt())
            return doc[key.c_str()].GetInt();
        if(doc[key.c_str()].IsUint())
            return doc[key.c_str()].GetUint();
        if(doc[key.c_str()].IsDouble())
            return (int)doc[key.c_str()].GetDouble();
        if(doc[key.c_str()].IsFloat())
            return (int)doc[key.c_str()].GetFloat();
        return def;
    }
    static int GetInt(const rapidjson::Value& doc, const std::string& key, const int& def=0) {
        if(!doc.HasMember(key.c_str()))
            return def;
        if(doc[key.c_str()].IsInt())
            return doc[key.c_str()].GetInt();
        if(doc[key.c_str()].IsUint())
            return doc[key.c_str()].GetUint();
        if(doc[key.c_str()].IsDouble())
            return (int)doc[key.c_str()].GetDouble();
        if(doc[key.c_str()].IsFloat())
            return (int)doc[key.c_str()].GetFloat();
        return def;
    }
    static int GetInt(const rapidjson::Value& doc, const int& def=0) {
        if(doc.IsInt())
            return doc.GetInt();
        if(doc.IsUint())
            return doc.GetUint();
        if(doc.IsDouble())
            return (int)doc.GetDouble();
        if(doc.IsFloat())
            return (int)doc.GetFloat();
        return def;
    }
    static int64_t GetInt64(const rapidjson::Document& doc, const std::string& key, const int64_t& def=0) {
        if(!doc.HasMember(key.c_str()))
            return def;
        if(doc[key.c_str()].IsInt64())
            return doc[key.c_str()].GetInt64();
        if(doc[key.c_str()].IsUint64())
            return doc[key.c_str()].GetUint64();
        if(doc[key.c_str()].IsInt())
            return doc[key.c_str()].GetInt();
        if(doc[key.c_str()].IsUint())
            return doc[key.c_str()].GetUint();
        if(doc[key.c_str()].IsDouble())
            return (int64_t)doc[key.c_str()].GetDouble();
        if(doc[key.c_str()].IsFloat())
            return (int64_t)doc[key.c_str()].GetFloat();
        return def;
    }
    static int64_t GetInt64(const rapidjson::Value& doc, const std::string& key, const int64_t& def=0) {
        if(!doc.HasMember(key.c_str()))
            return def;
        if(doc[key.c_str()].IsInt64())
            return doc[key.c_str()].GetInt64();
        if(doc[key.c_str()].IsUint())
            return doc[key.c_str()].GetUint64();
        if(doc[key.c_str()].IsInt())
            return doc[key.c_str()].GetInt();
        if(doc[key.c_str()].IsUint())
            return doc[key.c_str()].GetUint();
        if(doc[key.c_str()].IsDouble())
            return (int64_t)doc[key.c_str()].GetDouble();
        if(doc[key.c_str()].IsFloat())
            return (int64_t)doc[key.c_str()].GetFloat();
        return def;
    }
    static int64_t GetInt64(const rapidjson::Value& val, const int64_t& def=0) {
        if(val.IsInt64())
            return val.GetInt64();
        if(val.IsUint())
            return val.GetUint64();
        if(val.IsInt())
            return val.GetInt();
        if(val.IsUint())
            return val.GetUint();
        if(val.IsDouble())
            return (int64_t)val.GetDouble();
        if(val.IsFloat())
            return (int64_t)val.GetFloat();
        return def;
    }
    static double GetDouble(const rapidjson::Value& val, const double& def=0) {
        if(val.IsInt64())
            return (double)val.GetInt64();
        if(val.IsUint())
            return (double)val.GetUint64();
        if(val.IsInt())
            return (double)val.GetInt();
        if(val.IsUint())
            return (double)val.GetUint();
        if(val.IsDouble())
            return val.GetDouble();
        if(val.IsFloat())
            return val.GetFloat();
        return def;
    }
    static double GetDouble(const rapidjson::Document& doc, const std::string& key, const double& def=0) {
        if(!doc.HasMember(key.c_str()))
            return def;
        if(doc[key.c_str()].IsDouble())
            return doc[key.c_str()].GetDouble();
        if(doc[key.c_str()].IsFloat())
            return doc[key.c_str()].GetFloat();
        if(doc[key.c_str()].IsInt())
            return (double)doc[key.c_str()].GetInt();
        if(doc[key.c_str()].IsUint())
            return (double)doc[key.c_str()].GetUint();
        if(doc[key.c_str()].IsInt64())
            return (double)doc[key.c_str()].GetInt64();
        if(doc[key.c_str()].IsUint64())
            return (double)doc[key.c_str()].GetUint64();
        return def;
    }

    static double GetDouble(const rapidjson::Value& doc, const std::string& key, const double& def=0) {
        if(!doc.HasMember(key.c_str()))
            return def;
        if(doc[key.c_str()].IsDouble())
            return doc[key.c_str()].GetDouble();
        if(doc[key.c_str()].IsFloat())
            return doc[key.c_str()].GetFloat();
        if(doc[key.c_str()].IsInt())
            return (double)doc[key.c_str()].GetInt();
        if(doc[key.c_str()].IsUint())
            return (double)doc[key.c_str()].GetUint();
        if(doc[key.c_str()].IsInt64())
            return (double)doc[key.c_str()].GetInt64();
        if(doc[key.c_str()].IsUint64())
            return (double)doc[key.c_str()].GetUint64();

        return def;
    }

    static bool GetBool(const rapidjson::Document& doc, const std::string& key, const bool& def=false) {
        if(!doc.HasMember(key.c_str()))
            return def;
        if(doc[key.c_str()].IsBool())
            return doc[key.c_str()].GetBool();
        if(doc[key.c_str()].IsInt())
            return (bool)doc[key.c_str()].GetInt();
        if(doc[key.c_str()].IsUint())
            return (bool)doc[key.c_str()].GetUint();
        return def;
    }
    static int GetBool(const rapidjson::Value& doc, const std::string& key, const bool& def=false) {
        if(!doc.HasMember(key.c_str()))
            return def;
        if(doc[key.c_str()].IsBool())
            return doc[key.c_str()].GetBool();
        if(doc[key.c_str()].IsInt())
            return (bool)doc[key.c_str()].GetInt();
        if(doc[key.c_str()].IsUint())
            return (bool)doc[key.c_str()].GetUint();
        return def;
    }

    static void AddMember(rapidjson::Value& doc, const std::string& key, const std::string& value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        rapidjson::Value rvalue(value.data(), value.size(), allocator);
        doc.AddMember(rkey, rvalue, allocator);
    }

    static void AddMember(rapidjson::Value& doc, const std::string& key, int value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }
    static void AddMember(rapidjson::Value& doc, const std::string& key, unsigned int value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }
    static void AddMember(rapidjson::Value& doc, const std::string& key, int64_t value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }
    static void AddMember(rapidjson::Value& doc, const std::string& key, size_t value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }
    static void AddMember(rapidjson::Value& doc, const std::string& key, double value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }
    static void AddMember(rapidjson::Value& doc, const std::string& key, rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }
    static void AddMember(rapidjson::Value& doc, const std::string& key, bool value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }


    static void AddMember(rapidjson::Document& doc, const std::string& key, const std::string& value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        rapidjson::Value rvalue(value.data(), value.size(), allocator);
        doc.AddMember(rkey, rvalue, allocator);
    }
    static void AddMember(rapidjson::Document& doc, const std::string& key, int value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }

    static void AddMember(rapidjson::Document& doc, const std::string& key, unsigned int value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }
    static void AddMember(rapidjson::Document& doc, const std::string& key, rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }

    static void AddMember(rapidjson::Document& doc, const std::string& key, int64_t value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }

    static void AddMember(rapidjson::Document& doc, const std::string& key, size_t value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }
    static void AddMember(rapidjson::Document& doc, const std::string& key, double value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }
    static void AddMember(rapidjson::Document& doc, const std::string& key, bool value, rapidjson::Document::AllocatorType& allocator) {
        rapidjson::Value rkey(key.data(), key.size(), allocator);
        doc.AddMember(rkey, value, allocator);
    }


    static void RemoveMember(rapidjson::Value& doc, const std::string& key) {
        doc.RemoveMember(key.c_str());
    }
    static void RemoveMember(rapidjson::Document& doc, const std::string& key) {
        doc.RemoveMember(key.c_str());
    }
 
    static std::string RespSuccess(int code, const std::string& message) {

        rapidjson::Document document{ rapidjson::kObjectType };
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value empty(rapidjson::kArrayType);

        document.AddMember("code", code, allocator);
        JSON::AddMember(document, "message", message, allocator);
        document.AddMember("data", empty, allocator);

        rapidjson::StringBuffer rsbuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(rsbuf);
        document.Accept(writer);
        return rsbuf.GetString();
    }
    static std::string RespError(int code, const std::string& message) {

        rapidjson::Document document{ rapidjson::kObjectType };
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        //rapidjson::Value empty(rapidjson::kArrayType);

        document.AddMember("code", code, allocator);
        JSON::AddMember(document, "message", message, allocator);
        //document.AddMember("data", empty, allocator);

        rapidjson::StringBuffer rsbuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(rsbuf);
        document.Accept(writer);
        return rsbuf.GetString();
    }

};

