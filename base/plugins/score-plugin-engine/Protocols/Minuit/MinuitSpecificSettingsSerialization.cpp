// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "MinuitSpecificSettings.hpp"

#include <score/serialization/DataStreamVisitor.hpp>
#include <score/serialization/JSONVisitor.hpp>

#include <QJsonObject>
#include <QJsonValue>
#include <QString>

template <>
void DataStreamReader::read(const Protocols::MinuitSpecificSettings& n)
{
  m_stream << n.inputPort << n.outputPort << n.host << n.localName;
  insertDelimiter();
}

template <>
void DataStreamWriter::write(Protocols::MinuitSpecificSettings& n)
{
  m_stream >> n.inputPort >> n.outputPort >> n.host >> n.localName;
  checkDelimiter();
}

template <>
void JSONObjectReader::read(const Protocols::MinuitSpecificSettings& n)
{
  obj["InPort"] = n.inputPort;
  obj["OutPort"] = n.outputPort;
  obj["Host"] = n.host;
  obj["LocalName"] = n.localName;
}

template <>
void JSONObjectWriter::write(Protocols::MinuitSpecificSettings& n)
{
  n.inputPort = obj["InPort"].toInt();
  n.outputPort = obj["OutPort"].toInt();
  n.host = obj["Host"].toString();
  n.localName = obj["LocalName"].toString();
}
