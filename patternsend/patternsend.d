import std.stdio;
import std.socket;

import lightcrafter;


class Lightcrafter {
   

    private Socket socket;

    this(Address address = new InternetAddress("192.168.1.100", 0x5555)) {
        this.socket = new TcpSocket(address);
    }

    ~this() {
        socket.close();
    }

    void setSolidColor(ubyte r, ubyte g, ubyte b) {
        Packet packet;
        packet.packetType = PacketType.WRITE_COMMAND;
        packet.command = Command.STATIC_COLOR;
        packet.flags = CommandFlag.PAYLOAD_COMPLETE_DATA;

        packet.payloadLength = 4;
        packet.payload ~= b;
        packet.payload ~= g;
        packet.payload ~= r;
        packet.payload ~= 0x00;

        sendPacket(packet);
    }

    void sendPacket(Packet packet) {
        uint packetSize = packet.payloadLength + 7;
        ubyte[] data;
        data.length = packetSize;

        // Create the header
        data[0] = packet.packetType;
        data[1] = (packet.command & 0xff00) >> 8;
        data[2] = packet.command & 0x00ff;
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
        this.socket.send(data);
    }

}

void main() {
    auto lightcrafter = new Lightcrafter();
    lightcrafter.setSolidColor(0x00, 0xff, 0xff);
}
