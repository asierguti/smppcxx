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
#ifndef __SMPP_SUBMIT_SM_RESP_HPP__
#define __SMPP_SUBMIT_SM_RESP_HPP__

/// @file submit_sm_resp.hpp
/// @brief An SMPP submit_sm_resp PDU.

#include "aux_types.hpp"
#include "header.hpp"

namespace Smpp {

    /// @class SubmitSmResp
    /// @brief Definition of an SMPP submit_sm_resp, derived from a Response.
    class SubmitSmResp : public Response {
        MessageId message_id_;

        Smpp::Buffer buff_;

      public:
        /// submit_sm_resp minimum length in octets.
        const static int MinLength = 17;

        /// @brief Default constructor.
        SubmitSmResp();

        /// @brief Constructor requiring all mandatory parameters.
        SubmitSmResp(
                const CommandStatus& commandStatus,
                const SequenceNumber& sequenceNumber,
                MessageId&& messageId);

        /// @brief Construct from a buffer.
        SubmitSmResp(const Smpp::Uint8* b);

        /// @brief Destructor - does nothing.
        ~SubmitSmResp() = default;

        //
        // Mutating
        //

        /// @brief Sets the message id.
        /// @param p The message id.
        void message_id(const MessageId& p) {
            auto diff = p.length() - message_id_.length();
            message_id_ = p;
            Header::update_length(diff);
        }

        /// @brief Sets the message id.
        /// @param p The message id.
        void message_id(const Smpp::Char* p) {
            auto diff = strlen(p) - message_id_.length();
            message_id_ = p;
            Header::update_length(diff);
        }

        //
        // Accessing
        //

        /// @brief Accesses the message id.
        /// @return The message id.
        const MessageId& message_id() const { return message_id_; }

        /// @brief Serialize the PDU.
        /// @note The length is taken from the command_length().
        /// @return The PDU as an octet array, suitable for outputting.
        const Smpp::Uint8* encode();

        /// @brief Populates the PDU from an array of octets.
        /// @param buff containing PDU as octet array.
        void decode(const Smpp::Uint8* buff);
    };

} // namespace Smpp

#endif

