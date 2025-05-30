#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <memory>

class Message {
 public:
  virtual ~Message() = default;

  virtual void PrintLayer() const = 0;
  virtual std::string Serialize() const = 0;
};

class TextMessage : public Message {
 public:
  explicit TextMessage(std::string content);
  void PrintLayer() const override;
  std::string Serialize() const override;

 private:
  std::string content_;
};

class ImageMessage : public Message {
 public:
  explicit ImageMessage(std::string imageFileName);
  void PrintLayer() const override;
  std::string Serialize() const override;

 private:
  std::string imageFileName_;
};

class MessageDecorator : public Message {
 public:
  explicit MessageDecorator(std::unique_ptr<Message>&& message);

  void PrintLayer() const final;
  std::string Serialize() const final;

 private:
  virtual void PrintLayerImpl_() const = 0;
  virtual void SerializeImpl_(std::string& buffer) const = 0;

  std::unique_ptr<Message> message_;
};

class EncryptionMessageDecorator : public MessageDecorator {
 public:
  using MessageDecorator::MessageDecorator;

 private:
  void PrintLayerImpl_() const override;
  void SerializeImpl_(std::string& buffer) const override;
};

class CompressionMessageDecorator : public MessageDecorator {
 public:
  using MessageDecorator::MessageDecorator;

 private:
  void PrintLayerImpl_() const override;
  void SerializeImpl_(std::string& buffer) const override;
};

#endif // MESSAGE_HPP
