//
// Created by rohan on 12/14/15.
//

#include "Component.h"
#include <iostream>


Component::Component(std::string referenceID, std::string value) {
    component_mutex_ = new std::mutex;
    std::lock_guard<std::mutex> guard(*component_mutex_);

    referenceID_ = referenceID;
    value_ = value;
}

Component::Component(std::string referenceID, std::string value, std::map<std::string, std::string> fields) {
    component_mutex_ = new std::mutex;
    std::lock_guard<std::mutex> guard(*component_mutex_);

    referenceID_ = referenceID;
    value_ = value;
    fields_ = fields;
}

Component::Component(const Component &other) {
    component_mutex_ = new std::mutex;
    std::lock_guard<std::mutex> this_guard(*component_mutex_);
    std::lock_guard<std::mutex> other_guard(*other.component_mutex_);

    referenceID_ = other.referenceID_;
    value_ = other.value_;
    fields_ = other.fields_;
}

Component &Component::operator=(Component &&other) {
    if (this != &other) {
        //delete the old component mutex, create a new one and lock it
        delete component_mutex_;
        component_mutex_ = new std::mutex;
        std::lock_guard<std::mutex> this_guard(*component_mutex_);

        //lock the mutex of other
        other.component_mutex_->lock();

        //Copy all the data to the new object
        referenceID_ = other.referenceID_;
        value_ = other.value_;
        fields_ = other.fields_;

        //unlock mutex of other
        other.component_mutex_->unlock();

        // get rid of other mutex and set to nullptr
        delete other.component_mutex_;
        other.component_mutex_ = nullptr;
    }
    return *this;
}

Component::~Component() {
    if (component_mutex_ != nullptr) {
        delete component_mutex_;
    }
}

std::string Component::getReferenceID() {
    std::lock_guard<std::mutex> guard(*component_mutex_);
    return referenceID_;
}

std::string Component::getValue() {
    std::lock_guard<std::mutex> guard(*component_mutex_);
    return value_;
}

std::map<std::string, std::string> Component::getFields() {
    std::lock_guard<std::mutex> guard(*component_mutex_);
    return fields_;
}

bool Component::operator==(Component& other) {
    std::lock_guard<std::mutex> this_guard(*component_mutex_);
    std::lock_guard<std::mutex> other_guard(*other.component_mutex_);

    auto a = referenceID_ == other.referenceID_;
    auto b = value_ == other.value_;
    auto c = !_fields_conflict(other.fields_);
    return (a && b && c);
}

void Component::printReferenceID() {
    std::lock_guard<std::mutex> guard(*component_mutex_);
    std::cout << referenceID_ << std::endl;
}

bool Component::fields_conflict(std::map<std::string, std::string>& other_fields) {
    std::lock_guard<std::mutex> guard(*component_mutex_);
    return _fields_conflict(other_fields);
}

bool Component::has_field(std::string field) {
    std::lock_guard<std::mutex> guard(*component_mutex_);
    return _has_field(std::ref(field));
}

bool Component::_fields_conflict(std::map<std::string, std::string>& other_fields) {
    bool conflict = true;

    if (!fields_.empty()) {
        for (auto iter : fields_) {
            auto matching_field = other_fields.find(iter.first);
            if (matching_field != other_fields.end()) {
                if (matching_field->second == iter.second) {
                    conflict = false;
                }
                else {
                    return true;
                }
            }
        }
    }
    else {
        return false;
    }

    return conflict;
}

bool Component::_has_field(std::string field) {
    auto has = fields_.count(field);
    if(has > 0){
        return true;
    }
    else {
        return false;
    }
}
