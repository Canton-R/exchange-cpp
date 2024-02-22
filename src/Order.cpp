//
// Created by Riccardo on 17/02/2024.
//

#include "Order.h"

Order::Order(std::string idNumber, bool orderType, int shares, int limit, int entryTime, int eventTime,
             Order *nextOrder, Order *prevOrder,
             Limit *parentLimit) : idNumber(idNumber), orderType(orderType), shares(shares), limit(limit),
                                   entryTime(entryTime),
                                   eventTime(eventTime), nextOrder(nextOrder), prevOrder(prevOrder),
                                   parentLimit(parentLimit) {}

Order::Order() : idNumber("0"), orderType(true), shares(0), limit(0), entryTime(0),
                 eventTime(0), nextOrder(nullptr), prevOrder(nullptr),
                 parentLimit(nullptr) {}

Order::Order(bool orderType, int shares, int limit, int entryTime, int eventTime, Limit *parentLimit) {

    auto nextOrder = parentLimit->getTailOrder();
    if (nextOrder == nullptr) {
        parentLimit->setTailOrder(this);
        parentLimit->setHeadOrder(this);
        this->nextOrder = this;
        this->prevOrder = this;
    } else {
        this->prevOrder = nextOrder;
        this->nextOrder = nullptr;
        parentLimit->setTailOrder(this);
    }
    this->orderType = orderType;
    this->shares = shares;
    this->limit = limit;
    this->entryTime = entryTime;
    this->eventTime = eventTime;
}

const std::string Order::generateUuid() {
    boost::uuids::random_generator generator;
    boost::uuids::uuid uuid = generator();
    return boost::uuids::to_string(uuid);
};



