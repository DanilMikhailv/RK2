#include "message.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <numeric>

TextMessage::TextMessage(std::string content)
    : content_(std::move(content)) {}

void TextMessage::PrintLayer() const {
  std::cout << "Text Message : " << content_ << std::endl;
}

std::string TextMessage::Serialize() const {
  return content_;
}

ImageMessage::ImageMessage(std::string imageFileName)
    : imageFileName_(std::move(imageFileName)) {}

void ImageMessage::PrintLayer() const {
  std::cout << "Image Message : " << imageFileName_ << std::endl;
}

std::string ImageMessage::Serialize() const {
  return "Binary Data Of " + imageFileName_;
}

MessageDecorator::MessageDecorator(std::unique_ptr<Message>&& message)
    : message_(std::move(message)) {}

void MessageDecorator::PrintLayer() const {
  message_->PrintLayer();
  PrintLayerImpl_();
}

std::string MessageDecorator::Serialize() const {
  std::string buffer = message_->Serialize();
  SerializeImpl_(buffer);
  return buffer;
}

void EncryptionMessageDecorator::PrintLayerImpl_() const {
  std::cout << "Encrypt Message" << std::endl;
}

void EncryptionMessageDecorator::SerializeImpl_(std::string& buffer) const {
  std::rotate(buffer.begin(), buffer.begin() + buffer.length() / 2, buffer.end());
}

void CompressionMessageDecorator::PrintLayerImpl_() const {
  std::cout << "Compress Message" << std::endl;
}

void CompressionMessageDecorator::SerializeImpl_(std::string& buffer) const {
  buffer.erase(std::unique(buffer.begin(), buffer.end()), buffer.end());
}
