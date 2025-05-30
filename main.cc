#include <queue>
#include <memory>
#include <iostream>
#include "message.hpp"

int main() {
    std::queue<std::unique_ptr<Message>> messageQueue;

    messageQueue.push(
        std::make_unique<EncryptionMessageDecorator>(
            std::make_unique<CompressionMessageDecorator>(
                std::make_unique<TextMessage>("Helloooooo, I'm taeguk. Feel so gooooooood!"))));

    messageQueue.push(
        std::make_unique<EncryptionMessageDecorator>(
            std::make_unique<ImageMessage>("This-is-image-file-name.PNG")));

    while (!messageQueue.empty()) {
        auto message = std::move(messageQueue.front()); messageQueue.pop();

        std::cout << "---------------------------------------" << std::endl;
        message->PrintLayer();
        std::cout << "Serialized Data : " << message->Serialize() << '\n' << std::endl;
    }

    return 0;
}
