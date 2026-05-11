// Jakub Iliński 346796

#include <cerrno>
#include <limits>
#include <tuple>
#include <arpa/inet.h>

#include "utils/chunk.hpp"
#include "socket/udpSocket.hpp"
#include "utils/receiver.hpp"
#include "utils/transportMessage.hpp"

constexpr std::chrono::milliseconds pollTimeout(50);
constexpr std::size_t maxDatagramSize = 2048;

std::tuple<std::uint32_t, std::uint16_t, std::string, std::uint32_t> parseArguments(int argc, char* argv[]) {
    if(argc != 5) {
        throw std::invalid_argument("Error, you have to pass: transport <adres_IP> <port> <file_path> <file_size>");
    }

    // ip address
    const std::string serverIp = argv[1];
    in_addr parsedAddress{};
    if (inet_pton(AF_INET, serverIp.c_str(), &parsedAddress) != 1) {
        throw std::invalid_argument("Error: invalid IP address");
    }

    // port
    char* portEnd = nullptr;
    const unsigned long parsedPort = std::strtoul(argv[2], &portEnd, 10);
    if (errno != 0 or portEnd == nullptr or *portEnd != '\0' or parsedPort == 0 or parsedPort > 65535UL) {
        throw std::invalid_argument("Error: invalid port");
    }

    // file path
    const std::string outputPath = argv[3];

    // file size
    char* sizeEnd = nullptr;
    const unsigned long parsedSize = std::strtoul(argv[4], &sizeEnd, 10);
    if (errno != 0 or sizeEnd == nullptr or *sizeEnd != '\0' or parsedSize == 0 or
        parsedSize > static_cast<unsigned long>(std::numeric_limits<std::uint32_t>::max())) {
        throw std::invalid_argument("Error: invalid file size");
    }

    return {
        parsedAddress.s_addr,
        static_cast<std::uint16_t>(parsedPort),
        outputPath,
        static_cast<std::uint32_t>(parsedSize)
    };

}


int main(int argc, char* argv[]) {
    auto [serverIp, port, filePath, fileSize] = parseArguments(argc, argv);

    UdpSocket socket(serverIp, port);
    Receiver receiver(filePath, fileSize);

    while(receiver.writeChunks(), !receiver.isComplete()) {
        const std::vector<Chunk> missingChunks = receiver.getMissingChunks();
        for(const Chunk& chunk : missingChunks) {
            const std::vector<std::uint8_t> request = TransportMessage::buildGetRequest(chunk);
            socket.send(request);
        }

        const auto recvResult = socket.tryRecv();
        if(!recvResult) {
            continue;
        }

        const auto [senderIp, payload] = recvResult.value();
        if(senderIp != serverIp) continue; 

        const auto parseResultOpt = TransportMessage::tryParseDataResponse(payload);
        if(parseResultOpt) {
            auto [chunk, data] = parseResultOpt.value();
            receiver.addReceivedChunk(chunk, std::move(data));
        }
    }
}
