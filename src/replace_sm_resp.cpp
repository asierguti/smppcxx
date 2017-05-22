/*
 * SMPP Encoder/Decoder
 * Copyright (C) 2006 redtaza@users.sourceforge.net
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
/// @file replace_sm_resp.cpp
/// @brief Declares a replace_sm_resp

#include "replace_sm_resp.hpp"

/// @brief Default constructor.
/// note Sets all values to their defaults.
Smpp::ReplaceSmResp::ReplaceSmResp() :
    Response(CommandLength(MinLength),
              CommandId(CommandId::ReplaceSmResp),
              CommandStatus(CommandStatus::ESME_ROK),
              SequenceNumber::Min)
{
}

/// @brief Constructor that requires values for all the mandatory parameters.
/// @param commandStatus The command status to use.
/// @param sequenceNumber The sequence number to use.
Smpp::ReplaceSmResp::ReplaceSmResp(const CommandStatus& commandStatus,
                                    const SequenceNumber& sequenceNumber) :
    Response(CommandLength(MinLength), 
              CommandId(CommandId::ReplaceSmResp), 
              commandStatus,
              sequenceNumber)
{
}

/// @brief Construct from a buffer.
/// @param b The buffer (octet array).
Smpp::ReplaceSmResp::ReplaceSmResp(const Smpp::Uint8* b) :
    Response(CommandLength(MinLength),
              CommandId(CommandId::ReplaceSmResp),
              CommandStatus(CommandStatus::ESME_ROK),
              1)
{
    decode(b);
}

Smpp::ReplaceSmResp::~ReplaceSmResp()
{
}

/// @brief Encode the message into an octet array.
/// @return Pointer to the encoded message.
/// @note The Buffer length is the command_length.
const Smpp::Uint8*
Smpp::ReplaceSmResp::encode()
{
    buff_.reset(Header::command_length());
    Response::encode(buff_); // insert the header first
    Header::encode_tlvs(buff_);
    return buff_.get();
}

/// @brief Decode the message from an octet array.
/// @param buff The octet array to decode.
/// @note The octet array maybe the data read from a socket.
void
Smpp::ReplaceSmResp::decode(const Smpp::Uint8* buff)
{
    Response::decode(buff);

    Smpp::Uint32 len = Response::command_length();
    Smpp::Uint32 offset = 16;
    const char* err = "Bad length in replace_sm_resp";
    if(len < offset)
        throw Error(err);
 
    Header::decode_tlvs(buff + offset, len - offset);
}

