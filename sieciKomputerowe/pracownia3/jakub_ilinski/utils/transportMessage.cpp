// Jakub Iliński 346796
#include "transportMessage.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace TransportMessage {
namespace {

constexpr std::string_view DataPrefix = "DATA ";
constexpr std::uint32_t MaxLength = 1000;

struct ParsedHeader {
    std::uint32_t start;
    std::uint16_t length;
    std::size_t payloadStart;
};

bool consumeChar(const std::string_view input, std::size_t& pos, const char expected) {
    if(pos >= input.size() or input[pos] != expected)
        return false;

    pos++;
    return true;
}

bool isValidDataLength(const std::uint32_t length) {
    return length >= 1 and length <= MaxLength;
}

bool parseUint32(const std::string_view input, std::size_t& pos, std::uint32_t& value) {
    if(pos >= input.size() or input[pos] < '0' or input[pos] > '9') {
        return false;
    }

    std::uint64_t parsed = 0;
    while(pos < input.size() and input[pos] >= '0' and input[pos] <= '9') {
        parsed = parsed * 10 + static_cast<std::uint64_t>(input[pos] - '0');
        if(parsed > std::numeric_limits<std::uint32_t>::max())
            return false;
        pos++;
    }

    value = parsed;
    return true;
}

std::optional<std::pair<std::string_view, std::size_t>> trySplitHeader(const std::vector<std::uint8_t>& datagram) {
    const auto newlineIt = std::find(datagram.begin(), datagram.end(), '\n');
    if(newlineIt == datagram.end()) {
        return std::nullopt;
    }

    const std::size_t headerSize = newlineIt - datagram.begin();
    return std::make_optional(std::make_pair(
        std::string_view(reinterpret_cast<const char*>(datagram.data()), headerSize),
        headerSize + 1
    ));
}

std::optional<ParsedHeader> tryParseHeader(const std::vector<std::uint8_t>& datagram) {
    const auto splitHeader = trySplitHeader(datagram);
    if(!splitHeader)
        return std::nullopt;

    const std::string_view header = splitHeader->first;
    const std::size_t payloadStart = splitHeader->second;
    if(!header.starts_with(DataPrefix)) {
        return std::nullopt;
    }

    std::size_t pos = DataPrefix.size();
    std::uint32_t start = 0;
    std::uint32_t length = 0;

    if(!parseUint32(header, pos, start) or !consumeChar(header, pos, ' ') or
        !parseUint32(header, pos, length) or pos != header.size()) {
        return std::nullopt;
    }

    if(!isValidDataLength(length)) {
        return std::nullopt;
    }

    return ParsedHeader{start, static_cast<std::uint16_t>(length), payloadStart};
}

std::optional<std::vector<std::uint8_t>> tryExtractPayload(
    const std::vector<std::uint8_t>& datagram,
    const std::size_t payloadStart,
    const std::uint16_t expectedLength) {

    if(payloadStart > datagram.size() or expectedLength != datagram.size() - payloadStart) {
        return std::nullopt;
    }

    return std::vector<std::uint8_t>(
        datagram.begin() + payloadStart,
        datagram.end()
    );
}
}

std::vector<std::uint8_t> buildGetRequest(const Chunk& chunk) {
    const std::string request = "GET " + std::to_string(chunk.start) + " " + std::to_string(chunk.length) + "\n";
    return std::vector<std::uint8_t>(request.begin(), request.end());
}

std::optional<std::pair<Chunk, std::vector<std::uint8_t>>> tryParseDataResponse(
    const std::vector<std::uint8_t>& datagram) {

    const auto parsedHeader = tryParseHeader(datagram);
    if(!parsedHeader) {
        return std::nullopt;
    }

    const auto payload = tryExtractPayload(datagram, parsedHeader->payloadStart, parsedHeader->length);
    if(!payload) {
        return std::nullopt;
    }

    return std::make_optional(std::make_pair(
        Chunk(parsedHeader->start, parsedHeader->length),
        std::move(*payload)
    ));
}
}