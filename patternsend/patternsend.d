
import std.stdio;
import std.socket;

import lightcrafter;

void sendPacket(Socket socket, Packet packet) {
    uint packetSize = packet.payloadLength + 7;
    ubyte[] data;
    data.length = packetSize;

    // Create the header
    data[0] = packet.packetType;
    data[1] = packet.command[0];
    data[2] = packet.command[1];
    data[3] = packet.flags;
    data[4] = cast(ubyte)packet.payloadLength;
    data[5] = 0x00;

    // Add the payload
    for (int i = 0; i < packet.payloadLength; i++) {
        data[i + 6] = packet.payload[i];
    }

    // Compute the checksum
    ubyte checksum = 0;
    for (int i = 0; i < packetSize - 1; i++) {
        checksum += data[i];
    }
    data[packetSize - 1] = checksum % 0x100;

    // Send the packet
    socket.send(data);
}

void main() {
    auto address = new InternetAddress("192.168.1.100", 0x5555);
    //auto address = new InternetAddress("127.0.0.1", 5000);
    auto socket = new TcpSocket(address);

    Packet packet;
    packet.packetType = PacketType.WRITE_COMMAND;
    packet.command[0] = 0x01;
    packet.command[1] = 0x06;
    packet.flags = CommandFlag.PAYLOAD_COMPLETE_DATA;

    packet.payloadLength = 4;
    packet.payload ~= 0xff;
    packet.payload ~= 0xff;
    packet.payload ~= 0x00;
    packet.payload ~= 0x00;

    sendPacket(socket, packet);

    socket.close();
}
