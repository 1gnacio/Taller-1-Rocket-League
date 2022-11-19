#include "room_responses.h"
#include "../serializer/serializer.h"

RoomResponses::RoomResponses(std::vector<unsigned char> &serialized) : rooms() {
    int count = 0;
    int begin = 0;
    int end = 0;
    Serializer serializer;

    serializer.parse(count, serialized, begin, end);

    for (int i = 0; i < count; i++) {
        int size = 0;
        serializer.parse(size, serialized, begin, end);
        std::vector<unsigned char> room(serialized.begin() + end + 1,
                                        serialized.begin() + end + size + 1);

        this->rooms.emplace_back(room);

        begin += size;
        end += size;
    }
}

std::vector<unsigned char> RoomResponses::serialize() {
    Serializer serializer;
    std::vector<unsigned char> serialized;
    std::vector<unsigned char> result;

    int count = this->rooms.size();
    serializer.merge(serialized, serializer.serializeInt(count));

    for (auto& room : this->rooms) {
        serializer.merge(serialized, room.serialize());
    }

    serializer.merge(result, serializer.serializeInt(serialized.size()));
    serializer.merge(result, serialized);

    return result;
}

RoomResponses::RoomResponses() : rooms() {}

void RoomResponses::addRoom(RoomResponse &room) {
    this->rooms.push_back(room);
}
