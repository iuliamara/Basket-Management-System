#pragma once
#include <string>
#include <stdexcept>

class EmptyListException : public std::runtime_error {
public:
    explicit EmptyListException(const std::string& msg) : std::runtime_error(msg) {}
};

class ActivitateNotFoundException : public std::runtime_error {
public:
    explicit ActivitateNotFoundException(const std::string& msg) : std::runtime_error(msg) {}
};

class ActivitateAlreadyExistsException : public std::runtime_error {
public:
    explicit ActivitateAlreadyExistsException(const std::string& msg) : std::runtime_error(msg) {}
};

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& msg) : std::runtime_error(msg) {}
};

class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string& msg) : std::runtime_error(msg) {}
};

class UndoException : public std::runtime_error {
public:
    explicit UndoException(const std::string& msg) : std::runtime_error(msg) {}
};