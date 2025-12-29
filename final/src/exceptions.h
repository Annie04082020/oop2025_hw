#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class WeightLimitExceeded : public std::runtime_error {
public:
    explicit WeightLimitExceeded(const std::string& message)
        : std::runtime_error(message) {}
};

class UnsupportedOperationException : public std::logic_error {
public:
    explicit UnsupportedOperationException(const std::string& message)
        : std::logic_error(message) {}
};

#endif // EXCEPTIONS_H
