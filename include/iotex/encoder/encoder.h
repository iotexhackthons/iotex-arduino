#ifndef IOTEX_ENCODER_H
#define IOTEX_ENCODER_H

#include <stdint.h>
#include <stddef.h>
#include <string>
#include <vector>
#include "constants.h"
#include "result_codes.h"
#include "protobuf/pb_api.h"

namespace Iotex
{
    class Encoder
    {
        public:
            //Bech32
            ResultCode bech32_encodeHexString(const std::string &data, std::string &encodedData);
            ResultCode bech32_encode(const std::vector<uint8_t> data, std::string &encodedData);
            ResultCode bech32_convertBytesTo5Bit(const std::vector<uint8_t> &in, std::vector<uint8_t> &out);

            // Base64
            ResultCode base64_encode(const uint8_t *data, size_t size, char *out);

            // Protobuf
            /**
             * \return  The number of bytes encoded if out buffer is big enough
             *          -1 if outBuf is too small
             */
            int32_t protobuf_encodeTransfer(ResponseTypes::ActionCore_Transfer &transfer, uint8_t *out, size_t maxOutSize);

        private:
    };
}

// Declare global encoder
extern Iotex::Encoder encoder;

#endif